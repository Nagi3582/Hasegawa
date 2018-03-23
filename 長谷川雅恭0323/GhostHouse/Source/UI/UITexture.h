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
	//コンストラクタ
	UITexture() = default;
	UITexture(IWorld&world
		, std::string name
		, GSvector2 position
		, int width = 64
		, int height = 64);
	//デストラクタ
	virtual ~UITexture() {}
	//初期化
	virtual void initialise() {};

	//更新
	void main_update(float deltaTime);
	//描画
	void main_draw()const;
	//値の取得
	GSuint get_param()const;
	//名前の取得
	std::string get_name()const;
	//消すか？
	bool is_delete()const;
	//消す
	void delete_UI();
	//画像を表示させない
	void hide_On();
	//画像を表示させる
	void hide_Off();
	//画像を表示しているか
	bool is_Hide()const;
	//子の巡回
	void each_children(std::function<void(UITexture&)>fn);
	//const版
	void each_children(std::function<void(const UITexture&)>fn)const;

	//子の検索
	UIPtr find_children(const std::string& name);
	UIPtr find_children(std::function<bool(const UITexture&)>fn);

	//子の追加
	void add_child(const UIPtr& child);

	//子の削除
	void remove_children(std::function<bool(UITexture& other)>fn);
	void remove_children();

	//子を消去
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
	//パラメーター
	GSuint m_UI_param{ 0 };
	NumberTexture m_num{ 0,0 };
};

#endif // !UI_TEXTURE_H_