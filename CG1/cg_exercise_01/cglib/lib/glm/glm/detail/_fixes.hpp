/// @ref core
/// @file glm/detail/_fixes.hpp

#include <cmath>

//! Workaround for compatibility with other libraries
#ifdef max
#undef max
#endif

//! Workaround for compatibility with other libraries
#ifdef min
#undef min
#endif

//! Workaround for Android
#ifdef isnan
#undef isnan
#endif

//! Workaround for Android
#ifdef isinf
#undef isinf
#endif

//! Workaround for Chrone Native Client
#ifdef log2
#undef log2
#endif

// CG_REVISION 1d384085f04ade0a730db0ed88bbd9f2df80dad9
