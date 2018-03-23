#version 330
layout(location=0)out vec4 out_FragColor;

in vec3 v_WorldPosition;
uniform vec4 gs_MaterialAmbient;
uniform vec4 gs_MaterialDiffuse;
uniform vec4 gs_MaterialSpecular;
uniform float gs_MaterialShininess;

void main(void)
{
  vec4 color=gs_MaterialAmbient+gs_MaterialDiffuse+gs_MaterialSpecular;
  color.a=1.0;
  out_FragColor=color;
}
