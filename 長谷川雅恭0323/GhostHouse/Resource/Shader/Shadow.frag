#version 330
layout(location=0)out vec4 out_DepthColor;

in vec4 v_ViewPosition;

uniform float u_LightLenge;
uniform vec3 u_LightPosition;

void main(void)
{
  float depth=v_ViewPosition.z/v_ViewPosition.w;
  out_DepthColor=vec4(depth,depth,depth,1.0f);
}
