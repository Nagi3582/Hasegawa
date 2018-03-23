#ifndef _SCENE_TYPE_H_
#define _SCENE_TYPE_H_


enum class SceneType
{
	GameTitle			= 0,	   // csvのステージ番号と合わせる
	GamePlay			= 1,

	Stage1				= 1,
	Stage2				= 2,
	Stage3				= 3,
	Stage4				= 4,
	Stage5				= 5,
	Stage6				= 6,
	Stage7				= 7,
	Stage8				= 8,
	Stage9				= 9,		
	Stage10				= 10,


	GameOver			= 100,
	GameResult			= 101,	   // リザルトシーン
	Operation			= 102,
	GameClear			= 103,

	ShaderTest			= 103,     //シェーダーテスト用

	Debug				= 104,	   //デバック用ステージ

	None				= 1000,	   //どのステージでも読み込むリソース用

};

#endif // !_SCENE_TYPE_H_
