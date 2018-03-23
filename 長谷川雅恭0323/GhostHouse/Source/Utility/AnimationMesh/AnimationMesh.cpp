#include "AnimationMesh.h"

AnimationMesh::AnimationMesh()
	: m_Mesh{ 0 }
	, m_Skeleton{ 0 }
	, m_Animation{ 0,0 }
{
}

AnimationMesh::AnimationMesh(GSuint mesh, GSuint skeleton, GSuint animation, GSuint motion = 0)
	: m_Mesh(mesh)
	, m_Skeleton(skeleton)
	, m_Animation(animation, motion)
{

}

void AnimationMesh::Update(float deltaTime)
{
	//���[�V�����N���X���X�V
	m_Animation.Update(deltaTime);
}

void AnimationMesh::Draw()const
{
	//�X�P���g�������v�Z
	gsDisable(GS_CALC_SKELETON);
	//�{�[���̓��������b�V���̒��_�ɍ��킹��@�\��L���ɂ���
	gsEnable(GS_SKIN_MESH);
	//�{�[�������т���
	gsBindSkeleton(m_Skeleton);
	//�ϊ��s���m_Matrices�ɓǂݍ���
	gsSetMatrixSkeleton(m_Matrices.data());
	//�`��
	gsDrawMeshEx(m_Mesh);
}

void AnimationMesh::ChangeMotion(GSuint motion)
{
	m_Animation.ChangeMotion(motion);
}
//�X�P���g���̕ϊ��s����v�Z
void AnimationMesh::Calculate(const GSmatrix4& world)
{
	gsBindSkeleton(m_Skeleton);
	gsCalculateSkeleton(
		&world, //��]�ϊ��s��
		m_Animation.GetMatrices().data(),//�A�j���[�V�����ϊ��s��z��
		m_Matrices.data() //�p���ϊ��s��z��
		);
}

GSuint AnimationMesh::GetMotionEndTime()const
{
	return m_Animation.GetEndTime();
}

const AnimationMesh::Matrices& AnimationMesh::GetMatrices()const
{
	return m_Matrices;
}