#include "RenderBatch.h"

#include <iostream>

RenderBatch::RenderBatch()
{

}

RenderBatch::~RenderBatch()
{
    glDeleteVertexArrays(1, &this->vao);
}

void RenderBatch::load(unsigned int width, unsigned int height, unsigned int tileWidth, unsigned int tileHeight, std::vector<int> mapData)
{
// Generate vertices
    std::vector<float> g_vertices;
    unsigned int rows = width;
    unsigned int columns = height;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float scale = 1.0f;
    unsigned int quads = rows * columns;
    unsigned int mapIndex = 0;

    VertexAttribute v_attribute;

    for (float r = 0; r < rows; r++) {
        for (float c = 0; c < columns; c++) {
            // quad
            
            // bottom left vertex
            v_attribute.vertex = glm::vec3(x, y + scale, z);
            v_attribute.colour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
            //v_attribute.textureUV = glm::vec2(0.0f, 0.0f);
            v_attribute.textureUV = glm::vec2(0.0f, 0.5f);
            this->vertex_attributes.push_back(v_attribute);

            // bottom right vertex
            v_attribute.vertex = glm::vec3(x + scale, y + scale, z);
            v_attribute.colour = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
            //v_attribute.textureUV = glm::vec2(1.0f, 0.0f);
            v_attribute.textureUV = glm::vec2(0.5f, 0.5f);
            this->vertex_attributes.push_back(v_attribute);

            // top right vertex
            v_attribute.vertex = glm::vec3(x + scale, y, z);
            v_attribute.colour = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
            //v_attribute.textureUV = glm::vec2(1.0f, 1.0f);
            v_attribute.textureUV = glm::vec2(0.5f, 1.0f);
            this->vertex_attributes.push_back(v_attribute);

            // top left vertex
            v_attribute.vertex = glm::vec3(x, y, z);
            v_attribute.colour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
            //v_attribute.textureUV = glm::vec2(0.0f, 1.0f);
            v_attribute.textureUV = glm::vec2(0.0f, 1.0f);
            this->vertex_attributes.push_back(v_attribute);

            x = x + scale;

            //unsigned int tileSheetWidth = 64;
            //unsigned int tileSheetHeight = 32;
            //unsigned int tileIndex = mapData[mapIndex];

            printf("%i", mapData[mapIndex]);
            mapIndex++;
        }

        y = y + scale;
        x = 0;
    }

    // Generate indices
    uint32_t index = 0;

    for (int i = 0; i < quads; i++) {
        this->g_indices.push_back(index);
        this->g_indices.push_back(index + 1);
        this->g_indices.push_back(index + 2);
        this->g_indices.push_back(index + 2);
        this->g_indices.push_back(index + 3);
        this->g_indices.push_back(index);

        index = index + 4;
    }

    unsigned int vbo, ibo;

    // VBO
    glCreateBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //glBufferData(GL_ARRAY_BUFFER, g_vertices.size() * sizeof(float), &g_vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, this->vertex_attributes.size() * sizeof(VertexAttribute), &this->vertex_attributes[0], GL_STATIC_DRAW);

    // VAO
    glCreateVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    // IBO
    glCreateBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->g_indices.size() * sizeof(uint32_t), &this->g_indices[0], GL_STATIC_DRAW);

    // Create vertex attributes
    // vertex
    glEnableVertexArrayAttrib(vbo, 0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)0);
    // colour
    glEnableVertexArrayAttrib(vbo, 1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)offsetof(VertexAttribute, colour));
    // texture
    glEnableVertexArrayAttrib(vbo, 2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)offsetof(VertexAttribute, textureUV));

    // unbind vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderBatch::render(Shader& shader, Texture2d& texture, glm::vec2 position, glm::vec2 size, float rotate)
{
    shader.use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

    shader.setMat4("model", model);

    glBindVertexArray(this->vao);
    glDrawElements(
        GL_TRIANGLES,
        this->g_indices.size(),                 // total number of indices
        GL_UNSIGNED_INT,
        nullptr
    );
}