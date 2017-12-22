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
// CG_REVISION b30b521c442c9eeb92ce1af7012b38130e53efcd
