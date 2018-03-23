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
	//���b�V���ǂݍ���
	void LoadMesh(int id, const std::string& meshName);
	//�I�N�c���[�ǂݍ���
	void LoadOctree(int id, const std::string& meshName, const std::string& octreeName);

	//�e�N�X�`���[�ǂݍ���
	void LoadTexture(int id, const std::string& textureName);

	//���f���ǂݍ���
	void LoadModel(int id, const std::string& mesh, const std::string& skl, const std::string& anm);

	//���b�V���̍폜
	void DeleteMesh();
	//�I�N�c���[�̍폜
	void DeleteOctree();
	//�e�N�X�`���̍폜
	void DeleteTexture();

	//������
	void initialize();
	//�f�o�b�N�p�����[�^�[
	void show_debug_param();
	//�A�j���[�V�����̒ǉ�
	void add_anm(GSuint mesh, GSuint skeleton, GSuint animation, GSuint motion, int& vectorID);
	//�A�j���[�V�����̍X�V
	void anm_update(float deltaTime, int vectorID, const GSmatrix4& pose);
	//�A�j���[�V�����ύX
	void anm_chamge(int motion, int vectorID);
	//�A�j���[�V�����̍폜
	void remove_anm(int vectorID);
	//���C�g�ǉ�
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
	//���C�g�̍폜
	void remove_light(int vectorID);
	void clear_light();
	//���[���h�A���r�G���g�̐ݒ�
	void set_ambient(float color = 1.0f);
	//�v���W�F�N�V�����̃Z�b�g
	void set_projection(const GSmatrix4& projection);
	//����s��̃Z�b�g
	void set_view(const GSmatrix4 view);
	//�J�������W�̃Z�b�g
	void set_camera_position(const GSvector3 position);
	//���[���h��]���W�̃Z�b�g
	void set_world(const GSmatrix4& world);
	//�A�j���[�V�����t�����f���p���[���h��]���W�̃Z�b�g
	void set_anm_world();
	//�����_�[�^�[�Q�b�g�̍쐬
	void create_rendererTarget(const GSuint renderID, const float scalar = 2);
	void create_shadow_map(const GSuint renderID, const float scalar = 2);

	void draw_manager(const bool is_shadow
		, const GSuint meshID
		, const GSuint shaderID
		, const GSuint depthID
		, const bool is_animation = false
		, const int motionID = -1
		, const int anmID = -1)const;
	//�`��p�����_�[�^�[�Q�b�g�̊J�n
	void start_render_target();

	//�`��p�����_�[�^�[�Q�b�g�̏I��
	void end_render_target();
	void draw_render_target();
	//�f�v�X�e�N�X�`���쐬�J�n
	void start_depth_map(const GSuint renderID);
	//�f�v�X�e�N�X�`���쐬�I��
	void end_depth_map();
	//�����_�[�^�[�Q�b�g�̍폜
	void delete_render_target()const;
	//���C�g���̎擾
	GSuint get_light_params_size()const;
	//�A�j���[�V�����̃{�[���̍��W�擾
	GSmatrix4 get_bone_matrices(GSuint anmID,GSuint boneNum)const;


private:
	//�f�v�X�e�N�X�`���̍쐬
	void draw_depth_map_mesh(GSuint meshID
		, const GSuint shaderID
		, const bool is_animation = false
		, const int motionID = -1
		, const int anmID = -1)const;
	//���b�V���̕`��
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
