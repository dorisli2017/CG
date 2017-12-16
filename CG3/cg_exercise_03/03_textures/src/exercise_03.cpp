#include <cglib/rt/intersection.h>
#include <cglib/rt/object.h>
#include <cglib/rt/ray.h>
#include <cglib/rt/raytracing_context.h>
#include <cglib/rt/render_data.h>
#include <cglib/rt/renderer.h>
#include <cglib/rt/texture.h>
#include <cglib/rt/texture_mapping.h>
#include <cglib/core/thread_local_data.h>

#include <cglib/core/image.h>
#include <cglib/core/glmstream.h>
#include <cglib/core/assert.h>

#include <algorithm>

// -----------------------------------------------------------------------------

/*
 * Evaluates a texture for the given uv-coordinate without filtering.
 *
 * This method transformes the uv-coordinate into a st-coordinate and
 * rounds down to integer pixel values.
 *
 * The parameter level in [0, mip_levels.size()-1] is the miplevel of
 * the texture that is to be evaluated.
 */
glm::vec4 ImageTexture::
evaluate_nearest(int level, glm::vec2 const& uv) const
{
	cg_assert(level >= 0 && level < static_cast<int>(mip_levels.size()));
	cg_assert(mip_levels[level]);

	// TODO: compute the st-coordinates for the given uv-coordinates and mipmap level
	int W = mip_levels.at(level)->getWidth();
	int H = mip_levels.at(level)->getHeight();
	cg_assert(W > 0);
	cg_assert(H > 0);
	int s = (int)(floor(uv.x*(float)W));
	int t = (int)(floor(uv.y*(float)H));
	// get the value of pixel (s, t) of miplevel level
	return get_texel(level, s, t);
}

// -----------------------------------------------------------------------------

/*
 * Implement clamping here.
 *
 * The input "val" may be arbitrary, including negative and very large positive values.
 * The method shall always return a value in [0, size).
 * Out-of-bounds inputs must be clamped to the nearest boundary.
 */
int ImageTexture::
wrap_clamp(int val, int size)
{
	cg_assert(size > 0);
	if(val < 0) return 0;
    if (val > size-1) return size-1;
	return val;
}

/*
 * Implement repeating here.
 *
 * The input "val" may be arbitrary, including negative and very large positive values.
 * The method shall always return a value in [0, size).
 * Out-of-bounds inputs must be mapped back into [0, size) so that
 * the texture repeats infinitely.
 */
int ImageTexture::
wrap_repeat(int val, int size)
{
	cg_assert(size > 0);
	int diff = val%size;
	if (diff < 0){
		return diff+size;
	}
	else return diff;

	return 0;
}

// -----------------------------------------------------------------------------


/*
 * Implement bilinear filtering here.
 *
 * Use mip_levels[level] as the image to filter.
 * The input uv coordinates may be arbitrary, including values outside [0, 1).
 *
 * Callers of this method must guarantee that level is valid, and
 * that mip_levels[level] is properly initialized. Compare the assertions.
 *
 * The color of a texel is to be interpreted as the color at the texel center.
 */
glm::vec4 ImageTexture::
evaluate_bilinear(int level, glm::vec2 const& uv) const
{
	cg_assert(level >= 0 && level < static_cast<int>(mip_levels.size()));
	cg_assert(mip_levels[level]);
	float s = uv.s*mip_levels.at(level)->getWidth();
	float t = uv.t*mip_levels.at(level)->getHeight();
	int s0 = (int)(floor(s));
	int t0 = (int)(floor(t));
	float s_middle = s0+0.5;
	float t_middle = t0+0.5;
	float a = s-s_middle;
	float b = t-t_middle;
	int s1, t1;
	if (a > 0) s1 = s0+1;
	else s1 = s0-1;
	if (b > 0) t1 = t0+1;
	else t1 = t0-1;
	glm::vec4 t_1 =get_texel(level, s0, t0);
	glm::vec4 t_2 =get_texel(level, s1, t0);
	glm::vec4 t_3 =get_texel(level, s0, t1);
	glm::vec4 t_4 =get_texel(level, s1, t1);
	a = std::abs(a);
	b = std::abs(b);
	return (1-a)*(1-b)*t_1 + a*(1-b)*t_2 +(1-a)*b*t_3+a*b*t_4;
}
// -----------------------------------------------------------------------------

/*
 * This method creates a mipmap hierarchy for
 * the texture.
 *
 * This is done by iteratively reducing the
 * dimenison of a mipmap level and averaging
 * pixel values until the size of a mipmap
 * level is [1, 1].
 *
 * The original data of the texture is stored
 * in mip_levels[0].
 *
 * You can allocale memory for a new mipmap level
 * with dimensions (size_x, size_y) using
 *		mip_levels.emplace_back(new Image(size_x, size_y));
 */
void ImageTexture::
create_mipmap()
{
	/* this are the dimensions of the original texture/image */
	int size_x = mip_levels[0]->getWidth();
	int size_y = mip_levels[0]->getHeight();

	cg_assert("must be power of two" && !(size_x & (size_x - 1)));
	cg_assert("must be power of two" && !(size_y & (size_y - 1)));
	int level = 0;
	int group_x,group_y,x_left,y_below;
	while(size_x >1 || size_y > 1){
		group_x = ceil((float)size_x/2.f);
		group_y = ceil((float)size_y/2.f);
		mip_levels.emplace_back(new Image(group_x, group_y));
		for(int g_x = 0; g_x < group_x;g_x++){
			for(int g_y = 0; g_y < group_y;g_y++){
				x_left = g_x *2;
				y_below =g_y *2;
				std::vector<glm::vec4> candidates;
				int p_x,p_y;
				for(int i = 0; i < 2;i++){
					    p_x = x_left+i;
						if (p_x >= size_x) break;
					for(int j = 0; j < 2; j++){
						p_y = y_below+j;
						if (p_y >= size_y) break;
						candidates.push_back(get_texel(level,  p_x, p_y));
					}
				}
				glm::vec4 p_aver = glm::vec4(0.f);
			    for(size_t i = 0; i < candidates.size(); i++){
			    	p_aver += candidates[i];
			    }
				cg_assert((int)candidates.size() == 2 or (int)candidates.size() == 4);
				set_texel(level+1, g_x, g_y, p_aver/(float)candidates.size());
			}
		}
		level++;
		size_x = mip_levels[level]->getWidth();
		size_y = mip_levels[level]->getHeight();
	}
}
/*
 * Compute the dimensions of the pixel footprint's AABB in uv-space.
 *
 * First intersect the four rays through the pixel corners with
 * the tangent plane at the given intersection.
 *
 * Then the given code computes uv-coordinates for these
 * intersection points.
 *
 * Finally use the uv-coordinates and compute the AABB in
 * uv-space.
 *
 * Return width (du) and height (dv) of the AABB.
 *
 */

glm::vec2 Object::
compute_uv_aabb_size(const Ray rays[4], Intersection const& isect)
{
	// TODO: compute intersection positions
	glm::vec3 intersection_positions[4] = {
		isect.position, isect.position, isect.position, isect.position
	};

	for (int i = 0; i < 4; ++i) {
		// todo: compute intersection positions using a ray->plane
		// intersection
		float t;
	    bool inter =intersect_plane(rays[i].origin,rays[i].direction,isect.position,isect.normal,&t);
		if(inter) intersection_positions[i] = rays[i].origin + t* rays[i].direction;

	}

	// compute uv coordinates from intersection positions
	glm::vec2 intersection_uvs[4];
	get_intersection_uvs(intersection_positions, isect, intersection_uvs);

	// TODO: compute dudv = length of sides of AABB in uv space
	//return glm::vec2(0.0);
	float max =-std::numeric_limits<float>::max();
	float min = std::numeric_limits<float>::max();
	float max_x = max;float max_y= max; float min_x = min; float min_y = min;
	for(int i =0; i < 4; i++){
		if(intersection_uvs[i].x > max_x) max_x = intersection_uvs[i].x;
		if(intersection_uvs[i].y > max_y) max_y = intersection_uvs[i].y;
		if(intersection_uvs[i].x < min_x) min_x = intersection_uvs[i].x;
		if(intersection_uvs[i].y < min_y) min_y = intersection_uvs[i].y;
	}
	return glm::vec2(max_x-min_x, max_y-min_y);
}

/*
 * Implement trilinear filtering at a given uv-position.
 *
 * Transform the AABB dimensions dudv in st-space and
 * take the maximal coordinate as the 1D footprint size T.
 *
 * Determine mipmap levels i and i+1 such that
 *		texel_size(i) <= T <= texel_size(i+1)
 *
 *	Hint: use std::log2(T) for that.
 *
 *	Perform bilinear filtering in both mipmap levels and
 *	linearly interpolate the resulting values.
 *
 */
glm::vec4 ImageTexture::
evaluate_trilinear(glm::vec2 const& uv, glm::vec2 const& dudv) const
{
	int W = mip_levels.at(0)->getWidth();
	int H = mip_levels.at(0)->getHeight();
	cg_assert(W > 0);
	cg_assert(H > 0);
	float s = dudv.x*(float)W;
	float t = dudv.y*(float)H;
	float S = std::max(s,t);
	float T = std::log2(S);
	int stufe_1 = floor(T);
	int stufe_2 = ceil(T);
	if(stufe_1 < 0 )stufe_1 = 0;
	if(stufe_2 < 0)stufe_2 = 0;
	if(stufe_1 >= static_cast<int>(mip_levels.size()))stufe_1 = static_cast<int>(mip_levels.size())-1;
	if(stufe_2 >= static_cast<int>(mip_levels.size()))stufe_2 = static_cast<int>(mip_levels.size())-1;
	float Weight = T-(float)floor(T);
	return (1-Weight) *evaluate_bilinear(stufe_1, uv) +	Weight*evaluate_bilinear(stufe_2, uv);
	return glm::vec4(0.f);
}
// -----------------------------------------------------------------------------

/*
 * Transform the given direction d using the matrix transform.
 *
 * The output direction must be normalized, even if d is not.
 */
glm::vec3 transform_direction(glm::mat4 const& transform, glm::vec3 const& d)
{
	glm::vec4 result = transform*glm::vec4 (d,0.f);
	return glm::normalize(glm::vec3 (result[0],result[1],result[2]));
	  //return d;
}

/*
 * Transform the given position p using the matrix transform.
 */
glm::vec3 transform_position(glm::mat4 const& transform, glm::vec3 const& p)
{
	glm::vec4 result =(transform *glm::vec4 (p,1.f));
	return glm::vec3(result[0], result[1],result[2]);
}

/*
 * Intersect with the ray, but do so in object space.
 *
 * First, transform ray into object space. Use the methods you have
 * implemented for this.
 * Then, intersect the object with the transformed ray.
 * Finally, make sure you transform the intersection back into world space.
 *
 * isect is guaranteed to be a valid pointer.
 * The method shall return true if an intersection was found and false otherwise.
 *
 * isect must be filled properly if an intersection was found.
 */
bool Object::
intersect(Ray const& ray, Intersection* isect) const
{
	cg_assert(isect);
	bool result = false;
	if (RaytracingContext::get_active()->params.transform_objects) {
		// TODO: transform ray, intersect object, transform intersection
		// information back
		Ray oRay = transform_ray(ray,Object::transform_world_to_object);
		result =  geo->intersect(oRay, isect);
		if (result) {
			*isect = transform_intersection(*isect,
					Object::transform_object_to_world,
					Object::transform_object_to_world_normal);
			isect->t = glm::length((isect->position-ray.origin));
		}
		return result;
	}
	return geo->intersect(ray, isect);
}
/*
 * Transform a direction from tangent space to object space.
 *
 * Tangent space is a right-handed coordinate system where
 * the tangent is your thumb, the normal is the index finger, and
 * the bitangent is the middle finger.
 *
 * normal, tangent, and bitangent are given in object space.
 * Build a matrix that rotates d from tangent space into object space.
 * Then, transform d with this matrix to obtain the result.
 *
 * You may assume that normal, tangent, and bitangent are normalized
 * to length 1.
 *
 * The output vector must be normalized to length 1, even if d is not.
 */
glm::vec3 transform_direction_to_object_space(
	glm::vec3 const& d,
	glm::vec3 const& normal,
	glm::vec3 const& tangent,
	glm::vec3 const& bitangent)
{
	cg_assert(std::fabs(glm::length(normal)    - 1.0f) < 1e-4f);
	cg_assert(std::fabs(glm::length(tangent)   - 1.0f) < 1e-4f);
	cg_assert(std::fabs(glm::length(bitangent) - 1.0f) < 1e-4f);
	glm::mat3 Mt2o(tangent,normal,bitangent);
	return glm::normalize(Mt2o*d);
	return d;
}

// -----------------------------------------------------------------------------
// CG_REVISION ffdba33bdd397b1f22d668dac0736e242994752f
