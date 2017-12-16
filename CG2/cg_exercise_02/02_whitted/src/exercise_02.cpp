#include <cglib/rt/renderer.h>
#include <cglib/rt/intersection_tests.h>
#include <cglib/rt/raytracing_context.h>
#include <cglib/rt/intersection.h>
#include <cglib/rt/ray.h>
#include <cglib/rt/scene.h>
#include <cglib/rt/light.h>
#include <cglib/rt/material.h>
#include <cglib/rt/render_data.h>

/*
 * TODO: implement a ray-sphere intersection test here.
 * The sphere is defined by its center and radius.
 *
 * Return true, if (and only if) the ray intersects the sphere.
 * In this case, also fill the parameter t with the distance such that
 *    ray_origin + t * ray_direction
 * is the intersection point.
 */
bool intersect_sphere(
    glm::vec3 const& ray_origin,    // starting point of the ray
    glm::vec3 const& ray_direction, // direction of the ray
    glm::vec3 const& center,        // position of the sphere
    float radius,                   // radius of the sphere
    float* t)                       // output parameter which contains distance to the hit point
{
    cg_assert(t);
	cg_assert(std::fabs(glm::length(ray_direction) - 1.f) < EPSILON);
	float a = glm::dot (ray_direction,ray_direction);
	glm::vec3 diff = ray_origin -center;
	float b = 2*glm::dot(ray_direction,diff);
	float c = glm::dot(diff,diff)-radius*radius;
    float disk = b*b-4*a*c;
    float t1, t2;
    if (disk <= 0.0) return false;
    if (disk == 0.0){
    	t1= -b/2*a;
    	if(t1 > 0){
    		*t = t1;
    		return true;
    	}
    	else return false;
    }
    if (disk > 0){
    	t1 = (-b-std::sqrt(disk))/2*a;
    	t2 = (-b+ std::sqrt(disk))/2*a;
    	assert(t1<t2);
    	if(t1 > 0){
    		*t = t1;
    		return true;
    	}
    	if(t2 > 0){
    		*t = t2;
    		return true;
    	}
    }
    return false;
}
/*
 * emission characteristic of a spotlight
 */
glm::vec3 SpotLight::getEmission(
		glm::vec3 const& omega // world space direction
		) const
{
	cg_assert(std::fabs(glm::length(omega) - 1.f) < EPSILON);
 
	// TODO: implement a spotlight emitter as specified on the exercise sheet
	 glm::vec3 P = this->power;
	 float alpha = this->falloff;
	 float cosTheta = glm::dot(omega,this->direction);
	 return P*(alpha+2)*std::pow(std::max(0.f,cosTheta),alpha);
	 //return glm::vec3(0.f);
}


glm::vec3 evaluate_phong(
	RenderData &data,			// class containing raytracing information
	MaterialSample const& mat,	// the material at position
	glm::vec3 const& P,			// world space position
	glm::vec3 const& N,			// normal at the position (already normalized)
	glm::vec3 const& V)			// view vector (already normalized)
{
	cg_assert(std::fabs(glm::length(N) - 1.f) < EPSILON);
	cg_assert(std::fabs(glm::length(V) - 1.f) < EPSILON);

	glm::vec3 contribution(0.f);

	// iterate over lights and sum up their contribution
	for (auto& light_uptr : data.context.scene->lights) 
	{
		// TODO: calculate the (normalized) direction to the light
		const Light *light = light_uptr.get();
		glm::vec3 L = glm::normalize(light->getPosition()-P);
		//glm::vec3 L(0.0f, 1.0f, 0.0f);

		float visibility = 1.f;
		if (data.context.params.shadows) {
			// TODO: check if light source is visible
			bool v = visible(data,P,light->getPosition());
			if(v == false) visibility = 0.f;
		}
		glm::vec3 diffuse(0.f);
		if (data.context.params.diffuse) {
			// TODO: compute diffuse component of phong model
			diffuse = mat.k_d;
		}

		glm::vec3 specular(0.f);
		if (data.context.params.specular) {
			// TODO: compute specular component of phong model
            specular = mat.k_s;
		}

		glm::vec3 ambient = data.context.params.ambient ? mat.k_a : glm::vec3(0.0f);

		// TODO: modify this and implement the phong model as specified on the exercise sheet
		float dis_XL = glm::distance(P,light->getPosition());
		contribution += ambient * light->getPower()/(dis_XL*dis_XL);
		float cosTheta = dot(N,L);
		glm::vec3 rL= reflect(L,N);
		float cosPhi = glm::dot(rL,V);
		float o = cosTheta > 0.f ? 1.f:0.f;
		glm::vec3 common = light->getEmission(-L)*visibility*o/(dis_XL*dis_XL);
		contribution += common*diffuse*std::max(0.f,cosTheta);
		contribution += common*specular*std::pow(std::max(0.f,std::max(0.f,cosPhi)),mat.n);

	}

	return contribution;
}
glm::vec3 evaluate_reflection(
	RenderData &data,			// class containing raytracing information
	int depth,					// the current recursion depth
	glm::vec3 const& P,			// world space position
	glm::vec3 const& N,			// normal at the position (already normalized)
	glm::vec3 const& V)			// view vector (already normalized)
{
	// TODO: calculate reflective contribution by constructing and shooting a reflection ray.
	//return glm::vec3(0.f);
	/**********************/
	glm::vec3 R = reflect(V,N);
	glm::vec3 O = P+data.context.params.ray_epsilon *R;
	return trace_recursive(data,Ray(O,R),depth+1);
    /************************/
}

glm::vec3 evaluate_transmission(
	RenderData &data,			// class containing raytracing information
	int depth,					// the current recursion depth
	glm::vec3 const& P,			// world space position
	glm::vec3 const& N,			// normal at the position (already normalized)
	glm::vec3 const& V,			// view vector (already normalized)
	float eta)					// the relative refraction index
{
	// TODO: calculate transmissive contribution by constructing and shooting a transmission ray.
	glm::vec3 contribution(0.f);
	//return contribution;
	/**********************/
	glm::vec3 t;
	bool ref = refract(V,N,eta,&t);
	if(ref == false) return contribution;
	glm::vec3 O = P+data.context.params.ray_epsilon *t;
	return trace_recursive(data,Ray(O,t),depth+1);
    /************************/
}

glm::vec3 handle_transmissive_material_single_ior(
	RenderData &data,			// class containing raytracing information
	int depth,					// the current recursion depth
	glm::vec3 const& P,			// world space position
	glm::vec3 const& N,			// normal at the position (already normalized)
	glm::vec3 const& V,			// view vector (already normalized)
	float eta)					// the relative refraction index
{
	if (data.context.params.fresnel) {
		// TODO: replace with proper fresnel handling.
		float F = fresnel(V, N, eta);
		return (1-F)*evaluate_transmission(data, depth, P, N, V, eta)+F*evaluate_reflection(data, depth, P, N, V);
	}
	else {
		// just regular transmission
		return evaluate_transmission(data, depth, P, N, V, eta);
	}
}

glm::vec3 handle_transmissive_material(
	RenderData &data,					// class containing raytracing information
	int depth,							// the current recursion depth
	glm::vec3 const& P,					// world space position
	glm::vec3 const& N,					// normal at the position (already normalized)
	glm::vec3 const& V,					// view vector (already normalized)
	glm::vec3 const& eta_of_channel)	// relative refraction index of red, green and blue color channel
{
	if (data.context.params.dispersion && !(eta_of_channel[0] == eta_of_channel[1] && eta_of_channel[0] == eta_of_channel[2])) {
		// TODO: split ray into 3 rays (one for each color channel) and implement dispersion here
		glm::vec3 contribution(0.f);
		contribution.r=handle_transmissive_material_single_ior(data, depth, P, N, V, eta_of_channel[0]).r;
		contribution.g=handle_transmissive_material_single_ior(data, depth, P, N, V, eta_of_channel[1]).g;
		contribution.b=handle_transmissive_material_single_ior(data, depth, P, N, V, eta_of_channel[2]).b;
		return contribution;
	}
	else {
		// dont handle transmission, take average refraction index instead.
		const float eta = 1.f/3.f*(eta_of_channel[0]+eta_of_channel[1]+eta_of_channel[2]);
		return handle_transmissive_material_single_ior(data, depth, P, N, V, eta);
	}
	return glm::vec3(0.f);
}
// CG_REVISION 0b499c51037b55f8a55bc2b58f19cac16b11de4c

