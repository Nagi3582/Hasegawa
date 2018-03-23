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

	//UI�\���Ɏg������
	//void Draw()const {};

	void SetUnLock(bool unlock);
	void DoorUnLock();
	bool get_is_lock()const;


	//���C�g�̒ǉ�
	void AddLight(LightColor color, int batterySize = 100);
	void AddLight(LightParameter& color);


	//���C�g������
	void RemoveLight(LightColor color);

	void TakeBattery();

	//���C�g�̌�
	int GetLightSize(LightColor color);
	//int��
	int GetLightSize(int color);

	//�o�b�e���[�c��
	int BatterySize();
	//�o�b�e���[�c��(�����ŐF���w��)
	int BatterySize(LightColor color);


	//�G�ɓ��������Ƃ��̏���
	void HitEnemy();

	//���C�g�������Ă��邩�H
	bool IsHaveLight();

	LightColor GetColor()const;


	void ChangeColor(bool change = false);

	//�X�e�[�W�J�n���̏�Ԃɖ߂�
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