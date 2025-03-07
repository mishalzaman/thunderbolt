#include "DebugDraw.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

DebugDraw::DebugDraw(): mRatio(1.0f)
{
}

DebugDraw::DebugDraw(float ratio): mRatio(ratio)
{
}

void DebugDraw::DrawPolygon(const b2Vec2* old_vertices, int vertexCount, const b2Color& color)
{
	b2Vec2* vertices = new b2Vec2[vertexCount];
	for (int i = 0; i < vertexCount; i++)
	{
		vertices[i] = old_vertices[i];
		vertices[i] *= mRatio;
	}

	glColor4f(color.r, color.g, color.b, 1);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);

	delete[] vertices;
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* old_vertices, int vertexCount, const b2Color& color)
{
	b2Vec2* vertices = new b2Vec2[vertexCount];
	for (int i = 0; i < vertexCount; i++) {
		vertices[i] = old_vertices[i];
		vertices[i] *= mRatio;
	}

	glVertexPointer(2, GL_FLOAT, 0, vertices);

	glColor4f(color.r, color.g, color.b, 0.5f);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

	glColor4f(color.r, color.g, color.b, 1);
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);

	delete[] vertices;
}

void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{

	const float k_segments = 16.0f;
	int vertexCount = 16;
	const float k_increment = 2.0f * b2_pi / k_segments;
	float theta = 0.0f;

	GLfloat* glVertices = new GLfloat[vertexCount * 2];
	for (int i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		glVertices[i * 2] = v.x * mRatio;
		glVertices[i * 2 + 1] = v.y * mRatio;
		theta += k_increment;
	}

	glColor4f(color.r, color.g, color.b, 1);
	glVertexPointer(2, GL_FLOAT, 0, glVertices);

	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

	delete[] glVertices;
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{

	const float k_segments = 16.0f;
	int vertexCount = 16;
	const float k_increment = 2.0f * b2_pi / k_segments;
	float theta = 0.0f;

	GLfloat* glVertices = new GLfloat[vertexCount * 2];
	for (int i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		glVertices[i * 2] = v.x * mRatio;
		glVertices[i * 2 + 1] = v.y * mRatio;
		theta += k_increment;
	}

	glColor4f(color.r, color.g, color.b, 0.5f);
	glVertexPointer(2, GL_FLOAT, 0, glVertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
	glColor4f(color.r, color.g, color.b, 1);
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);

	// Draw the axis line
	DrawSegment(center, center + radius * axis, color);

	delete[] glVertices;
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	glColor4f(color.r, color.g, color.b, 1);
	GLfloat	glVertices[] =
	{
		p1.x * mRatio, p1.y * mRatio,
		p2.x * mRatio, p2.y * mRatio
	};
	glVertexPointer(2, GL_FLOAT, 0, glVertices);
	glDrawArrays(GL_LINES, 0, 2);
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{

}

void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
	glColor4f(color.r, color.g, color.b, 1);
	glPointSize(size);
	GLfloat				glVertices[] = {
		p.x * mRatio, p.y * mRatio
	};
	glVertexPointer(2, GL_FLOAT, 0, glVertices);
	glDrawArrays(GL_POINTS, 0, 1);
	glPointSize(1.0f);
}

void DebugDraw::DrawAABB(b2AABB* aabb, const b2Color& c)
{
	glColor4f(c.r, c.g, c.b, 1);

	GLfloat				glVertices[] = {
		aabb->lowerBound.x * mRatio, aabb->lowerBound.y * mRatio,
		aabb->upperBound.x * mRatio, aabb->lowerBound.y * mRatio,
		aabb->upperBound.x * mRatio, aabb->upperBound.y * mRatio,
		aabb->lowerBound.x * mRatio, aabb->upperBound.y * mRatio
	};
	glVertexPointer(2, GL_FLOAT, 0, glVertices);
	glDrawArrays(GL_LINE_LOOP, 0, 8);

}