#include "stdafx.h"
#include "Animation.h"
#include "ResourceManager.h"

Animation::Animation(SpriteGO& spriteGO)
	: Component(spriteGO, ComponentType::Animation, true)
{
	target = &spriteGO.sprite;
}

Animation::~Animation()
{
}

void Animation::SetClip(AnimationClip* newClip)
{
	clip = newClip;
	currentFrame = 0;
	totalFrame = clip->frames.size();
	clipFrameTime = 1.0f / clip->fps;
	accumTime = 0.0f;
}

void Animation::Update(float dt)
{
	if (!isEnable || !isPlaying)
		return;

	accumTime += dt * speed;

	if (accumTime < clipFrameTime)
		return;

	accumTime = 0.0f;
	++currentFrame;

	if (currentFrame == totalFrame)
	{
		switch (clip->loopType)
		{
		case AnimationLoopTypes::Single:
			currentFrame = totalFrame - 1;
			return;
		case AnimationLoopTypes::Loop:
			currentFrame = 0;
			break;
		}
	}
	if (clip->frames[currentFrame].action != nullptr)
	{
		clip->frames[currentFrame].action();
	}
	if (target != nullptr)
	{
		SetFrame(clip->frames[currentFrame]);
	}
}

void Animation::Play(int frame)
{
	isPlaying = true; 
	Seek(frame);
}

void Animation::Seek(int frame)
{
	currentFrame = frame;
	SetFrame(clip->frames[currentFrame]);
	if (clip->frames[currentFrame].action != nullptr)
	{
		clip->frames[currentFrame].action();
	}
}

float Animation::GetClipDuration()
{
	return clipFrameTime * totalFrame;
}

void Animation::Stop()
{
	isPlaying = false;
}

std::string Animation::GetClipName()
{
	return clip->id;
}

void Animation::SetFrame(const AnimationFrame& frame)
{
	if (frame.textureID != "")
	{
		sf::Texture* tex = Resources.GetTexture(frame.textureID);
		target->setTexture(*tex);
	}
	target->setTextureRect(frame.tecCoord);
}

void Animation::Init()
{
}

void Animation::Draw(sf::RenderWindow& window)
{
}

void Animation::Release()
{
}
