#version 330
layout(location=0)in vec4 in_Position;
layout(location=2)in vec3 in_Normal;

const int listSize=6;
out vec3 v_WorldPosition;
out vec3 v_WorldNormal;
out vec4 v_ShadowCoord;
out vec4 v_ShadowCoords[listSize];

uniform mat4 u_WorldViewProjectionMatrix;
uniform mat4 u_WorldMatrix;
uniform mat4 u_LightViewProjection;
uniform mat4 u_LightViewProjections[listSize];
uniform float u_listSize;
uniform mat4 gs_BoneMatrices[128];

void main(void)
{
  v_WorldPosition=vec3(u_WorldMatrix*in_Position);
  v_WorldNormal=mat3(u_WorldMatrix)*in_Normal;

  for(int i = 0;  i< int(u_listSize);i ++)
  {
    /* code */
    v_ShadowCoords[i]=u_LightViewProjections[i]*in_Position;
  }

  gl_Position=u_WorldViewProjectionMatrix*in_Position;
}
