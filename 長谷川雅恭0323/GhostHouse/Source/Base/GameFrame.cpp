#include "GameFrame.h"
#include "Screen.h"
#include "DebugMode.h"

GameFrame::GameFrame()
	: Game(WIDTH, HEIGHT, FULL_SCREEN, FPS)
	, m_Scene()
{
	ShowCursor(FALSE);
}

void GameFrame::start()
{
	m_Scene.Initialize(START_SCENE);
}

void GameFrame::update(float deltaTime)
{
	m_Scene.Update(deltaTime);
}

void GameFrame::draw()
{
	m_Scene.Draw();
}

void GameFrame::end()
{
	m_Scene.End();
}
