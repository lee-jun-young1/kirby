#pragma once
#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include "ResourceManager.h"

class SpriteGO : public GameObject
{
protected:
	sf::Vector2f spriteDirection;

public:
	sf::Sprite sprite;
	std::string textureID;
	SpriteGO(const std::string textureID = "", const std::string & name = "");

	void SetTexture(sf::Texture& texture, sf::Vector2f spriteDir = sf::Vector2f(-1.0f, 0.0f));
	void SetTextureID(const std::string textureID);

	virtual void SetPosition(const sf::Vector2f& position) override;
	virtual void SetPosition(const float& x, const float& y) override;

	virtual void SetOrigin(const Origins& origin) override;
	virtual void SetOrigin(const sf::Vector2f& origin) override;
	sf::Vector2f GetOrigin() const;

	sf::Vector2f GetSize() const;

	void SetColor(const sf::Color color) { sprite.setColor(color); }
	const sf::Color& GetColor() { return sprite.getColor(); }

	// GameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetFlipX(bool flip);
	void SetFlipY(bool flip);
};

