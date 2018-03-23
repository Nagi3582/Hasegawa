#ifndef _COLLIDE_ACTOR_H_
#define _COLLIDE_ACTOR_H_
#include "Actor.h"
#include "CollideActorPtr.h"
#include "../GameObject/Light/LightColor.h"

class Shape;

//�����蔻�莝���A�N�^�[
class CollideActor :public Actor
{
public:
	//�R���X�g���N�^
	CollideActor() = default;
	CollideActor(IWorld& world, std::string name, GSvector3 position, Shape* shape, LightColor color = LightColor::None);

	//�f�X�g���N�^
	~CollideActor();


	//�Փ˒��̍X�V
	void Collide(CollideActor& other);
	//�h����̏Փ˒��̍X�V
	virtual void OnCollide(CollideActor& other) {};
	//�q�̏Փ�
	void CollideChildren(CollideActor& other);
	//�Փ˂��Ă��邩
	bool IsCollide(const CollideActor& other);

	//�q���m�̏���CollideActor��
	void EachCollideChildren(std::function<void(CollideActor&)>fn);
	//const��
	void EachCollideChildren(std::function<void(const CollideActor&)>fn)const;


	//�q�̒ǉ�
	void AddCollideChild(const CollideActorPtr& child);

	//�q�̍폜
	void RemoveCollideChildren(std::function<bool(CollideActor& other)>fn);
	void RemoveCollideChildren();

	//�����蔻��̎擾
	Shape* GetBody()const;

	LightColor GetColor()const;


private:
	std::forward_list<CollideActorPtr> m_CollideChildren;

protected:
	Shape* p_Body{ nullptr };
	LightColor m_Color{ LightColor::None };

};


#endif // !_COLLIDE_ACTOR_H_
