#pragma once
namespace Gengine {
	class FrameRateLimiter
	{
		
	private:
		float _maxFps;
		float _fps;
		float _frameTime;
		unsigned int _startTicks;
		void calculateFPS();
		

	public:
		FrameRateLimiter();
		~FrameRateLimiter();		
		void init(float maxFps);
		void begin();
		void setMaxFPS(float targtFps);
		float end();
	};
}

