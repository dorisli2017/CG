#include <cglib/rt/bvh.h>

#include <cglib/rt/triangle_soup.h>

#include <cglib/core/image.h>
#include <complex>

/*
 * Create a 1 dimensional normalized gauss kernel
 *
 * Parameters:
 *  - sigma:       the parameter of the gaussian
 *  - kernel_size: the size of the kernel (has to be odd)
 *  - kernel:      an array with size kernel_size elements that
 *                 has to be filled with the kernel values
 *
 */
void Image::create_gaussian_kernel_1d(
		float sigma,
		int kernel_size,
		float* kernel) 
{
	cg_assert(kernel_size%2==1);

	// TODO: calculate filter values as described on the exercise sheet. 
	// Make sure your kernel is normalized
	float com1 = 1.f/(sqrt(2.f*M_PI)*sigma);
	float com2 = -1.f/(2.f*sigma*sigma);
	float sum = 0.f;
	int radius = kernel_size/2;
	for (int i = 0; i < kernel_size; ++i) {
		kernel[i] = com1*exp((float)(i-radius)*(i-radius)*com2);
		sum+= kernel[i];
	}
	float com3 = 1.f/sum;
	for (int i = 0; i < kernel_size; ++i) {
		kernel[i] = kernel[i]*com3;
	}
}

/*
 * Create a 2 dimensional quadratic and normalized gauss kernel
 *
 * Parameters:
 *  - sigma:       the parameter of the gaussian
 *  - kernel_size: the size of the kernel (has to be odd)
 *  - kernel:      an array with kernel_size*kernel_size elements that
 *                 has to be filled with the kernel values
 */
void Image::create_gaussian_kernel_2d(
		float sigma,
		int kernel_size,
		float* kernel) 
{
	cg_assert(kernel_size%2==1);

	// TODO: calculate filter values as described on the exercise sheet. 
	// Make sure your kernel is normalized
	float com1 = 1.f/(2.f*M_PI*sigma*sigma);
	float com2 = -1.f/(2.f*sigma*sigma);
	float sum = 0.f;
	int radius = kernel_size/2;
	for (int j = 0; j < kernel_size; ++j) {
		for (int i = 0; i < kernel_size; ++i) {
			int current = i+j*kernel_size;
			kernel[current] = com1*exp((float)((i-radius)*(i-radius)+(j-radius)*(j-radius))*com2);
			sum+=  kernel[current];
		}
	}
	float com3 = 1.f/sum;
	for (int j = 0; j < kernel_size; ++j) {
		for (int i = 0; i < kernel_size; ++i) {
			kernel[i+j*kernel_size] = kernel[i+j*kernel_size]*com3;
		}
	}
}

/*
 * Convolve an image with a 2d filter kernel
 *
 * Parameters:
 *  - kernel_size: the size of the 2d-kernel
 *  - kernel:      the 2d-kernel with kernel_size*kernel_size elements
 *  - wrap_mode:   needs to be known to handle repeating 
 *                 textures correctly
 */
void Image::filter(Image *target, int kernel_size, float* kernel, WrapMode wrap_mode) const
{
	cg_assert (kernel_size%2==1 && "kernel size should be odd.");
	cg_assert (kernel_size > 0 && "kernel size should be greater than 0.");
	cg_assert (target);
	cg_assert (target->getWidth() == m_width && target->getHeight() == m_height);
	int radius = kernel_size/2;
	glm::vec4 targetValue = glm::vec4(0.f);
	int kernel_index = 0;
	int k1,q1;
	glm::vec4 pixel_value;
	//get the value of each target pixel
	for(int i =0; i < m_width; i++){
		for(int j = 0; j < m_height; j++){
			targetValue = glm::vec4(0.f);
			kernel_index = 0;
			//traverse the values in corresponding original pixels
			for(int k = i-radius; k <= i+radius; k++){
				for(int q = j-radius; q <= j+radius; q++){
					if (k >= 0 && q >= 0&&k <m_width&& q <m_height){
						pixel_value = getPixel(k,q);
					}
					else{
						k1 = k;q1 =q;
						switch(wrap_mode){//ZERO
							case 0:{
								pixel_value = glm::vec4(0.f);break;
							}
							case 1 :{//CLAMP
								if (k1 < 0) k1 =0;
								if(q1 < 0) q1 = 0;
								if (k1 >= m_width) k1 =m_width-1;
								if(q1 >= m_height) q1 = m_height-1;
								pixel_value = getPixel(k1,q1);break;
							}
							case 2 :{//REPEAT
								while (k1 < 0) k1 =k1+m_width;
								while(q1 < 0) q1 = q1+m_height;
								if (k1 >= m_width) k1 =k1%m_width;
								if(q1 >= m_height) q1 = q1%m_height;
								pixel_value = getPixel(k1,q1);break;
							}}}
					targetValue+= pixel_value*kernel[kernel_index];
					kernel_index++;
				}
			}
			target->setPixel(i,j,targetValue);
			}}

}

/*
 * Convolve an image with a separable 1d filter kernel
 *
 * Parameters:
 *  - kernel_size: the size of the 1d kernel
 *  - kernel:      the 1d-kernel with kernel_size elements
 *  - wrap_mode:   needs to be known to handle repeating 
 *                 textures correctly
 */
void Image::filter_separable(Image *target, int kernel_size, float* kernel, WrapMode wrap_mode) const
{
	cg_assert (kernel_size%2==1 && "kernel size should be odd.");
	cg_assert (kernel_size > 0 && "kernel size should be greater than 0.");
	cg_assert (target);
	cg_assert (target->getWidth() == m_width && target->getHeight() == m_height);
	// TODO: realize the 2d convolution with two
	// convolutions of the image with a 1d-kernel.
	// convolve the image horizontally and then convolve
	// the result vertically (or vise-versa).
	//
	// use the methods getPixel(x, y, wrap_mode) and
	// setPixel(x, y, value) to get and set pixels of an image
	std::vector<std::vector<glm::vec4>> target_horizontal(m_width, std::vector<glm::vec4>(m_height, glm::vec4(0.f)));
	int radius = kernel_size/2;
	glm::vec4 targetValue = glm::vec4(0.f);
	int kernel_index = 0;
	int k1,q1;
	glm::vec4 pixel_value;
	//do the horizontal convolution.
	for(int i =0; i < m_width; i++){
		for(int j = 0; j < m_height; j++){
			targetValue = glm::vec4(0.f);
			kernel_index = 0;
			//traverse the values in corresponding original pixels
			for(int k = i-radius; k <= i+radius; k++){
					if (k >= 0 && k <m_width){
						pixel_value = getPixel(k,j);
					}
					else{
						k1 = k;
						switch(wrap_mode){//ZERO
							case 1 :{//CLAMP
								if (k1 < 0) k1 =0;
								if (k1 >= m_width) k1 =m_width-1;
								pixel_value = getPixel(k1,j);break;
							}
							case 2 :{//REPEAT
								while (k1 < 0) k1 =k1+m_width;
								if (k1 >= m_width) k1 =k1%m_width;
								pixel_value = getPixel(k1,j);break;
							}
							default:{
								pixel_value = glm::vec4(0.f);break;
							}}}
					targetValue+= pixel_value*kernel[kernel_index];
					kernel_index++;
				}
			target_horizontal[i][j]=targetValue;
		}
	}
	//do the vertical convolution.
	for(int i =0; i < m_width; i++){
		for(int j = 0; j < m_height; j++){
			targetValue = glm::vec4(0.f);
			kernel_index = 0;
			//traverse the values in corresponding original pixels
			for(int q = j-radius; q <= j+radius; q++){
					if (q >= 0 && q <m_height){
						pixel_value = target_horizontal[i][q];
					}
					else{
						q1 = q;
						switch(wrap_mode){//ZERO
							case 0:{
								pixel_value = glm::vec4(0.f);break;
							}
							case 1 :{//CLAMP
								if (q1 < 0) q1 =0;
								if (q1 >= m_height) q1 =m_height-1;
								pixel_value = target_horizontal[i][q1];break;
							}
							case 2 :{//REPEAT
								while (q1 < 0) q1 =q1+m_width;
								if (q1 >= m_height) q1 =q1%m_height;
								pixel_value = target_horizontal[i][q1];break;
							}}}
					targetValue+= pixel_value*kernel[kernel_index];
					kernel_index++;
				}
			target->setPixel(i,j,targetValue);
		}
	}
}
bool comp(std::pair<int,float> np1,std::pair<int,float> np2){
	return np1.second<np2.second;
}
float aabbCenter(float a,float b,float c){
	return (std::min(std::min(a,b),c)+std::max(std::max(a,b),c))/2.f;
}
/**
 * Reorder triangle indices in the vector triangle_indices 
 * in the range [first_triangle_idx, first_triangle_idx+num_triangles-1] 
 * so that the range is split in two sets where all triangles in the first set
 * are "less than equal" than the median, and all triangles in the second set
 * are "greater than equal" the median.
 *
 * Ordering ("less than") is defined by the ordering of triangle
 * bounding box centers along the given axis.
 *
 * Triangle indices within a set need not be sorted.
 *
 * The resulting sets must have an equal number of elements if num_triangles
 * is even. Otherwise, one of the sets must have one more element.
 *
 * For example, 8 triangles must be split 4-4. 7 Triangles must be split
 * 4-3 or 3-4.
 *
 * Parameters:
 *  - first_triangle_idx: The index of the first triangle in the given range.
 *  - num_triangles:      The number of triangles in the range.
 *  - axis:               The sort axis. 0 is X, 1 is Y, 2 is Z.
 *
 * Return value:
 *  - The number of triangles in the first set.
 */
int BVH::reorder_triangles_median(
	int first_triangle_idx, 
	int num_triangles, 
	int axis)
{
	cg_assert(first_triangle_idx < static_cast<int>(triangle_indices.size()));
	cg_assert(first_triangle_idx >= 0);
	cg_assert(num_triangles <= static_cast<int>(triangle_indices.size() - first_triangle_idx));
	cg_assert(num_triangles > 1);
	cg_assert(axis >= 0);
	cg_assert(axis < 3);
	// TODO: Implement reordering.
	std::vector<std::pair<int,float>> v;
	for(int i = first_triangle_idx; i < first_triangle_idx+num_triangles; i++){
		int index = triangle_indices[i];
		float center = aabbCenter(triangle_soup.vertices[3*index][axis],
				triangle_soup.vertices[3*index+1][axis],triangle_soup.vertices[3*index+2][axis]);
		std::pair<int,float> np = std::pair<int,float>(index,center);
		v.push_back(np);
	}
	std::nth_element(v.begin(), v.begin() + (v.size())/2, v.end(),comp);
	for(int i = 0; i < num_triangles; i++){
		triangle_indices[first_triangle_idx+i] = v[i].first;
	}
	return (num_triangles)/2;
}

/*
 * Build a BVH recursively using the object median split heuristic.
 *
 * This method must first fully initialize the current node, and then
 * potentially split it. 
 *
 * A node must not be split if it contains MAX_TRIANGLES_IN_LEAF triangles or
 * less. No leaf node may be empty. All nodes must have either two or no
 * children.
 *
 * Use reorder_triangles_median to perform the split in triangle_indices.
 * Split along X for depth 0. Then, proceed in the order Y, Z, X, Y, Z, X, Y, ..
 *
 * Parameters:
 *  - node_idx:           The index of the node to be split.
 *  - first_triangle_idx: An index into the array triangle_indices. It points 
 *                        to the first triangle contained in the current node.
 *  - num_triangles:      The number of triangles contained in the current node.
 */
void BVH::
build_bvh(int node_idx, int first_triangle_idx, int num_triangles, int depth)
{
	cg_assert(num_triangles > 0);
	cg_assert(node_idx >= 0);
	cg_assert(num_triangles <= static_cast<int>(triangle_indices.size() - first_triangle_idx));
	cg_assert(node_idx < static_cast<int>(nodes.size()));
	cg_assert(depth >= 0);
	Node& node = nodes[node_idx];
	// TODO: Implement recursive build.
	node.triangle_idx  = first_triangle_idx;
	node.num_triangles = num_triangles;
	node.left          = -1;
	node.right         = -1;
	//if(node.num_triangles <= triangle_soup.num_triangles){
	if(node.num_triangles <= 1){
		node.left          = -1;
		node.right         = -1;
		for(int i = 0; i < num_triangles; i++){
            node.aabb.extend(triangle_soup.vertices[3*triangle_indices[(node.triangle_idx+i)]]);
            node.aabb.extend(triangle_soup.vertices[3*triangle_indices[(node.triangle_idx+i)]+1]);
            node.aabb.extend(triangle_soup.vertices[3*triangle_indices[(node.triangle_idx+i)]+2]);
		}
	}
	else{
		int split = reorder_triangles_median(first_triangle_idx, num_triangles, depth%3);
		Node left = Node();
		Node right = Node();
		nodes.push_back(left);
		node.left = nodes.size()-1;
		nodes.push_back(right);
		node.right = nodes.size()-1;
		build_bvh(node.left,first_triangle_idx, split, depth+1);
		glm::vec3 kindMin = nodes[node.left].aabb.min;
		glm::vec3 kindMax = nodes[node.left].aabb.max;
        node.aabb.extend(kindMin);
        node.aabb.extend(kindMax);
		build_bvh(node.right, first_triangle_idx+split, node.num_triangles-split, depth+1);
		kindMin = nodes[node.right].aabb.min;
		kindMax = nodes[node.right].aabb.max;
        node.aabb.extend(kindMin);
        node.aabb.extend(kindMax);
	}
}

/*
 * Intersect the BVH recursively, returning the nearest intersection if
 * there is one.
 *
 * Caution: BVH nodes may overlap.
 *
 * Parameters:
 *  - ray:                  The ray to intersect the BVH with.
 *  - idx:                  The node to be intersected.
 *  - nearest_intersection: The distance to the intersection point, if an 
 *                          intersection was found. Must not be changed 
 *                          otherwise.
 *  - isect:                The intersection, if one was found. Must not be 
 *                          changed otherwise.
 *
 * Return value:
 *  true if an intersection was found, false otherwise.
 */
bool BVH::
intersect_recursive(const Ray &ray, int idx, float *nearest_intersection, Intersection* isect) const
{
	cg_assert(nearest_intersection);
	cg_assert(isect);
	cg_assert(idx >= 0);
	cg_assert(idx < static_cast<int>(nodes.size()));

	const Node &n = nodes[idx];

	// This is a leaf node. Intersect all triangles.
	if(n.left < 0) {
		glm::vec3 bary(0.f);
		bool hit = false;
		for(int i = 0; i < n.num_triangles; i++) {
			int x = triangle_indices[n.triangle_idx + i];
			float dist;
			glm::vec3 b;
			if(intersect_triangle(ray.origin, ray.direction,
						triangle_soup.vertices[x * 3 + 0],
						triangle_soup.vertices[x * 3 + 1],
						triangle_soup.vertices[x * 3 + 2],
						b, dist)) {
				hit = true;
				if(dist <= *nearest_intersection) {
					*nearest_intersection = dist;
					bary = b;
					cg_assert(x >= 0);
					if(isect)
						triangle_soup.fill_intersection(isect, x, *nearest_intersection, bary);
				}
			}
		}
		return hit;
	}

	// This is an inner node. Recurse into child nodes.
  else {
    // TODO: Implement recursive traversal here.
	bool hit = false;
    float t_min_left = 0.f;
    float t_max_left = *nearest_intersection;
    float t_min_right = 0.f;
    float t_max_right = *nearest_intersection;
    bool hit_left = nodes[n.left].aabb.intersect(ray, t_min_left, t_max_left);
    bool hit_right = nodes[n.right].aabb.intersect(ray, t_min_right, t_max_right);
	int min_kind= -1;
	int max_kind = -1;
    if (hit_left && hit_right) {
    	if(t_min_left < t_min_right){
    		if(t_min_left < *nearest_intersection) min_kind = n.left;
    		if(t_min_right < *nearest_intersection) max_kind = n.right;
    	}
    	else{
    		if(t_min_left < *nearest_intersection) max_kind = n.left;
    		if(t_min_right < *nearest_intersection) min_kind = n.right;
    	}
    }
    else {
    	if(hit_left){
    		if(t_min_left < *nearest_intersection) min_kind =n.left;
    	}
    	else{
    	    if(hit_right){
    	    	if(t_min_right < *nearest_intersection) min_kind =n.right;
    	    	}
    	    else return false;
    	    }
    }
    if(min_kind !=-1){
    	hit = hit |intersect_recursive(ray, min_kind, nearest_intersection,isect);
     }
     if(max_kind != -1){
    	 hit = hit |intersect_recursive(ray, max_kind, nearest_intersection,isect);
     }
    return hit;
  }
	//return false;
}

// Spectrum and reconstruction are 2D memory blocks of the same size [sx, sy]
// in row major layout, i.e one row of size sx after the other. 
//
// Spectrum contains the complex fourier-coefficients \hat{x}_{kl}.
//
// Reconstruct the original grayscale image using fourier transformation!
void DiscreteFourier2D::reconstruct(
	int M, int N,
	std::complex<float> const* spectrum,
	std::complex<float>	* reconstruction)
{
}
// CG_REVISION b30b521c442c9eeb92ce1af7012b38130e53efcd
