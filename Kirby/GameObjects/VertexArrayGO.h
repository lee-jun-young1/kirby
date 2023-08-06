#pragma once
#include "GameObject.h"
class VertexArrayGO : public GameObject
{
protected:
	std::string textureID;
	sf::Texture* texture;
	sf::Vector2f originPosition;
public:
	sf::VertexArray vertexArray;

	VertexArrayGO(const std::string& textureID = "", const std::string & name = "");
	virtual ~VertexArrayGO() override;

	virtual void SetPosition(const sf::Vector2f& position) override;
	virtual void SetPosition(const float& x, const float& y) override;

	virtual void SetOrigin(const Origins& origin) override;
	virtual void SetOrigin(const sf::Vector2f& origin) override;
	
	void DrawRenderTexture(sf::RenderTexture& renderTexture);

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override; //√ ±‚»≠

	virtual sf::Vector2f GetSize();

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

