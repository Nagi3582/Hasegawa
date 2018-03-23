//プレイヤー状態管理クラス
#ifndef _PLAYER_MANAGER_H_
#define _PLAYER_MANAGER_H_
#include <unordered_map>
#include <gslib.h>
#include "PlayerState/PlayerStateBasePtr.h"

enum class PlayerState;
class CollideActor;
class IWorld;
class ItemManager;
class Player;
class Renderer;
class OperationManager;
struct SceneInfo;

class PlayerManager
{
public:
	PlayerManager(IWorld& world, Player& player, ItemManager& item, Renderer& renderer, SceneInfo& info);

	void SetUp(Renderer& renderer);
	void SetUpOperation(Renderer& renderer, OperationManager& operationManager);

	void Update(float deltaTime);
	void Collide(CollideActor& other);


	//移動力取得
	GSvector3 GetVelocity(float deltaTime);
	//行列取得
	GSmatrix4 GetRotate()const;
	//速度取得
	float GetSpeed()const;
	//移動する
	void Move(float deltaTime);
	//キャラクターの回転
	void Rotate(float deltaTime);
	//右スティックでの向き操作
	bool RightStick(float deltaTime);
	//移動する方向を向く
	bool FaceForward(float deltaTime);

	void SpeedUp(float plus, float max, float deltaTime);

	void SetSpeed(float speed);

	int GetMotionID()const;
	void SetMotionID(int id);

	float GetTimer()const;
	void ResetTimer();

	void SetNextState(PlayerState state);


	Player* GetPlayer()const;

	PlayerState GetState()const;

	ItemManager& get_item();

	void SetDamageTime(int time);

	float GetDamageTime()const;


private:
	void Change();
	void WalkSE();


private:
	using StateList = std::unordered_map<PlayerState, PlayerStateBasePtr>;
	StateList m_States;
	PlayerStateBasePtr m_CurrentState;
	PlayerState m_CurrentStateName;
	PlayerState m_NextStateName;
	float m_Timer;

	GSvector3 m_Velocity;
	GSmatrix4 m_Rotate;
	float m_Speed;

	Player* p_Player;
	IWorld* p_World;
	ItemManager* p_ItemManager;
	SceneInfo& m_Info;

	float m_LerpTimer;
	const float LERP_TIME;

	int m_MotionID;

	float m_DamageTime;

};

#endif // !_PLAYER_MANAGER_H_