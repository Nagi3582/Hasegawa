#ifndef _COLLIDE_ACTOR_H_
#define _COLLIDE_ACTOR_H_
#include "Actor.h"
#include "CollideActorPtr.h"
#include "../GameObject/Light/LightColor.h"

class Shape;

//当たり判定持ちアクター
class CollideActor :public Actor
{
public:
	//コンストラクタ
	CollideActor() = default;
	CollideActor(IWorld& world, std::string name, GSvector3 position, Shape* shape, LightColor color = LightColor::None);

	//デストラクタ
	~CollideActor();


	//衝突中の更新
	void Collide(CollideActor& other);
	//派生先の衝突中の更新
	virtual void OnCollide(CollideActor& other) {};
	//子の衝突
	void CollideChildren(CollideActor& other);
	//衝突しているか
	bool IsCollide(const CollideActor& other);

	//子同士の巡回CollideActor版
	void EachCollideChildren(std::function<void(CollideActor&)>fn);
	//const版
	void EachCollideChildren(std::function<void(const CollideActor&)>fn)const;


	//子の追加
	void AddCollideChild(const CollideActorPtr& child);

	//子の削除
	void RemoveCollideChildren(std::function<bool(CollideActor& other)>fn);
	void RemoveCollideChildren();

	//当たり判定の取得
	Shape* GetBody()const;

	LightColor GetColor()const;


private:
	std::forward_list<CollideActorPtr> m_CollideChildren;

protected:
	Shape* p_Body{ nullptr };
	LightColor m_Color{ LightColor::None };

};


#endif // !_COLLIDE_ACTOR_H_
