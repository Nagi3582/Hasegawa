#include "GameOverUIManager.h"
#include "../../World/IWorld.h"
#include "../../UI/UIGroup.h"
#include "GameOverUI.h"
#include "../../Scene/SceneInfo/SceneInfo.h"
#include "../../Scene/SceneType/SceneType.h"


GameOverUIManager::GameOverUIManager(SceneInfo & info)
	: UIManagerBase{ info,2,GSvector2(540.0f,200.0f) }
{
}

void GameOverUIManager::Initialize(IWorld & world, Renderer & renderer)
{
	m_Cursor = 0;
	world.AddUI(UIGroup::main, std::make_shared<GameOverUI>(world, m_Info));
}

void GameOverUIManager::OnUpdate(float deltaTime)
{
}

void GameOverUIManager::Draw() const
{
	if (m_Info.m_PlayerDead == true)
	{
		CursorDraw();
		SelectDraw(1, TextureName::Retry);
		SelectDraw(2, TextureName::TitleReturn);
	}
}

void GameOverUIManager::Decision()
{
	if (m_Cursor == 0)
	{
		m_Info.m_Pause = false;
		m_Info.m_NextScene = SceneType::GamePlay;
		m_Info.m_Goal = true;
	}
	else if (m_Cursor == 1)
	{
		m_Info.m_NextScene = SceneType::GameTitle;
		m_Info.m_Goal = true;
	}
	gsPlaySE((GSuint)SoundName::PauseDecisionSE);
}