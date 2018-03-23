//�v���C���[��ԊǗ��N���X
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


	//�ړ��͎擾
	GSvector3 GetVelocity(float deltaTime);
	//�s��擾
	GSmatrix4 GetRotate()const;
	//���x�擾
	float GetSpeed()const;
	//�ړ�����
	void Move(float deltaTime);
	//�L�����N�^�[�̉�]
	void Rotate(float deltaTime);
	//�E�X�e�B�b�N�ł̌�������
	bool RightStick(float deltaTime);
	//�ړ��������������
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