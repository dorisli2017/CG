/// @ref gtx_perpendicular
/// @file glm/gtx/perpendicular.inl

namespace glm
{
	template <typename vecType> 
	GLM_FUNC_QUALIFIER vecType perp
	(
		vecType const & x, 
		vecType const & Normal
	)
	{
		return x - proj(x, Normal);
	}
}//namespace glm
// CG_REVISION b30b521c442c9eeb92ce1af7012b38130e53efcd
