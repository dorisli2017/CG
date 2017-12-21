/// @ref gtx_optimum_pow
/// @file glm/gtx/optimum_pow.inl

namespace glm
{
	template <typename genType>
	GLM_FUNC_QUALIFIER genType pow2(genType const & x)
	{
		return x * x;
	}

	template <typename genType>
	GLM_FUNC_QUALIFIER genType pow3(genType const & x)
	{
		return x * x * x;
	}

	template <typename genType>
	GLM_FUNC_QUALIFIER genType pow4(genType const & x)
	{
		return (x * x) * (x * x);
	}
}//namespace glm
// CG_REVISION b30b521c442c9eeb92ce1af7012b38130e53efcd
