#ifndef _UI_MANAGER_BASE_H_
#define _UI_MANAGER_BASE_H_
#include "../../Utility/Asset/SoundName.h"
#include <gslib.h>

class IWorld;
class Renderer;
struct SceneInfo;
enum class TextureName;

class UIManagerBase
{
public:
	UIManagerBase(SceneInfo& info, int select, GSvector2 select_size, float select_centerY = 450.0f);

	virtual void Initialize(IWorld& world, Renderer& renderer) {};
	void Update(float deltaTime);
	virtual void Draw()const {};


protected:
	virtual void OnUpdate(float deltaTime) {};
	virtual void Decision() {};
	virtual void CursorSE() { gsPlaySE((GSuint)SoundName::CursorSE); };

	void CursorMove();
	void SelectDraw(int num, const TextureName& name)const;
	void CursorDraw()const;


protected:
	int m_Cursor;
	SceneInfo& m_Info;
	const int SELECT_MAX;

private:
	bool m_StickReset;

protected:
	//�I�����镶���̒��S
	const GSvector2 SELECT_CENTER;
	//�I�����镶���̑傫��
	const GSvector2 SELECT_SIZE;
	//������Y���W1
	const float SELECT1_POS_Y;
	//������Y���W2
	const float SELECT2_POS_Y;
	//������Y���W3
	const float SELECT3_POS_Y;
};


#endif // !_UI_MANAGER_BASE_H_
