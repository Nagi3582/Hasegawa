#include "CollideActor.h"
#include "../Collide/BoundingSphere.h"
#include <algorithm>

CollideActor::CollideActor(IWorld & world, std::string name, GSvector3 position, Shape* shape, LightColor color)
	: Actor{ world, name, position }
	, p_Body{ shape }
	, m_Color{ color }
{
	p_Body->SetUp();
}

CollideActor::~CollideActor()
{
	delete p_Body;
}


void CollideActor::Collide(CollideActor & other)
{
	if (IsCollide(other))
	{
		OnCollide(other);
		other.OnCollide(*this);
	}
	EachCollideChildren([&](CollideActor& child)
	{
		child.Collide(other);
	});
}

void CollideActor::CollideChildren(CollideActor & other)
{
	EachCollideChildren([&](CollideActor& my)
	{
		other.EachCollideChildren([&](CollideActor& target)
		{
			my.Collide(target);
		});
	});
}

bool CollideActor::IsCollide(const CollideActor & other)
{
	if (GetBody()->IsCollide() == false ||
		other.GetBody()->IsCollide() == false)
	{
		return false;
	}

	return GetBody()->Intersect(*other.GetBody());
}


void CollideActor::EachCollideChildren(std::function<void(CollideActor&)>fn)
{
	std::for_each(m_CollideChildren.begin(), m_CollideChildren.end(),
		[&](const CollideActorPtr& child)
	{
		fn(*child);
	});
}

void CollideActor::EachCollideChildren(std::function<void(const CollideActor&)> fn) const
{
	std::for_each(m_CollideChildren.begin(), m_CollideChildren.end(),
		[&](const CollideActorPtr& child)
	{
		fn(*child);
	});
}

void CollideActor::AddCollideChild(const CollideActorPtr & child)
{
	m_CollideChildren.push_front(child);
	AddChild(child);
}

void CollideActor::RemoveCollideChildren(std::function<bool(CollideActor&other)> fn)
{
	m_CollideChildren.remove_if(
		[&](const CollideActorPtr& child)
	{return fn(*child); });
}

void CollideActor::RemoveCollideChildren()
{
	RemoveCollideChildren([](CollideActor& child)
	{ return child.IsDead(); });
	EachCollideChildren(
		[](CollideActor& child)
	{child.RemoveChildren(); });

}

Shape* CollideActor::GetBody()const
{
	return p_Body->Transform(GetPose());
}

LightColor CollideActor::GetColor() const
{
	return m_Color;
}
