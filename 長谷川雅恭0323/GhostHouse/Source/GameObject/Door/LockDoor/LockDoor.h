#ifndef LOCK_DOOR_H_
#define LOCK_DOOR_H_

#include"../DoorBase.h"

enum class SceneType;
class Player;
class OperationPlayer;

class LockDoor :public DoorBase
{
public:
	LockDoor(IWorld& world
		, const GSvector3& position
		, GSuint meshName
		, SceneInfo& info
		, SceneType type);

	//チュートリアル用コンストラクタ
	LockDoor(IWorld& world
		, const GSvector3& position
		, GSuint meshName
		, SceneInfo& info
		, SceneType type
		, OperationManager& operationManager);

	virtual void OnCollide(CollideActor&other);

private:
	void un_lock(Player&player);
	void un_lock(OperationPlayer&player);

};

#endif // !LOCK_DOOR_H_
