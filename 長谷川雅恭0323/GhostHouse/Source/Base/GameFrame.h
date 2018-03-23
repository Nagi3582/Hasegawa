#ifndef _GAME_FRAME_H_
#define _GAME_FRAME_H_
#include <GSgame.h>
#include "../Scene/SceneManager/SceneManager.h"

class GameFrame :public gslib::Game
{
public:
	GameFrame();

	virtual void start()override;

	virtual void update(float deltaTime)override;

	virtual void draw()override;

	virtual void end()override;


private:
	SceneManager m_Scene;

};


#endif // !_GAME_FRAME_H_
