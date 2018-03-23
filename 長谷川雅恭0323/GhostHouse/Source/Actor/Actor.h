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
	//コンストラクタ
	Actor() = default;
	Actor(IWorld& world, std::string name, GSvector3 position);

	//デストラクタ
	virtual ~Actor() {}


	//更新
	void Update(float deltaTime);
	//描画
	void Draw(const bool is_shadow, Renderer& renderer)const;


	//位置の取得
	GSvector3 GetPosition()const;

	//名前の取得
	std::string GetName()const;

	//変換行列を取得
	GSmatrix4 GetPose()const;

	//行列の取得
	GSmatrix4 GetRotate()const;


	//死んでいるか
	bool IsDead()const;

	//死亡させる
	void Dead();

	void HideOn();
	void HideOff();

	bool IsHide();

	//子の巡回
	void EachChildren(std::function<void(Actor&)>fn);
	//const版
	void EachChildren(std::function<void(const Actor&)>fn)const;

	//子の検索
	ActorPtr FindChildren(const std::string& name);
	ActorPtr FindChildren(std::function<bool(const Actor&)>fn);

	//子の追加
	void AddChild(const ActorPtr& child);

	//子の削除
	void RemoveChildren(std::function<bool(Actor& other)>fn);
	void RemoveChildren();

	//子を消去
	void ClearChildren();


protected:
	//派生先の更新、描画
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
