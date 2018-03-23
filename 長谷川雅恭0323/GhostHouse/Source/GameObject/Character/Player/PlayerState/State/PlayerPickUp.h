#ifndef _PLAYER_PICK_UP_H_
#define _PLAYER_PICK_UP_H_
#include "../PlayerStateBase.h"

class PlayerPickUp :public PlayerStateBase
{
public:
	PlayerPickUp();


	virtual void Initialize()override;
	virtual void Update(float deltaTime)override;
	virtual void OnCollide(CollideActor& other)override;
	virtual void Draw()const override;


private:
	bool m_IsPickUp;

};


#endif // !_PLAYER_PICK_UP_H_