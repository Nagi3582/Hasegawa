#ifndef _OPERATION_MANAGER_H_
#define _OPERATION_MANAGER_H_

class ItemManager;

enum class OperationState
{
	TakeLight = 0,
	PlayerRotate,
	LightChange,
	PutLight,
	TakeShiningLight,
	TakeBattery,
	TakeKey,
	EnemyStop,
	EnemyStopPutLight,
	NormalDoor,
	LockDoor,
	ColorDoor,
	PutLightColorDoor,
	OpenColorDoor,
	NextRoom,
	TutorialEnd,

};

class OperationManager
{
public:
	OperationManager(ItemManager& itemManager);

	void Initialize();
	void Update(float deltaTime);

	int GetCurrentState()const;
	void SetCurrentState(OperationState state);

	void PlayerRotate();
	void TakeShiningLight();
	void TakeBattery();
	void EnemyStop();
	void EnemyStopPutLight();
	void NormalDoor();
	void LockDoor();
	void ColorDoor();
	void PutLightColorDoor();
	void OpenColorDoor();

	//移動できるか
	bool IsMove()const;

	//置いたライトを消すか？
	bool IsPutLightClear()const;
	void SetPutLightClear(bool clear);


private:
	void TakeLight();
	void LightChange();
	void PutLight();
	void TakeKey();

private:
	int m_State;
	ItemManager* p_ItemManager;
	bool m_IsMove;
	bool m_IsLightClear;

};

#endif // !_OPERATION_MANAGER_H_
