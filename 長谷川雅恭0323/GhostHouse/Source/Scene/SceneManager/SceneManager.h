#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_
#include <unordered_map>
#include "../Scene/SceneBase.h"
#include "../SceneType/SceneType.h"
#include "../Scene/SceneBasePtr.h"
#include "../../GameObject/Item/ItemManager/ItemManager.h"
#include "../SceneInfo/SceneInfo.h"
#include "../SceneHide/SceneHide.h"

class SceneManager
{
public:
	SceneManager();

	//������
	void Initialize(SceneType scene);
	//�X�V
	void Update(float deltaTime);
	//�`��
	void Draw();
	//�I��
	void End();


private:
	//�V�[���؂�ւ�
	void Change();



private:
	std::unordered_map<SceneType, SceneBasePtr> m_Scenes;
	SceneBasePtr	m_pCurrentScene;
	SceneType		m_CurrentType;

	ItemManager m_ItemManager;
	SceneInfo m_Info;
	SceneHide m_Hide;

};

#endif // !_SCENE_MANAGER_H_
