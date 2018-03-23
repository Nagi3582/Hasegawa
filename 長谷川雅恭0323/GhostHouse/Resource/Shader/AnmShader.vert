#version 330
layout(location = 0)in vec4 in_Position;
layout(location = 1)in vec4 in_BoneWeight;
layout(location = 2)in vec3 in_Normal;
layout(location = 7)in vec4 in_BoneIndices;

const int listSize=6;
out vec3 v_WorldPosition;
out vec3 v_WorldNormal;
out vec4 v_ShadowCoords[listSize];

uniform mat4 u_WorldViewProjectionMatrix;
uniform mat4 u_WorldMatrix;
uniform mat4 u_LightViewProjection;
uniform mat4 u_LightViewProjections[listSize];
uniform float u_listSize;
uniform mat4 gs_BoneMatrices[128];

void main(void)
{
  mat4 matLocal = gs_BoneMatrices[int(in_BoneIndices.x)] * in_BoneWeight.x
                + gs_BoneMatrices[int(in_BoneIndices.y)] * in_BoneWeight.y
                + gs_BoneMatrices[int(in_BoneIndices.z)] * in_BoneWeight.z
                + gs_BoneMatrices[int(in_BoneIndices.w)] * in_BoneWeight.w;
  // スキニング後のローカル座標に変換
  vec4 localPosition = matLocal * in_Position;
  vec3 localNormal  = mat3(matLocal)* in_Normal;

  v_WorldPosition=vec3(localPosition);
  v_WorldNormal=localNormal;

  for(int i = 0;  i< int(u_listSize);i ++)
  {
    /* code */
    v_ShadowCoords[i]=u_LightViewProjections[i]*localPosition;
  }

  gl_Position=u_WorldViewProjectionMatrix*localPosition;
}
