#ifndef _OPERATION_UI_H_
#define _OPERATION_UI_H_

enum class TextureName;
class CollideActor;
class OperationManager;

class OperationUI
{
public:
	OperationUI();

	void SetUp(OperationManager& operationManager);

	void Update(float deltaTime);

	void Draw()const;



private:
	void SetTexture();


private:
	TextureName m_Texture;
	TextureName m_PrevTexture;
	float m_Alpha;
	OperationManager* p_OperationManager;

	bool m_IsOperation;
	TextureName m_OperateTexture;

};


#endif // !_OPERATION_UI_H_
