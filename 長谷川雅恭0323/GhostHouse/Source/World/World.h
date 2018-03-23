#ifndef _WORLD_H_
#define _WORLD_H_
#include "IWorld.h"
#include "../Actor/ActorPtr.h"
#include "../Actor/ActorManager.h"
#include"../UI/UIManager.h"
#include "../GameObject/Field/FieldPtr.h"
#include <string>

class World :public IWorld
{
public:
	World();

	void Update(float deltaTime);
	void DirectionUpdate(float deltaTime);
	void Draw(bool is_shadow, Renderer& m_renderer)const;
	void Draw_UI();
	virtual ActorPtr FindActor(const std::string name)override;
	virtual UIPtr FindUI(const std::string) override;

	virtual void AddActor(ActorGroup group, const ActorPtr& actor)override;
	virtual void AddUI(UIGroup group, const UIPtr & ui) override;

	virtual void AddCollideActor(ActorGroup group, const CollideActorPtr& actor)override;

	virtual void AddCamera(const ActorPtr& camera);

	virtual void AddField(const FieldPtr& field);

	virtual void SetNextField(FieldName name)override;

	virtual FieldPtr GetField()const override;


	World(const World& other) = delete;
	World operator=(const World& other) = delete;

private:
	ActorManager m_Manager;
	UIManager m_UImanager;
	FieldPtr m_Field;
	ActorPtr m_Camera;

};

#endif // !_WOALD_H_
