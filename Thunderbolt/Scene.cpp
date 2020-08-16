#include "Scene.h"

Scene::Scene(unsigned int screenWidth, unsigned int screenHeight, const char* sceneDataFilePath):
	screenWidth(screenWidth),
	screenHeight(screenHeight),
	sceneDataFilePath(sceneDataFilePath)
{
	this->setProjectionMat4();
	this->setShaders();
	this->setSceneData();
	this->setTextures();
	this->setBatchProcesses();
}

Scene::~Scene()
{
	delete(this->shader);
	delete(this->tileTexture);
	delete(this->tileMapRenderer);
	delete(this->sceneData);
}

void Scene::renderTileMap()
{
	//int offsetX = 100;
	//int offsetY = 100;
	//int x = offsetX;
	//int y = offsetY;
	//int tileWidth = 32;
	//int tileHeight = 32;
	//for (int i = 0; i < 400; i++) {
	//	if (i % 20 == 0) {
	//		y = y + tileHeight;
	//		x = offsetX;
	//	}
	//	else {
	//		x = x + tileWidth;
	//	}

	//	if (this->map[i] != 0) {n 
	//		this->renderSprite->DrawSprite(*this->tileTexture, glm::vec2(x, y), glm::vec2(32.0f, 32.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	//	}
	//}

	this->tileMapRenderer->render(*this->shader, *this->tileTexture, glm::vec2(32.0f, 32.0f), glm::vec2(this->sceneData->tileWidth, this->sceneData->tileHeight), 0.0f);
}

void Scene::load()
{
	this->sceneData->loadFile("assets/level1.tmx");
	this->tileTexture->load("assets/test_sheet.png", false);
	this->tileMapRenderer->load(this->sceneData->mapWidth, this->sceneData->mapHeight, this->sceneData->tileWidth, this->sceneData->tileHeight, this->sceneData->renderMap);

	shader->use();
	shader->setMat4("projection", this->projection);
}

void Scene::setSceneData()
{
	this->sceneData = new SceneData();
}

void Scene::setProjectionMat4()
{
	this->projection = glm::ortho(0.0f, static_cast<float>(this->screenWidth), static_cast<float>(this->screenHeight), 0.0f, -1.0f, 1.0f);
}

void Scene::setShaders()
{
	this->shader = new Shader("programs/sprite.vert", "programs/sprite.frag");
}

void Scene::setTextures()
{
	this->tileTexture = new Texture2d();	
}

void Scene::setBatchProcesses()
{
	this->tileMapRenderer = new RenderBatch();
}
