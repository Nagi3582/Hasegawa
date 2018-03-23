#ifndef _FIELD_H_
#define _FIELD_H_
#include <gslib.h>
#include "FieldName.h"
#include "../../Utility/Renderer/ShaderName/ShaderName.h"

class Ray;
class Line;
class BoundingSphere;
class Renderer;

class Field
{
public:
	Field(FieldName field);
	Field(FieldName field, ShaderName shader);

	bool IsCollide(const Ray& ray, GSvector3* intersect = nullptr, GSplane* plane = nullptr, bool hitObj = true);

	bool IsCollide(const Line& line, GSvector3* intersect = nullptr, GSplane* plane = nullptr, bool hitObj = true);

	bool IsCollide(const BoundingSphere& sphere, GSvector3* intersect = nullptr, bool hitObj = true);

	void Draw(bool is_shadow, Renderer& renderer)const;

	void OnEnable();
	void NotEnable();

	void SetNextField(FieldName field);


private:
	void DrawField(bool is_shadow, Renderer&m_renderer)const;
	void DrawCollider(Renderer& m_renderer)const;

private:
	bool m_Enable;//有向か

	GSuint m_CurrentField; //表示するフィールド
	GSuint m_NextField;	   //次のフィールド

	GSuint m_Floor;		   //床のID(ステージID + 1)
	GSuint m_CollideField; //当たり判定用(ステージ + 2)
	GSuint m_CollideWall;  //壁の当たり判定用ID(ステージID + 3)
	GSuint m_Texture;	   //モデルのテクスチャー表示用ID(ステージID + 4)

	float m_Timer;		   //フィールド変更用のタイマー

	ShaderName m_Shader;


};

#endif // !_FIELD_H_