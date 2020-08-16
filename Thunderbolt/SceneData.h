#ifndef SCENE_DATA_H
#define SCENE_DATA_H

#include <vector>
#include <string>
#include <sstream>
#include "vendor/pugixml.hpp"

class SceneData
{
public:
	SceneData();
	~SceneData();
	bool loadFile(const char* path);

	unsigned int mapWidth;
	unsigned int mapHeight;
	unsigned int tileWidth;
	unsigned int tileHeight;
	std::vector<int> renderMap;
private:
	void convertCSVStringToList(std::string value, std::vector<int> &list);
};

#endif

