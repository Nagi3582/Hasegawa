#version 330
layout(location=0)in vec4 in_Position;
layout(location = 1)in vec4 in_BoneWeight;
layout(location = 7)in vec4 in_BoneIndices;

out vec4 v_ViewPosition;

uniform mat4 u_WorldViewProjectionMatrix;
uniform mat4 gs_BoneMatrices[128];

void main(void)
{
  mat4 matLocal = gs_BoneMatrices[int(in_BoneIndices.x)] * in_BoneWeight.x
                + gs_BoneMatrices[int(in_BoneIndices.y)] * in_BoneWeight.y
                + gs_BoneMatrices[int(in_BoneIndices.z)] * in_BoneWeight.z
                + gs_BoneMatrices[int(in_BoneIndices.w)] * in_BoneWeight.w;
  vec4 localPosition = matLocal * in_Position;

  v_ViewPosition=vec4(u_WorldViewProjectionMatrix*localPosition);//u_WorldViewProjectionMatrix*in_Position;
  gl_Position=u_WorldViewProjectionMatrix*localPosition;
}
