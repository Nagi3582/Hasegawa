#include "SceneManager.h"
#include "../Scene/TitleScene.h"
#include "../Scene/GamePlayScene.h"
#include "../Scene/OperationScene.h"
#include "../Scene/ResultScene.h"
#include "../Scene/OperationScene.h"

#include "../../Base/Screen.h"

SceneManager::SceneManager()
	: m_pCurrentScene{ nullptr }
	, m_CurrentType{ SceneType::None }
	, m_ItemManager{}
	, m_Hide{}
{
}

void SceneManager::Initialize(SceneType scene)
{
	m_ItemManager.Initialize();

	m_Scenes[SceneType::GameTitle] = std::make_shared<TitleScene>(m_ItemManager, m_Info);
	m_Scenes[SceneType::GamePlay] = std::make_shared<GamePlayScene>(m_ItemManager, m_Info);
	m_Scenes[SceneType::Operation] = std::make_shared<OperationScene>(m_ItemManager, m_Info);
	m_Scenes[SceneType::GameResult] = std::make_shared<ResultScene>(m_ItemManager, m_Info);
	m_CurrentType = scene;
	m_pCurrentScene = m_Scenes[m_CurrentType];
	m_Info.m_CurrentScene = m_CurrentType;
	m_pCurrentScene->Initialize();
}

void SceneManager::Update(float deltaTime)
{
	m_pCurrentScene->Update(deltaTime);
	m_Hide.SetColor(m_Info.m_Red, m_Info.m_Green, m_Info.m_Blue);
	m_Hide.SetAlpha(m_Info.m_Alpha);

	Change();
}

void SceneManager::Draw()
{
	m_pCurrentScene->Draw();
	m_Hide.Draw();
}

void SceneManager::End()
{
	m_pCurrentScene->Shutdown();
	m_pCurrentScene->GameEnd();
}

//ƒV[ƒ“Ø‚è‘Ö‚¦
void SceneManager::Change()
{
	if (m_pCurrentScene->NextScene() != SceneType::None &&
		m_pCurrentScene->Goal() == true)
	{
		m_CurrentType = m_pCurrentScene->NextScene();
		m_pCurrentScene->Shutdown();
		m_pCurrentScene = m_Scenes[m_CurrentType];
		m_Info.m_CurrentScene = m_CurrentType;
		m_pCurrentScene->Initialize();
	}
	else if (gsGetKeyTrigger(GKEY_1))
	{
		m_pCurrentScene->Shutdown();
		m_pCurrentScene->Initialize();
	}
}
