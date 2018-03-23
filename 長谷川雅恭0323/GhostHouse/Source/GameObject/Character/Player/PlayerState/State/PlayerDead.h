#ifndef _PLAYER_DEAD_H_
#define _PLAYER_DEAD_H_
#include "../PlayerStateBase.h"

class PlayerDead :public PlayerStateBase
{
public:
	PlayerDead();

	virtual void Initialize()override;
	virtual void Update(float deltaTime)override;
	virtual void OnCollide(CollideActor& other)override;
	virtual void Draw()const override;

};


#endif // !_PLAYER_DEAD_H_
