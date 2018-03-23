#ifndef _SCENE_BASE_H_
#define _SCENE_BASE_H_
#include "../SceneType/SceneType.h"
#include "../../Utility/Renderer/Renderer.h"
#include"../../Utility/Sound/Sound.h"
#include "../SceneInfo/SceneInfo.h"
#include <string>

class ItemManager;
class ResultScore;

class SceneBase
{
public:
	SceneBase(SceneInfo& info);

	void Initialize();
	virtual void OnInitialize() = 0;
	void Update(float deltaTime);

	void Draw()const;
	virtual void Shutdown() = 0;
	//�Q�[�����I�����鎞�ɌĂ΂��
	void GameEnd();

	SceneType NextScene()const;
	bool Goal()const;
	void SetScore(ResultScore& score);


protected:
	//��ɍX�V����
	virtual void OnUpdate(float deltaTime) {};
	//�Q�[���v���C���̍X�V
	virtual void NormalUpdate(float deltaTime) {};
	//�|�[�Y���̍X�V
	virtual void PauseUpdate(float deltaTime) {};
	//�Q�[���v���C���̕`��
	virtual void OnDraw()const {};
	//�Q�[�����I�����鎞�ɌĂ΂��
	virtual void OnGameEnd() {}

	void LoadMesh(int stage, const std::string file);

	void LoadOctree(int stage, const std::string file);

	void LoadTexture(int stage, const std::string file);

	void LoadModel(int stage, const std::string& file);

	void LoadBGM(int stage, const std::string& file);

	void LoadSE(int stage, const std::string& file);


protected:
	float m_Timer{ 0 };
	Renderer m_Renderer{};
	Sound m_Sound{};
	SceneInfo& m_Info;

};

#endif // !_SCENE_BASE_H_
