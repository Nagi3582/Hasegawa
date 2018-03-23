#ifndef COLOR_DOOR_H_
#define COLOR_DOOR_H_

#include "../DoorBase.h"
#include"../../Light/LightColor.h"
#include<vector>

enum class SceneType;
class CollideLight;

class ColorDoor :public DoorBase
{
public:
	ColorDoor(IWorld& world
		, const GSvector3& position
		, SceneInfo& info
		, SceneType type
		, GSuint mesh
		, int color_num
		, LightColor my_color1
		, LightColor my_color2 = LightColor::White);

	//チュートリアル用コンストラクタ
	ColorDoor(IWorld& world
		, const GSvector3& position
		, SceneInfo& info
		, SceneType type
		, GSuint mesh
		, int color_num
		, OperationManager& operationManager
		, LightColor my_color1
		, LightColor my_color2 = LightColor::White);


	virtual void DoorUpdate(float deltaTime)override;

	virtual void OnCollide(CollideActor& other);
private:
	void set_UI();

	void checkLight(CollideActor& light, std::string& otherName);
	bool is_hit_color()const;
	void is_lock();
private:
	SceneType m_Type;
	std::vector<bool>m_is_hit_color;
	std::vector<float>m_color_timer;
	std::vector<LightColor>m_my_color;
};

#endif // !RED_DOOR_H_