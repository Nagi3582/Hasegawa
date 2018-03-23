#version 330
layout(location=0)in vec4 in_Position;

//out vec4 v_ShadowCoord;
out vec4 v_ViewPosition;

uniform mat4 u_WorldViewProjectionMatrix;
uniform mat4 u_WorldViewMatrix;

void main(void)
{
  //v_WorldNormal=mat3(u_WorldMatrix)*in_Normal;
  //v_ShadowCoord=gl_TextureMatrix[7]*gl_ModelViewMatrix*gl_Vertex;
  v_ViewPosition=u_WorldViewProjectionMatrix*in_Position;
  gl_Position=u_WorldViewProjectionMatrix*in_Position;
  //gl_FrontColor = gl_Color;                // 頂点色
  //gl_TexCoord[0] = gl_MultiTexCoord0; // 頂点テクスチャ座標

}
