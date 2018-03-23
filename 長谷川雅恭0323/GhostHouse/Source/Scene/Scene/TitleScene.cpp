#include "TitleScene.h"
#include <gslib.h>
#include "../../Actor/ActorGroup.h"
#include "../../GameObject/Field/FieldName.h"
#include "../../GameObject/Character/Player/Player.h"


#include "../../GameObject/Camera/Camera.h"
#include "../../GameObject/Camera/TitleCamera.h"

#include "../../GameObject/Door/NormalDoor.h"
#include"../../Utility/Renderer/ShaderName/ShaderName.h"
#include "../../GameObject/Item/ItemManager/ItemManager.h"

#include "../../Utility/Asset/MeshName.h"

#include"../../GameObject/Door/RoomDoor/RoomDoor.h"

TitleScene::TitleScene(ItemManager& item, SceneInfo& info)
	: SceneBase{ info }
	, m_World{ nullptr }
	, p_ItemManager{ &item }
{
}

void TitleScene::OnInitialize()
{
	m_renderer.initialize();
	m_renderer.set_ambient(0.2f);
	m_World = std::make_shared<World>();
	LoadOctree((int)SceneType::GameTitle, "Resource/csv/Field.csv");
	LoadMesh((int)SceneType::GameTitle, "Resource/csv/Mesh.csv");
	LoadModel((int)SceneType::GameTitle, "Resource/csv/Model.csv");
	LoadTexture((int)SceneType::GameTitle, "Resource/csv/Texture.csv");
	LoadBGM((int)SceneType::GamePlay, "Resource/csv/BGM.csv");
	LoadSE((int)SceneType::GamePlay, "Resource/csv/SE.csv");

	if (!gsLoadShader((GSuint)ShaderName::Standerd, "Resource/Shader/Standerd.vert", "Resource/Shader/Standerd.frag"))throw;
	//if (!gsLoadShader((GSuint)ShaderName::Standerd, "Resource/Shader/ThoonStanderd.vert", "Resource/Shader/ThoonStanderd.frag"))throw;
	if (!gsLoadShader((GSuint)ShaderName::Anmation, "Resource/Shader/AnmShader.vert", "Resource/Shader/Standerd.frag"))throw;
	if (!gsLoadShader((GSuint)ShaderName::Floor, "Resource/Shader/Standerd_Texture.vert", "Resource/Shader/Floor.frag"))throw;
	if (!gsLoadShader((GSuint)ShaderName::Depth, "Resource/Shader/Shadow.vert", "Resource/Shader/Shadow.frag"))throw;
	if (!gsLoadShader((GSuint)ShaderName::AnmDepth, "Resource/Shader/AnmShadow.vert", "Resource/Shader/Shadow.frag"))throw;
	if (!gsLoadShader((GSuint)ShaderName::Textured, "Resource/Shader/Standerd_Texture.vert", "Resource/Shader/Standerd_Texture.frag"))throw;

	p_ItemManager->Initialize();

	CollideActorPtr l_Player = std::make_shared<Player>(*m_World.get()
		, GSvector3(0.0f, -1.0f, 10.0f)
		, m_renderer
		, *p_ItemManager
		, m_Info);
	m_World->AddCamera(std::make_shared<TitleCamera>());
	m_World->AddField(std::make_shared<Field>(FieldName::TitleStage
		, ShaderName::Standerd));

	m_World->AddCollideActor(ActorGroup::Player
		, l_Player);

	m_World->AddCollideActor(ActorGroup::HitToPlayer
		, std::make_shared<NormalDoor>(
			*m_World.get()
			, GSvector3(21.4f, 0, 39.7f)
			, (GSuint)MeshName::Door
			, m_Info
			, SceneType::GamePlay));

	m_World->AddCollideActor(ActorGroup::HitToPlayer
		, std::make_shared<NormalDoor>(
			*m_World.get()
			, GSvector3(-16.3f, 0, 39.7f)
			, (GSuint)MeshName::Door
			, m_Info
			, SceneType::Operation));

	m_doorlights.clear();
	m_doorlights.push_back(std::make_shared<TitleLight>(GSvector3{ 18.0f, 4.0f, 5.0f }, m_renderer, *m_World.get(), -3.0f));
	//m_doorlights.push_back(std::make_shared<TitleLight>(GSvector3{ -2.0f,4.0f,5.0f }, m_renderer, *m_World.get(), -3.0f));
	m_doorlights.push_back(std::make_shared<TitleLight>(GSvector3{ -20.0f,4.0f,5.0f }, m_renderer, *m_World.get(), -3.0f));
	m_doorlights.push_back(std::make_shared<TitleLight>(GSvector3{ -15.0f,33.0f,10.0f }, m_renderer, *m_World.get()));
	m_doorlights.push_back(std::make_shared<TitleLight>(GSvector3{ 15.0f,33.0f,10.0f }, m_renderer, *m_World.get()));

}

void TitleScene::NormalUpdate(float deltaTime)
{
	for (auto&door_light : m_doorlights)
	{
		door_light->update(deltaTime);
	}

	m_World->Update(deltaTime);
	p_ItemManager->TakeBattery();
}

void TitleScene::PauseUpdate(float deltaTime)
{
}

void TitleScene::OnDraw() const
{
	for (auto& door_light : m_doorlights)
	{
		door_light->draw(m_renderer);
	}

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
	if (gsGetKeyState(GKEY_SPACE))
	{
		gsBindRenderTargetDepth(1);
		gsDrawRenderTarget(1);
		gsUnbindRenderTargetTexture(1, 0);
	}
}

void TitleScene::Shutdown()
{
	m_Renderer.DeleteMesh();
	m_Renderer.DeleteOctree();
	m_Renderer.DeleteTexture();
	gsDeleteShader((GSuint)ShaderName::Standerd);
	gsDeleteShader((GSuint)ShaderName::Floor);
	gsDeleteShader((GSuint)ShaderName::Anmation);
	gsDeleteShader((GSuint)ShaderName::Depth);
	gsDeleteShader((GSuint)ShaderName::AnmDepth);
	gsDeleteShader((GSuint)ShaderName::Textured);

	m_renderer.delete_render_target();
	m_renderer.clear_light();
	m_Sound.delete_bgm();
	m_Sound.delete_se();
	m_doorlights.clear();
	m_World = nullptr;
	m_Info.m_Goal = false;

	m_Info.m_Door = 0;
	m_Info.m_ColorDoor = 0;
	m_Info.m_MixColorDoor = 0;
}
