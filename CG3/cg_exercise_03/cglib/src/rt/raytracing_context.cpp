#include <cglib/rt/raytracing_context.h>

RaytracingContext *RaytracingContext::current_context = nullptr;
RaytracingContext *RaytracingContext::old_context = nullptr;

RaytracingContext::
RaytracingContext()
{
	cg_assert(old_context == nullptr);
	old_context = current_context;
	current_context = this;
	params.initialize();
}

RaytracingContext::
~RaytracingContext()
{
	cg_assert_noexcept(current_context);
	current_context = old_context;
	old_context = nullptr;
}

RaytracingContext * RaytracingContext::
get_active()
{
	return current_context;
}
