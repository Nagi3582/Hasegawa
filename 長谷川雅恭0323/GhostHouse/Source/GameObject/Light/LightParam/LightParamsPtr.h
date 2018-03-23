#ifndef LIGHT_PARAMS_PTR_H_
#define LIGHT_PARAMS_PTR_H_

#include<memory>

class LightParams;
using LightParamsPtr = std::shared_ptr<LightParams>;

template<class T,class ...Args>
inline LightParamsPtr new_LightParams(Args&&...args)
{
	return std::shared_ptr<T>(args...);
}
#endif // !LIGHT_PARAMS_PTR_H_
