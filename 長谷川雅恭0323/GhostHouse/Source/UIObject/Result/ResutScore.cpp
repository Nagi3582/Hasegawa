#include "ResutScore.h"

ResultScore::ResultScore()
	: m_MusicBox{ 0 }
	, m_Door{ 0 }
	, m_ColorDoor{ 0 }
	, m_MixColorDoor{ 0 }
{
}

void ResultScore::Initialize()
{
	m_MusicBox = 0;
	m_Door = 0;
	m_ColorDoor = 0;
	m_MixColorDoor = 0;
}

int ResultScore::MusicBoxSize() const
{
	return m_MusicBox;
}

int ResultScore::DoorSize() const
{
	return m_Door;
}

int ResultScore::ColorDoorSize() const
{
	return m_ColorDoor;
}

int ResultScore::MixColorDoorSize() const
{
	return m_MixColorDoor;
}

void ResultScore::SetMusicBox(int musicBox)
{
	m_MusicBox += musicBox;
}

void ResultScore::SetDoor(int door)
{
	m_Door += door;
}

void ResultScore::SetColorDoor(int door)
{
	m_ColorDoor += door;
}

void ResultScore::SetMixColorDoor(int door)
{
	m_MixColorDoor += door;
}
