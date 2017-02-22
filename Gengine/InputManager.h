#pragma once
#include <unordered_map>
#include <glm/glm.hpp>
namespace Gengine {
	class InputManager
	{
	private:
		std::unordered_map<unsigned int, bool> _keyMap;
		glm::vec2 _mouseCoords;
	public:
		InputManager();
		~InputManager();
		void pressKey(unsigned int keyId);
		void releaseKey(unsigned int keyId);
		bool isKeyPressed(unsigned int keyId);
		void setMouseCoords(float x,float y);
		glm::vec2 getMouseCoords()const { return _mouseCoords; }
	};
}
