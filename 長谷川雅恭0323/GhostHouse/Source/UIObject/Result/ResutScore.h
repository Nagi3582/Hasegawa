#ifndef _RESULT_SCORE_H_
#define _RESULT_SCORE_H_

class ResultScore
{
public:
	ResultScore();

	void Initialize();

	int MusicBoxSize()const;
	int DoorSize()const;
	int ColorDoorSize()const;
	int MixColorDoorSize()const;

	//オルゴールを追加
	void SetMusicBox(int musicBox);
	//通常ドアを追加
	void SetDoor(int door);
	//3色ドアを追加
	void SetColorDoor(int door);
	//合成色ドアを追加
	void SetMixColorDoor(int door);



private:
	int m_MusicBox;
	int m_Door;
	int m_ColorDoor;
	int m_MixColorDoor;

};


#endif // !_RESULT_SCORE_H_
