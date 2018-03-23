#include "Player.h"
#include "../../../Collide/BoundingSphere.h"
#include "../../../Utility/Asset/MeshName.h"
#include "../../../Utility/Asset/AnimationName.h"
#include "../../Light/PlayerLight.h"
#include"../../../Utility/Renderer/Renderer.h"
#include"../../../Utility/Renderer/ShaderName/ShaderName.h"

#include "../../../World/IWorld.h"
#include "../../../Actor/ActorGroup.h"


#include <iostream>


Player::Player(IWorld & world, const GSvector3 position, Renderer& renderer, ItemManager& item, SceneInfo& info, bool is_operation)
	: ModelBase{ world, "Player", position, new BoundingSphere(GSvector3(0.0f, 0.0f, 0.0f), 2.0f) }
	, m_player_light{ this ,renderer ,world ,item }
	, m_Manager{ world, *this, item ,renderer,info }
	, m_AnmID{ 0 }
	, p_Renderer{ &renderer }
	, m_MotionID{ 2 }
	, m_HandLight{ *this ,item }
{
	m_Position.y = -0.05f;
	SetAnimation(renderer, MeshName::Player, m_MotionID);
	if (is_operation == false)
		m_Manager.SetUp(renderer);
}

void Player::OnUpdate(float deltaTime)
{
	m_Manager.Update(deltaTime);

	m_Rotate = m_Manager.GetRotate();
	m_Rotate.rotateY(180.0f);
	m_Position += m_Manager.GetVelocity(deltaTime);

	HitField();

	p_Renderer->anm_chamge(m_Manager.GetMotionID(), m_AnmID);

	p_Renderer->anm_update(deltaTime, m_AnmID, GetPose());
	m_player_light.update(deltaTime);

	m_HandLight.Update(p_Renderer->get_bone_matrices(m_AnmID, 7));
}

void Player::SubDraw(bool is_shadow, Renderer& renderer) const
{
	GSmatrix4 pose;
	pose.identity();
	renderer.set_world(pose);
	renderer.draw_manager(is_shadow
		, (GSuint)MeshName::Player
		, (GSuint)ShaderName::Anmation
		, (GSuint)ShaderName::AnmDepth
		, true
		, 1
		, m_AnmID);


	m_player_light.draw(renderer);
	m_HandLight.Draw(is_shadow, renderer);
	//p_Body->Translate(m_Position)->Draw();
}

void Player::OnCollide(CollideActor & other)
{
	m_Manager.Collide(other);
}

PlayerManager & Player::get_manager()
{
	return m_Manager;
}
