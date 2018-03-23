#ifndef _ENEMY_STATE_MUSIC_STOP_H_
#define _ENEMY_STATE_MUSIC_STOP_H_
#include "../EnemyStateBase.h"

class IWorld;
struct SceneInfo;

class EnemyStateMusicStop :public EnemyStateBase
{
public:
	EnemyStateMusicStop(SceneInfo& info);

	virtual void Initialize()override;
	virtual void Update(float deltaTime)override;
	virtual void Draw()const override;
	virtual void Shutdown()override;


private:
	bool m_PutMusicBox;
	SceneInfo& m_Info;


};


#endif // !_ENEMY_STATE_MUSIC_STOP_H_
