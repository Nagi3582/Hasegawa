#ifndef GIMMICK_ASSIST_H_
#define GIMMICK_ASSIST_H_

#include"../../Utility/Asset/TextureName.h"
#include"../../Base/Screen.h"
#include<gslib.h>

class GimmickAssist
{
public:
	static void initialize();
	static void finalize();
	static void update();
	static void draw();
	static void bind(GSuint texID, GSvector2 pos = GSvector2{675,200});
private:
	static GSuint m_bindID;
	static int m_del_count;
	static GSvector2 m_pos;
};

#endif // !GIMMICK_ASSIST_H_
