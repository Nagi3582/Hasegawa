#ifndef _ITEM_BASE_H_
#define _ITEM_BASE_H_
#include "../../../Actor/CollideActor.h"
#include "../../../Utility/Asset/MeshName.h"


class ItemBase :public CollideActor
{
public:
	ItemBase(IWorld& world, std::string name, GSvector3 position,Shape* shape);


protected:
	void SetUp(MeshName name);



private:
	MeshName m_Mesh;

};

#endif // !_ITEM_BASE_H_
