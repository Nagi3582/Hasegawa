#include "MusicBox.h"
#include "../../../Utility/Asset/SoundName.h"
#include "../../../Utility/Renderer/Renderer.h"
#include"../../../Collide/BoundingSphere.h"
#include "../../../Utility/Renderer/ShaderName/ShaderName.h"
#include "../../../Scene/SceneInfo/SceneInfo.h"


#include <GSmusic.h>
#include "../../../Utility/Asset/SoundName.h"


MusicBox::MusicBox(IWorld & world, GSvector3 position, SceneInfo& info)
	:CollideActor(world, "Item", position, new BoundingSphere(GSvector3(0.0f, 0.0f, 0.0f), 5.0f))
	, m_Info{ info }
{

}

void MusicBox::OnUpdate(float deltaTime)
{
	gsPlayBGM((GSuint)SoundName::MusixBox_BGM);
}

void MusicBox::OnCollide(CollideActor & other)
{
	if (other.GetName() == "Player")
	{
		gsStopBGM();
		Dead();
		gsStopMusic();
		gsBindMusic((GSuint)SoundName::PlayScene_BGM);
		gsPlaySE((GSuint)SoundName::GetItemSE);
		m_Info.m_MusicBox++;
	}
}

void MusicBox::OnDraw(bool is_shadow, Renderer & renderer) const
{
	renderer.set_world(GetPose());
	renderer.draw_manager(is_shadow
		, (GSuint)MeshName::MusixBox
		, (GSuint)ShaderName::Standerd
		, (GSuint)ShaderName::Depth);

}
