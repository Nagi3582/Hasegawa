#ifndef SCORE_H_
#define SCORE_H_

#include "../../../UIObject/Result/ResultIcon.h"	

#include<gslib.h>

class ItemManager;
class ResultScore;
struct SceneInfo;

class Score
{
public:
	Score(IWorld & world, Renderer & renderer, ItemManager& item, SceneInfo& info);
	void initialize();
	void update(float deltaTime);
	void draw()const;


private:
	void drawNum()const;
	void drawScore()const;
	void drawMultiply()const;
	void drawTortalScore()const;

private:
	GSvector3 m_position;
	ResultIcon m_ResultIcon;
	ItemManager* p_Item;
	SceneInfo& m_Info;
	int m_Numbers[8];
	int m_Scores[8];
};

#endif // !SCORE_H_