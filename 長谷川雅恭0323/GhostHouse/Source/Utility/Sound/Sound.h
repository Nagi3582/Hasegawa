#ifndef SOUND_H_
#define SOUND_H_

#include <string>
#include <vector>
#include<gslib.h>

class Sound
{
public:
	Sound();
	void load_bgm(GSuint bgm_id, const std::string& bgm_name);
	void load_se(GSuint se_id, const std::string& se_name);
	void delete_sound();
	void delete_bgm();
	void delete_se();

private:
	std::vector<int> m_LoadBGM;
	std::vector<int> m_LoadSE;

};

#endif // !SOUND_H_
