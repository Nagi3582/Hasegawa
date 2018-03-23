#include "SceneBase.h"
#include "../../Utility/csvReader/csvReader.h"
#include "../../Utility/Renderer/Renderer.h"
#include"../../Utility/Sound/Sound.h"
#include "../../UIObject/Result/ResutScore.h"
#include"../../UIObject/GimmickAssist/GimmickAssist.h"


SceneBase::SceneBase(SceneInfo& info)
	: m_Timer{ 0 }
	, m_Renderer{}
	, m_Info{ info }
{
}

void SceneBase::Initialize()
{
	GimmickAssist::initialize();
	m_Info.m_NextScene = SceneType::None;
	m_Info.m_Pause = false;
	m_Timer = 0;
	m_Info.m_Alpha = 1.0f;

	OnInitialize();
}

void SceneBase::Update(float deltaTime)
{
	GimmickAssist::update();
	m_Info.m_Alpha -= 0.05f;
	OnUpdate(deltaTime);
	if (m_Info.m_Pause == false)
		NormalUpdate(deltaTime);
	else
		PauseUpdate(deltaTime);

	m_Timer += deltaTime;
}

void SceneBase::Draw() const
{
	OnDraw();
	GimmickAssist::draw();

}

void SceneBase::GameEnd()
{
	GimmickAssist::finalize();
	OnGameEnd();
}

SceneType SceneBase::NextScene() const
{
	return m_Info.m_NextScene;
}

bool SceneBase::Goal() const
{
	return m_Info.m_Goal;
}

void SceneBase::SetScore(ResultScore & score)
{
	//score.SetMusicBox(m_Info.m_MusicBox);
	//score.SetDoor(m_Info.m_Door);
	//score.SetColorDoor(m_Info.m_ColorDoor);
	//score.SetMixColorDoor(m_Info.m_MixColorDoor);
}



void SceneBase::LoadMesh(int stage, const std::string file)
{
	csvReader l_csvReader;

	l_csvReader.Load(file);
	for (int i = 1; i < l_csvReader.GetLineSize(); ++i)
	{
		if (l_csvReader.GetI(i, STAGE_ID) != (int)SceneType::None && (int)stage != l_csvReader.GetI(i, STAGE_ID))continue;

		m_Renderer.LoadMesh(l_csvReader.GetI(i, RESOURCE_ID), l_csvReader.GetS(i, RESOURCE_NAME).c_str());
	}
}

void SceneBase::LoadOctree(int stage, const std::string file)
{
	csvReader l_csvReader;

	l_csvReader.Load(file);
	for (int i = 1; i < l_csvReader.GetLineSize(); ++i)
	{
		if (l_csvReader.GetI(i, STAGE_ID) != (int)SceneType::None && (int)stage != l_csvReader.GetI(i, STAGE_ID))continue;

		m_Renderer.LoadOctree(l_csvReader.GetI(i, RESOURCE_ID), l_csvReader.GetS(i, RESOURCE_NAME).c_str(),
			l_csvReader.GetS(i, OCTREE_NAME).c_str());
	}
}

void SceneBase::LoadTexture(int stage, const std::string file)
{
	csvReader l_csvReader;

	l_csvReader.Load(file);
	for (int i = 1; i < l_csvReader.GetLineSize(); ++i)
	{
		if (l_csvReader.GetI(i, STAGE_ID) != (int)SceneType::None && (int)stage != l_csvReader.GetI(i, STAGE_ID))continue;

		m_Renderer.LoadTexture(l_csvReader.GetI(i, RESOURCE_ID), l_csvReader.GetS(i, RESOURCE_NAME).c_str());
	}
}

void SceneBase::LoadModel(int stage, const std::string & file)
{
	csvReader l_csvReader;

	l_csvReader.Load(file);

	for (int i = 1; i < l_csvReader.GetLineSize(); ++i)
	{
		if (l_csvReader.GetI(i, STAGE_ID) != (int)SceneType::None && (int)stage != l_csvReader.GetI(i, STAGE_ID))continue;

		m_Renderer.LoadModel(l_csvReader.GetI(i, RESOURCE_ID),
			l_csvReader.GetS(i, RESOURCE_NAME), l_csvReader.GetS(i, SKELETON_ID).c_str(), l_csvReader.GetS(i, ANIMATION_ID).c_str());
	}
}

void SceneBase::LoadBGM(int stage, const std::string & file)
{
	csvReader l_csvReader;

	l_csvReader.Load(file);

	for (int i = 1; i < l_csvReader.GetLineSize(); ++i)
	{
		if (l_csvReader.GetI(i, STAGE_ID) != (int)SceneType::None && (int)stage != l_csvReader.GetI(i, STAGE_ID))continue;

		m_Sound.load_bgm(l_csvReader.GetI(i, RESOURCE_ID), l_csvReader.GetS(i, RESOURCE_NAME));
	}
}

void SceneBase::LoadSE(int stage, const std::string & file)
{
	csvReader l_csvReader;

	l_csvReader.Load(file);

	for (int i = 1; i < l_csvReader.GetLineSize(); ++i)
	{
		if (l_csvReader.GetI(i, STAGE_ID) != (int)SceneType::None && (int)stage != l_csvReader.GetI(i, STAGE_ID))continue;

		m_Sound.load_se(l_csvReader.GetI(i, RESOURCE_ID), l_csvReader.GetS(i, RESOURCE_NAME));
	}
}
