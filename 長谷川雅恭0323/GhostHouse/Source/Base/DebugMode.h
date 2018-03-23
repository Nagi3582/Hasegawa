#ifndef _DEBUG_MODE_H_
#define _DEBUG_MODE_H_
#include <list>
#include "../Scene/SceneType/SceneType.h"

const float FPS = 30;

#ifdef _DEBUG


const bool FULL_SCREEN = false;
const SceneType START_SCENE = SceneType::GameTitle;

#else

//フルスクリーンにしたいときはコメント外す
#define _MASTER

#ifdef _MASTER

const bool FULL_SCREEN = true;
const SceneType START_SCENE = SceneType::GameTitle;

#else

const bool FULL_SCREEN = false;
const SceneType START_SCENE = SceneType::GameTitle;

#endif //_MASTER
#endif //_DEBUG


#endif // !_DEBUG_MODE_H_

