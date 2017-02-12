#include "IOManager.h"
#include<fstream>
namespace Gengine {
	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer)
	{
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail())
		{
			perror(filePath.c_str());
			return false;
		}
		//seek to the end
		file.seekg(0, std::ios::end);
		//Get file size
		int fileSize = file.tellg();
		//Came back to begining
		file.seekg(0, std::ios::beg);

		fileSize -= file.tellg();//NOt sure if this matters - header text in file
		buffer.resize(fileSize);
		file.read((char *)&(buffer[0]), fileSize);

		file.close();
		return true;
	}
}