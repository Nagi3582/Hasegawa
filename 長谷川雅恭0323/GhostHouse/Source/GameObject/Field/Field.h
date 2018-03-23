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
	bool m_Enable;//�L����

	GSuint m_CurrentField; //�\������t�B�[���h
	GSuint m_NextField;	   //���̃t�B�[���h

	GSuint m_Floor;		   //����ID(�X�e�[�WID + 1)
	GSuint m_CollideField; //�����蔻��p(�X�e�[�W + 2)
	GSuint m_CollideWall;  //�ǂ̓����蔻��pID(�X�e�[�WID + 3)
	GSuint m_Texture;	   //���f���̃e�N�X�`���[�\���pID(�X�e�[�WID + 4)

	float m_Timer;		   //�t�B�[���h�ύX�p�̃^�C�}�[

	ShaderName m_Shader;


};

#endif // !_FIELD_H_