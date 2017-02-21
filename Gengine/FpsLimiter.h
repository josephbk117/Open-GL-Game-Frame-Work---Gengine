#pragma once
namespace Bengine
{
	class FpsLimiter
	{
	private:
		float _targetFps;
		unsigned int _startTicks;
	public:
		FpsLimiter();
		void init(float targetFps);
		void begin();
		void setTargetFPS(float targtFps);
		float end(); // return current fps
	};

}