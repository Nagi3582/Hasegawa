#include "PauseManager.h"
#include "../../World/IWorld.h"
#include "../../UI/UIGroup.h"
#include "Pause.h"
#include "../../Scene/SceneInfo/SceneInfo.h"
#include "../../Scene/SceneType/SceneType.h"


PauseManager::PauseManager(SceneInfo& info)
	: UIManagerBase{ info,2,GSvector2(540.0f,200.0f) }
{
}

void PauseManager::Initialize(IWorld& world, Renderer& renderer)
{
	m_Cursor = 0;
	world.AddUI(UIGroup::main, std::make_shared<Pause>(world, m_Info));
}

void PauseManager::OnUpdate(float deltaTime)
{
}

void PauseManager::Draw() const
{
	if (m_Info.m_Pause == true && m_Info.m_PlayerDead == false)
	{
		CursorDraw();
		SelectDraw(1, TextureName::BackGame);
		SelectDraw(2, TextureName::TitleReturn);
	}
}

void PauseManager::Decision()
{
	if (m_Cursor == 0 && m_Info.m_PlayerDead == false)
	{
		m_Info.m_Pause = false;
		m_Info.m_Goal = false;
	}
	else if (m_Cursor == 1)
	{
		m_Info.m_NextScene = SceneType::GameTitle;
		m_Info.m_Goal = true;
	}
	gsPlaySE((GSuint)SoundName::PauseDecisionSE);
}