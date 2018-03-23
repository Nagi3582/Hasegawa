#ifndef _RENDERER_H_
#define _RENDERER_H_
#include <string>
#include <vector>
#include<map>
#include<gslib.h>
#include"../../GameObject/Light/LightParam/LightParams.h"
#include"../../GameObject/Light/LightParam/LightParamsPtr.h"
#include"../AnimationMesh/AnimationMesh.h"

enum LightType
{
	Spot,
	Point
};

class Renderer
{
public:
	Renderer();
	//メッシュ読み込み
	void LoadMesh(int id, const std::string& meshName);
	//オクツリー読み込み
	void LoadOctree(int id, const std::string& meshName, const std::string& octreeName);

	//テクスチャー読み込み
	void LoadTexture(int id, const std::string& textureName);

	//モデル読み込み
	void LoadModel(int id, const std::string& mesh, const std::string& skl, const std::string& anm);

	//メッシュの削除
	void DeleteMesh();
	//オクツリーの削除
	void DeleteOctree();
	//テクスチャの削除
	void DeleteTexture();

	//初期化
	void initialize();
	//デバックパラメーター
	void show_debug_param();
	//アニメーションの追加
	void add_anm(GSuint mesh, GSuint skeleton, GSuint animation, GSuint motion, int& vectorID);
	//アニメーションの更新
	void anm_update(float deltaTime, int vectorID, const GSmatrix4& pose);
	//アニメーション変更
	void anm_chamge(int motion, int vectorID);
	//アニメーションの削除
	void remove_anm(int vectorID);
	//ライト追加
	LightParams* add_light();
	void set_light_param(GSvector3 light_position
		, GSvector3 light_direction
		, GSvector3 light_up
		, GScolor light_color
		, float light_inner_angle
		, float light_outer_angle
		, int vectorID
		, float lenge = 40.0f
		, float area_lenge = 3.0f
		, float area_power = 1.0f);
	//ライトの削除
	void remove_light(int vectorID);
	void clear_light();
	//ワールドアンビエントの設定
	void set_ambient(float color = 1.0f);
	//プロジェクションのセット
	void set_projection(const GSmatrix4& projection);
	//視野行列のセット
	void set_view(const GSmatrix4 view);
	//カメラ座標のセット
	void set_camera_position(const GSvector3 position);
	//ワールド回転座標のセット
	void set_world(const GSmatrix4& world);
	//アニメーション付きモデル用ワールド回転座標のセット
	void set_anm_world();
	//レンダーターゲットの作成
	void create_rendererTarget(const GSuint renderID, const float scalar = 2);
	void create_shadow_map(const GSuint renderID, const float scalar = 2);

	void draw_manager(const bool is_shadow
		, const GSuint meshID
		, const GSuint shaderID
		, const GSuint depthID
		, const bool is_animation = false
		, const int motionID = -1
		, const int anmID = -1)const;
	//描画用レンダーターゲットの開始
	void start_render_target();

	//描画用レンダーターゲットの終了
	void end_render_target();
	void draw_render_target();
	//デプステクスチャ作成開始
	void start_depth_map(const GSuint renderID);
	//デプステクスチャ作成終了
	void end_depth_map();
	//レンダーターゲットの削除
	void delete_render_target()const;
	//ライト数の取得
	GSuint get_light_params_size()const;
	//アニメーションのボーンの座標取得
	GSmatrix4 get_bone_matrices(GSuint anmID,GSuint boneNum)const;


private:
	//デプステクスチャの作成
	void draw_depth_map_mesh(GSuint meshID
		, const GSuint shaderID
		, const bool is_animation = false
		, const int motionID = -1
		, const int anmID = -1)const;
	//メッシュの描画
	void draw_mesh(const GSuint meshID
		, const GSuint shaderID
		, const bool is_animation = false
		, const int motionID = -1
		, const int anmID = -1)const;

private:
	std::vector<int> m_LoadMesh;
	std::vector<int> m_LoadOctree;
	std::vector<int> m_LoadTexture;

	std::vector<LightParamsPtr>m_light_params;
	LightParams m_param[6];
	std::vector<AnimationMesh>m_anms;
	GScolor m_world_ambient;
	GSmatrix4 m_projection_;
	GSmatrix4 m_view_;
	GSmatrix4 m_world_;
	mutable GSmatrix4 m_light_view_projection_[6];
	LightType m_light_type_ = LightType::Point;

	GSvector3 m_camera_position_;
	//GScolor m_light_color_;
	//float m_light_cut_off_;
	float m_exponent;

	//GSuint m_shaderID = 0;
	GSuint m_depth_shaderID = 10;
	const GSuint m_draw_render_targetID = 10;
	const GSuint m_renderer_targetID = 1;
	mutable GSuint m_renderer_target_textureID[6];
	const int m_light_size = 6;
	int m_targetID;

	float timer_ = 0.0f;
};

#endif // !_RENDERER_H_
