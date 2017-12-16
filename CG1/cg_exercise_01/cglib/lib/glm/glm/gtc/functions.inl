/// @ref gtc_functions
/// @file glm/gtc/functions.inl

#include "../detail/func_exponential.hpp"

namespace glm
{
	template <typename T>
	GLM_FUNC_QUALIFIER T gauss
	(
		T x,
		T ExpectedValue,
		T StandardDeviation
	)
	{
		return exp(-((x - ExpectedValue) * (x - ExpectedValue)) / (static_cast<T>(2) * StandardDeviation * StandardDeviation)) / (StandardDeviation * sqrt(static_cast<T>(6.28318530717958647692528676655900576)));
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER T gauss
	(
		tvec2<T, P> const& Coord,
		tvec2<T, P> const& ExpectedValue,
		tvec2<T, P> const& StandardDeviation
	)
	{
		tvec2<T, P> const Squared = ((Coord - ExpectedValue) * (Coord - ExpectedValue)) / (static_cast<T>(2) * StandardDeviation * StandardDeviation);
		return exp(-(Squared.x + Squared.y));
	}
}//namespace glm

// CG_REVISION 1d384085f04ade0a730db0ed88bbd9f2df80dad9
