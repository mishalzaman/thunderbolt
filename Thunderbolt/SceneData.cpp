#include "SceneData.h"
#include <iostream>

SceneData::SceneData()
{

}

SceneData::~SceneData()
{
}

bool SceneData::loadFile(const char* path)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(path);

    if (!result) {
        return false;
    }

    pugi::xml_node map = doc.child("map");

    this->mapWidth = std::stoi(map.attribute("width").value());
    this->mapHeight = std::stoi(map.attribute("height").value());
    this->tileWidth = std::stoi(map.attribute("tilewidth").value());
    this->tileHeight = std::stoi(map.attribute("tileheight").value());

    std::string mapString = map.child("layer").child("data").child_value();
    this->convertCSVStringToList(mapString, this->renderMap);

    return true;
}

// TODO: Turn this in to a utility function in a static class
void SceneData::convertCSVStringToList(std::string value, std::vector<int> &list)
{
    std::vector<int> vect;

    std::stringstream ss(value);

    for (int i; ss >> i;) {
        list.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }

    for (std::size_t i = 0; i < vect.size(); i++)
        std::cout << vect[i] << std::endl;
}
