#include "Sound.h"
#include<GSmusic.h>
#ifdef DEBUG
#include <iostream>

#endif // DEBUG

#include"../../Base/Screen.h"

Sound::Sound()
{
	m_LoadBGM.clear();
	m_LoadSE.clear();
}

void Sound::load_bgm(GSuint bgm_id, const std::string & bgm_name)
{
	if (gsLoadMusic(bgm_id, bgm_name.c_str(), true))
	{
#ifdef DEBUG
		std::cout << "BGM“Ç‚Ýž‚Ý" << "  ID::" << std::to_string(bgm_id) << "  Name::" << bgm_name << std::endl;

#endif // DEBUG

		m_LoadBGM.push_back(bgm_id);
	}
	else
	{
#ifdef DEBUG
		std::cout << "BGM“Ç‚Ýž‚ÝŽ¸”s" << "  ID::" << std::to_string(bgm_id) << "  Name::" << bgm_name << std::endl;

#endif // DEBUG

		throw;
	}
}

void Sound::load_se(GSuint se_id, const std::string & se_name)
{
	if (gsLoadSE(se_id, se_name.c_str(), 60, false))
	{
#ifdef DEBUG
		std::cout << "SE“Ç‚Ýž‚Ý" << "  ID::" << std::to_string(se_id) << "  Name::" << se_name << std::endl;

#endif // DEBUG

		m_LoadBGM.push_back(se_id);
	}
	else
	{
#ifdef DEBUG
		std::cout << "SE“Ç‚Ýž‚ÝŽ¸”s" << "  ID::" << std::to_string(se_id) << "  Name::" << se_name << std::endl;

#endif // DEBUG

		throw;
	}
}

void Sound::delete_sound()
{
	delete_bgm();
	delete_se();
}

void Sound::delete_bgm()
{
	for (int i = 0; i < m_LoadBGM.size(); ++i)
	{
		gsDeleteMusic(m_LoadBGM[i]);
	}
}

void Sound::delete_se()
{
	for (int i = 0; i < m_LoadSE.size(); ++i)
	{
		gsDeleteSE(m_LoadSE[i]);
	}
}
