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
	//モーションクラスを更新
	m_Animation.Update(deltaTime);
}

void AnimationMesh::Draw()const
{
	//スケルトン自動計算
	gsDisable(GS_CALC_SKELETON);
	//ボーンの動きをメッシュの頂点に合わせる機能を有効にする
	gsEnable(GS_SKIN_MESH);
	//ボーンを結びつける
	gsBindSkeleton(m_Skeleton);
	//変換行列をm_Matricesに読み込む
	gsSetMatrixSkeleton(m_Matrices.data());
	//描画
	gsDrawMeshEx(m_Mesh);
}

void AnimationMesh::ChangeMotion(GSuint motion)
{
	m_Animation.ChangeMotion(motion);
}
//スケルトンの変換行列を計算
void AnimationMesh::Calculate(const GSmatrix4& world)
{
	gsBindSkeleton(m_Skeleton);
	gsCalculateSkeleton(
		&world, //回転変換行列
		m_Animation.GetMatrices().data(),//アニメーション変換行列配列
		m_Matrices.data() //姿勢変換行列配列
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