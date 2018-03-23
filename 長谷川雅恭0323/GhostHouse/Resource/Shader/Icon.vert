#version 330
layout(location=0)in vec4 in_Position;

out vec3 v_WorldPosition;

uniform mat4 u_WorldViewProjectionMatrix;
uniform mat4 u_WorldMatrix;

void main(void)
{
  v_WorldPosition=vec3(u_WorldMatrix*in_Position);
  gl_Position=u_WorldViewProjectionMatrix*in_Position;
}
