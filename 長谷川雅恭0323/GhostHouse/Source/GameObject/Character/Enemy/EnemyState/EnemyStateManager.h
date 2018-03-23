#ifndef _ENEMY_STATE_MANAGER_H_
#define _ENEMY_STATE_MANAGER_H_
#include <gslib.h>
#include <unordered_map>
#include "EnemyStateBasePtr.h"

enum class EnemyStateName;
class CollideActor;
class ModelBase;
class IWorld;
class Actor;

class EnemyStateManager
{
public:
	//コンストラクタ
	EnemyStateManager(CollideActor& player, ModelBase& me, IWorld& world);

	//更新
	void Update(float deltaTime);
	//衝突中の更新
	void Collide(CollideActor & other);
	//描画
	void Draw()const;


	//位置取得
	GSvector3 GetPosition();
	//行列取得
	GSmatrix4 GetRotate()const;

	//移動する方向に回転させる
	void Rotate(float deltaTime);

	//移動させる
	void Move(float deltaTime);

	//ふわふわ上下移動させる
	void Fly(float deltaTime);

	//移動力を設定
	void SetVelocity(GSvector3 velocity);
	//位置を設定
	void SetPosition(GSvector3 position);
	//任意に移動させる
	void OnMove(GSvector3 velocity, float deltaTime);
	//移動速度を上げる
	void SpeedUp(float plus, float max, float deltaTime);
	//移動速度をセット
	void SetSpeed(float speed);
	//移動速度を取得
	float GetSpeed()const;

	//ワールドを取得
	IWorld* GetWorld();

	Actor* GetMark();

	//次のシーンをセット
	void SetNextState(const EnemyStateName& next);

	//時間を取得
	float GetTimer()const;
	//タイマーを0にする
	void TimerReset();

	//状態の追加
	void AddState(EnemyStateName name, const EnemyStateBasePtr& state, CollideActor& player, ModelBase& me);

	//状態を設定
	void SetUp(EnemyStateName name);

	int GetMotionID()const;
	void SetMotionID(int id);



private:
	void Change();


private:
	using States = std::unordered_map<EnemyStateName, EnemyStateBasePtr>;
	States	m_States;
	EnemyStateBasePtr m_CurrentState;
	EnemyStateName m_CurrentStateName;

	GSvector3 m_Position;
	GSvector3 m_Velocity;
	GSmatrix4 m_Rotate;
	float m_Speed;

	IWorld* p_World;

	EnemyStateName m_NextState;

	Actor* p_Mark;



	float m_Timer;

	float m_SwingTimer;
	float m_LerpTimer;

	int m_MotionID;

};

#endif // !_ENEMY_STATE_MANAGER_H_
