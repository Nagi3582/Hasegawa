#ifndef _RESULT_ICON_H_
#define _RESULT_ICON_H_
#include "../../UI/UITexture.h"
#include <vector>

class ResultScore;
enum class TextureName;

class ResultIcon:public UITexture
{
public:
	ResultIcon(IWorld&world);


	virtual void on_update(float deltaTime);
	virtual void on_draw()const;



private:
	ResultScore* p_Score;
	std::vector<TextureName> m_TextureNames;

};


#endif // !_RESULT_ICON_H_
