#ifndef _ACTOR_H_
#define _ACTOR_H_
#include <forward_list>
#include <gslib.h>
#include <string>
#include <functional>
#include "../Collide/Shape.h"
#include "ActorPtr.h"

class CollideActor;
class Renderer;
class IWorld;

class Actor
{
public:
	//�R���X�g���N�^
	Actor() = default;
	Actor(IWorld& world, std::string name, GSvector3 position);

	//�f�X�g���N�^
	virtual ~Actor() {}


	//�X�V
	void Update(float deltaTime);
	//�`��
	void Draw(const bool is_shadow, Renderer& renderer)const;


	//�ʒu�̎擾
	GSvector3 GetPosition()const;

	//���O�̎擾
	std::string GetName()const;

	//�ϊ��s����擾
	GSmatrix4 GetPose()const;

	//�s��̎擾
	GSmatrix4 GetRotate()const;


	//����ł��邩
	bool IsDead()const;

	//���S������
	void Dead();

	void HideOn();
	void HideOff();

	bool IsHide();

	//�q�̏���
	void EachChildren(std::function<void(Actor&)>fn);
	//const��
	void EachChildren(std::function<void(const Actor&)>fn)const;

	//�q�̌���
	ActorPtr FindChildren(const std::string& name);
	ActorPtr FindChildren(std::function<bool(const Actor&)>fn);

	//�q�̒ǉ�
	void AddChild(const ActorPtr& child);

	//�q�̍폜
	void RemoveChildren(std::function<bool(Actor& other)>fn);
	void RemoveChildren();

	//�q������
	void ClearChildren();


protected:
	//�h����̍X�V�A�`��
	virtual void OnUpdate(float deltaTime) {}
	virtual void OnDraw(bool is_shadow, Renderer& renderer)const {}


protected:
	std::forward_list<ActorPtr> m_Children;


protected:
	GSvector3	m_Position{ 0.0f,0.0f,0.0f };
	GSmatrix4	m_Rotate{ GS_MATRIX4_IDENTITY };
	std::string m_Name{ "None" };
	IWorld*		p_World{ nullptr };
	bool		m_Dead{ false };
	bool		m_Hide{ false };
};

#endif // !_ACTOR_H_
