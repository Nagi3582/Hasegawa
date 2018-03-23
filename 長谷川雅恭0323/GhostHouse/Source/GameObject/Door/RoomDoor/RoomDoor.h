#ifndef ROOM_DOOR_H_
#define ROOM_DOOR_H_
#include"../DoorBase.h"

class OperationManager;
enum class OperationState;

class RoomDoor :public DoorBase
{
private:
	enum DefaultDir
	{
		Right,
		Left,
		Back,
		Top,
	};
public:
	RoomDoor(IWorld&world
		, const GSvector3& position
		, GSuint meshName
		, SceneInfo& info
		, float default_roll//左側に開く場合0　右側に開く場合180
		);

	RoomDoor(IWorld&world
		, const GSvector3& position
		, GSuint meshName
		, SceneInfo& info
		, float default_roll//左側に開く場合0　右側に開く場合180
		, OperationManager& operationManager
		, OperationState state
		);


	void OnCollide(CollideActor&other)override;
	void update_opening(float deltaTime)override;
private:
	void check_recerse(CollideActor& other);
private:
	bool m_reverse_open;
	float m_default_roll;
	DefaultDir m_dir;
	OperationManager* p_OperationManager;
	OperationState m_NextOperation;

};

#endif // !ROOM_DOOR_H_
