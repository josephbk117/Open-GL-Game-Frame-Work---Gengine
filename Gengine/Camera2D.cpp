#include "Camera2D.h"

namespace Gengine {

	Camera2D::Camera2D() : _position(0.0f, 0.0f), _cameraMatrix(1.0f), _orthoMatrix(1.0f), _scale(1.0f), _needsMatrixUpdate(true)
		, _screenWidth(500), _screenHeight(500)
	{
	}

	Camera2D::~Camera2D()
	{
	}
	void Camera2D::update()
	{
		if (_needsMatrixUpdate)
		{
			glm::vec3 translate(-_position.x + _screenWidth/2, -_position.y + _screenHeight/2, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);
			glm::vec3 scale(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(_cameraMatrix, scale);
			_needsMatrixUpdate = false;
		}
	}
	void Camera2D::init(int screenWidth, int screenHeight)
	{
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
	}
	glm::vec2 Camera2D::getWorldCoordsFromScreen(glm::vec2 screenCoords)
	{
		//Invert Y
		screenCoords.y = _screenHeight - screenCoords.y;
		screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2); //Makes 0 the center of the screen
		//Scale the coordinates
		screenCoords /= _scale;
		//Translate with the camera position
		screenCoords += _position;

		return screenCoords;

	}
}