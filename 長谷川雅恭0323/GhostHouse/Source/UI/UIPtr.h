#ifndef UI_PTR_H_
#define UI_PTR_H_

#include<memory>

//UI�|�C���^
class UITexture;
using UIPtr = std::shared_ptr<UITexture>;

//UI����
template<class T,class ...Args>
inline UIPtr new_UI(Args&&...args)
{
	return std::make_shared<T>(args...);
};

#endif // !UI_PTR_H_