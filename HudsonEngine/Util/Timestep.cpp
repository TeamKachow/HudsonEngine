#include "Timestep.h"

Hudson::Util::Timestep::Timestep()
{
	_lastTime = glfwGetTime();
	_timer = _lastTime;
	_accumulator = 0;
	_nowTime = 0;
	_frames = 0;
	_updates = 0;
	DeltaTime = 0;
}

Hudson::Util::Timestep::~Timestep()
{

}

void Hudson::Util::Timestep::CalculateTimestep()
{
	_nowTime = glfwGetTime();
	_accumulator += ((_nowTime - _lastTime) / FPS_60);
	_lastTime = _nowTime;

	while (_accumulator >= 1.0)
	{
		_doTick();
		DeltaTime = FPS_60;
		_updates++;
		_accumulator--;
	}

	// Renders at maximum possible _frames - Render Here
	_frames++;

	// Reset after one second
	if (glfwGetTime() - _timer > 1.0)
	{
		_timer++;
		std::cout << "FPS: " << _updates << std::endl;
		_updates = 0;
		_frames = 0;
	}

}