/// @ref gtx_projection
/// @file glm/gtx/projection.inl

namespace glm
{
	template <typename vecType>
	GLM_FUNC_QUALIFIER vecType proj(vecType const & x, vecType const & Normal)
	{
		return glm::dot(x, Normal) / glm::dot(Normal, Normal) * Normal;
	}
}//namespace glm
// CG_REVISION ffdba33bdd397b1f22d668dac0736e242994752f
