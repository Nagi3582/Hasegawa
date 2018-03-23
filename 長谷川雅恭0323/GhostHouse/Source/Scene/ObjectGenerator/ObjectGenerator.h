#ifndef _OBJECT_GENERATOR_H_
#define _OBJECT_GENERATOR_H_
#include <gslib.h>

class World;
class CollideActor;
class Renderer;
class ItemManager;
struct SceneInfo;
enum class SceneType;
enum class FieldName;

class ObjectGenerator
{
public:
	ObjectGenerator(World& world, Renderer& renderer, ItemManager& item, SceneInfo& info, SceneType scene);

	void Generator(int stage);


private:
	void AddObject(int objectID, GSvector3 position);
	void AddField(int stage);


private:
	World* p_World;
	CollideActor* p_Player;
	Renderer* p_Renderer;
	ItemManager* p_Item;
	SceneInfo& m_Info;
	SceneType m_Scene;

};


#endif // !_OBJECT_GENERATOR_H_
