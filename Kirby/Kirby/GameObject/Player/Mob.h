#pragma once
#include "SpriteGO.h"
class Mob : public SpriteGO
{
protected:
    bool suctionable = true;
    KirbyAbility type;
public:
    Mob(KirbyAbility type, const std::string textureID = "", const string& name = "") : SpriteGO(textureID, name), type(type) {};
    bool IsSuctionable() { return suctionable; }
    KirbyAbility GetType() { return type; }
};

