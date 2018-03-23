#ifndef _ITEM_MANAGER_H_
#define _ITEM_MANAGER_H_
#include <vector>
#include <unordered_map>
#include <memory>

class LightParameter;
enum class LightColor;
class IWorld;
class TakeItemManager;
enum class TextureName;

class ItemManager
{
public:
	ItemManager();

	void Initialize(bool add_light = true);

	void Update(float deltaTime);

	//UI表示に使うかも
	//void Draw()const {};

	void SetUnLock(bool unlock);
	void DoorUnLock();
	bool get_is_lock()const;


	//ライトの追加
	void AddLight(LightColor color, int batterySize = 100);
	void AddLight(LightParameter& color);


	//ライトを消す
	void RemoveLight(LightColor color);

	void TakeBattery();

	//ライトの個数
	int GetLightSize(LightColor color);
	//int版
	int GetLightSize(int color);

	//バッテリー残量
	int BatterySize();
	//バッテリー残量(引数で色を指定)
	int BatterySize(LightColor color);


	//敵に当たったときの処理
	void HitEnemy();

	//ライトを持っているか？
	bool IsHaveLight();

	LightColor GetColor()const;


	void ChangeColor(bool change = false);

	//ステージ開始時の状態に戻す
	void SetPrevLight(ItemManager& prev);

	void SetTakeItemManager(TakeItemManager& takeItemManager);
	void TakeItem(TextureName texture);

private:
	void ChangeColor(int direction);


private:
	using LightParameterPtr = std::shared_ptr<LightParameter>;
	using LightList = std::vector<LightParameterPtr>;
	using LightListMap = std::unordered_map<int, LightList>;


private:
	bool m_UnLock;
	LightColor m_CurrentColor;


	LightListMap m_Lights;
	TakeItemManager* p_TakeItemManager;



};

#endif // !_ITEM_MANAGER_H_