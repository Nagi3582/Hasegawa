#include "Renderer.h"
#include <gslib.h>
#ifdef DEBUG
#include <iostream>

#endif // DEBUG

#include"../../Base/Screen.h"
#include"ShaderName\ShaderName.h"

#include<memory>

Renderer::Renderer()
{
	create_rendererTarget(m_draw_render_targetID - 1, 1.0f);
}

//メッシュ読み込み
void Renderer::LoadMesh(int id, const std::string & meshName)
{
#ifdef DEBUG
	std::cout << "メッシュ読み込み" << "  ID::" << std::to_string(id) << "  Name::" << meshName << std::endl;

#endif // DEBUG

	if (!gsLoadMeshEx((GSuint)id, meshName.c_str()))throw;
	m_LoadMesh.push_back(id);
}

//オクツリー読み込み
void Renderer::LoadOctree(int id, const std::string & meshName, const std::string & octreeName)
{
#ifdef DEBUG
	std::cout << "オクツリー読み込み" << "  ID::" << std::to_string(id) << "  Mesh::" << meshName << "  Octree::" << octreeName << std::endl;

#endif // DEBUG

	if (octreeName != "None")
	{
		if (!gsLoadOctree((GSuint)id, octreeName.c_str()))throw;
		m_LoadOctree.push_back(id);
	}
	if (!gsLoadMeshEx((GSuint)id, meshName.c_str()))
		throw;
	m_LoadMesh.push_back(id);
}

void Renderer::LoadTexture(int id, const std::string & textureName)
{
	if (gsLoadTexture((GSuint)id, textureName.c_str()))
	{
#ifdef DEBUG

		std::cout << "テクスチャ読み込み" << "  ID::" << std::to_string(id) << "  Name::" << textureName << std::endl;
#endif // DEBUG
	}
	else
	{
#ifdef DEBUG
		std::cout << "テクスチャ読み込み失敗" << "  ID::" << std::to_string(id) << "  Name::" << textureName << std::endl;
#endif // DEBUG
	}


	m_LoadTexture.push_back(id);
}

void Renderer::LoadModel(int id, const std::string & mesh, const std::string & skl, const std::string & anm)
{
	LoadMesh(id, mesh);
#ifdef DEBUG
	std::cout << "スケルトン読み込み" << "  ID::" << std::to_string(id) << "  Mesh::" << skl << std::endl;
	std::cout << "アニメーション読み込み" << "  ID::" << std::to_string(id) << "  Mesh::" << anm << std::endl;

#endif // DEBUG

	gsLoadSkeleton(id, skl.c_str());
	gsLoadAnimation(id, anm.c_str());
}

void Renderer::DeleteMesh()
{
	for (unsigned i = 0; i < m_LoadMesh.size(); i++)
	{
		int l_MeshID = m_LoadMesh[i];
#ifdef DEBUG
		std::cout << "メッシュ削除" << std::to_string(l_MeshID) << std::endl;
#endif // DEBUG
		gsDeleteMesh(l_MeshID);
	}
}

void Renderer::DeleteOctree()
{
	for (unsigned i = 0; i < m_LoadOctree.size(); i++)
	{
		int l_OctreeID = m_LoadOctree[i];
#ifdef DEBUG
		std::cout << "オクツリー削除" << std::to_string(l_OctreeID) << std::endl;

#endif // DEBUG

		gsDeleteOctree(l_OctreeID);
	}
}

void Renderer::DeleteTexture()
{
	for (unsigned i = 0; i < m_LoadTexture.size(); i++)
	{
		int l_TextureID = m_LoadTexture[i];
#ifdef DEBUG
		std::cout << "テクスチャー削除" << std::to_string(l_TextureID) << std::endl;

#endif // DEBUG

		gsDeleteTexture(l_TextureID);
	}
}
void Renderer::initialize()
{
	m_light_params.clear();
	m_anms.clear();
}
void Renderer::show_debug_param()
{
#ifdef DEBUG
	std::cout << "ライトの数" << m_light_params.size() << std::endl;

#endif // DEBUG

}
void Renderer::add_anm(GSuint mesh, GSuint skeleton, GSuint animation, GSuint motion, int & vectorID)
{
	int no = m_anms.size();
	vectorID = no;
	m_anms.push_back(AnimationMesh(mesh, skeleton, animation, motion));
}
void Renderer::anm_update(float deltaTime, int vectorID, const GSmatrix4& pose)
{
	m_anms[vectorID].Update(deltaTime);
	m_anms[vectorID].Calculate(pose);
	timer_ += deltaTime;
}
void Renderer::anm_chamge(int motion, int vectorID)
{
	m_anms[vectorID].ChangeMotion(motion);
}
void Renderer::remove_anm(int vectorID)
{
	//m_anms.erase(m_anms.begin() + vectorID);
}
LightParams* Renderer::add_light()
{
	int no = m_light_params.size();
	m_light_params.push_back(std::make_shared<LightParams>());
	create_shadow_map(no);
	m_light_params[no]->initialize();
	m_light_params[no]->set_ID(no);
	return m_light_params[no].get();
}

void Renderer::set_light_param(GSvector3  light_position
	, GSvector3  light_direction
	, GSvector3  light_up
	, GScolor  light_color
	, float light_inner_angle
	, float light_outer_angle
	, int  vectorID
	, float lenge
	, float area_lenge
	, float area_power)
{
	m_light_params[vectorID]->set_param(light_position
		, light_direction
		, light_up
		, light_color
		, light_inner_angle
		, light_outer_angle
		, lenge
		, area_lenge
		, area_power);
}

void Renderer::remove_light(int vectorID)
{
	//delete &m_light_params[vectorID];
	m_light_params.erase(m_light_params.begin() + vectorID);
	for (auto&light : m_light_params)
	{
		if (light->get_ID() > vectorID)
		{
			light->set_ID(light->get_ID() - 1);
		}
	}
}
void Renderer::clear_light()
{
	m_light_params.clear();
}
void Renderer::set_ambient(float color)
{
	m_world_ambient = GScolor{ color,color,color,1.0f };
}
void Renderer::set_projection(const GSmatrix4 & projection)
{
	m_projection_ = projection;
}

void Renderer::set_view(const GSmatrix4  view)
{
	m_view_ = view;
}

void Renderer::set_camera_position(const GSvector3 position)
{
	m_camera_position_ = position;
}

void Renderer::set_world(const GSmatrix4 & world)
{
	m_world_ = world;
}

void Renderer::set_anm_world()
{
	GSmatrix4 world;
	world.identity();
	m_world_ = world;
}

void Renderer::create_rendererTarget(const GSuint renderID, const float scalar)
{
	//gsCreateRenderTarget(/*m_renderer_targetID*/1 + renderID, WIDTH/scalar, HEIGHT/scalar, true, true, true);
	gsCreateRenderTarget(/*m_renderer_targetID*/1 + renderID, 1024 * 2.0f, 1024 * 2.0f, true, true, true);
}

void Renderer::create_shadow_map(const GSuint renderID, const float scalar)
{
	gsCreateRenderTargetShadowMap(1 + renderID, 1024 * 2.0f, 1024 * 2.0f, false);
}

void Renderer::draw_manager(const bool is_shadow
	, const GSuint meshID
	, const GSuint shaderID
	, const GSuint depthID
	, const bool is_animation
	, const int motionID
	, const int anmID) const
{
	if (is_shadow)
		draw_depth_map_mesh(meshID, depthID, is_animation, motionID, anmID);
	else
		draw_mesh(meshID, shaderID, is_animation, motionID, anmID);
}

void Renderer::start_render_target()
{
	gsBeginRenderTarget(m_draw_render_targetID);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw_mesh(const GSuint meshID
	, const GSuint shaderID
	, const bool is_animation
	, const int motionID
	, const int anmID) const
{
	/*ライトの個数*/
	int light_param_size = m_light_params.size();
	/*バイアス補正*/
	static const GSmatrix4 SHADOW_BIAS = GSmatrix4(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0);
	GSmatrix4 world_view_projection;
	if (is_animation)
		world_view_projection = m_view_ * m_projection_;
	else
		world_view_projection = m_world_ * m_view_*m_projection_;

	GSmatrix4 world_view = m_world_ * m_view_;
	GSmatrix4 view = m_view_;

	const int light_size = 6;
	GSmatrix4 light_view_projection[light_size];
	GSvector3 light_pos[light_size];
	GSvector3 light_direc[light_size];
	GSvector3 light_up[light_size];
	GScolor light_color[light_size];
	float light_inner_angle[light_size];
	float light_outer_angle[light_size];
	float light_lenge[light_size];
	float light_area_lenge[light_size];
	float light_area_power[light_size];

	for (int i = 0; i < light_param_size; i++)
	{
		//容量超過防止
		if (i > light_size)
		{
			light_param_size = light_size;
			break;
		}

		light_pos[i] = m_light_params[i]->get_light_pos();/*ライト座標*/
		light_direc[i] = m_light_params[i]->get_light_direc();/*ライトの向き*/
		light_up[i] = m_light_params[i]->get_light_up();/*ライトの上ベクトル*/
		light_color[i] = m_light_params[i]->get_light_color();/*ライトカラー*/
		light_inner_angle[i] = gsCos(m_light_params[i]->get_light_cos_inner_angle());/*ライトのカットオフ*/
		light_outer_angle[i] = gsCos(m_light_params[i]->get_light_cos_outer_angle());/*ライトのカットオフ*/
		light_lenge[i] = m_light_params[i]->get_lenge();//距離
		light_area_lenge[i] = m_light_params[i]->get_area_lenge();
		light_area_power[i] = m_light_params[i]->get_area_power();

		if (is_animation)
			light_view_projection[i] = m_light_view_projection_[i] * SHADOW_BIAS;/*ライト視点のプロジェクション*/

		else
			light_view_projection[i] = m_world_ * m_light_view_projection_[i] * SHADOW_BIAS;/*ライト視点のプロジェクション*/
	}

	view.inverse();

	gsBeginShader(shaderID);//シェーダー開始

	/*デプステクスチャのバインド*/
	for (int i = 0; i < light_param_size; i++)
	{
		int render_target = 1 + i;
		m_renderer_target_textureID[i] = 5 + i;
		gsBindRenderTargetDepthEx(render_target, m_renderer_target_textureID[i]);
	}
	gsSetShaderParam4f("u_worldAmbient", &m_world_ambient);
	gsSetShaderParamMatrix4("u_WorldViewProjectionMatrix", &world_view_projection);/*ワール視点のプロジェクション*/
	gsSetShaderParamMatrix4("u_WorldMatrix", &m_world_);/*回転*/
	gsSetShaderParamMatrix4("u_WorldViewMatrix", &world_view);/*ワールド視点の回転*/
	gsSetShaderParamArrayMatrix4("u_LightViewProjections", light_param_size, light_view_projection);/*ライト視点のプロジェクション*/
	gsSetShaderParamMatrix4("u_viewInversMatrix", &view);/*視点の回転*/
	gsSetShaderParamArray4f("u_LightColor", light_param_size, light_color);/*ライトカラー*/
	gsSetShaderParamArray3f("u_LightPosition", light_param_size, light_pos);/*ライト座標*/
	gsSetShaderParamArray3f("u_LightDirection", light_param_size, light_direc);/*ライトの向き*/
	gsSetShaderParamArray1f("u_LightRange", light_param_size, light_lenge);
	gsSetShaderParamArray1f("u_LightCosInnerAngle", light_param_size, light_inner_angle);/*ライトのカットオフ*/
	gsSetShaderParamArray1f("u_LightCosOuterAngle", light_param_size, light_outer_angle);/*ライトのカットオフ*/
	gsSetShaderParam1f("u_listSize", light_param_size);/*ライトの数*/
	gsSetShaderParam3f("u_CameraPosition", &m_camera_position_);/*カメラ座標*/
	gsSetShaderParam1f("u_ShadowAmbient", 0.8f);/*影の濃さ*/
	gsSetShaderParamArray1f("u_LightAreaLenge", light_param_size, light_area_lenge);
	gsSetShaderParamArray1f("u_LightAreaPower", light_param_size, light_area_power);
	/*デプステクスチャ*/
	for (int i = 0; i < light_param_size; i++)
	{
		std::string s = "u_DepthTexture" + std::to_string(i);
		gsSetShaderParamTexture(s.c_str(), m_renderer_target_textureID[i]);
	}

	/*アニメーション関係*/
	if (is_animation)
		m_anms[anmID].Draw();
	else
		gsDrawMeshEx(meshID);//メッシュ描画

	for (int i = 0; i < light_param_size; i++)
	{
		gsUnbindRenderTargetDepthEx(/*m_renderer_targetID*/1 + i, m_renderer_target_textureID[i]);/*デプステクスチャのアンバインド*/
	}
	gsEndShader();//シェーダー終了
}

void Renderer::end_render_target()
{
	gsEndRenderTarget();
}

void Renderer::draw_render_target()
{
	gsBindRenderTargetTexture(m_draw_render_targetID, 0);
	gsDrawRenderTarget(m_draw_render_targetID);
	gsUnbindRenderTargetTexture(m_draw_render_targetID, 0);
}

void Renderer::start_depth_map(const GSuint renderID)
{
	//gsBeginRenderTarget(m_renderer_targetID + 0);
	gsBeginRenderTarget(1 + renderID);
	glClear(GL_DEPTH_BUFFER_BIT);
	glCullFace(GL_FRONT);
	m_targetID = renderID;
}

void Renderer::draw_depth_map_mesh(GSuint meshID
	, const GSuint shaderID
	, const bool is_animation
	, const int motionID
	, const int anmID) const
{
	GSmatrix4 light_view;
	GSmatrix4 lightProjection;
	lightProjection.setPerspectiveRH(60, 1.0f, 0.1, 50);

	GSvector3 at = m_light_params[m_targetID]->get_light_pos() + m_light_params[m_targetID]->get_light_direc();
	light_view.setLookAtRH(m_light_params[m_targetID]->get_light_pos(), at, m_light_params[m_targetID]->get_light_up());

	GSmatrix4 world_view_projection;
	if (is_animation)
		world_view_projection = light_view * lightProjection;
	else
		world_view_projection = m_world_ * light_view*lightProjection;
	GSmatrix4 world_view = m_world_ * light_view;

	m_light_view_projection_[m_targetID] = light_view * lightProjection;

	gsBeginShader(shaderID);//シェーダー開始
	gsSetShaderParamMatrix4("u_WorldViewProjectionMatrix", &world_view_projection);
	gsSetShaderParamMatrix4("u_WorldMatrix", &m_world_);
	gsSetShaderParamMatrix4("u_WorldViewMatrix", &world_view);
	if (is_animation)
		m_anms[anmID].Draw();
	else
		gsDrawMeshEx(meshID);//メッシュ描画
	gsEndShader();//シェーダー終了
}

void Renderer::end_depth_map()
{
	glCullFace(GL_BACK);
	gsEndRenderTarget();
}


void Renderer::delete_render_target() const
{
	/*ライトの個数*/
	int light_param_size = m_light_params.size();

	for (int i = 1; i < light_param_size; i++)
	{
		//デプステクスチャのレンダーターゲット
		gsDeleteRenderTarget(i);
	}
	//描画用レンダーターゲット
	gsDeleteRenderTarget(m_depth_shaderID);
}

GSuint Renderer::get_light_params_size() const
{
	return m_light_params.size();
}

GSmatrix4 Renderer::get_bone_matrices(GSuint anmID, GSuint boneNum) const
{
	return m_anms[anmID].GetMatrices().at(boneNum);
}