#include "stdafx.h"
#include "TextGameObj.h"
#include <Utils.h>
#include <ResourceManager.h>

TextGameObj::TextGameObj(const string& fontID, const int& fontSize, const string& name)
	:GameObject(name), fontID(fontID), fontSize(fontSize)
{
}

TextGameObj::~TextGameObj()
{
}

void TextGameObj::Init()
{
}

void TextGameObj::SetPosition(float width, float height)
{
	text.setPosition(width, height);
}

sf::Text& TextGameObj::GetText()
{
	return text;
}

void TextGameObj::Release()
{
}

void TextGameObj::Reset()
{
	sf::Font* font = Resources.GetFont(fontID);
	if (font != nullptr)
	{
		text.setFont(*font);
		text.setCharacterSize(fontSize);
		SetOrigin(origin);
	}
}

void TextGameObj::Update(float deltaTime)
{
}

void TextGameObj::SetOrigin(const Origins& origin)
{
	this->origin = Utils::SetOrigin(text, origin);
}

void TextGameObj::SetOrigin(const sf::Vector2f& origin)
{
	GameObject::SetOrigin(origin);
	text.setOrigin(origin);
}


void TextGameObj::SetString(const string& str)
{
	std::string utf8String = str;
	sf::String unicodeString = sf::String::fromUtf8(utf8String.begin(), utf8String.end());
	text.setString(unicodeString);
}

void TextGameObj::SetFillColor(const sf::Color& color)
{
	text.setFillColor(color);
}

void TextGameObj::SetFont(sf::Font& font)
{
	text.setFont(font);
}

void TextGameObj::SetCharacterSize(const int& fontSize)
{
	text.setCharacterSize(fontSize);
}

void TextGameObj::Draw(sf::RenderWindow& window)
{
	window.draw(text);
}
