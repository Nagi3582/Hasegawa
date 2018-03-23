#ifndef _TEXTURE_NAME_H_
#define _TEXTURE_NAME_H_

//************************
// IDのつけ方
// 3桁目を読み込むシーンごとに変える

// 9 = 全部のシーンで読み込む
// 1 = タイトル
// 2 = プレイシーン
// 3 = リザルト

//************************

enum class TextureName
{
	Title									= 101,	//タイトル

	Cursor									= 201,	//カーソル
	GameOver								= 280,	//ゲームオーバー文字
	Retry									= 281,	//リトライ文字
	Pause									= 290,	//ポーズ文字
	BackGame								= 205,	//ゲームに戻る文字
	TitleReturn								= 206,  //タイトルに戻る文字


	Battery									= 207,	//バッテリーUI
	Window									= 208,	//ライトUIの枠
	Red_light								= 209,	//赤いライト
	Green_light								= 210,	//緑のライト
	Blue_light								= 211,	//青いライト
	White_light								= 212,	//白いライト
	UICursor								= 213,	//ライトの選択カーソル
	Kakeru									= 214,	//ライトの個数

	Gage_Frame								= 215,	//ゲージ（フレーム）
	Gage									= 216,	//ゲージ
	GimmiccAssist							= 217,	//操作アシスト（吹き出し）
	GimmiccAssist_ButtomX					= 218,	//操作アシスト（Xボタン）
	GimmiccAssist_ButtomA					= 221,	//操作アシスト（Aボタン）
	GimmiccAssist_ButtomB					= 222,	//操作アシスト（Bボタン）
	GimmiccAssist_CulorPurple				= 223,//操作アシスト（紫いろ）
	GimmiccAssist_CulorYellow				= 224,//操作アシスト（黄色）
	GimmiccAssist_CulorLightblue			= 225,//操作アシスト（水色）


	ExclamationMark							= 219,	//敵に発見されたビックリマーク
	ExclamationRed							= 220,	//敵に発見されたら赤く縁取る

	Key										= 230,	//鍵
	Key_Window								= 231,	//鍵の取得枠

	StageTitle1								= 232,	//ステージタイトル1
	StageTitle2								= 233,	//ステージタイトル2
	StageTitle3								= 234,	//ステージタイトル3
	StageTitle4								= 235,	//ステージタイトル4
	StageTitle5								= 236,	//ステージタイトル5
	StageTitle6								= 237,	//ステージタイトル6
	StageTitle7								= 238,	//ステージタイトル7
	StageTitle8								= 239,	//ステージタイトル8
	StageTitle9								= 240,	//ステージタイトル9
	StageTitle10							= 241,	//ステージタイトル10
	StageTitle_rouka						= 242,	//ステージタイトル廊下
	StageTitleFrame							= 243,	//ステージタイトルフレーム

	ItemTakeWhiteLight						= 260,	//白いライトを入手したUI
	ItemTakeRedLight						= 261,	//赤いライトを入手したUI
	ItemTakeGreenLight						= 262,	//緑のライトを入手したUI
	ItemTakeBlueLight						= 263,	//青いライトを入手したUI
	ItemTakeBattery							= 264,	//バッテリーを入手したUI
	ItemTakeKey								= 265,	//鍵を入手したUI


	TakeLight								= 300,	//ライトを拾う見出し
	TakeLightOperation						= 301,	//ライトを拾う説明
	ChangeLight								= 302,	//ライトの切り替え説明
	PutLight								= 303,	//ライトを置く見出し
	TakeShiningLight						= 304,	//置いたライトを拾う見出し
	TakeBattery								= 305,	//バッテリーを拾う見出し
	BatteryOperation						= 306,	//バッテリーの説明
	TakeKey									= 307,	//鍵を拾う見出し
	TakeKeyOperate							= 308,	//鍵を拾う説明
	EnemyStop								= 309,	//敵の動きを止める見出し
	EnemyStopOperation						= 310,	//敵の動きを止める説明
	EnemyStopPutLight						= 311,	//置いたライトで敵の動きを止める見出し
	OpenNormalDoor							= 312,	//通常ドアの見出し
	NormalDoorOperation						= 313,	//通常ドアの説明
	OpenLockDoor							= 314,	//鍵ドアの説明
	OpenColorDoor							= 315,	//色付きドアの見出し
	ColorDoorOperate						= 316,	//色付きドアの説明
	ColorDoorPutLight						= 317,	//色付きドアライトを置く見出し
	ColorDoorPutLightOperation				= 318,	//色付きドアライトを置く説明
	ColorDoorOperate2						= 319,	//色付きドアの説明2
	NextRoom								= 320,	//つぎの部屋に移動見出し
	TutorialEnd								= 321,	//チュートリアル終了見出し
	
	OperationCharBack						= 330,	//チュートリアル見出しの背景


	MiniMapBack								= 400,	//ミニマップ背景
	MiniMapStage1							= 401,	//ステージ1ミニマップ
	MiniMapStage2							= 402,	//ステージ2ミニマップ
	MiniMapStage3							= 403,	//ステージ3ミニマップ
	MiniMapStage4							= 404,	//ステージ4ミニマップ
	MiniMapStage5							= 405,	//ステージ5ミニマップ
	MiniMapStage6							= 406,	//ステージ6ミニマップ
	MiniMapStage7							= 407,	//ステージ7ミニマップ
	MiniMapStage8							= 408,	//ステージ8ミニマップ
	MiniMapStage9							= 409,	//ステージ9ミニマップ
	MiniMapStage10							= 410,	//ステージ10ミニマップ

	MiniMapPlayer							= 420,	//ミニマップのプレイヤー位置



	Clear									= 700,	//クリアー



	ResultTitle								= 800,	//「リザルト」の文字を表示
	NextB									= 801,	//Bボタンで次に進む
	DoorIcon								= 802,	//通常ドアのアイコン
	ColorDoorIcon							= 803,	//3色ドアのアイコン
	MixColorDoorIcon						= 804,	//合成色ドアのアイコン
	MusicBoxIcon							= 805,	//オルゴールのアイコン
	Equal									= 806,	//「=」の文字を表示
	ResultScore								= 807,	//「点」の文字を表示




	NumberTexture							= 900,	//数字文字

	OperationControl						= 901,
	OperationGhost							= 902,
	OperationDoor							= 903,


	ScreenHide								= 999,	//画面の色を変える

};

#endif // !_TEXTURE_NAME_H_
