#ifndef RENDER_BATCH_H
#define RENDER_BATCH_h

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Texture2d.h"

struct VertexAttribute {
	glm::vec3 vertex;
	glm::vec4 colour;
	glm::vec2 textureUV;
};

class RenderBatch
{
public:
	RenderBatch();
	~RenderBatch();
	void load(unsigned int width, unsigned int height, unsigned int tileWidth, unsigned int tileHeight, std::vector<int> mapData);
	void render(Shader &shader, Texture2d& texture, glm::vec2 position, glm::vec2 size, float rotate);
private:


	unsigned int vao;
	std::vector<uint32_t> g_indices;
	std::vector<VertexAttribute> vertex_attributes;
};

#endif

