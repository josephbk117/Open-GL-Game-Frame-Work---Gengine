#pragma once
#include<SDL\SDL.h>
#include <GL\glew.h>
#include <Gengine/Sprite.h>
#include <Gengine/GLSLProgram.h>
#include <Gengine/GLTexture.h>
#include <Gengine/Window.h>
#include <Gengine/Camera2D.h>
#include <vector>

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
	//Sprite collection
	std::vector <Sprite*> _sprites;

	GLSLProgram _colourProgram;
	GLTexture _playerTexture;
	Camera2D _camera;
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

