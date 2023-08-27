#pragma once
#include "SpriteGO.h"
class ModeButton : public SpriteGO
{
protected:
	SceneId nextSceneID = SceneId::None;

	SpriteGO* guide = nullptr;
	bool showGuide = false;

	bool isTwinkle = false;
	float twinkleTimer = 0.0f;
	float twinkleInterval = 0.5f;

	bool isLock = false;
public:
	ModeButton(const std::string textureID, const std::string& name) : SpriteGO(textureID, name){}

	const SceneId& GetNextSceneID() const { return nextSceneID; }
	const bool& IsShowGuide() const { return showGuide; }
	const bool& IsLock() const { return isLock; }

	void SetNextSceneID(SceneId sceneID) { this->nextSceneID = sceneID; }
	void SetGuide(SpriteGO* guide) { this->guide = guide; }
	void SetLock(bool lock) { this->isLock = true; }

	bool HasGuide();
	void ShowGuide();
	void CloseGuide();

	virtual void Reset() override;
	virtual void Update(float deltaTime) override;
};

