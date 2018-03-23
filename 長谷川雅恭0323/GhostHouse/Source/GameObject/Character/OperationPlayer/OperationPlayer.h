#ifndef _OPERATION_PLAYER_H_
#define _OPERATION_PLAYER_H_
#include "../Player/Player.h"

#include"../../Light/PlayerLight.h"
#include "../Player/PlayerManager.h"
#include "../Player/PlayerHandLight/PlayerHandLight.h"

class ItemManager;
class OperationManager;
struct SceneInfo;

class OperationPlayer :public Player
{
public:
	OperationPlayer(IWorld & world, const GSvector3 position, Renderer&renderer, ItemManager& item, SceneInfo& info, OperationManager& operationManager);

	virtual void OnUpdate(float deltaTime)override;


private:
	void MoveLimit();


private:
	OperationManager* p_OperationManager;

};


#endif // !_OPERATION_PLAYER_H_