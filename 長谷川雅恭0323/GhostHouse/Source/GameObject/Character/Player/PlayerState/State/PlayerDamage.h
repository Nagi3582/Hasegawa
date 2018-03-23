#ifndef _PLAYER_DAMAGE_H_
#define _PLAYER_DAMAGE_H_
#include "../PlayerStateBase.h"

class PlayerDamage :public PlayerStateBase
{
public:
	PlayerDamage();

	virtual void Initialize()override;
	virtual void Update(float deltaTime)override;
	virtual void OnCollide(CollideActor& other)override;
	virtual void Draw()const override;
	virtual void OnShutdown()override;

};


#endif // !_PLAYER_DAMAGE_H_
