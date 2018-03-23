#ifndef _PLAYER_HAND_LIGHT_H_
#define _PLAYER_HAND_LIGHT_H_
#include <gslib.h>

class CollideActor;
class IWorld;
class Renderer;
enum class MeshName;
class ItemManager;

class PlayerHandLight
{
public:
	PlayerHandLight(CollideActor& player, ItemManager& item);

	void Update(const GSmatrix4& rotate);

	void Draw(bool is_shadow, Renderer& renderer)const;



private:
	void SetMesh();

private:
	CollideActor* p_Player;
	ItemManager* p_Item;
	GSmatrix4 m_Rotate;
	MeshName m_Mesh;


};


#endif // !_PLAYER_HAND_LIGHT_H_
