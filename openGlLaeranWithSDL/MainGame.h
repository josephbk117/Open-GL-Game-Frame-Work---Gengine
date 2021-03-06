#pragma once
#include<SDL\SDL.h>
#include <GL\glew.h>
#include <Gengine/Sprite.h>
#include <Gengine/GLSLProgram.h>
#include <Gengine/GLTexture.h>
#include <Gengine/Window.h>
#include <Gengine/Camera2D.h>
#include <Gengine/InputManager.h>
#include <Gengine/FrameRateLimiter.h>
#include <vector>
#include <Gengine/SpriteBatch.h>

#include "Bullet.h"

using namespace Gengine;
enum class GameState
{
	PLAY,EXIT
};


class MainGame
{
private:
#pragma region privateMemberVariables
	Window _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;	
	FrameRateLimiter _fpsLimiter;
	

	std::vector<Bullet> _bullets;

	GLSLProgram _colourProgram;
	GLTexture _playerTexture;
	Camera2D _camera;
	SpriteBatch _spriteBatch;
	InputManager _inputManager;
	float _time;
	float _fps;
	float _maxFps;
#pragma endregion

#pragma region privateFunctions
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();
#pragma endregion
	
public:
	MainGame();
	~MainGame();

	void run();
	
};

