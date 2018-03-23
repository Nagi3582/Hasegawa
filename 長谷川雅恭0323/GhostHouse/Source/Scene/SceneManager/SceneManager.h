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

	//初期化
	void Initialize(SceneType scene);
	//更新
	void Update(float deltaTime);
	//描画
	void Draw();
	//終了
	void End();


private:
	//シーン切り替え
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
