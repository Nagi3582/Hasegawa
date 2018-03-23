#include "OperationScene.h"
#include <gslib.h>
#include "../../GameObject/Item/ItemManager/ItemManager.h"
#include "../../UIObject/TakeItem/TakeItemManager.h"
#include "../../Base/Screen.h"
#include "../../Utility/MoveHelper/MoveHelper.h"
#include "../../Utility/Asset/SoundName.h"
#include "../../Utility/Asset/TextureName.h"

#include "../../Actor/ActorGroup.h"
#include "../../UI/UIGroup.h"
#include "../../GameObject/Field/FieldName.h"
#include "../../GameObject/Character/Player/Player.h"
#include "../../GameObject/Character/OperationPlayer/OperationPlayer.h"

#include "../../GameObject/Camera/Camera.h"
#include"../../Utility/Renderer/ShaderName/ShaderName.h"

#include "../../GameObject/Character/Enemy/OperationEnemy.h"

#include "../../GameObject/Item/Battery/Battery.h"
#include "../../GameObject/Item/DoorKey/DoorKey.h"
#include "../../GameObject/Item/Flashlight/FlashLight.h"
#include "../../GameObject/Item/MusicBox/MusicBox.h"

#include "../../GameObject/Door/NormalDoor.h"
#include "../../GameObject/Door/LockDoor/LockDoor.h"
#include "../../GameObject/Door/ColorDoor/ColorDoor.h"

#include "../../GameObject/Light/LightColor.h"

#include "../../UIObject/GamePlay/Pause.h"
#include "../../GameObject/Item/Flashlight/RePopFlashLight.h"
//#include"../../GameObject/Door/TestDoor/TestDoor.h"
#include "../../GameObject/Door/RoomDoor/RoomDoor.h"

#include <GSmusic.h>


OperationScene::OperationScene(ItemManager& item, SceneInfo& info)
	: SceneBase{ info }
	, p_World{ nullptr }
	, p_ItemManager{ &item }
	, m_UI{ m_Info,item }
	, m_OperationManager{ item }
	, m_Operation{}
{
}

void OperationScene::OnInitialize()
{
	m_renderer.initialize();
	m_renderer.set_ambient(0.35f);
	gsBindMusic((GSuint)SoundName::PlayScene_BGM);

	m_Info.m_PlayerDead = false;
	m_Info.m_Pause = false;

	p_ItemManager->Initialize();
	m_OperationManager.Initialize();

	p_World = std::make_shared<World>();
	m_UI.Initialize(*p_World.get(), m_renderer);
	LoadOctree((int)SceneType::Operation, "Resource/csv/Field.csv");
	LoadMesh((int)SceneType::Stage1, "Resource/csv/Mesh.csv");
	LoadModel((int)SceneType::Stage1, "Resource/csv/Model.csv");
	LoadTexture((int)SceneType::Stage1, "Resource/csv/Texture.csv");
	LoadBGM((int)SceneType::Stage1, "Resource/csv/BGM.csv");
	LoadSE((int)SceneType::Stage1, "Resource/csv/SE.csv");
	if (!gsLoadShader((GSuint)ShaderName::Standerd, "Resource/Shader/Standerd.vert", "Resource/Shader/Standerd.frag"))throw;
	if (!gsLoadShader((GSuint)ShaderName::Anmation, "Resource/Shader/AnmShader.vert", "Resource/Shader/Standerd.frag"))throw;
	if (!gsLoadShader((GSuint)ShaderName::Floor, "Resource/Shader/Standerd_Texture.vert", "Resource/Shader/Floor.frag"))throw;
	if (!gsLoadShader((GSuint)ShaderName::Depth, "Resource/Shader/Shadow.vert", "Resource/Shader/Shadow.frag"))throw;
	if (!gsLoadShader((GSuint)ShaderName::AnmDepth, "Resource/Shader/AnmShadow.vert", "Resource/Shader/Shadow.frag"))throw;
	if (!gsLoadShader((GSuint)ShaderName::Textured, "Resource/Shader/Standerd_Texture.vert", "Resource/Shader/Standerd_Texture.frag"))throw;
	if (!gsLoadShader((GSuint)ShaderName::Icon, "Resource/Shader/Icon.vert", "Resource/Shader/Icon.frag"))throw;

	UIPtr l_TakeItemPtr = std::make_shared<TakeItemManager>(*p_World.get());
	p_World->AddUI(UIGroup::main, l_TakeItemPtr);
	TakeItemManager* l_TakeItem = dynamic_cast<TakeItemManager*>(l_TakeItemPtr.get());
	p_ItemManager->SetTakeItemManager(*l_TakeItem);

	m_Info.m_NextScene = SceneType::GameTitle;
	m_Info.m_CurrentScene = SceneType::Operation;

	CollideActorPtr l_Player = std::make_shared<OperationPlayer>(*p_World.get(), GSvector3(0.0f, 0.0f, -50.0f), m_renderer, *p_ItemManager, m_Info, m_OperationManager);
	p_World->AddCamera(std::make_shared<Camera>(l_Player));
	p_World->AddField(std::make_shared<Field>(FieldName::Stage));
	p_World->AddCollideActor(ActorGroup::Player, l_Player);


	p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<RePopFlashLight>(
		*p_World.get(), GSvector3(0.0f, 0.0f, -20.0f), LightColor::Green, *p_ItemManager, 60 * 10));

	p_World->AddCollideActor(ActorGroup::HitToPlayer
		, std::make_shared<Battery>(*p_World.get()
			, GSvector3(0.0f, 0.0f, 5.0f), *p_ItemManager, &m_OperationManager));

	p_World->AddCollideActor(ActorGroup::HitToPlayer
		, std::make_shared<DoorKey>(*p_World.get()
			, GSvector3(0.0f, 0.0f, 30.0f), *p_ItemManager, m_Info));

	p_World->AddCollideActor(ActorGroup::HitToPlayer
		, std::make_shared<RoomDoor>(*p_World.get(), GSvector3(2.7f, 0.0f, 56.0f), (GSuint)MeshName::Door, m_Info, 270.0f, m_OperationManager, OperationState::EnemyStop));


	p_World->AddCollideActor(ActorGroup::HitToPlayer
		, std::make_shared<OperationEnemy>(*p_World.get(), GSvector3(0.0f, 3.0f, 140.0f), *l_Player.get(), m_renderer, m_OperationManager));
	p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<RePopFlashLight>(
		*p_World.get(), GSvector3(10.0f, 0.0f, 125.0f), LightColor::White, *p_ItemManager, 60 * 10));


	p_World->AddCollideActor(ActorGroup::HitToPlayer
		, std::make_shared<RoomDoor>(*p_World.get(), GSvector3(2.7f, 0.0f, 166.0f), (GSuint)MeshName::Door, m_Info, 270.0f, m_OperationManager, OperationState::NormalDoor));


	p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<NormalDoor>(
		*p_World.get(), GSvector3(0.0f, 0.0f, 210.0f), (GSuint)MeshName::Door, m_Info, SceneType::GameTitle, m_OperationManager));

	p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<LockDoor>(
		*p_World.get(), GSvector3(0.0f, 0.0f, 230.5f), (GSuint)MeshName::LockDoor, m_Info, SceneType::GameTitle, m_OperationManager));

	p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<ColorDoor>(
		*p_World.get(), GSvector3(0.0f, 0.0f, 255.0f), m_Info, SceneType::GameTitle, (int)MeshName::PurpleDoor, 2, m_OperationManager, LightColor::Red, LightColor::Blue));
	p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<RePopFlashLight>(
		*p_World.get(), GSvector3(-11.0f, 0.0f, 243.0f), LightColor::Red, *p_ItemManager, 60 * 10));
	p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<RePopFlashLight>(
		*p_World.get(), GSvector3(9.0f, 0.0f, 243.0f), LightColor::Blue, *p_ItemManager, 60 * 10));


	p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<NormalDoor>(
		*p_World.get(), GSvector3(2.7f, 0.0f, 277.5f), (GSuint)MeshName::Door, m_Info, SceneType::GameTitle));


	m_Operation.SetUp(m_OperationManager);
}

void OperationScene::OnUpdate(float deltaTime)
{
	if (gsXBoxPadButtonTrigger(0, GS_XBOX_PAD_START))
	{
		m_Info.m_Pause = !m_Info.m_Pause;
		gsPlaySE((GSuint)SoundName::OpenPauseSE);
	}
}

void OperationScene::NormalUpdate(float deltaTime)
{
	gsPlayMusic();
	p_World->Update(deltaTime);
	m_UI.NormalUpdate(deltaTime);
	p_ItemManager->Update(deltaTime);
	m_Operation.Update(deltaTime);
	m_OperationManager.Update(deltaTime);

}

void OperationScene::PauseUpdate(float deltaTime)
{
	m_UI.PauseUpdate(deltaTime);
}

void OperationScene::OnDraw() const
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
	m_Operation.Draw();
}

void OperationScene::Shutdown()
{
	m_Renderer.DeleteMesh();
	m_Renderer.DeleteOctree();
	m_Renderer.DeleteTexture();
	gsDeleteShader((GSuint)ShaderName::Standerd);
	gsDeleteShader((GSuint)ShaderName::Floor);
	gsDeleteShader((GSuint)ShaderName::Anmation);
	gsDeleteShader((GSuint)ShaderName::Depth);
	m_renderer.delete_render_target();
	m_Sound.delete_sound();
	p_World = nullptr;
	m_Info.m_Goal = false;

	gsDrawSprite2D(2525, &GSvector2(0.0f, 0.0f), NULL, NULL, NULL, NULL, 0.0f);

}