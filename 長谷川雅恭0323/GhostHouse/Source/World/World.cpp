#include "World.h"
#include "../GameObject/Field/Field.h"
#include"../Utility/Renderer/Renderer.h"

World::World()
	: m_Manager{}
	, m_UImanager{}
	, m_Field{ nullptr }
	, m_Camera{ nullptr }
{
}

void World::Update(float deltaTime)
{
	m_Manager.Update(deltaTime);
	m_UImanager.update(deltaTime);
	m_Camera->Update(deltaTime);
}

void World::DirectionUpdate(float deltaTime)
{
	m_Manager.EffectUpdate(deltaTime);
	m_Camera->Update(deltaTime);
}

void World::Draw(bool is_shadow, Renderer& renderer) const
{
	m_Camera->Draw(is_shadow, renderer);
	m_Field->Draw(is_shadow, renderer);
	m_Manager.Draw(is_shadow, renderer);
}

void World::Draw_UI()
{
	m_UImanager.draw();
}

ActorPtr World::FindActor(const std::string name)
{
	return m_Manager.FindActor(name);
}

UIPtr World::FindUI(const std::string name)
{
	return m_UImanager.find_UI(name);
}

void World::AddActor(ActorGroup group, const ActorPtr & actor)
{
	m_Manager.AddActor(group, actor);
}

void World::AddUI(UIGroup group, const UIPtr & ui)
{
	m_UImanager.add_ui(group, ui);
}

void World::AddCollideActor(ActorGroup group, const CollideActorPtr & actor)
{
	m_Manager.AddCollideActor(group, actor);
}

void World::AddCamera(const ActorPtr & camera)
{
	m_Camera = camera;
}

void World::AddField(const FieldPtr & field)
{
	m_Field = field;
}

void World::SetNextField(FieldName name)
{
	m_Field->SetNextField(name);
}

FieldPtr World::GetField() const
{
	return m_Field;
}
