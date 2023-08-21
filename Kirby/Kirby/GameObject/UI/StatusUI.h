#pragma once
#include "GameObject.h"
#include <SpriteTextGO.h>


class StatusUI : public GameObject
{
public:
	enum class UIMode 
	{
		Default,
		Boss,
		WithPartner,
		BossWithPartner
	};
protected:
	sf::RectangleShape bgL;
	sf::RectangleShape bgR;
	sf::Sprite ability1P;
	sf::Sprite ability2P;
	sf::RectangleShape hp1P;
	sf::RectangleShape hp2P;
	sf::RectangleShape hpEnemy;
	sf::Sprite statusCover;

	SpriteTextGO* lifeText;
	SpriteTextGO* scoreText;

	float hpSize = 56.0f;
	float player1PrevHP = 56.0f;
	float player1CurrentHP = 56.0f;
	float player1HitTime = 1.0f;
	float player2PrevHP = 56.0f;
	float player2CurrentHP = 56.0f;
	float player2HitTime = 1.0f;
	float enemyPrevHP = 56.0f;
	float enemyCurrentHP = 56.0f;
	float enemyHitTime = 1.0f;
public:
	StatusUI(const std::string& name = "") :GameObject(name) {}

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetUIMode(UIMode mode);

	void SetPlayer1HP(float hpPercent);
	void SetPlayer1Ability(KirbyAbility ability);

	void SetPlayer2HP(float hpPercent);
	void SetPlayer2Ability(KirbyAbility ability);

	void SetEnemyHP(float hpPercent);

	void SetLifeText(SpriteTextGO* spriteTextGO) { lifeText = spriteTextGO; }
	void SetScoreText(SpriteTextGO* spriteTextGO) { scoreText = spriteTextGO; }

	void SetLife(int life);
	void SetScore(int score);
};

