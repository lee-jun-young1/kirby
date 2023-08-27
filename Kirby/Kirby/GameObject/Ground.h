#pragma once
#include "SpriteGO.h"
#include "json.h"
class Ground : public SpriteGO
{
protected:
	GroundType type = GroundType::None;
	int groundIndex;
	
	bool throughAble;
	bool crashAble;
	
	sf::Vector2f groundSize = { 24.0f, 24.0f };
	Json::Value node;
	sf::IntRect textureRect;
public:
	Ground(const std::string textureID = "", const std::string& name = "");

	const int& GetGroundIndex() const { return groundIndex; }
	void SetGroundIndex(const int& index) { groundIndex = index; }

	const GroundType& GetGroundType() const { return type; }
	void SetGroundType(const GroundType& type) { this->type = type; }
	
	void SetData(const Json::Value& data) { this->node = data; }
	void SetTextureRect(const sf::IntRect textureRect) { this->textureRect = textureRect; }

	virtual void Init() override;
	virtual void Reset() override;
};