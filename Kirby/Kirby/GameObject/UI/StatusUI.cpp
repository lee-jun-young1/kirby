#include "stdafx.h"
#include "StatusUI.h"
#include <Framework.h>
#include <ResourceManager.h>
#include <Utils.h>
#include <sstream>

void StatusUI::Init()
{
	bgL.setFillColor({ 8, 64, 72, 255});
	bgL.setSize({ FRAMEWORK.GetWindowSize().x * 0.5f, 53.0f });
	bgL.setPosition({0.0f, FRAMEWORK.GetWindowSize().y - bgL.getSize().y});
	bgR.setFillColor({ 8, 64, 72, 255});
	bgR.setSize({ FRAMEWORK.GetWindowSize().x * 0.5f, 53.0f });
	bgR.setPosition({ FRAMEWORK.GetWindowSize().x * 0.5f, FRAMEWORK.GetWindowSize().y - bgR.getSize().y });

	hp1P.setPosition(bgL.getPosition() + sf::Vector2f(56.0f, 18.0f));
	hp1P.setSize({ hpSize, 10.0f });
	hp1P.setFillColor(sf::Color::Red);
	hp2P.setPosition(bgR.getPosition() + sf::Vector2f(16.0f, 18.0f));
	hp2P.setSize({ hpSize, 10.0f });
	hp2P.setFillColor(sf::Color::Red);
	hpEnemy.setPosition(bgR.getPosition() + sf::Vector2f(56.0f, 14.0f));
	hpEnemy.setSize({ hpSize, 6.0f });
	hpEnemy.setFillColor(sf::Color::Red);

	ability1P.setPosition(bgL.getPosition() + sf::Vector2f(8.0f, 7.0f));

	ability2P.setPosition(bgR.getPosition() + sf::Vector2f(88.0f, 7.0f));

	statusCover.setPosition({ 0.0f, FRAMEWORK.GetWindowSize().y - bgL.getSize().y });
}

void StatusUI::Reset()
{
	statusCover.setTexture(*Resources.GetTexture("sprites/UI/Game/Status.png"));
	ability1P.setTexture(*Resources.GetTexture("sprites/UI/Game/Ability.png"));
	SetLife(0);
	SetScore(0);
	SetPlayer1Ability(KirbyAbility::None);
	SetUIMode(UIMode::Default);
}

void StatusUI::Update(float deltaTime)
{
	if (player1HitTime < 1.0f)
	{
		player1HitTime += deltaTime;
		hp1P.setSize({ Utils::Lerp(player1PrevHP, player1CurrentHP, player1HitTime), 10.0f });
		hp1P.setFillColor((int)(player1HitTime * 10.0f) % 2 == 0 ? sf::Color::Red : sf::Color::White);
	}

	if (enemyHitTime < 1.0f)
	{
		enemyHitTime += deltaTime;
		hpEnemy.setSize({ Utils::Lerp(enemyPrevHP, enemyCurrentHP, enemyHitTime), 10.0f });
		hpEnemy.setFillColor((int)(enemyHitTime * 10.0f) % 2 == 0 ? sf::Color::Red : sf::Color::White);
	}
}

void StatusUI::Draw(sf::RenderWindow& window)
{
	window.draw(bgL);
	window.draw(bgR);
	window.draw(hp1P);
	window.draw(hp2P);
	window.draw(hpEnemy);
	window.draw(ability1P);
	window.draw(ability2P);
	window.draw(statusCover);
}

void StatusUI::SetUIMode(UIMode mode)
{
	switch (mode)
	{
	case UIMode::Default:
		statusCover.setTextureRect({ 0, 53 * (int)mode, (int)FRAMEWORK.GetWindowSize().x, 53 });
		hpEnemy.setPosition(bgR.getPosition() + sf::Vector2f(56.0f, 16.0f));
		scoreText->SetPosition(bgR.getPosition() + sf::Vector2f(16.0f, 15.0f));
		scoreText->SetActive(true);
		lifeText->SetPosition(bgR.getPosition() + sf::Vector2f(52.0f, 30.0f));
		break;
	case UIMode::Boss:
		statusCover.setTextureRect({ 0, 53 * (int)mode, (int)FRAMEWORK.GetWindowSize().x, 53 });
		hp2P.setSize({ 0.0f, 10.0f });
		hpEnemy.setPosition(bgR.getPosition() + sf::Vector2f(56.0f, 16.0f));
		scoreText->SetPosition(bgR.getPosition() + sf::Vector2f(16.0f, 15.0f));
		scoreText->SetActive(false);
		lifeText->SetPosition(bgR.getPosition() + sf::Vector2f(52.0f, 30.0f));
		break;
	case UIMode::WithPartner:
		statusCover.setTextureRect({ 0, 53 * (int)mode, (int)FRAMEWORK.GetWindowSize().x, 53 });
		hp2P.setSize({ 56.0f, 10.0f });
		hpEnemy.setPosition(bgR.getPosition() + sf::Vector2f(16.0f, 40.0f));
		scoreText->SetPosition(bgL.getPosition() + sf::Vector2f(103.0f, 39.0f));
		scoreText->SetActive(true);
		lifeText->SetPosition(bgL.getPosition() + sf::Vector2f(64.0f, 39.0f));
		break;
	case UIMode::BossWithPartner:
		statusCover.setTextureRect({ 0, 53 * (int)mode, (int)FRAMEWORK.GetWindowSize().x, 53 });
		hp2P.setSize({ 56.0f, 10.0f });
		hpEnemy.setPosition(bgR.getPosition() + sf::Vector2f(16.0f, 40.0f));
		scoreText->SetPosition(bgL.getPosition() + sf::Vector2f(103.0f, 39.0f));
		scoreText->SetActive(false);
		lifeText->SetPosition(bgL.getPosition() + sf::Vector2f(64.0f, 39.0f));
		break;
	}
}

void StatusUI::SetPlayer1HP(float hpPercent)
{
	player1PrevHP = player1CurrentHP;
	player1CurrentHP = hpSize * hpPercent;
	player1HitTime = 0.0f;
}

void StatusUI::SetPlayer1Ability(KirbyAbility ability)
{
	int abilityIndex = (int)ability;
	int verIndex = abilityIndex / 3;
	int horiIndex = abilityIndex % 3;
	ability1P.setTextureRect({ horiIndex * 64, verIndex * 40, 32, 40 });
}

void StatusUI::SetPlayer2HP(float hpPercent)
{
}

void StatusUI::SetPlayer2Ability(KirbyAbility ability)
{
	int abilityIndex = (int)ability;
	int verIndex = abilityIndex / 3;
	int horiIndex = abilityIndex % 3;
}

void StatusUI::SetEnemyHP(float hpPercent)
{
	enemyPrevHP = enemyCurrentHP;
	enemyCurrentHP = hpSize * hpPercent;
	enemyHitTime = 0.0f;
}

void StatusUI::SetLife(int life)
{
	stringstream ss;
	ss << "@x" << life;
	lifeText->SetText(ss.str());
}

void StatusUI::SetScore(int score)
{
	stringstream ss;
	ss << "SCORE:" << score;
	scoreText->SetText(ss.str());
}
