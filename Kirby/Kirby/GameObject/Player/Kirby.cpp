#include "stdafx.h"
#include "Kirby.h"
#include <SceneManager.h>
#include <Mob.h>
#include <Utils.h>
#include <GameObjects/RectangleShapeGO.h>
#include <Door.h>
#include <InputManager.h>
#include <KirbyBackdancer.h>
#include <GameObjects/SpriteEffect.h>

#pragma region KeyInput

void Kirby::MoveKey(const float& axisX)
{
	if (moveKey != nullptr)
	{
		moveKey(axisX);
	}
}

void Kirby::DashKey(const float& axisX)
{
	if (dashKey != nullptr)
	{
		dashKey(axisX);
	}
}

void Kirby::MoveKeyEnd(const float& axisX)
{
	if (moveKeyEnd != nullptr)
	{
		moveKeyEnd(axisX);
	}
}

void Kirby::DoorKey()
{
	if (doorKey != nullptr)
	{
		doorKey();
	}
}

void Kirby::DoorKeyEnd()
{
	if (doorKeyEnd != nullptr)
	{
		doorKeyEnd();
	}
}

void Kirby::ChargeKey()
{
	if (chargeKey != nullptr)
	{
		chargeKey();
	}
}

void Kirby::ChargeKeyContinue()
{
	if (chargeKeyContinue != nullptr)
	{
		chargeKeyContinue();
	}
}

void Kirby::ChargeKeyEnd()
{
	if (chargeKeyEnd != nullptr)
	{
		chargeKeyEnd();
	}
}

void Kirby::SitKey()
{
	if (sitKey != nullptr)
	{
		sitKey();
	}
}

void Kirby::SitKeyEnd()
{
	if (sitKeyEnd != nullptr)
	{
		sitKeyEnd();
	}
}

void Kirby::JumpKey()
{
	if (jumpKey != nullptr)
	{
		jumpKey();
	}
}

void Kirby::VKey()
{
	if (vKey != nullptr)
	{
		vKey();
	}
}

#pragma endregion


void Kirby::ChangeState(const KirbyState& state)
{
	this->state = state;
	switch (state)
	{
		case KirbyState::Idle:
			cout << "state :: Idle" << endl;
			moveKey = std::bind(&Kirby::Move, this, std::placeholders::_1);
			dashKey = std::bind(&Kirby::Dash, this, std::placeholders::_1);
			moveKeyEnd = nullptr;
			switch (ability)
			{
				case KirbyAbility::None:
					chargeKey = nullptr;
					chargeKeyContinue = std::bind(&Kirby::DoSuction, this);
					break;
				case KirbyAbility::Cutter:
					chargeKey = std::bind(&Kirby::CutterAttack, this);
					chargeKeyContinue = nullptr;
					break;
				default:
					chargeKey = nullptr;
					chargeKeyContinue = nullptr;
					break;
			}
			chargeKeyEnd = nullptr;
			doorKey = std::bind(&Kirby::OnDoorKeyDown, this);
			doorKeyEnd = std::bind(&Kirby::OnDoorKeyUp, this);
			sitKey = std::bind(&Kirby::Sit, this);
			sitKeyEnd = nullptr;
			jumpKey = std::bind(&Kirby::Jump, this);
			vKey = std::bind(&Kirby::UnequipAbility, this);
			update = nullptr;
			onCollisionEnter = nullptr;
			onCollisionStay = nullptr;
			break;
		case KirbyState::Move:
			cout << "state :: Move" << endl;
			moveKey = std::bind(&Kirby::Move, this, std::placeholders::_1);
			dashKey = nullptr;
			moveKeyEnd = std::bind(&Kirby::MoveEnd, this, std::placeholders::_1);
			switch (ability)
			{
			case KirbyAbility::None:
				chargeKey = nullptr;
				chargeKeyContinue = std::bind(&Kirby::DoSuction, this);
				break;
			case KirbyAbility::Cutter:
				chargeKey = std::bind(&Kirby::CutterAttack, this);
				chargeKeyContinue = nullptr;
				break;
			default:
				chargeKey = nullptr;
				chargeKeyContinue = nullptr;
				break;
			}
			chargeKeyEnd = nullptr;
			doorKey = std::bind(&Kirby::OnDoorKeyDown, this);
			doorKeyEnd = std::bind(&Kirby::OnDoorKeyUp, this);
			sitKey = nullptr;
			sitKeyEnd = nullptr;
			jumpKey = std::bind(&Kirby::Jump, this);
			vKey = std::bind(&Kirby::UnequipAbility, this);
			update = std::bind(&Kirby::MoveUpdate, this, std::placeholders::_1);
			onCollisionEnter = std::bind(&Kirby::MoveCollisionEnter, this, std::placeholders::_1);
			onCollisionStay = nullptr;
			break;
		case KirbyState::Dash:
			cout << "state :: Dash" << endl;
			moveKey = std::bind(&Kirby::Dash, this, std::placeholders::_1);
			dashKey = nullptr;
			moveKeyEnd = std::bind(&Kirby::MoveEnd, this, std::placeholders::_1);
			switch (ability)
			{
			case KirbyAbility::None:
				chargeKey = nullptr;
				chargeKeyContinue = std::bind(&Kirby::DoSuction, this);
				break;
			case KirbyAbility::Cutter:
				chargeKey = std::bind(&Kirby::CutterDashAttack, this);
				chargeKeyContinue = nullptr;
				break;
			default:
				chargeKey = nullptr;
				chargeKeyContinue = nullptr;
				break;
			}
			chargeKeyEnd = nullptr;
			doorKey = std::bind(&Kirby::OnDoorKeyDown, this);
			doorKeyEnd = std::bind(&Kirby::OnDoorKeyUp, this);
			sitKey = nullptr;
			sitKeyEnd = nullptr;
			jumpKey = std::bind(&Kirby::DashJump, this);
			vKey = std::bind(&Kirby::UnequipAbility, this);
			update = std::bind(&Kirby::RunUpdate, this, std::placeholders::_1);
			onCollisionEnter = std::bind(&Kirby::MoveCollisionEnter, this, std::placeholders::_1);
			onCollisionStay = nullptr;
			break;
		case KirbyState::Balloon:
			cout << "state :: Balloon" << endl;
			moveKey = std::bind(&Kirby::BalloonMove, this, std::placeholders::_1);
			dashKey = nullptr;
			moveKeyEnd = nullptr;
			chargeKey = std::bind(&Kirby::ShotStar, this);
			chargeKeyContinue = nullptr;
			chargeKeyEnd = nullptr;
			doorKey = std::bind(&Kirby::OnDoorKeyDown, this);
			doorKeyEnd = std::bind(&Kirby::OnDoorKeyUp, this);
			sitKey = std::bind(&Kirby::Eat, this);
			sitKeyEnd = nullptr;
			jumpKey = std::bind(&Kirby::BalloonJump, this);
			vKey = std::bind(&Kirby::UnequipAbility, this);
			update = nullptr;
			onCollisionEnter = nullptr;
			onCollisionStay = nullptr;
			break;
		case KirbyState::BalloonMove:
			cout << "state :: BalloonMove" << endl;
			moveKey = nullptr;
			dashKey = nullptr;
			moveKeyEnd = std::bind(&Kirby::BalloonMoveEnd, this);
			chargeKey = std::bind(&Kirby::ShotStar, this);
			chargeKeyContinue = nullptr;
			chargeKeyEnd = nullptr;
			doorKey = std::bind(&Kirby::OnDoorKeyDown, this);
			doorKeyEnd = std::bind(&Kirby::OnDoorKeyUp, this);
			sitKey = std::bind(&Kirby::Eat, this);
			sitKeyEnd = nullptr;
			jumpKey = std::bind(&Kirby::BalloonJump, this);
			vKey = std::bind(&Kirby::UnequipAbility, this);
			update = std::bind(&Kirby::MoveUpdate, this, std::placeholders::_1);
			onCollisionEnter = nullptr;
			onCollisionStay = nullptr;
			break;
		case KirbyState::Eat:
			cout << "state :: Eat" << endl;
			moveKey = nullptr;
			dashKey = nullptr;
			moveKeyEnd = nullptr;
			chargeKey = nullptr;
			chargeKeyContinue = nullptr;
			chargeKeyEnd = nullptr;
			doorKey = nullptr;
			doorKeyEnd = nullptr;
			sitKey = nullptr;
			sitKeyEnd = nullptr;
			jumpKey = nullptr;
			vKey = nullptr;
			update = std::bind(&Kirby::EatUpdate, this, std::placeholders::_1);
			onCollisionEnter = nullptr;
			onCollisionStay = nullptr;
			break;
		case KirbyState::Falling:
			cout << "state :: Falling" << endl;
			moveKey = nullptr;
			dashKey = nullptr;
			moveKeyEnd = nullptr;
			chargeKey = nullptr;
			chargeKeyContinue = nullptr;
			chargeKeyEnd = nullptr;
			doorKey = std::bind(&Kirby::OnDoorKeyDown, this);
			doorKeyEnd = std::bind(&Kirby::OnDoorKeyUp, this);
			sitKey = nullptr;
			sitKeyEnd = nullptr;
			jumpKey = nullptr;
			vKey = std::bind(&Kirby::UnequipAbility, this);
			update = nullptr;
			onCollisionEnter = nullptr;
			onCollisionStay = nullptr;
			break;
		case KirbyState::Jump:
			cout << "state :: Jump" << endl;
			moveKey = std::bind(&Kirby::JumpMove, this, std::placeholders::_1);
			dashKey = nullptr;
			moveKeyEnd = std::bind(&Kirby::JumpMoveEnd, this);
			switch (ability)
			{
			case KirbyAbility::None:
				chargeKey = nullptr;
				chargeKeyContinue = std::bind(&Kirby::DoSuction, this);
				break;
			case KirbyAbility::Cutter:
				chargeKey = std::bind(&Kirby::CutterJumpAttack, this);
				chargeKeyContinue = nullptr;
				break;
			default:
				chargeKey = nullptr;
				chargeKeyContinue = nullptr;
				break;
			}
			doorKey = std::bind(&Kirby::OnDoorKeyDown, this);
			doorKeyEnd = std::bind(&Kirby::OnDoorKeyUp, this);
			sitKey = nullptr;
			sitKeyEnd = nullptr;
			jumpKey = std::bind(&Kirby::Fly, this);
			vKey = std::bind(&Kirby::UnequipAbility, this);
			update = std::bind(&Kirby::MoveUpdate, this, std::placeholders::_1);
			onCollisionEnter = std::bind(&Kirby::JumpCollisionEnter, this, std::placeholders::_1);
			onCollisionStay = nullptr;
			break;
		case KirbyState::BalloonJump:
			cout << "state :: BalloonJump" << endl;
			moveKey = std::bind(&Kirby::JumpMove, this, std::placeholders::_1);
			dashKey = nullptr;
			moveKeyEnd = std::bind(&Kirby::JumpMoveEnd, this);
			chargeKey = std::bind(&Kirby::ShotStar, this);
			chargeKeyContinue = nullptr;
			chargeKeyEnd = nullptr;
			doorKey = std::bind(&Kirby::OnDoorKeyDown, this);
			doorKeyEnd = std::bind(&Kirby::OnDoorKeyUp, this);
			sitKey = nullptr;
			sitKeyEnd = nullptr;
			jumpKey = nullptr;
			vKey = std::bind(&Kirby::UnequipAbility, this);
			update = std::bind(&Kirby::MoveUpdate, this, std::placeholders::_1);
			onCollisionEnter = std::bind(&Kirby::BalloonJumpCollisionEnter, this, std::placeholders::_1);
			onCollisionStay = nullptr;
			break;
		case KirbyState::BalloonFly:
			cout << "state :: BalloonFly" << endl;
			moveKey = std::bind(&Kirby::JumpMove, this, std::placeholders::_1);
			dashKey = nullptr;
			moveKeyEnd = std::bind(&Kirby::JumpMoveEnd, this);
			chargeKey = std::bind(&Kirby::ShotEmpty, this);
			chargeKeyContinue = std::bind(&Kirby::DoSuction, this);
			chargeKeyEnd = nullptr;
			doorKey = std::bind(&Kirby::OnDoorKeyDown, this);
			doorKeyEnd = std::bind(&Kirby::OnDoorKeyUp, this);
			sitKey = nullptr;
			sitKeyEnd = nullptr;
			jumpKey = std::bind(&Kirby::Fly, this);
			vKey = std::bind(&Kirby::UnequipAbility, this);
			update = std::bind(&Kirby::MoveUpdate, this, std::placeholders::_1);
			onCollisionEnter = std::bind(&Kirby::JumpCollisionEnter, this, std::placeholders::_1);
			onCollisionStay = nullptr;
			break;
		case KirbyState::DashJump:
			cout << "state :: DashJump" << endl;
			moveKey = nullptr;
			dashKey = nullptr;
			moveKeyEnd = std::bind(&Kirby::JumpMoveEnd, this);
			switch (ability)
			{
			case KirbyAbility::None:
				chargeKey = nullptr;
				chargeKeyContinue = std::bind(&Kirby::DoSuction, this);
				break;
			case KirbyAbility::Cutter:
				chargeKey = std::bind(&Kirby::CutterDashJumpAttack, this);
				chargeKeyContinue = nullptr;
				break;
			default:
				chargeKey = nullptr;
				chargeKeyContinue = nullptr;
				break;
			}
			chargeKeyEnd = nullptr;
			doorKey = std::bind(&Kirby::OnDoorKeyDown, this);
			doorKeyEnd = std::bind(&Kirby::OnDoorKeyUp, this);
			sitKey = nullptr;
			sitKeyEnd = nullptr;
			jumpKey = std::bind(&Kirby::Fly, this);
			vKey = std::bind(&Kirby::UnequipAbility, this);
			update = std::bind(&Kirby::RunUpdate, this, std::placeholders::_1);
			onCollisionEnter = std::bind(&Kirby::JumpCollisionEnter, this, std::placeholders::_1);
			onCollisionStay = nullptr;
			break;
		case KirbyState::TackleJump:
			cout << "state :: TackleJump" << endl;
			moveKey = nullptr;
			dashKey = nullptr;
			moveKeyEnd = nullptr;
			chargeKey = nullptr;
			chargeKeyContinue = nullptr;
			chargeKeyEnd = nullptr;
			doorKey = nullptr;
			doorKeyEnd = std::bind(&Kirby::OnDoorKeyUp, this);
			sitKey = nullptr;
			sitKeyEnd = nullptr;
			jumpKey = nullptr;
			vKey = std::bind(&Kirby::UnequipAbility, this);
			update = std::bind(&Kirby::MoveUpdate, this, std::placeholders::_1);
			onCollisionEnter = std::bind(&Kirby::JumpCollisionEnter, this, std::placeholders::_1);
			onCollisionStay = nullptr;
			break;
		case KirbyState::Collided:
			cout << "state :: Collided" << endl;
			moveKey = nullptr;
			dashKey = nullptr;
			moveKeyEnd = nullptr;
			chargeKey = nullptr;
			chargeKeyContinue = nullptr;
			chargeKeyEnd = nullptr;
			doorKey = nullptr;
			doorKeyEnd = std::bind(&Kirby::OnDoorKeyUp, this);
			sitKey = nullptr;
			sitKeyEnd = nullptr;
			jumpKey = nullptr;
			vKey = nullptr;
			update = std::bind(&Kirby::CollideUpdate, this, std::placeholders::_1);
			onCollisionEnter = nullptr;
			onCollisionStay = nullptr;
			break;
		case KirbyState::BalloonCollided:
			cout << "state :: BalloonCollided" << endl;
			moveKey = nullptr;
			dashKey = nullptr;
			moveKeyEnd = nullptr;
			chargeKey = nullptr;
			chargeKeyContinue = nullptr;
			chargeKeyEnd = nullptr;
			doorKey = nullptr;
			doorKeyEnd = std::bind(&Kirby::OnDoorKeyUp, this);
			sitKey = nullptr;
			sitKeyEnd = nullptr;
			jumpKey = nullptr;
			vKey = nullptr;
			update = std::bind(&Kirby::BalloonCollideUpdate, this, std::placeholders::_1);
			onCollisionEnter = nullptr;
			onCollisionStay = nullptr;
			break;
		case KirbyState::Tackle:
			cout << "state :: Tackle" << endl;
			moveKey = nullptr;
			dashKey = nullptr;
			moveKeyEnd = nullptr;
			chargeKey = nullptr;
			chargeKeyContinue = nullptr;
			chargeKeyEnd = nullptr;
			doorKey = nullptr;
			doorKeyEnd = std::bind(&Kirby::OnDoorKeyUp, this);
			sitKey = nullptr;
			sitKeyEnd = nullptr;
			jumpKey = nullptr;
			vKey = nullptr;
			update = std::bind(&Kirby::TackleUpdate, this, std::placeholders::_1);
			onCollisionEnter = std::bind(&Kirby::TackleCollisionEnter, this, std::placeholders::_1);
			onCollisionStay = nullptr;
			break;
		case KirbyState::Suction:
			cout << "state :: Suction" << endl;
			moveKey = nullptr;
			dashKey = nullptr;
			moveKeyEnd = nullptr;
			chargeKey = nullptr;
			chargeKeyContinue = nullptr;
			chargeKeyEnd = std::bind(&Kirby::SuctionEnd, this);
			doorKey = nullptr;
			doorKeyEnd = std::bind(&Kirby::OnDoorKeyUp, this);
			sitKey = nullptr;
			sitKeyEnd = nullptr;
			jumpKey = nullptr;
			vKey = nullptr;
			update = nullptr;
			onCollisionEnter = std::bind(&Kirby::SuctionCollisionEnter, this, std::placeholders::_1);
			onCollisionStay = nullptr;
			break;
		case KirbyState::Sit:
			cout << "state :: Sit" << endl;
			moveKey = nullptr;
			dashKey = nullptr;
			moveKeyEnd = nullptr;
			chargeKey = nullptr;
			chargeKeyContinue = nullptr;
			chargeKeyEnd = nullptr;
			doorKey = nullptr;
			doorKeyEnd = std::bind(&Kirby::OnDoorKeyUp, this);
			sitKey = nullptr;
			sitKeyEnd = std::bind(&Kirby::UnSit, this);
			jumpKey = std::bind(&Kirby::Tackle, this);
			vKey = std::bind(&Kirby::UnequipAbility, this);
			update = nullptr;
			onCollisionEnter = nullptr;
			onCollisionStay = std::bind(&Kirby::SitCollisionStay, this, std::placeholders::_1);
			break;
		case KirbyState::Shot:
			cout << "state :: Shot" << endl;
			moveKey = nullptr;
			dashKey = nullptr;
			moveKeyEnd = nullptr;
			chargeKey = nullptr;
			chargeKeyContinue = nullptr;
			chargeKeyEnd = nullptr;
			doorKey = nullptr;
			doorKeyEnd = std::bind(&Kirby::OnDoorKeyUp, this);
			sitKey = nullptr;
			sitKeyEnd = nullptr;
			jumpKey = nullptr;
			vKey = nullptr;
			update = std::bind(&Kirby::ShotUpdate, this, std::placeholders::_1);
			onCollisionEnter = nullptr;
			onCollisionStay = nullptr;
			break;
		case KirbyState::Door:
			cout << "state :: Door" << endl;
			moveKey = nullptr;
			dashKey = nullptr;
			moveKeyEnd = nullptr;
			chargeKey = nullptr;
			chargeKeyContinue = nullptr;
			chargeKeyEnd = nullptr;
			doorKey = nullptr;
			doorKeyEnd = std::bind(&Kirby::OnDoorKeyUp, this);
			sitKey = nullptr;
			sitKeyEnd = nullptr;
			jumpKey = nullptr;
			vKey = nullptr;
			update = std::bind(&Kirby::DoorUpdate, this, std::placeholders::_1);
			onCollisionEnter = nullptr;
			onCollisionStay = nullptr;
			break;
		case KirbyState::Wall:
			cout << "state :: Wall" << endl;
			moveKey = nullptr;
			dashKey = nullptr;
			moveKeyEnd = nullptr;
			chargeKey = nullptr;
			chargeKeyContinue = nullptr;
			chargeKeyEnd = nullptr;
			doorKey = nullptr;
			doorKeyEnd = nullptr;
			sitKey = nullptr;
			sitKeyEnd = nullptr;
			jumpKey = nullptr;
			vKey = nullptr;
			update = std::bind(&Kirby::WallUpdate, this, std::placeholders::_1);
			onCollisionEnter = nullptr;
			onCollisionStay = nullptr;
			break;
		case KirbyState::DanceReady:
			cout << "state :: DanceReady" << endl;
			moveKey = nullptr;
			dashKey = nullptr;
			moveKeyEnd = nullptr;
			chargeKey = nullptr;
			chargeKeyContinue = nullptr;
			chargeKeyEnd = nullptr;
			doorKey = nullptr;
			doorKeyEnd = nullptr;
			sitKey = nullptr;
			sitKeyEnd = nullptr;
			jumpKey = nullptr;
			vKey = nullptr;
			update = std::bind(&Kirby::DanceReadyUpdate, this, std::placeholders::_1);
			onCollisionEnter = nullptr;
			onCollisionStay = nullptr;
			break;
		case KirbyState::Dance:
			cout << "state :: Dance" << endl;
			moveKey = nullptr;
			dashKey = nullptr;
			moveKeyEnd = nullptr;
			chargeKey = nullptr;
			chargeKeyContinue = nullptr;
			chargeKeyEnd = nullptr;
			doorKey = nullptr;
			doorKeyEnd = nullptr;
			sitKey = nullptr;
			sitKeyEnd = nullptr;
			jumpKey = nullptr;
			vKey = nullptr;
			update = std::bind(&Kirby::DanceUpdate, this, std::placeholders::_1);
			onCollisionEnter = nullptr;
			onCollisionStay = nullptr;
			break;
		case KirbyState::Attack:
			cout << "state :: Attack" << endl;
			moveKey = nullptr;
			dashKey = nullptr;
			moveKeyEnd = nullptr;
			chargeKey = nullptr;
			chargeKeyContinue = nullptr;
			chargeKeyEnd = nullptr;
			doorKey = nullptr;
			doorKeyEnd = nullptr;
			sitKey = nullptr;
			sitKeyEnd = nullptr;
			jumpKey = nullptr;
			vKey = nullptr;
			update = std::bind(&Kirby::AttackUpdate, this, std::placeholders::_1);
			onCollisionEnter = nullptr;
			onCollisionStay = nullptr;
			break;
		case KirbyState::JumpAttack:
			cout << "state :: JumpAttack" << endl;
			moveKey = nullptr;
			dashKey = nullptr;
			moveKeyEnd = nullptr;
			chargeKey = nullptr;
			chargeKeyContinue = nullptr;
			chargeKeyEnd = nullptr;
			doorKey = nullptr;
			doorKeyEnd = nullptr;
			sitKey = nullptr;
			sitKeyEnd = nullptr;
			jumpKey = nullptr;
			vKey = nullptr;
			update = nullptr;
			onCollisionEnter = std::bind(&Kirby::JumpCollisionEnter, this, std::placeholders::_1);
			onCollisionStay = nullptr;
			break;
	}
}

void Kirby::Move(const float& axis)
{
	ChangeState(KirbyState::Move);
	moveAxisX = axis; 
	forwardTrigger->SetOffset({ -12.0f + 24.0f * moveAxisX, -24.0f });
	SetFlipX(axis > 0.0f ? true : false);
	animator->SetEvent("PressMove");
}

void Kirby::BalloonMove(const float& axis)
{
	ChangeState(KirbyState::BalloonMove);
	moveAxisX = axis;
	forwardTrigger->SetOffset({ -12.0f + 24.0f * moveAxisX, -24.0f });
	SetFlipX(axis > 0.0f ? true : false);
	animator->SetEvent("PressMove");
}

void Kirby::JumpMove(const float& axis)
{
	moveAxisX = axis;
	forwardTrigger->SetOffset({ -12.0f + 24.0f * moveAxisX, -24.0f });
	SetFlipX(axis > 0.0f ? true : false);
}


void Kirby::Dash(const float& axis)
{
	ChangeState(KirbyState::Dash);
	moveAxisX = axis;
	forwardTrigger->SetOffset({ -12.0f + 24.0f * moveAxisX, -24.0f });
	SetFlipX(axis > 0.0f ? true : false);
	animator->SetEvent("Run");
}

void Kirby::MoveEnd(const float& axis)
{
	if (axis == moveAxisX)
	{
		ChangeState(KirbyState::Idle);
		animator->SetEvent("Idle");
		moveAxisX = 0.0f;
	}
}

void Kirby::BalloonMoveEnd()
{
	ChangeState(KirbyState::Balloon);
	animator->SetEvent("Idle");
	moveAxisX = 0.0f;
}

void Kirby::JumpMoveEnd()
{
	moveAxisX = 0.0f;
}

void Kirby::EquipAbility()
{
	ability = keepInMouseAbility;
	keepInMouseAbility = KirbyAbility::None;
	sf::Texture* tex = Resources.GetTexture(abilityTextureIDs[(int)ability]);
	if (tex != nullptr)
	{
		SetTexture(*tex);
		SetOrigin(origin);
	}
}

void Kirby::UnequipAbility()
{
	if (ability != KirbyAbility::None)
	{
		ChangeState(KirbyState::Shot);
		animator->SetEvent("Shot");
		ability = KirbyAbility::None;
		keepInMouseAbility = KirbyAbility::None;
		ShotStar();
		sf::Texture* tex = Resources.GetTexture(abilityTextureIDs[(int)ability]);
		if (tex != nullptr)
		{
			SetTexture(*tex);
			SetOrigin(origin);
		}
	}
}

void Kirby::Jump()
{
	ChangeState(KirbyState::Jump);
	animator->SetEvent("PressJump");
	rigidbody->AddForce({ 0.0f, -150.0f });
}

void Kirby::Fly()
{
	ChangeState(KirbyState::BalloonFly);
	animator->SetEvent("PressJump");
	rigidbody->AddForce({ 0.0f, -100.0f });
}

void Kirby::DashJump()
{
	ChangeState(KirbyState::DashJump);
	animator->SetEvent("PressJump");
	rigidbody->AddForce({ 0.0f, -150.0f });
}

void Kirby::BalloonJump()
{
	ChangeState(KirbyState::BalloonJump);
	animator->SetEvent("PressJump");
	rigidbody->AddForce({ 0.0f, -150.0f });
}

void Kirby::Tackle()
{
	ChangeState(KirbyState::Tackle);
	animator->SetEvent("PressJump");
	rigidbody->AddForce({ 200.0f * GetScale().x, 0.0f});
	rigidbody->SetDrag(0.7f);
}

void Kirby::CutterAttack()
{
	ChangeState(KirbyState::Attack);
	if (forwardObjects.size() == 0)
	{
		animator->SetEvent("CutterAttack");
	}
	else
	{
		animator->SetEvent("CutterNearAttack");
	}
}
void Kirby::CutterDashAttack()
{
	ChangeState(KirbyState::Attack);
	animator->SetEvent("CutterDashAttack");
}
void Kirby::CutterJumpAttack()
{
	ChangeState(KirbyState::JumpAttack);
	animator->SetEvent("CutterSkyAttack");
}
void Kirby::CutterDashJumpAttack()
{
	ChangeState(KirbyState::JumpAttack);
	animator->SetEvent("CutterSkyDashAttack");
}


void Kirby::DoSuction()
{
	ChangeState(KirbyState::Suction);
	animator->SetEvent("AbilityKeyContinue");
	suction->SetActive(true);
}

void Kirby::SuctionEnd()
{
	ChangeState(KirbyState::Idle);
	animator->SetEvent("Idle");
	suction->SetActive(false);
}

void Kirby::Eat()
{
	ChangeState(KirbyState::Eat);
	animator->SetEvent("Eat");
	EquipAbility();
}

void Kirby::Sit()
{
	ChangeState(KirbyState::Sit);
	animator->SetEvent("PressSit");
	collider->SetRect({ 0.0f, 0.0f, 24.0f, 12.0f });
	collider->SetOffset({ -12.0f, -12.0f });
}

void Kirby::UnSit()
{
	ChangeState(KirbyState::Idle);
	animator->SetEvent("Idle");
	collider->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
	collider->SetOffset({ -12.0f, -24.0f });
}

void Kirby::OnDoorKeyDown()
{
	isDoorKeyPress = true;
}

void Kirby::OnDoorKeyUp()
{
	cout << "isDoorKeyPress = false" << endl;
	isDoorKeyPress = false;
}


void Kirby::Init()
{
	abilityTextureIDs.push_back("sprites/kirby/Class_Normal.png");
	abilityTextureIDs.push_back("sprites/kirby/Class_Cutter.png");
	abilityTextureIDs.push_back("sprites/kirby/Class_Beam.png");
	abilityTextureIDs.push_back("sprites/kirby/Class_Bomb.png");
	SpriteGO::Init();
	animator = (Animator*)AddComponent(new Animator(*this, "animations/Kirby/Kirby", "Idle"));
	collider = (BoxCollider*)AddComponent(new BoxCollider(*this));
	collider->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
	collider->SetOffset({ -12.0f, -24.0f });

	rigidbody = (RigidBody2D*)AddComponent(new RigidBody2D(*this));
	collider->SetRigidbody(rigidbody);



	ChangeState(KirbyState::Idle);

}

void Kirby::ShotStar() 
{
	animator->SetEvent("Shot");
	kirbyEffect->SetActive(true);
	kirbyEffect->SetPosition(GetPosition() - sf::Vector2f(0.0f, GetOrigin().y * 0.5f));
	kirbyEffect->StarShot(GetScale().x);
	((Animator*)kirbyEffect->GetComponent(ComponentType::Animation))->SetState("Star");
	keepInMouseAbility = KirbyAbility::None;
	rigidbody->SetVelocity({ 0.0f, 0.0f });
	ChangeState(KirbyState::Shot);
	moveAxisX = 0.0f;
}

void Kirby::ShotEmpty()
{
	animator->SetEvent("Shot");
	kirbyEffect->SetActive(true);
	kirbyEffect->SetPosition(GetPosition() - sf::Vector2f(0.0f, GetOrigin().y * 0.5f));
	kirbyEffect->EmptyShot(GetScale().x);
	((Animator*)kirbyEffect->GetComponent(ComponentType::Animation))->SetState("EmptyShot");
	keepInMouseAbility = KirbyAbility::None;
	rigidbody->SetVelocity({ 0.0f, 0.0f });
	ChangeState(KirbyState::Shot);
	moveAxisX = 0.0f;
	RigidBody2D* effectRig = (RigidBody2D*)kirbyEffect->GetComponent(ComponentType::RigidBody);
	effectRig->SetGravity(false);
	effectRig->SetVelocity({ GetScale().x * 300.0f, 0.0f });
}

void Kirby::Release()
{
	SpriteGO::Release();
}

void Kirby::Reset()
{
	SpriteGO::Reset();
	forwardTrigger = (KirbyForward*)SCENE_MANAGER.GetCurrentScene()->AddGameObject(new KirbyForward());
	forwardTrigger->physicsLayer = (int)PhysicsLayer::Player;
	forwardTrigger->SetKirby(this);


	SetOrigin({ 36.0f, 48.0f});
	Resources.GetAnimationClip("animations/Kirby/Kirby_Dance.csv")->frames[0].action =
		[this]() {
		SetFlipX(true);
	};
	Resources.GetAnimationClip("animations/Kirby/Kirby_Dance.csv")->frames[1].action =
		[this]() {
		rigidbody->SetVelocity({ 96.0f, -96.0f });
	};
	Resources.GetAnimationClip("animations/Kirby/Kirby_Dance.csv")->frames[7].action =
		[this]() {
		rigidbody->SetGravity(false);
		rigidbody->SetVelocity({ 0.0f, 0.0f });
	};
	Resources.GetAnimationClip("animations/Kirby/Kirby_Dance.csv")->frames[11].action =
		[this]() {
		rigidbody->SetGravity(true);
		rigidbody->SetVelocity({ -96.0f, -96.0f });
	};
	Resources.GetAnimationClip("animations/Kirby/Kirby_Dance.csv")->frames[16].action =
		[this]() {
		rigidbody->SetGravity(false);
		rigidbody->SetVelocity({ 0.0f, 0.0f });
	};
	Resources.GetAnimationClip("animations/Kirby/Kirby_Dance.csv")->frames[21].action =
		[this]() {
		rigidbody->SetGravity(true);
		rigidbody->SetMass(1.5f);
		rigidbody->SetVelocity({ 0.0f, 0.0f });
	};
	Resources.GetAnimationClip("animations/Kirby/Kirby_Dance.csv")->frames[35].action =
		[this]() {
		rigidbody->SetMass(1.0f);
		rigidbody->SetVelocity({ 0.0f, 0.0f });
	};
	Resources.GetAnimationClip("animations/Kirby/Kirby_Dance.csv")->frames[42].action =
		[this]() {
		rigidbody->SetMass(2.0f);
		rigidbody->SetVelocity({ -96.0f, -150.0f });
	};
	Resources.GetAnimationClip("animations/Kirby/Kirby_Dance.csv")->frames[66].action =
		[this]() {
		rigidbody->SetVelocity({ 0.0f, 0.0f });
	};
	Resources.GetAnimationClip("animations/Kirby/Kirby_Dance.csv")->frames[82].action =
		[this]() {
		rigidbody->SetVelocity({ 102.0f, -150.0f });
	};
	Resources.GetAnimationClip("animations/Kirby/Kirby_Dance.csv")->frames[105].action =
		[this]() {
		rigidbody->SetMass(1.5f);
		rigidbody->SetVelocity({ 48.0f, -48.0f });
	};
	Resources.GetAnimationClip("animations/Kirby/Kirby_Dance.csv")->frames[117].action =
		[this]() {
		rigidbody->SetMass(1.0f);
		rigidbody->SetVelocity({ 0.0f, 0.0f });
	};
	Resources.GetAnimationClip("animations/Kirby/Kirby_Dance.csv")->frames[127].action =
		[this]() {
		rigidbody->SetVelocity({ -48.0f, 0.0f });
	};
	Resources.GetAnimationClip("animations/Kirby/Kirby_Dance.csv")->frames[142].action =
		[this]() {
		rigidbody->SetVelocity({ 0.0f, 0.0f });
	};
}

void Kirby::Update(float dt)
{
	if (update != nullptr)
	{
		update(dt);
	}
	if (Input.GetKeyDown(Keyboard::Q))
	{
		StageClear();
	}
	SpriteGO::Update(dt);
}

void Kirby::DoorUpdate(float dt)
{
	actionTime += dt;
	if (actionTime >= 1.0f)
	{
		ChangeState(KirbyState::Idle);
	}
	else if (actionTime < 0.2f)
	{
	}
	else if (actionTime < 0.4f)
	{
		RectangleShapeGO* curtain = (RectangleShapeGO*)SCENE_MANAGER.GetCurrentScene()->FindGameObject("Curtain");
		curtain->SetFillColor(Utils::Lerp({ 0, 0, 0, 0 }, { 0, 0, 0, 255 }, actionTime * 5.0f - 1.0f, true));
	}
	else if (actionTime < 0.6f)
	{
		SetPosition(doorTarget);
		animator->SetEvent("Idle");
	}
	else if (actionTime < 0.8f)
	{
		SetPosition(doorTarget);
		RectangleShapeGO* curtain = (RectangleShapeGO*)SCENE_MANAGER.GetCurrentScene()->FindGameObject("Curtain");
		curtain->SetFillColor(Utils::Lerp({ 0, 0, 0, 255 }, { 0, 0, 0, 0 }, actionTime * 5.0f - 3.0f, true));
	}

}

void Kirby::MoveUpdate(float dt)
{
	SetPosition(GetPosition().x + moveAxisX * speed * dt, GetPosition().y);
}

void Kirby::RunUpdate(float dt)
{
	SetPosition(GetPosition().x + moveAxisX * runSpeed * dt, GetPosition().y);
}

void Kirby::TackleUpdate(float dt)
{
	if (abs(rigidbody->GetVelocity().x) < 80.0f)
	{
		animator->SetEvent("Idle");
		rigidbody->SetVelocity({ 0.0f, rigidbody->GetVelocity().y });
		rigidbody->SetDrag(0.0f);
		collider->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
		collider->SetOffset({ -12.0f, -24.0f });
		ChangeState(KirbyState::Idle);
	}
}

void Kirby::ShotUpdate(float dt)
{
	if (animator->GetClipName() != "BalloonShot")
	{
		ChangeState(KirbyState::Idle);
	}
}

void Kirby::WallUpdate(float dt)
{
	if (animator->GetClipName() != "Wall")
	{
		ChangeState(KirbyState::Idle);
	}
}


void Kirby::AttackUpdate(float dt)
{
	if (animator->GetClipName() == "Idle" || animator->GetClipName() == "TiltedIdleL" || animator->GetClipName() == "TiltedIdleR" )
	{
		ChangeState(KirbyState::Idle);
	}
}

void Kirby::CollideUpdate(float dt)
{
	if (rigidbody->GetVelocity().y == 0.0f && abs(rigidbody->GetVelocity().x) < 30.0f)
	{
		cout << "stop!!" << endl;
		animator->SetEvent("Idle");
		rigidbody->SetVelocity({ 0.0f, rigidbody->GetVelocity().y });
		rigidbody->SetDrag(0.0f);
		ChangeState(KirbyState::Idle);
	}
}

void Kirby::BalloonCollideUpdate(float dt)
{
	if (rigidbody->GetVelocity().y == 0.0f && abs(rigidbody->GetVelocity().x) < 30.0f)
	{
		cout << "stop!!" << endl;
		animator->SetEvent("Idle");
		rigidbody->SetVelocity({ 0.0f, rigidbody->GetVelocity().y });
		rigidbody->SetDrag(0.0f);
		ChangeState(KirbyState::Balloon);
	}
}

void Kirby::EatUpdate(float dt)
{
	if (animator->GetClipName() != "BalloonEat")
	{
		ChangeState(KirbyState::Idle);
	}
}

void Kirby::DanceReadyUpdate(float dt)
{
	actionTime += dt;
	if (actionTime >= 1.3f)
	{
		ChangeState(KirbyState::Dance);
		KirbyBackdancer* kirbyCopyL = new KirbyBackdancer();
		kirbyCopyL->SetKirby(this, { -84.0f, -48.0f });
		SCENE_MANAGER.GetCurrentScene()->AddGameObject(kirbyCopyL);
		kirbyCopyL->Reset();
		KirbyBackdancer* kirbyCopyR = new KirbyBackdancer();
		kirbyCopyR->SetKirby(this, { 12.0f, -48.0f });
		SCENE_MANAGER.GetCurrentScene()->AddGameObject(kirbyCopyR);
		kirbyCopyR->Reset();
		animator->SetState("Dance");
	}
}

void Kirby::DanceUpdate(float dt)
{
	/*actionTime += dt;
	if (actionTime >= 1.3f)
	{
		ChangeState(KirbyState::Dance);
	}*/
}

void Kirby::StageClear()
{
	ChangeState(KirbyState::DanceReady);
	actionTime = 0.0f;
	animator->SetState("DanceReady");
	animator->Play();
	SpriteEffect* kirbyStarL = new SpriteEffect(1.3f, "sprites/effects/KirbyEffect.png", "BackdancerStar");
	kirbyStarL->SetPosition(position + sf::Vector2f(-6.0f, -18.0f));
	kirbyStarL->SetScale({ 0.5f, 0.5f });
	Animation* aniL = (Animation*)kirbyStarL->AddComponent(new Animation(*kirbyStarL));
	aniL->SetClip(Resources.GetAnimationClip("animations/Effect/Star.csv"));
	aniL->Play();
	kirbyStarL->Reset();
	RigidBody2D* rigL = (RigidBody2D*)kirbyStarL->AddComponent(new RigidBody2D(*kirbyStarL));
	rigL->AddForce({ -40.0f, -120.0f });
	SCENE_MANAGER.GetCurrentScene()->AddGameObject(kirbyStarL);


	SpriteEffect* kirbyStarR = new SpriteEffect(1.3f, "sprites/effects/KirbyEffect.png", "BackdancerStar");
	kirbyStarR->SetPosition(position + sf::Vector2f(-6.0f, -18.0f));
	kirbyStarR->SetScale({ 0.5f, 0.5f });
	Animation* aniR = (Animation*)kirbyStarR->AddComponent(new Animation(*kirbyStarR));
	aniR->SetClip(Resources.GetAnimationClip("animations/Effect/Star.csv"));
	aniR->Play();
	kirbyStarR->Reset();
	RigidBody2D* rigR = (RigidBody2D*)kirbyStarR->AddComponent(new RigidBody2D(*kirbyStarR));
	rigR->AddForce({ 40.0f, -120.0f });
	SCENE_MANAGER.GetCurrentScene()->AddGameObject(kirbyStarR);
}

void Kirby::Draw(sf::RenderWindow& window)
{
	SpriteGO::Draw(window);
}

void Kirby::Damage(const int& damage, const float hitAxisX)
{
	if (state == KirbyState::Tackle || state == KirbyState::Suction || state == KirbyState::Eat)
	{
		return;
	}
	//hp -= damage;
	if (state == KirbyState::Balloon || state == KirbyState::BalloonFly || state == KirbyState::BalloonJump || state == KirbyState::BalloonMove)
	{
		ChangeState(KirbyState::BalloonCollided);
		rigidbody->SetDrag(0.99f);
	}
	else
	{
		ChangeState(KirbyState::Collided);
		rigidbody->SetDrag(0.7f);
	}
	animator->SetEvent("Hit");
	collider->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
	collider->SetOffset({ -12.0f, -24.0f });
	moveAxisX = -GetScale().x;
	rigidbody->SetVelocity({ hitAxisX * 100.0f, 0.0f });
}

void Kirby::SetInMouseType(const KirbyAbility& ability)
{
	if (keepInMouseAbility != KirbyAbility::None)
	{
		return;
	}
	keepInMouseAbility = ability;
	cout << "keepInMouseAbility!!" << (int)keepInMouseAbility << endl;
	ChangeState(KirbyState::Balloon);
	animator->SetEvent("Balloon");
}

void Kirby::OnCollisionEnter(Collider* col)
{
	if (onCollisionEnter != nullptr)
	{
		onCollisionEnter(col);
	}

	if (col->GetGameObject().HasTag("Mob"))
	{
		((Mob*)&col->GetGameObject())->Damage(10.0f, col->GetGameObject().GetPosition().x < GetPosition().x ? -1.0f : 1.0f);
		RigidBody2D* rig = ((RigidBody2D*)col->GetGameObject().GetComponent(ComponentType::RigidBody));
	}
}

void Kirby::MoveCollisionEnter(Collider* col)
{
	if (col->GetGameObject().GetName() == "Ground" && abs(col->GetNormal(position + sf::Vector2f(0.0f, -12.0f)).x) > 0.8f)
	{
		ChangeState(KirbyState::Wall);
		animator->SetEvent("Wall");
	}
}

void Kirby::JumpCollisionEnter(Collider* col)
{
	if ((col->GetGameObject().GetName() == "Ground" || col->GetGameObject().GetName() == "ThroughtableGround") && rigidbody->GetVelocity().y >= 0.0f)
	{
		ChangeState(KirbyState::Idle);
		animator->SetEvent("Idle");
		rigidbody->SetDrag(0.0f);
		rigidbody->SetVelocity({ 0.0f, 0.0f });
		moveAxisX = 0.0f;
	}
}

void Kirby::TackleCollisionEnter(Collider * col)
{
	if (col->GetRotationOffset() + col->GetGameObject().GetRotation() == 0.0f && !col->IsTrigger() && col->GetCenter().y < position.y)
	{
		ChangeState(KirbyState::TackleJump);
		animator->SetEvent("Hit");
		rigidbody->SetDrag(0.0f);
		collider->SetRect({ 0.0f, 0.0f, 24.0f, 24.0f });
		collider->SetOffset({ -12.0f, -24.0f });
		moveAxisX = -GetScale().x;
		rigidbody->SetVelocity({ 0.0f, -100.0f });
	}
}

void Kirby::CutterCollisionEnter(Collider* col)
{
	if (col->GetGameObject().HasTag("CutterEffect"))
	{
		animator->SetEvent("CutterCatch");
	}
}

void Kirby::BalloonJumpCollisionEnter(Collider* col)
{
	if ((col->GetGameObject().GetName() == "Ground" || col->GetGameObject().GetName() == "ThroughtableGround") && rigidbody->GetVelocity().y >= 0.0f)
	{
		ChangeState(KirbyState::Balloon);
		animator->SetEvent("Idle");
		rigidbody->SetDrag(0.0f);
		rigidbody->SetVelocity({ 0.0f, 0.0f });
	}
}

void Kirby::SuctionCollisionEnter(Collider* col)
{
	if (col->GetGameObject().HasTag("Suctionable"))
	{
		Mob* suctionable = (Mob*)&col->GetGameObject();
		/////
		suctionable->SetActive(false);
		suction->SetActive(false);
	}
}

void Kirby::OnCollisionStay(Collider* col)
{
	if (col->GetGameObject().GetName() == "Ground" && col->GetRotationOffset() + col->GetGameObject().GetRotation() != 0.0f)
	{
		if (col->GetNormal(position + sf::Vector2f(0.0f, -12.0f)).x * scale.x < 0.0f)
		{
			animator->SetEvent("TiltedL");
		}
		else
		{
			animator->SetEvent("TiltedR");
		}
	}
	else
	{
		animator->SetEvent("NoTilted");
	}

	if (onCollisionStay != nullptr)
	{
		onCollisionStay(col);
	}

	if (col->GetGameObject().GetName() == "Door")
	{
		if (state != KirbyState::Door && isDoorKeyPress)
		{
			Door* door = (Door*)&col->GetGameObject();
			ChangeState(KirbyState::Door);
			animator->SetEvent("Door");
			actionTime = 0.0f;
			doorTarget = door->GetMovePosition();
			isDoorKeyPress = false;
		}
	}
}

void Kirby::SitCollisionStay(Collider* col)
{
	if (col->GetGameObject().GetName() == "ThroughtableGround")
	{
		//cout << "Kirby On!!" << endl;
		((Collider*)col->GetGameObject().GetComponent(ComponentType::Collider))->SetTrigger(true);
	}
}

void Kirby::AddNearUnit(GameObject* enemy) 
{ 
	for (auto forwardObject : forwardObjects)
	{
		if (enemy == forwardObject)
		{
			return;
		}
	}
	forwardObjects.push_back(enemy); 
}

void Kirby::RemoveNearUnit(GameObject* enemy) 
{
	for (auto forwardObject : forwardObjects)
	{
		if (enemy == forwardObject)
		{
			forwardObjects.remove(enemy);
			return;
		}
	}
}