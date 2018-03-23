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

	//�I���S�[����ǉ�
	void SetMusicBox(int musicBox);
	//�ʏ�h�A��ǉ�
	void SetDoor(int door);
	//3�F�h�A��ǉ�
	void SetColorDoor(int door);
	//�����F�h�A��ǉ�
	void SetMixColorDoor(int door);



private:
	int m_MusicBox;
	int m_Door;
	int m_ColorDoor;
	int m_MixColorDoor;

};


#endif // !_RESULT_SCORE_H_
