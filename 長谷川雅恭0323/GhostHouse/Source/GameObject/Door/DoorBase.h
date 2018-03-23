#ifndef _DOOR_BASE_H_
#define _DOOR_BASE_H_
#include "../Character/ModelBase.h"

struct SceneInfo;
class Renderer;
enum class SceneType;
class OperationManager;

class DoorBase :public CollideActor
{
protected:
	enum class DoorState
	{
		Close,
		Opening,
		Open,
	};
public:
	DoorBase(IWorld& world
		, std::string name
		, GSvector3 position
		, Shape* shape
		, GSuint meshName
		, SceneInfo& info
		, SceneType type
		, float default_roll = -90.0f);

	DoorBase(IWorld& world
		, std::string name
		, GSvector3 position
		, Shape* shape
		, GSuint meshName
		, SceneInfo& info
		, SceneType type
		, OperationManager& operationManager
		, float default_roll = -90.0f);


	virtual void OnUpdate(float deltaTime)override;

	virtual void DoorUpdate(float deltaTime);

	virtual void OnDraw(bool is_shadow, Renderer& m_renderer)const override;

	virtual void on_draw(bool is_shadow, Renderer&render)const {}
protected:
	virtual void update_state(float deltaTime);
	virtual void update_close(float deltaTime);
	virtual void update_opening(float deltaTime);
	virtual void update_open(float deltaTime);

protected:
	SceneInfo& m_Info;
	SceneType m_Type;
	DoorState m_state;
	GSuint m_meshName;
	float m_opening_timer;
	bool is_open = false;
	bool m_IsNextScene;

	OperationManager* p_OperationManager;
};


#endif // !_DOOR_BASE_H_
