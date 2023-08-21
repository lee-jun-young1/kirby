#pragma once
#include "Playable.h"
#include <Animator.h>
#include <BoxCollider.h>
#include <RigidBody2D.h>
#include <Suction.h>
#include <KirbyEffect.h>
#include <KirbyForward.h>
#include <EffectPool.h>

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
	BalloonCollided,
	Tackle,
	Suction,
	Sit,
	Shot,
	Door,
	Wall,
	DanceReady,
	Dance,
	Attack, 
	JumpAttack,
	MeleeAttack,
	JumpMeleeAttack,
};


class Kirby : public Playable
{
protected:
	KirbyAbility ability = KirbyAbility::None;
	KirbyState state;
	vector<string> abilityTextureIDs;

    Animator* animator;
	BoxCollider* collider;
	RigidBody2D* rigidbody;

	float moveAxisX = 0.0f;
	float speed = 75.0f;
	float runSpeed = 150.0f;

	float actionTime = 0.0f;

	bool isDoorKeyPress = false;

	bool isDownKeyPress = false;
	sf::Vector2f doorTarget;

	Suction* suction;

	KirbyAbility keepInMouseAbility = KirbyAbility::None;

	KirbyEffect* kirbyEffect;
	EffectPool* effectPool;
	
	function<void(const float&)> moveKey;
	function<void(const float&)> dashKey;
	function<void(const float&)> moveKeyEnd;
	function<void()> chargeKey;
	function<void()> chargeKeyContinue;
	function<void()> chargeKeyEnd;
	function<void()> sitKey;
	function<void()> sitKeyEnd;
	function<void()> doorKey;
	function<void()> doorKeyEnd;
	function<void()> jumpKey;
	function<void()> vKey;
	function<void(float)> update;
	function<void(Collider*)> onCollisionEnter;
	function<void(Collider*)> onCollisionEnterByAbility;
	function<void(Collider*)> onCollisionStay;


	KirbyForward* forwardTrigger;
	list<GameObject*> forwardObjects;
public:
	Kirby(const std::string textureID = "", const std::string& name = "") : Playable(textureID, name) {};

	void ChangeState(const KirbyState& state);

#pragma region KeyInput
	// Arrow
	virtual void MoveKey(const float& axisX) override;
	virtual void DashKey(const float& axisX) override;
	virtual void MoveKeyEnd(const float& axisX) override;

	// Down
	virtual void SitKey() override;
	virtual void SitKeyEnd() override;

	// Up
	virtual void DoorKey() override;
	virtual void DoorKeyEnd() override;

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
	void MoveEnd(const float& axis);
	void BalloonMoveEnd();
	void JumpMoveEnd();

	void EquipAbility();


	// Arrow Down
	void Eat();
	void Sit();
	void UnSit();
	void OnDownKeyDown();
	void OnDownKeyUp();

	// Arrow Up
	void OnDoorKeyDown();
	void OnDoorKeyUp();

	// X
	void ShotStar();
	void ShotEmpty();
	void DoSuction();
	void SuctionEnd();

	void CutterAttack();
	void BombAttack();
	void CutterDashAttack();

	void CutterJumpAttack();

	void CutterDashJumpAttack();

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
	void SetEffect(KirbyEffect* starEffect) { this->kirbyEffect = starEffect; }
	void SetEffectPool(EffectPool* effectPool) { this->effectPool = effectPool; }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	void DoorUpdate(float dt);
	void MoveUpdate(float dt);
	void RunUpdate(float dt);
	void TackleUpdate(float dt);

	void ShotUpdate(float dt);

	void WallUpdate(float dt); 
	void AttackUpdate(float dt);

	void NearAttackUpdate(float dt);
	void NearJumpAttackUpdate(float dt);

	void CollideUpdate(float dt);
	void BalloonCollideUpdate(float dt);

	void EatUpdate(float dt); 
	
	void DanceReadyUpdate(float dt); 
	void DanceUpdate(float dt); 
	
	void StageClear();

	virtual void Draw(sf::RenderWindow& window) override;
	void Damage(const int& damage, const float hitAxisX);
	void SetInMouseType(const KirbyAbility& ability);
	virtual void OnCollisionEnter(Collider* col) override;

	void MoveCollisionEnter(Collider* col);
	void JumpCollisionEnter(Collider* col);
	void BalloonJumpCollisionEnter(Collider* col);
	void SuctionCollisionEnter(Collider* col); 
	void TackleCollisionEnter(Collider* col);
	void CutterCollisionEnter(Collider* col);

	virtual void OnCollisionStay(Collider* col) override;

	void SitCollisionStay(Collider* col);

	void AddNearUnit(GameObject* enemy);
	void RemoveNearUnit(GameObject* enemy);

};

