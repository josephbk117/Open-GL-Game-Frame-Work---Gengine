#pragma once
#include<SDL\SDL.h>
#include <GL\glew.h>
#include <Gengine/Sprite.h>
#include <Gengine/GLSLProgram.h>
#include <Gengine/GLTexture.h>
#include <Gengine/Window.h>
#include <Gengine/Camera2D.h>
#include <Gengine/InputManager.h>
#include <Gengine/FpsLimiter.h>
#include <vector>
#include <Gengine/SpriteBatch.h>

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
	

	GLSLProgram _colourProgram;
	GLTexture _playerTexture;
	Camera2D _camera;
	SpriteBatch _spriteBatch;
	InputManager _inputManager;
	float _time;
	float _fps;
	float _frameTime;
#pragma endregion

#pragma region privateFunctions
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();
	void calculateFps();
#pragma endregion
	
public:
	MainGame();
	~MainGame();

	void run();
	
};

