<<<<<<< HEAD:focusfade.c
#include "animation.h"
=======
#include "animation-internal.h"
>>>>>>> 1d600624bf9a0956375a82cfdd1f99da511af55f:focusfade.c
// =====================  Effect: Focus Fade  =========================


void
fxFocusFadeUpdateWindowAttrib(AnimScreen * as,
							  AnimWindow * aw,
							  WindowPaintAttrib * wAttrib)
{
	float forwardProgress = 0;
	if (aw->animTotalTime - aw->timestep != 0)
		forwardProgress =
			1 - (aw->animRemainingTime - aw->timestep) /
			(aw->animTotalTime - aw->timestep);
	forwardProgress = MIN(forwardProgress, 1);
	forwardProgress = MAX(forwardProgress, 0);

	wAttrib->opacity = (GLushort)
		(aw->storedOpacity *
		 (1 - decelerateProgressCustom(1 - forwardProgress, 0.50, 0.75)));
}

void
fxFocusFadeUpdateWindowAttrib2(AnimScreen * as,
							   AnimWindow * aw,
							   WindowPaintAttrib * wAttrib)
{
	float forwardProgress = 0;
	if (aw->animTotalTime - aw->timestep != 0)
		forwardProgress =
			1 - (aw->animRemainingTime - aw->timestep) /
			(aw->animTotalTime - aw->timestep);
	forwardProgress = MIN(forwardProgress, 1);
	forwardProgress = MAX(forwardProgress, 0);

	wAttrib->opacity = (GLushort)
		(aw->storedOpacity *
		 (1 - decelerateProgressCustom(forwardProgress, 0.50, 0.75)));
}