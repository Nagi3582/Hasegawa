#ifndef _SCENE_INFO_H_
#define _SCENE_INFO_H_
#include <gslib.h>

enum class SceneType;

struct SceneInfo
{
	bool m_Pause = false;
	bool m_Goal = false;
	bool m_PlayerDead = false;
	SceneType m_NextScene;
	SceneType m_CurrentScene;

	bool m_Direction = false;

	bool m_GetKey = false;


	int m_MusicBox = 0;
	int m_Door = 0;
	int m_ColorDoor = 0;
	int m_MixColorDoor = 0;


	float m_Red = 0.0f;
	float m_Green = 0.0f;
	float m_Blue = 0.0f;
	float m_Alpha = 1.0f;

};

#endif // !_SCENE_INFO_H_
