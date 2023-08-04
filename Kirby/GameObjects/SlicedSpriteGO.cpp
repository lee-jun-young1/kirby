#include "stdafx.h"
#include "SlicedSpriteGO.h"
#include <ResourceManager.h>

SlicedSpriteGO::SlicedSpriteGO(const std::string& textureID, sf::Rect<float> centerRect, sf::Rect<float> size, const string& name)
	:VertexArrayGO(textureID, name), centerRect(centerRect), spriteSize(size)
{
}

void SlicedSpriteGO::SetTexture(sf::Texture& texture, sf::Rect<float> centerRect, sf::Rect<float> size)
{
	this->texture = &texture;
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(36);

	this->centerRect = centerRect;
	this->spriteSize = size;

	SetTextureSize(centerRect, spriteSize);
	SetSize({ size.width, size.height });
}

void SlicedSpriteGO::SetTextureSize(sf::Rect<float> centerRect, sf::Rect<float> spriteSize)
{
	vector<float> textureHorizontal;
	vector<float> textureVertical;

	textureHorizontal.push_back(spriteSize.left);
	textureHorizontal.push_back(centerRect.left);
	textureHorizontal.push_back(centerRect.left + centerRect.width);
	textureHorizontal.push_back(spriteSize.left + spriteSize.width);

	textureVertical.push_back(spriteSize.top);
	textureVertical.push_back(centerRect.top);
	textureVertical.push_back(centerRect.top + centerRect.height);
	textureVertical.push_back(spriteSize.top + spriteSize.height);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int index = (i * 3 + j) * 4;
			vertexArray[index].texCoords = { textureHorizontal[j], textureVertical[i] };
			vertexArray[index + 1].texCoords = { textureHorizontal[j + 1], textureVertical[i] };
			vertexArray[index + 2].texCoords = { textureHorizontal[j + 1], textureVertical[i + 1] };
			vertexArray[index + 3].texCoords = { textureHorizontal[j], textureVertical[i + 1] };
		}
	}
}

void SlicedSpriteGO::SetSize(sf::Vector2f size)
{
	vector<float> positionX;
	vector<float> positionY;
	sf::Vector2f borderSize = { spriteSize.width - centerRect.width, spriteSize.height - centerRect.height };
	//size -= borderSize;

	if (borderSize.x < size.x)
	{
		positionX.push_back(spriteSize.left);
		positionX.push_back(centerRect.left);
		positionX.push_back(centerRect.left + (size.x - borderSize.x));
		positionX.push_back(spriteSize.left + spriteSize.width - (centerRect.width - (size.x - borderSize.x)));
	}
	else
	{
		positionX.push_back(spriteSize.left);
		positionX.push_back(size.x * 0.5f);
		positionX.push_back(size.x * 0.5f);
		positionX.push_back(size.x);
	}

	if (borderSize.y < size.y)
	{
		positionY.push_back(spriteSize.top);
		positionY.push_back(centerRect.top);
		positionY.push_back(centerRect.top + (size.y - borderSize.y));
		positionY.push_back(spriteSize.top + spriteSize.height - (centerRect.height - (size.y - borderSize.y)));
	}
	else
	{
		positionY.push_back(spriteSize.top);
		positionY.push_back(size.y * 0.5f);
		positionY.push_back(size.y * 0.5f);
		positionY.push_back(size.y);
	}


	for (int i = 0; i < 3; i++) 
	{
		for (int j = 0; j < 3; j++)
		{
			int index = (i * 3 + j) * 4;
			vertexArray[index].position = { positionX[j], positionY[i] };
			vertexArray[index + 1].position = { positionX[j + 1], positionY[i] };
			vertexArray[index + 2].position = { positionX[j + 1], positionY[i + 1] };
			vertexArray[index + 3].position = { positionX[j], positionY[i + 1] };
		}
	}
}

void SlicedSpriteGO::Init()
{
	VertexArrayGO::Init();
}

void SlicedSpriteGO::Release()
{
	VertexArrayGO::Release();
}

void SlicedSpriteGO::Reset()
{
	SetTexture(*Resources.GetTexture(textureID), centerRect, spriteSize);
}

void SlicedSpriteGO::Update(float dt)
{
	VertexArrayGO::Update(dt);
}