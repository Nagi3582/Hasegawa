#include "PlaySceneUI.h"

PlaySceneUI::PlaySceneUI(SceneInfo & info, ItemManager& item)
	: m_GameOver{ info }
	, m_Pause{ info }
	, m_UIPlayManager{ info,item }
	, m_Info{ info }
{
}

void PlaySceneUI::Initialize(IWorld & world, Renderer & renderer)
{
	m_UIPlayManager.Initialize(world, renderer);
	m_GameOver.Initialize(world, renderer);
	m_Pause.Initialize(world, renderer);
}

void PlaySceneUI::NormalUpdate(float deltaTime)
{
	m_UIPlayManager.Update(deltaTime);
}

void PlaySceneUI::PauseUpdate(float deltaTime)
{
	m_GameOver.Update(deltaTime);
	m_Pause.Update(deltaTime);
}

void PlaySceneUI::Draw() const
{
	m_UIPlayManager.Draw();
	m_GameOver.Draw();
	m_Pause.Draw();
}
