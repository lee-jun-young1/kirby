#pragma once
#include "VertexArrayGO.h"
#include <SpriteFont.h>
class SpriteTextGO : public VertexArrayGO
{
protected:
	SpriteFont* font;
public:
	SpriteTextGO(const std::string& name = "");
	void SetText(std::string text, int colorIdx = 0);
	void SetFont(SpriteFont* font);

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override; //√ ±‚»≠

	virtual void Update(float dt) override;
};

