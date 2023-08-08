#include "stdafx.h"
#include "VertexArrayGO.h"
#include "ResourceManager.h"

VertexArrayGO::VertexArrayGO(const std::string& textureID, const std::string& name)
	:GameObject(name), textureID(textureID)
{
}

VertexArrayGO::~VertexArrayGO()
{
}

void VertexArrayGO::SetPosition(const sf::Vector2f& position)
{
	GameObject::SetPosition(position);

	sf::Vector2f diff = (position - originPosition) - vertexArray[0].position;
	for (int i = 0; i < vertexArray.getVertexCount(); i++)
	{
		vertexArray[i].position += diff;
	} 
}

void VertexArrayGO::SetPosition(const float& x, const float& y)
{
	GameObject::SetPosition(x, y);

	sf::Vector2f diff = (position - originPosition) - vertexArray[0].position;
	for (int i = 0; i < vertexArray.getVertexCount(); i++)
	{
		vertexArray[i].position += diff;
	}
}

void VertexArrayGO::SetOrigin(const Origins& origin)
{
	originPosition = { vertexArray.getBounds().width, vertexArray.getBounds().height};
	originPosition.x *= ((int)origin % 3) * 0.5f;
	originPosition.y *= ((int)origin / 3) * 0.5f;

	sf::Vector2f diff = this->origin - originPosition;
	for (int i = 0; i < vertexArray.getVertexCount(); i++)
	{
		vertexArray[i].position += diff;
	}
	GameObject::SetOrigin(originPosition);
}

void VertexArrayGO::SetOrigin(const sf::Vector2f& origin)
{
	sf::Vector2f diff = this->origin - origin;
	for (int i = 0; i < vertexArray.getVertexCount(); i++)
	{
		vertexArray[i].position += diff;
	}
	GameObject::SetOrigin(origin);
}

void VertexArrayGO::DrawRenderTexture(sf::RenderTexture& renderTexture)
{
	renderTexture.draw(vertexArray, texture);
}


void VertexArrayGO::Init()
{
}

void VertexArrayGO::Release()
{
	GameObject::Release();
}

void VertexArrayGO::Reset()
{
	texture = Resources.GetTexture(textureID);
}

sf::Vector2f VertexArrayGO::GetSize()
{
	return { vertexArray.getBounds().width, vertexArray.getBounds().height };
}

void VertexArrayGO::Update(float dt)
{
	GameObject::Update(dt);
}

void VertexArrayGO::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	window.draw(vertexArray, texture);
}