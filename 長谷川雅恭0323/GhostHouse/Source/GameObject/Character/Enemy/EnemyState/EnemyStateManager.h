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
	//�R���X�g���N�^
	EnemyStateManager(CollideActor& player, ModelBase& me, IWorld& world);

	//�X�V
	void Update(float deltaTime);
	//�Փ˒��̍X�V
	void Collide(CollideActor & other);
	//�`��
	void Draw()const;


	//�ʒu�擾
	GSvector3 GetPosition();
	//�s��擾
	GSmatrix4 GetRotate()const;

	//�ړ���������ɉ�]������
	void Rotate(float deltaTime);

	//�ړ�������
	void Move(float deltaTime);

	//�ӂ�ӂ�㉺�ړ�������
	void Fly(float deltaTime);

	//�ړ��͂�ݒ�
	void SetVelocity(GSvector3 velocity);
	//�ʒu��ݒ�
	void SetPosition(GSvector3 position);
	//�C�ӂɈړ�������
	void OnMove(GSvector3 velocity, float deltaTime);
	//�ړ����x���グ��
	void SpeedUp(float plus, float max, float deltaTime);
	//�ړ����x���Z�b�g
	void SetSpeed(float speed);
	//�ړ����x���擾
	float GetSpeed()const;

	//���[���h���擾
	IWorld* GetWorld();

	Actor* GetMark();

	//���̃V�[�����Z�b�g
	void SetNextState(const EnemyStateName& next);

	//���Ԃ��擾
	float GetTimer()const;
	//�^�C�}�[��0�ɂ���
	void TimerReset();

	//��Ԃ̒ǉ�
	void AddState(EnemyStateName name, const EnemyStateBasePtr& state, CollideActor& player, ModelBase& me);

	//��Ԃ�ݒ�
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
