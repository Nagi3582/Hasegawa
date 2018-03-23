#ifndef _MUSIC_ENEMY_H_
#define _MUSIC_ENEMY_H_
#include "EnemyBase.h"

struct SceneInfo;

class MusicEnemy :public EnemyBase
{
public:
	MusicEnemy(IWorld & world, GSvector3 position, CollideActor & player, Renderer& renderer, SceneInfo& info);
	~MusicEnemy();

	virtual void SetState(CollideActor& player)override;


private:
	Renderer* p_Renderer;
	SceneInfo& m_Info;

};


#endif // !_MUSIC_ENEMY_H_
