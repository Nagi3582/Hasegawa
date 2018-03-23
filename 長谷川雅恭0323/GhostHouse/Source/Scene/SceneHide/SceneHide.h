#ifndef _SCENE_HIDE_H_
#define _SCENE_HIDE_H_
#include <gslib.h>

enum class TextureName;

class SceneHide
{
public:
	SceneHide();

	void Draw()const;

	void SetColor(const float r, const float g, const float b);
	void SetAlpha(const float alpha);


private:
	GScolor m_Color;
	TextureName m_SubTexture;


};


#endif // !_SCENE_HIDE_H_
