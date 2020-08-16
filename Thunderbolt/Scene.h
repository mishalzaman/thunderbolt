#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Texture2d.h"
#include "RenderBatch.h"
#include "SceneData.h"

class Scene
{
public:
	Scene(unsigned int screenWidth, unsigned int screenHeight, const char* sceneDataFilePath);
	~Scene();
	void renderTileMap();
	void load();
private:
	// functions
	void setSceneData();
	void setProjectionMat4();
	void setShaders();
	void setTextures();
	void setBatchProcesses();

	// member variables
	unsigned int screenWidth;
	unsigned int screenHeight;
	Shader*		 shader;
	glm::mat4	 projection;
	Texture2d*	 tileTexture;
	RenderBatch* tileMapRenderer;
	SceneData*   sceneData;
	const char*  sceneDataFilePath;
};

#endif

