#include <cglib/colors/exercise.h>
#include <cglib/colors/convert.h>
#include <cglib/colors/cmf.h>

#include <cglib/core/glheaders.h>
#include <cglib/core/glmstream.h>

#include <cglib/core/assert.h>
#include <iostream>

/*
 * Draw the given vertices directly as GL_TRIANGLES.
 * For each vertex, also set the corresponding color.
 */
void draw_triangles(
	std::vector<glm::vec3> const& vertices,
	std::vector<glm::vec3> const& colors)
{
	cg_assert(vertices.size() == colors.size());
	cg_assert(vertices.size() % 3 == 0);
	size_t size = vertices.size();
	std::vector<glm::uvec3> idx = {};
	for(size_t i = 2; i < size; i=i+3){
		idx.push_back(glm::uvec3(i-2,i-1,i));
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(
	3, GL_FLOAT, 0,
	vertices.data());
	glColorPointer(
	3, GL_FLOAT, 0,
	colors.data());
	glDrawElements(
	GL_TRIANGLES,
	idx.size() * 3,
	GL_UNSIGNED_INT,
	idx.data());
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}
/*
 * Generate a regular grid of resolution N*N (2*N*N triangles) in the xy-plane (z=0).
 * Store the grid in vertex-index form.
 *
 * The vertices of the triangles should be in counter clock-wise order.
 *
 * The grid must fill exactly the square [0, 1]x[0, 1], and must
 * be generated as an Indexed Face Set (Shared Vertex representation).
 *
 * The first vertex should be at position (0,0,0) and the last
 * vertex at position (1,1,0)
 *
 * An example for N = 3:
 *
 *   ^
 *   |  ----------
 *   |  |\ |\ |\ |
 *   |  | \| \| \|
 *   |  ----------
 *   |  |\ |\ |\ |
 * y |  | \| \| \|
 *   |  ----------
 *   |  |\ |\ |\ |
 *   |  | \| \| \|
 *   |  ----------
 *   |
 *   |-------------->
 *          x
 *
 */
void generate_grid(
	std::uint32_t N,
	std::vector<glm::vec3>* vertices,
	std::vector<glm::uvec3>* indices)
{
	cg_assert(N >= 1);
	cg_assert(vertices);
	cg_assert(indices);
	vertices->clear();
	indices->clear();
	vertices->reserve((N+1)*(N+1));
	indices->reserve(2*N*N);
	//for vertices
    float width = float(1.0/N);
	std::vector<glm::vec3> row;
	row.push_back(glm::vec3(0.0,0.0,0.0));
	for(std::uint32_t i =1; i < N; i++){
        row.push_back(glm::vec3(i*width,0.0,0.0));
	}
	row.push_back(glm::vec3(1.0,0.0,0.0));
	vertices->insert(vertices->end(),row.begin(),row.end());
	for(std::uint32_t j = 1; j < N; j++){
		for(std::uint32_t i =0; i < N+1; i++){
			row[i] = row[i]+glm::vec3(0.0,width,0.0);
		}
		vertices->insert(vertices->end(),row.begin(),row.end());
	}
	vertices->push_back(glm::vec3(0.0,1.0,0.0));
	for(std::uint32_t i =1; i < N; i++){
        vertices->push_back(glm::vec3(i*width,1.0,0.0));
	}
	vertices->push_back(glm::vec3(1.0,1.0,0.0));
	//for indices
	unsigned int p0,p1,p2,p3;
	for(std::uint32_t i = 0; i < N; i++){
		for(std::uint32_t j = 0; j < N; j++){
			p0 = (N+1)*i+j;
			p1 = p0+1;
			p2= p1+N;
            p3 = p2+1;
			indices->push_back(glm::uvec3(p0, p1, p2));
			indices->push_back(glm::uvec3(p2, p1, p3));
		}
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
}
/*
 * Draw the given vertices as indexed GL_TRIANGLES using glDrawElements.
 * For each vertex, also set the corresponding color.
 *
 * Don't forget to enable the correct client states. After drawing
 * the triangles, you need to disable the client states again.
 */
void draw_indexed_triangles(
	std::vector<glm::vec3>  const& vertices,
	std::vector<glm::vec3>  const& colors,
	std::vector<glm::uvec3> const& indices)
{
	cg_assert(vertices.size() == colors.size());
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(
	3, GL_FLOAT, 0,
	vertices.data());
	glColorPointer(
	3, GL_FLOAT, 0,
	colors.data());
	glDrawElements(
	GL_TRIANGLES,
	indices.size() * 3,
	GL_UNSIGNED_INT,
	indices.data());
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

}

/*
 * Generate a triangle strip with N segments (2*N triangles)
 * in the xy plane (z=0).
 *
 * The vertices of the triangles should be in counter clock-wise order.
 *
 * The triangle strip must fill exactly the square [0, 1]x[0, 1].
 *
 * The first vertex should be at position (0,1,0) and the last
 * vertex at position (1,0,0)
 *
 * An example for N = 3:
 *
 *   ^
 *   |  ----------
 *   |  | /| /| /|
 * y |  |/ |/ |/ |
 *   |  ----------
 *   |
 *   |-------------->
 *           x
 *
 */
void generate_strip(
	std::uint32_t N,
	std::vector<glm::vec3>* vertices)
{
	cg_assert(N >= 1);
	cg_assert(vertices);
    float width = float(1.0/N);
	vertices->clear();
    vertices->reserve(2*(N+1));
    vertices->push_back(glm::vec3(0.0,1.0,0.0));
    vertices->push_back(glm::vec3(0.0,0.0,0.0));
    for(std::uint32_t i = 1; i < N; i++){
    	vertices->push_back(glm::vec3(i*width,1.0,0.0));
    	vertices->push_back(glm::vec3(i*width,0.0,0.0));
    }
    vertices->push_back(glm::vec3(1.0,1.0,0.0));
    vertices->push_back(glm::vec3(1.0,0.0,0.0));
}

/*
 * Draw the given vertices as a triangle strip.
 * For each vertex, also set the corresponding color.
 */
void draw_triangle_strip(
	std::vector<glm::vec3> const& vertices,
	std::vector<glm::vec3> const& colors)
{
	cg_assert(vertices.size() == colors.size());
	std::size_t size = vertices.size();
	glBegin(GL_TRIANGLE_STRIP);
	for(size_t i = 0; i < size; i++){
		glColor3f(colors[i][0],colors[i][1],colors[i][2]);
		glVertex3f(vertices[i][0],vertices[i][1],vertices[i][2]);
	}

	glEnd();

}

/*
 * Integrate the given piecewise linear function
 * using trapezoidal integration.
 *
 * The function is given at points
 *     x[0], ..., x[N]
 * and its corresponding values are
 *     y[0], ..., y[N]
 */
float integrate_trapezoidal(
	std::vector<float> const& x,
	std::vector<float> const& y)
{
	cg_assert(x.size() == y.size());
	cg_assert(x.size() > 1);
	float sum = 0.0f;
	size_t size = x.size();
    for(size_t i =0; i < size-1; i++){
    	sum+=(y[i]+y[i+1])*(x[i+1]-x[i])/2;
    }
	return sum;
}

/*
 * Convert the given spectrum to RGB using your
 * implementation of integrate_trapezoidal(...)
 *
 * The color matching functions and the wavelengths
 * for which they are given can be found in
 *     cglib/colors/cmf.h
 * and
 *     cglib/src/colors/cmf.cpp
 *
 * The wavelengths corresponding to the spectral values
 * given in spectrum are defined in cmf::wavelengths
 */

glm::vec3 spectrum_to_rgb(std::vector<float> const& spectrum)
{
	cg_assert(spectrum.size() == cmf::wavelengths.size());
	size_t size = cmf::wavelengths.size();
	float X,Y,Z;
	std::vector<float> valuesX, valuesY, valuesZ;
	valuesX.clear(); valuesY.clear(); valuesZ.clear();
	valuesX.reserve(size);valuesY.reserve(size);valuesZ.reserve(size);

	for(size_t i = 0; i < size; i++){
		valuesX.push_back(cmf::x[i]*spectrum[i]);
		valuesY.push_back(cmf::y[i]*spectrum[i]);
		valuesZ.push_back(cmf::z[i]*spectrum[i]);
	}
	X = integrate_trapezoidal(cmf::wavelengths,valuesX);
	Y = integrate_trapezoidal(cmf::wavelengths,valuesY);
	Z = integrate_trapezoidal(cmf::wavelengths,valuesZ);
	return convert::xyz_to_rgb(glm::vec3(X,Y,Z));
}
// CG_REVISION 1d384085f04ade0a730db0ed88bbd9f2df80dad9
