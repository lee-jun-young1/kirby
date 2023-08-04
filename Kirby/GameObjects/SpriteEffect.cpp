#include "stdafx.h"
#include "SpriteEffect.h"
#include "SceneManager.h"
#include <Utils.h>

SpriteEffect::SpriteEffect(const float& duration, const std::string textureID, const std::string& name)
	:SpriteGO(textureID, name), duration(duration), timer(duration), inverseDuration(1.0f / duration)
{
}

void SpriteEffect::Init()
{
	SpriteGO::Init();
}


void SpriteEffect::Reset()
{
	SpriteGO::Reset();
	timer = duration;
	sprite.setColor({ 255, 255, 255, 255});
}

void SpriteEffect::Update(float dt)
{
	SpriteGO::Update(dt);
	timer -= dt;
	//sprite.setColor({ 255, 255, 255, (sf::Uint8)(255 * timer * inverseDuration) });
	sf::Color a = { 255, 255, 255, 0 };
	sf::Color b = sf::Color::White;
	sf::Color color = Utils::Lerp(a, b, timer * inverseDuration);
	sprite.setColor(color);
	if (timer < 0.0f)
	{
		if (pool != nullptr)
		{
			SCENE_MANAGER.GetCurrentScene()->RemoveGameObject(this);
			pool->Return(this);
		}
		else
		{
			SetActive(false);
		}
	}
}

void SpriteEffect::SetDuration(float duration)
{
	this->duration = duration;
	inverseDuration = 1.0f / duration;
}
