#include "stdafx.h"
#include "BackgroundSea.h"
#include "Animation.h"
void BackgroundSea::Init()
{
	sortLayer = -10;
	SetPosition({ 0.0f, 120.0f });
}

void BackgroundSea::Reset()
{
	Animation* ani = (Animation*)GetComponent(ComponentType::Animation);
	if (ani == nullptr)
	{
		ani = (Animation*)AddComponent(new Animation(*this));
	}
	ani->SetClip(Resources.GetAnimationClip("animations/Background/GreenGreenSea.csv"));
	ani->Play();
}
