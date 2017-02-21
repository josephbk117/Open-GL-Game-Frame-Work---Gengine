#include "FpsLimiter.h"
#include <SDL/SDL.h>
namespace Bengine
{
	FpsLimiter::FpsLimiter()
	{
		
	}
	void FpsLimiter::init(float targetFps)
	{
		setTargetFPS(targetFps);
	}
	void FpsLimiter::begin()
	{
		_startTicks = SDL_GetTicks();
	}
	void FpsLimiter::setTargetFPS(float targetFps)
	{
		_targetFps = targetFps;
	}
	float FpsLimiter::end()
	{
		return 0;
	}

}