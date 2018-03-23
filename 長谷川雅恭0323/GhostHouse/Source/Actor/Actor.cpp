#include "Actor.h"
#include <algorithm>

Actor::Actor(IWorld & world, std::string name, GSvector3 position)
	: p_World{ &world }
	, m_Name{ name }
	, m_Position{ position }
	, m_Rotate{ GS_MATRIX4_IDENTITY }
	, m_Dead{ false }
	, m_Hide{ false }
{
}

void Actor::Update(float deltaTime)
{
	OnUpdate(deltaTime);
	EachChildren([&](Actor& child)
	{child.Update(deltaTime); });
}

void Actor::Draw(const bool is_shadow, Renderer& renderer) const
{
	if (m_Hide == true)return;
	OnDraw(is_shadow, renderer);
	EachChildren([&](const Actor& child)
	{child.Draw(is_shadow, renderer); });
}

GSvector3 Actor::GetPosition() const
{
	return m_Position;
}

std::string Actor::GetName() const
{
	return m_Name;
}

GSmatrix4 Actor::GetPose() const
{
	return GSmatrix4(m_Rotate).setPosition(m_Position);
}

GSmatrix4 Actor::GetRotate() const
{
	return m_Rotate;
}

bool Actor::IsDead() const
{
	return m_Dead;
}

void Actor::Dead()
{
	m_Dead = true;
}

void Actor::HideOn()
{
	m_Hide = true;
}

void Actor::HideOff()
{
	m_Hide = false;
}

bool Actor::IsHide()
{
	return m_Hide;
}

void Actor::EachChildren(std::function<void(Actor&)> fn)
{
	std::for_each(m_Children.begin(), m_Children.end(),
		[&](const ActorPtr& child)
	{
		fn(*child);
	});
}

void Actor::EachChildren(std::function<void(const Actor&)> fn) const
{
	std::for_each(m_Children.begin(), m_Children.end(),
		[&](const ActorPtr& child)
	{
		fn(*child);
	});
}

ActorPtr Actor::FindChildren(const std::string & name)
{
	return FindChildren(
		[&](const Actor& actor)
	{return actor.GetName() == name; });
}

ActorPtr Actor::FindChildren(std::function<bool(const Actor&)> fn)
{
	const std::forward_list<ActorPtr>::iterator& i =
		std::find_if(m_Children.begin(), m_Children.end(),
			[&](const ActorPtr& child)
	{ return fn(*child); });
	if (i != m_Children.end())
	{
		return *i;
	}
	for (const ActorPtr& child : m_Children)
	{
		const ActorPtr actor = child->FindChildren(fn);
		if (actor != nullptr)
		{
			return actor;
		}
	}
	return nullptr;
}

void Actor::AddChild(const ActorPtr & child)
{
	m_Children.push_front(child);
}

void Actor::RemoveChildren(std::function<bool(Actor& actor)> fn)
{
	m_Children.remove_if(
		[&](const ActorPtr& child)
	{return fn(*child); });
}

void Actor::RemoveChildren()
{
	RemoveChildren([](Actor& child)
	{ return child.IsDead(); });
	EachChildren(
		[](Actor& child)
	{child.RemoveChildren(); });
}

void Actor::ClearChildren()
{
	m_Children.clear();
}
