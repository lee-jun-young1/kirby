#include "stdafx.h"
#include "SpriteTextGO.h"
#include <ResourceManager.h>

SpriteTextGO::SpriteTextGO(const std::string& fontID, const std::string& name)
	:VertexArrayGO("", name), fontID(fontID)
{
}

void SpriteTextGO::SetText(std::string text, int colorIdx)
{
	sf::Vector2f offset = { 0.0f, 0.0f };
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(text.size() * 4);
	for (int i = 0; i < text.size(); i++)
	{
		int index = i * 4;
		SpriteFontData data = font->Get(*(text.c_str() + i));
		textureID = data.spriteID;

		for (int k = 0; k < 4; k++)
		{
			vertexArray[index].position = offset;
			vertexArray[index].texCoords = { (float)data.rect.left, (float)data.rect.top + colorIdx * (float)data.rect.height };


			vertexArray[index + 1].position = offset + sf::Vector2f((float)data.rect.width, 0.0f);
			vertexArray[index + 1].texCoords = { (float)data.rect.left + (float)data.rect.width, (float)data.rect.top + colorIdx * (float)data.rect.height };


			vertexArray[index + 2].position = offset + sf::Vector2f((float)data.rect.width, (float)data.rect.height);
			vertexArray[index + 2].texCoords = { (float)data.rect.left + (float)data.rect.width, (float)data.rect.top + (float)data.rect.height + colorIdx * (float)data.rect.height };


			vertexArray[index + 3].position = offset + sf::Vector2f(0.0f , (float)data.rect.height);
			vertexArray[index + 3].texCoords = { (float)data.rect.left, (float)data.rect.top + (float)data.rect.height + colorIdx * (float)data.rect.height };
		}
		offset.x += (float)data.rect.width;
	}

	SetPosition(position);
}

void SpriteTextGO::SetFont(SpriteFont* font)
{
	this->font = font;
}

void SpriteTextGO::Init()
{
	VertexArrayGO::Init();
}

void SpriteTextGO::Release()
{
	VertexArrayGO::Release();
}

void SpriteTextGO::Reset()
{
	SetFont(Resources.GetSpriteFont(fontID));
	VertexArrayGO::Reset();
}

void SpriteTextGO::Update(float dt)
{
	VertexArrayGO::Update(dt);
}