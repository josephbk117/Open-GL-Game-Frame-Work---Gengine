#include "FrameRateLimiter.h"
#include <SDL/SDL.h>
namespace Gengine {


	FrameRateLimiter::FrameRateLimiter()
	{
	}


	FrameRateLimiter::~FrameRateLimiter()
	{
	}

	void FrameRateLimiter::init(float maxFPS) 
	{
		setMaxFPS(maxFPS);
	}
	void FrameRateLimiter::begin()
	{
		_startTicks = SDL_GetTicks();
	}
	void FrameRateLimiter::setMaxFPS(float maxFps)
	{
		_maxFps = maxFps;
	}
	float FrameRateLimiter::end() 
	{
		calculateFPS();
		float frameTicks = SDL_GetTicks() - _startTicks;
		if (1000.0 / _maxFps > frameTicks)
		{
			SDL_Delay((Uint32)(1000.0 / _maxFps - frameTicks));
		}
		return _fps;
	}
	void FrameRateLimiter::calculateFPS()
	{
		static const int NUM_SAMPLES = 10;
		static float frameTimes[NUM_SAMPLES];
		static int currentFrame = 0;

		static float prevTicks = SDL_GetTicks(); //Only sets in the first frame
		static float currentTicks;

		currentTicks = SDL_GetTicks(); //Changed every frame
		_frameTime = currentTicks - prevTicks;
		frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

		prevTicks = currentTicks;

		int count;
		if (currentFrame < NUM_SAMPLES)
		{
			count = currentFrame;
		}
		else
		{
			count = NUM_SAMPLES;
			float frameTimeAvg = 0;
			for (int i = 0; i < count; i++)
			{
				frameTimeAvg += frameTimes[i];
			}
			frameTimeAvg /= count;
			if (frameTimeAvg > 0)
			{
				_fps = 1000.0f / frameTimeAvg;
			}
			else
			{
				_fps = 60.0;
			}
		}
		currentFrame++;
	}
}