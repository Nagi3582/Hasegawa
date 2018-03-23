#ifndef _PLAYER_IDLE_H_
#define _PLAYER_IDLE_H_
#include "../PlayerStateBase.h"

class PlayerIdle :public PlayerStateBase
{
public:
	PlayerIdle(Renderer& renderer);
	PlayerIdle(Renderer& renderer, OperationManager& operationManager);

	virtual void Initialize()override;
	virtual void Update(float deltaTime)override;
	virtual void OnCollide(CollideActor& other)override;
	virtual void Draw()const override;


private:
	bool m_IsPickUp;
	OperationManager* p_OperationManager;

};


#endif // !_PLAYER_IDLE_H_

