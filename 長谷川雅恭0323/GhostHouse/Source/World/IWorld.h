#ifndef _IWORLD_H_
#define _IWORLD_H_
#include "../Actor/ActorPtr.h"
#include"../UI/UIPtr.h"
#include "../Actor/CollideActorPtr.h"
#include "../GameObject/Field/FieldPtr.h"
#include "../GameObject/Field/FieldName.h"
#include <string>

enum class ActorGroup;
enum class UIGroup;

class IWorld
{
public:
	~IWorld() {}

	virtual void AddActor(ActorGroup group, const ActorPtr& actor) = 0;
	virtual void AddUI(UIGroup group, const UIPtr& ui) = 0;

	virtual void AddCollideActor(ActorGroup group, const CollideActorPtr& actor) = 0;

	virtual ActorPtr FindActor(const std::string name) = 0;
	virtual UIPtr FindUI(const std::string name) = 0;

	virtual void SetNextField(FieldName name) = 0;

	virtual FieldPtr GetField()const = 0;


};

#endif // !_IWORLD_H_
