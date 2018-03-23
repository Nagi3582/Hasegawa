#ifndef _LIGHT_PARAMETER_H_
#define _LIGHT_PARAMETER_H_

enum class LightColor;

class LightParameter
{
public:
	LightParameter(LightColor color);
	LightParameter(LightColor color, int batterySize);

	void Update(float deltaTime);

	void ChangeBattery();

	LightColor GetColor()const;
	int BatterySize()const;


private:
	LightColor m_Color;
	int m_Battery;


	float m_Timer;

};

#endif // !_LIGHT_PARAMETER_H_
