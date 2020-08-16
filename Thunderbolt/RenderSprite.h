#ifndef RENDER_SPRITE_H
#define RENDER_SPRITE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Texture2d.h"

class RenderSprite
{
public:
    RenderSprite(Shader& shader);
    ~RenderSprite();

    void DrawSprite(Texture2d& texture, glm::vec2 position,
        glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
        glm::vec3 color = glm::vec3(1.0f));
private:
    Shader   shader;
    unsigned int quadVAO;

    void initRenderData();
};

#endif