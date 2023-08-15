#pragma once
#include "Playable.h"
#include <Animator.h>
#include <BoxCollider.h>
#include <RigidBody2D.h>
#include <Suction.h>

enum class KirbyState
{
	Idle,
	Move,
	Dash,
	Balloon,
	BalloonMove,
	BalloonFly,
	Eat,
	Falling,
	Jump,
	DashJump,
	TackleJump,
	BalloonJump,
	Collided,
	Tackle,
	Suction,
	Sit,
	Shot,
};


class Kirby : public Playable
{
protected:
	KirbyAbility ability;
	KirbyState state;
	vector<string> abilityTextureIDs;

    Animator* animator;
	BoxCollider* collider;
	RigidBody2D* rigidbody;

	float moveAxisX = 0.0f;
	float speed = 30.0f;
	float runSpeed = 60.0f;

	Suction* suction;

	KirbyAbility keepInMouseAbility;

	SpriteGO* starEffect;
	
	function<void(const float&)> moveKey;
	function<void(const float&)> dashKey;
	function<void()> moveKeyEnd;
	function<void()> chargeKey;
	function<void()> chargeKeyContinue;
	function<void()> chargeKeyEnd;
	function<void()> sitKey;
	function<void()> sitKeyEnd;
	function<void()> jumpKey;
	function<void()> vKey;
	function<void(float)> update;
public:
	Kirby(const std::string textureID = "", const std::string& name = "") : Playable(textureID, name) {};

	void ChangeState(const KirbyState& state);

#pragma region KeyInput
	// Arrow
	virtual void MoveKey(const float& axisX) override;
	virtual void DashKey(const float& axisX) override;
	virtual void MoveKeyEnd() override;

	// Down
	virtual void SitKey() override;
	virtual void SitKeyEnd() override;

	// X
	virtual void ChargeKey() override;
	virtual void ChargeKeyContinue() override;
	virtual void ChargeKeyEnd() override;

	// C
	virtual void JumpKey() override;

	// V
	virtual void VKey() override;
#pragma endregion


#pragma region Actions
	// Arrow
	void Move(const float& axis);
	void BalloonMove(const float& axis);
	void JumpMove(const float& axis);
	void Dash(const float& axis);
	void MoveEnd();
	void BalloonMoveEnd();
	void JumpMoveEnd();


	// ArrowDown
	void Eat();
	void Sit();
	void UnSit();

	// X
	void ShotStar();
	void DoSuction();
	void SuctionEnd();

	// C
	void Jump();
	void Fly();
	void DashJump();
	void BalloonJump();
	void Tackle();

	// V
	void UnequipAbility();
#pragma endregion

	void SetSuction(Suction* suction) { this->suction = suction; }
	void SetStarEffect(SpriteGO* starEffect) { this->starEffect = starEffect; }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	void MoveUpdate(float dt);
	void RunUpdate(float dt);
	void TackleUpdate(float dt);

	void ShotUpdate(float dt);

	virtual void Draw(sf::RenderWindow& window) override;
	virtual void OnCollisionEnter(Collider* col) override;
	virtual void OnCollisionStay(Collider* col) override;

};

