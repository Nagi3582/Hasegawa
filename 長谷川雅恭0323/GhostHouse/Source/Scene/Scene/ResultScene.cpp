#include "ResultScene.h"
#include <gslib.h>
#include "../../Actor/ActorGroup.h"
#include "../../GameObject/Field/FieldName.h"

#include"../../Utility/Renderer/ShaderName/ShaderName.h"

#include"../../GameObject/Camera/TitleCamera.h"
#include"../../GameObject/ResultObject/ResultCharacter/ResultChrarcter.h"

#include"../../GameObject/Camera/ResultCamera.h"
#include"../../GameObject/Light/ResultLight/ResultLight.h"
#include "../../GameObject/Door/NormalDoor.h"

#include "../../UI/UIGroup.h"
#include "../../UIObject/Result/ResultIcon.h"

ResultScene::ResultScene(ItemManager& item, SceneInfo& info)
	:SceneBase{ info }
	, m_World{ nullptr }
	, p_ItemManager{ &item }
	, m_score{ *m_World.get(),m_renderer,*p_ItemManager,info }
{
}

void ResultScene::OnInitialize()
{
	m_renderer.initialize();
	m_renderer.set_ambient(0.3f);
	m_World = std::make_shared<World>();
	LoadOctree((int)SceneType::GameResult, "Resource/csv/Field.csv");

	LoadMesh((int)SceneType::GameResult, "Resource/csv/Mesh.csv");
	LoadModel((int)SceneType::GameResult, "Resource/csv/Model.csv");
	LoadTexture((int)SceneType::GameResult, "Resource/csv/Texture.csv");
	if (!gsLoadShader((GSuint)ShaderName::Result, "Resource/Shader/Standerd.vert", "Resource/Shader/Result.frag"))throw;
	if (!gsLoadShader((GSuint)ShaderName::Depth, "Resource/Shader/Shadow.vert", "Resource/Shader/Shadow.frag"))throw;


	m_World->AddField(std::make_shared<Field>(FieldName::ResultStage, ShaderName::Result));
	m_World->AddCamera(std::make_shared<ResultCamera>());
	CollideActorPtr character = std::make_shared<ResultCharacter>(*m_World.get(), GSvector3{ 10.0f,0.0f,5.0f }, m_renderer);
	m_World->AddCollideActor(ActorGroup::Player, character);
	//m_World->AddUI(UIGroup::main, std::make_shared<ResultIcon>(*m_World.get(), m_renderer));
	m_light.initialize(m_renderer);
	m_Info.m_NextScene = SceneType::GameTitle;

	m_score.initialize();
}

void ResultScene::NormalUpdate(float deltaTime)
{
	m_World->Update(deltaTime);
	m_light.update(deltaTime);
	if (m_light.get_end())
		m_Info.m_Goal = true;
	m_score.update(deltaTime);
}

void ResultScene::OnDraw() const
{
	m_light.draw(m_renderer);
	int size = m_renderer.get_light_params_size();
	for (int i = 0; i < size; i++)
	{
		m_renderer.start_depth_map(i);
		m_World->Draw(true, m_renderer);
		m_renderer.end_depth_map();
	}

	m_renderer.start_render_target();
	m_World->Draw(false, m_renderer);
	m_renderer.end_render_target();
	m_renderer.draw_render_target();
	m_World->Draw_UI();
	if (m_light.get_light_up())
		m_score.draw();
}

void ResultScene::Shutdown()
{
	m_Renderer.DeleteMesh();
	m_Renderer.DeleteOctree();
	m_Renderer.DeleteTexture();
	gsDeleteShader((GSuint)ShaderName::Floor);
	gsDeleteShader((GSuint)ShaderName::Depth);
	m_renderer.delete_render_target();
	m_World = nullptr;
	m_Info.m_Goal = false;
}

void ResultScene::PauseUpdate(float deltaTime)
{
}
