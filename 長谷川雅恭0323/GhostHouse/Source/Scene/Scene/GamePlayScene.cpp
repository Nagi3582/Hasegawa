#include "GamePlayScene.h"
#include <GSmusic.h>
#include "../../GameObject/Item/ItemManager/ItemManager.h"
#include "../../Utility/Renderer/ShaderName/ShaderName.h"
#include "../../GameObject/Character/Player/Player.h"
#include "../../GameObject/Camera/Camera.h"
#include "../../GameObject/Field/Field.h"

#include "../ObjectGenerator/ObjectGenerator.h"
#include"../../UIObject/StageTitle/StageTitle.h"
#include"../../UI/UIGroup.h"

#include "../../GameObject/Character/Enemy/WhiteEnemy.h"
#include "../../Actor/ActorGroup.h"
#include "../../UIObject/TakeItem/TakeItemManager.h"
#include "../../UI/UIPtr.h"
#include "../../UIObject/MiniMap/MiniMap.h"

GamePlayScene::GamePlayScene(ItemManager & item, SceneInfo& info)
	: SceneBase{ info }
	, p_World{ nullptr }
	, p_ItemManager{ &item }
	, m_UI{ m_Info,item }
	, m_Stage{ 0 }
	, m_PrevItem{}
{
	set_stage_name();
}

void GamePlayScene::OnInitialize()
{
	m_renderer.initialize();
	m_renderer.set_ambient(0.35f);

	if (m_Stage == 0)
	{
		LoadMesh((int)SceneType::GamePlay, "Resource/csv/Mesh.csv");
		LoadModel((int)SceneType::GamePlay, "Resource/csv/Model.csv");
		LoadTexture((int)SceneType::GamePlay, "Resource/csv/Texture.csv");
		LoadBGM((int)SceneType::GamePlay, "Resource/csv/BGM.csv");
		LoadSE((int)SceneType::GamePlay, "Resource/csv/SE.csv");
		if (!gsLoadShader((GSuint)ShaderName::Standerd, "Resource/Shader/Standerd.vert", "Resource/Shader/Standerd.frag"))throw;
		if (!gsLoadShader((GSuint)ShaderName::Anmation, "Resource/Shader/AnmShader.vert", "Resource/Shader/Standerd.frag"))throw;
		if (!gsLoadShader((GSuint)ShaderName::Floor, "Resource/Shader/Standerd_Texture.vert", "Resource/Shader/Floor.frag"))throw;
		if (!gsLoadShader((GSuint)ShaderName::Depth, "Resource/Shader/Shadow.vert", "Resource/Shader/Shadow.frag"))throw;
		if (!gsLoadShader((GSuint)ShaderName::AnmDepth, "Resource/Shader/AnmShadow.vert", "Resource/Shader/Shadow.frag"))throw;
		if (!gsLoadShader((GSuint)ShaderName::Textured, "Resource/Shader/Standerd_Texture.vert", "Resource/Shader/Standerd_Texture.frag"))throw;
		if (!gsLoadShader((GSuint)ShaderName::Icon, "Resource/Shader/Icon.vert", "Resource/Shader/Icon.frag"))throw;
	}


	gsBindMusic((GSuint)SoundName::PlayScene_BGM);

	m_PrevItem = *p_ItemManager;

	m_Stage++;

	//デバック用
	//m_Stage = 10;

	m_Info.m_PlayerDead = false;
	m_Info.m_Pause = false;
	m_Info.m_NextScene = SceneType::GamePlay;
	m_Info.m_CurrentScene = SceneType::GamePlay;

	p_World = std::make_shared<World>();
	m_UI.Initialize(*p_World.get(), m_renderer);
	LoadOctree(m_Stage, "Resource/csv/Field.csv");

	UIPtr l_TakeItemPtr = std::make_shared<TakeItemManager>(*p_World.get());
	p_World->AddUI(UIGroup::main, l_TakeItemPtr);
	TakeItemManager* l_TakeItem = dynamic_cast<TakeItemManager*>(l_TakeItemPtr.get());
	p_ItemManager->SetTakeItemManager(*l_TakeItem);



	ObjectGenerator l_Generator(*p_World.get(), m_renderer, *p_ItemManager, m_Info, SceneType::GamePlay);

	l_Generator.Generator(m_Stage);

	p_World->AddUI(UIGroup::main, std::make_shared<StageTitle>(*p_World.get(), (GSuint)m_stageNames[m_Stage]));

}

void GamePlayScene::OnUpdate(float deltaTime)
{
	if (gsXBoxPadButtonTrigger(0, GS_XBOX_PAD_START))
	{
		m_Info.m_Pause = !m_Info.m_Pause;
		gsPlaySE((GSuint)SoundName::OpenPauseSE);
	}


#ifdef DEBUG

	if (gsGetKeyTrigger(GKEY_S))
		m_Info.m_Goal = true;

#endif // DEBUG

}

void GamePlayScene::NormalUpdate(float deltaTime)
{
	gsPlayMusic();
	if (m_Info.m_Direction == false)
	{
		p_World->Update(deltaTime);
	}
	else if (m_Info.m_Direction == true)
	{
		p_World->DirectionUpdate(deltaTime);
	}	m_UI.NormalUpdate(deltaTime);
	p_ItemManager->Update(deltaTime);
}

void GamePlayScene::PauseUpdate(float deltaTime)
{
	m_UI.PauseUpdate(deltaTime);
}

void GamePlayScene::OnDraw() const
{
	int size = m_renderer.get_light_params_size();
	for (int i = 0; i < size; i++)
	{
		m_renderer.start_depth_map(i);
		p_World->Draw(true, m_renderer);
		m_renderer.end_depth_map();
	}

	m_renderer.start_render_target();
	p_World->Draw(false, m_renderer);
	m_renderer.end_render_target();
	m_renderer.draw_render_target();
	p_World->Draw_UI();
	m_UI.Draw();
}

void GamePlayScene::Shutdown()
{
	if (m_Info.m_NextScene != SceneType::GamePlay)
	{
		m_Stage = 0;

		m_Renderer.DeleteMesh();
		m_Renderer.DeleteTexture();
		//m_Sound.delete_sound();
		gsDeleteShader((GSuint)ShaderName::Standerd);
		gsDeleteShader((GSuint)ShaderName::Floor);
		gsDeleteShader((GSuint)ShaderName::Anmation);
		gsDeleteShader((GSuint)ShaderName::Depth);
	}
	else if (m_Info.m_PlayerDead == true)
	{
		m_Stage--;
		p_ItemManager->SetPrevLight(m_PrevItem);
	}

	m_Renderer.DeleteOctree();

	m_renderer.delete_render_target();
	p_World = nullptr;
	m_Info.m_Goal = false;


}

void GamePlayScene::OnGameEnd()
{
	m_Renderer.DeleteMesh();
	m_Renderer.DeleteTexture();
	//m_Sound.delete_sound();
	gsDeleteShader((GSuint)ShaderName::Standerd);
	gsDeleteShader((GSuint)ShaderName::Floor);
	gsDeleteShader((GSuint)ShaderName::Anmation);
	gsDeleteShader((GSuint)ShaderName::Depth);
	m_Sound.delete_sound();
}

void GamePlayScene::set_stage_name()
{
	m_stageNames[1] = TextureName::StageTitle1;
	m_stageNames[2] = TextureName::StageTitle2;
	m_stageNames[3] = TextureName::StageTitle3;
	m_stageNames[4] = TextureName::StageTitle4;
	m_stageNames[5] = TextureName::StageTitle5;
	m_stageNames[6] = TextureName::StageTitle6;
	m_stageNames[7] = TextureName::StageTitle7;
	m_stageNames[8] = TextureName::StageTitle8;
	m_stageNames[9] = TextureName::StageTitle9;
	m_stageNames[10] = TextureName::StageTitle10;
}

