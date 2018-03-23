#ifndef _NORMAL_DOOR_H_
#define _NORMAL_DOOR_H_
#include "DoorBase.h"

enum class SceneType;

class NormalDoor :public DoorBase
{
public:
	NormalDoor(IWorld& world
		, const GSvector3& position
		, GSuint meshName
		, SceneInfo& info
		, SceneType type);

	//チュートリアル用コンストラクタ
	NormalDoor(IWorld& world
		, const GSvector3& position
		, GSuint meshName
		, SceneInfo& info
		, SceneType type
		, OperationManager& operationManager);


	virtual void OnCollide(CollideActor& other);

};


#endif // !_NORMAL_DOOR_H_
