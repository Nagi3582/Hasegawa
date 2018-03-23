#ifndef _FILE_NAME_H_
#define _FILE_NAME_H_

enum class FieldName
{
	Stage							= 2000,
	Floor							= 2001,
	Collide							= 2002,
	Wall							= 2003,

	//Stage1						= 2010,	//ステージ1
	//Stage1Floor					= 2011,	//ステージ1床
	//Stage1Collide				= 2012,	//ステージ1障害物の当たり判定
	//Stage1CollideWall			= 2013,	//ステージ1壁だけの当たり判定

	//Stage2						= 2020,	//ステージ2
	//Stage2Floor					= 2021,	//ステージ2床
	//Stage2Collide				= 2022,	//ステージ2障害物の当たり判定
	//Stage2CollideWall			= 2023,	//ステージ2壁だけの当たり判定

	//Stage3						= 2030,	//ステージ3
	//Stage3Floor					= 2031,	//ステージ3床
	//Stage3Collide				= 2032,	//ステージ3障害物の当たり判定
	//Stage3CollideWall			= 2033,	//ステージ3壁だけの当たり判定

	//Stage1 = 2040,	//ステージ1
	//Stage1Floor = 2041,	//ステージ1床
	//Stage1Collide = 2042,	//ステージ1障害物の当たり判定
	//Stage1CollideWall = 2043,	//ステージ1壁だけの当たり判定

	//Stage2 = 2050,	//ステージ2
	//Stage2Floor = 2051,	//ステージ2床
	//Stage2Collide = 2052,	//ステージ2障害物の当たり判定
	//Stage2CollideWall = 2053,	//ステージ2壁だけの当たり判定

	//Stage3 = 2060,	//ステージ3
	//Stage3Floor = 2061,	//ステージ3床
	//Stage3Collide = 2062,	//ステージ3障害物の当たり判定
	//Stage3CollideWall = 2063,	//ステージ3壁だけの当たり判定

	//Stage1 = 2070,	//ステージ1
	//Stage1Floor = 2071,	//ステージ1床
	//Stage1Collide = 2072,	//ステージ1障害物の当たり判定
	//Stage1CollideWall = 2073,	//ステージ1壁だけの当たり判定

	//Stage2 = 2080,	//ステージ2
	//Stage2Floor = 2081,	//ステージ2床
	//Stage2Collide = 2082,	//ステージ2障害物の当たり判定
	//Stage2CollideWall = 2083,	//ステージ2壁だけの当たり判定

	//Stage3 = 2090,	//ステージ3
	//Stage3Floor = 2091,	//ステージ3床
	//Stage3Collide = 2092,	//ステージ3障害物の当たり判定
	//Stage3CollideWall = 2093,	//ステージ3壁だけの当たり判定

	//Stage3 = 2100,	//ステージ3
	//Stage3Floor = 2101,	//ステージ3床
	//Stage3Collide = 2102,	//ステージ3障害物の当たり判定
	//Stage3CollideWall = 2103,	//ステージ3壁だけの当たり判定

	ThirdStage = 2033,	//ステージ3

	TitleStage = 1000, //タイトル
	TitleStageCollide = 1001, //タイトル当たり判定 
	ResultStage = 3000,	//リザルト画面の壁
	ResultFloor = 3002,	//リザルト画面の床z

	None,
};

#endif // !_FILE_NAME_H_
