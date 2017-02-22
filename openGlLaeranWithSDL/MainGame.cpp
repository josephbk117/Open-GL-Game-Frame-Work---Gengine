#include "MainGame.h"
#include <Gengine/Error.h>
#include <Gengine/ImageLoader.h>
#include <iostream>
#include <string>
#include <Gengine/Gengine.h>
#include <Gengine/SpriteBatch.h>
#include <Gengine/ResourceManager.h>
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

	std::cout << "Open gl version : " << glGetString(GL_VERSION);
	gameLoop();
}
void MainGame::initSystems()
{
	//Initialize SDL
	init();
	_window.create("Game Engine v 0.0.1", _screenWidth, _screenHeight, 0);
	initShaders();
	_spriteBatch.init();
	_fpsLimiter.init(100.0);
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
		_fpsLimiter.begin();
		processInput();

		_time += 0.01f;

		_camera.update();

		//Update all bullets
		for (int i = 0; i < _bullets.size();)
		{
			if (_bullets[i].update())
			{
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
			}
			else
				i++;
		}

		drawGame();
		_fps = _fpsLimiter.end();
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 1000)
		{
			std::cout << "Frame rate : " << _fps<<std::endl;
			frameCounter = 0;
		}
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
			case SDL_KEYDOWN:
				_inputManager.pressKey(evnt.key.keysym.sym); break;
			case SDL_KEYUP:
				_inputManager.releaseKey(evnt.key.keysym.sym); break;
			case SDL_MOUSEBUTTONUP:
				_inputManager.pressKey(evnt.button.button); break;
			case SDL_MOUSEBUTTONDOWN:
				_inputManager.releaseKey(evnt.button.button); break;
			case SDL_MOUSEMOTION:
				_inputManager.setMouseCoords(evnt.motion.x,evnt.motion.y); break;
		}
	}
	if (_inputManager.isKeyPressed(SDLK_w))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, 1.0));
	}
	if (_inputManager.isKeyPressed(SDLK_s))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -1.0));
	}
	if (_inputManager.isKeyPressed(SDLK_a))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(1.0, 0.0));
	}
	if (_inputManager.isKeyPressed(SDLK_d))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(-1.0, 0.0));
	}
	if (_inputManager.isKeyPressed(SDLK_q))
	{
		_camera.setScale(_camera.getScale() + SCALE_SPEED);
	}
	if (_inputManager.isKeyPressed(SDLK_e))
	{
		_camera.setScale(_camera.getScale() - SCALE_SPEED);
	}
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT))
	{
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _camera.getWorldCoordsFromScreen(mouseCoords);
		
		glm::vec2 playerPosition(0.0);
		glm::vec2 direction = mouseCoords - playerPosition;
		direction = glm::normalize(direction);

		_bullets.emplace_back(playerPosition,direction,10.0f,1000);
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

	_spriteBatch.begin();

	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f,0.0f, 1.0f, 1.0f);
	static GLTexture texture = ResourceManager::getTexture("C:/Users/josep_000/Documents/Visual Studio 2017/Projects/openGlLaeranWithSDL/Textures/PlanetProctorTimeslow.png");
	Colour col;
	col.a = 255; col.r = 255; col.g = 255; col.b = 255;
	_spriteBatch.draw(pos, uv, texture.id, 0.0f, col);

	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].draw(_spriteBatch);
	}

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_colourProgram.unUse();

	_window.swapBuffer();
}
