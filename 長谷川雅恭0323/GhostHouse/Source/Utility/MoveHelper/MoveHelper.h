#ifndef _MOVE_HELPER_H_
#define _MOVE_HELPER_H_
#include <gslib.h>

class MoveHelper
{
public:
	/*
	なめらかな上下移動(sin波)
	引数1：1周する時間
	引数2：毎f増えるカウンター
	引数3：移動する範囲
	*/
	static float EasingSwing(const float& swingTime, float& count, const float& range);

	/*
	円を描くように移動する
	引数1：中心のX座標
	引数2：中心のY座標
	引数3：中心から離れる距離
	引数4：回転速度
	引数5：角度(参照)
	引数6：デルタタイム
	*/
	static GSvector2 CircleRotate(float baseX, float baseY, float distance, float speed, float& angle, float deltaTime);


	//ブールのtrueとfalseを反転させる
	static void BoolReverse(bool& reverse);


};

#endif // !_MOVE_HELPER_H_
