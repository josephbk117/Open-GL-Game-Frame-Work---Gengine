#include "MainGame.h"
#include <Gengine/Error.h>
#include <Gengine/ImageLoader.h>
#include <iostream>
#include <string>
#include <Gengine/Gengine.h>
using namespace Gengine;
MainGame::MainGame() : _time(0.0f),_screenWidth(1024),_screenHeight(720),_gameState(GameState::PLAY)
{
	_camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame()
{
}
void MainGame::run()
{
	
	initSystems();
	_sprites.push_back(new Sprite());
	_sprites.back()->init(0.0f, 0.0f, _screenWidth/2, _screenWidth / 2, "C:/Users/josep_000/Documents/Visual Studio 2017/Projects/openGlLaeranWithSDL/Textures/PlanetProctorTimeslow.png");
	_sprites.push_back(new Sprite());
	_sprites.back()->init(_screenWidth/2, 0.0, _screenWidth / 2, _screenWidth / 2, "C:/Users/josep_000/Documents/Visual Studio 2017/Projects/openGlLaeranWithSDL/Textures/PlanetProctorTimeslow.png");
	

	std::cout << "Open gl version : " << glGetString(GL_VERSION);
	gameLoop();
}
void MainGame::initSystems()
{
	//Initialize SDL
	init();
	_window.create("Game Engine v 0.0.1", _screenWidth, _screenHeight, 0);
	initShaders();
	
}
//TODO : Fix path problem
void MainGame::initShaders()
{
	_colourProgram.compileShaders("C:/Users/josep_000/Documents/Visual Studio 2017/Projects/openGlLaeranWithSDL/Shaders/colorShading.vert", 
		"C:/Users/josep_000/Documents/Visual Studio 2017/Projects/openGlLaeranWithSDL/Shaders/colorShading.frag");
	_colourProgram.addAttribute("vertexPosition");
	_colourProgram.addAttribute("vertexColor");
	_colourProgram.addAttribute("vertexUV");
	_colourProgram.linkShaders();
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();

		_time += 0.01f;

		_camera.update();
		drawGame();
		//calculateFps();
		//std::cout << _fps<<std::endl;
	}
}
void MainGame::processInput()
{
	SDL_Event evnt;
	const float SCALE_SPEED = 0.01f;

	while (SDL_PollEvent(&evnt) == true)
	{
		switch (evnt.type)
		{
			case SDL_QUIT: _gameState = GameState::EXIT; break;
			case SDL_MOUSEMOTION: 
				break;
			case SDL_KEYDOWN:
				switch (evnt.key.keysym.sym)
				{
				case SDLK_w: _camera.setPosition(_camera.getPosition() + glm::vec2(0.0, 5.0));
					break;
				case SDLK_s: _camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -5.0));
					break;
				case SDLK_a: _camera.setPosition(_camera.getPosition() + glm::vec2(5.0, 0.0));
					break;
				case SDLK_d: _camera.setPosition(_camera.getPosition() + glm::vec2(-5.0, 0.0));
					break;
				case SDLK_q: _camera.setScale(_camera.getScale() + SCALE_SPEED);
					break;
				case SDLK_e: _camera.setScale(_camera.getScale() - SCALE_SPEED);
					break;
				}
				break;
		}
	}

}

void MainGame::drawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colourProgram.use();
	glActiveTexture(GL_TEXTURE0);
	
	GLint textureLocation = _colourProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLint timeLocation = _colourProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);

	//Set the camera matrix
	GLint PLocation = _colourProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	glUniformMatrix4fv(PLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	//----Draw all sprites
	for (int i = 0; i < _sprites.size(); i++)
	{
		_sprites[i]->draw();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	_colourProgram.unUse();

	_window.swapBuffer();
}
void MainGame::calculateFps() 
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
