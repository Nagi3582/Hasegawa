#ifndef _PLAYER_PUT_H_
#define _PLAYER_PUT_H_
#include "../PlayerStateBase.h"

class Renderer;
class OperationManager;

class PlayerPut :public PlayerStateBase
{
public:
	PlayerPut(Renderer& renderer);
	PlayerPut(Renderer& renderer, OperationManager& operationManager, bool is_UseBattery = true);

	virtual void Initialize()override;
	virtual void Update(float deltaTime)override;
	virtual void OnCollide(CollideActor& other)override;
	virtual void Draw()const override;


private:
	Renderer* p_Renderer;
	bool m_IsUseBattery;
	OperationManager* p_OperationManager;
};


#endif // !_PLAYER_PUT_H_
