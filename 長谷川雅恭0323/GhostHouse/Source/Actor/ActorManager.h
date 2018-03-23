#ifndef _ACTOR_MANAGER_H_
#define _ACTOR_MANAGER_H_
#include "Actor.h"
#include "ActorPtr.h"
#include "CollideActor.h"
#include "CollideActorPtr.h"
#include <unordered_map>

enum class ActorGroup;
class Renderer;

class ActorManager
{
public:
	ActorManager();

	void Initialize();
	void Update(float deltaTime);
	void EffectUpdate(float deltaTime);
	void Draw(const bool is_shadow, Renderer& m_renderer)const;

	//�����蔻��Ȃ��̃A�N�^�[�p
	void AddActor(ActorGroup group, const ActorPtr& actor);
	//�����蔻�肪����A�N�^�[�p
	void AddCollideActor(ActorGroup group, const CollideActorPtr& actor);

	ActorPtr FindActor(const std::string& name);

	//�R�s�[�֎~
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator=(const ActorManager& other) = delete;

private:
	void Collide();


private:
	Actor m_Root;
	std::unordered_map<ActorGroup, ActorPtr> m_Actors;
	std::unordered_map<ActorGroup, CollideActorPtr> m_CollideActors;


};


#endif // !_ACTOR_MANAGER_H_
