#ifndef _PLAYER_STATE_H_
#define _PLAYER_STATE_H_

enum class PlayerState
{
	Idle = 0,	//通常
	PickUp,		//拾う
	Put,		//置く
	OpenDoor,	//ドアを開ける
	Grab,		//鏡とかつかむ
	Damage,		//ダメージを受ける
	Dead,		//死亡(ゲームオーバー)


	None,

};

#endif // !_PLAYER_STATE_H_
