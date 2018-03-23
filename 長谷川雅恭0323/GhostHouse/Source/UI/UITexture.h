#ifndef UI_TEXTURE_H_
#define UI_TEXTURE_H_

#include<forward_list>
#include<gslib.h>
#include<string>
#include<functional>
#include"../Utility/Number/NumberTexture.h"
#include"UIPtr.h"

class Renderer;
class IWorld;

class UITexture
{
public:
	//�R���X�g���N�^
	UITexture() = default;
	UITexture(IWorld&world
		, std::string name
		, GSvector2 position
		, int width = 64
		, int height = 64);
	//�f�X�g���N�^
	virtual ~UITexture() {}
	//������
	virtual void initialise() {};

	//�X�V
	void main_update(float deltaTime);
	//�`��
	void main_draw()const;
	//�l�̎擾
	GSuint get_param()const;
	//���O�̎擾
	std::string get_name()const;
	//�������H
	bool is_delete()const;
	//����
	void delete_UI();
	//�摜��\�������Ȃ�
	void hide_On();
	//�摜��\��������
	void hide_Off();
	//�摜��\�����Ă��邩
	bool is_Hide()const;
	//�q�̏���
	void each_children(std::function<void(UITexture&)>fn);
	//const��
	void each_children(std::function<void(const UITexture&)>fn)const;

	//�q�̌���
	UIPtr find_children(const std::string& name);
	UIPtr find_children(std::function<bool(const UITexture&)>fn);

	//�q�̒ǉ�
	void add_child(const UIPtr& child);

	//�q�̍폜
	void remove_children(std::function<bool(UITexture& other)>fn);
	void remove_children();

	//�q������
	void clear_children();

protected:
	virtual void on_update(float deltaTime) {};
	virtual void on_draw()const {};

protected:
	std::forward_list<UIPtr>m_children;
protected:
	GSvector2 m_position{ 0.0f,0.0f };
	std::string m_name{ "None" };
	IWorld* p_world{ nullptr };
	bool m_is_delete{ false };
	bool m_is_draw{ true };
	//�p�����[�^�[
	GSuint m_UI_param{ 0 };
	NumberTexture m_num{ 0,0 };
};

#endif // !UI_TEXTURE_H_