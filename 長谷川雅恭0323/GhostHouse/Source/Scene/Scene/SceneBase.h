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
	//ゲームを終了する時に呼ばれる
	void GameEnd();

	SceneType NextScene()const;
	bool Goal()const;
	void SetScore(ResultScore& score);


protected:
	//常に更新する
	virtual void OnUpdate(float deltaTime) {};
	//ゲームプレイ中の更新
	virtual void NormalUpdate(float deltaTime) {};
	//ポーズ中の更新
	virtual void PauseUpdate(float deltaTime) {};
	//ゲームプレイ中の描画
	virtual void OnDraw()const {};
	//ゲームを終了する時に呼ばれる
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
