#version 330
layout(location=0)out vec4 out_FragColor;
const int listSize=6;

in vec3 v_WorldPosition;
in vec3 v_WorldNormal;
in vec4 v_ShadowCoords[listSize];
in vec3 v_WorldTangent;
in vec3 v_WorldBinormal;
in vec2 v_TexCoord;

uniform vec3 u_LightPosition[listSize];
uniform vec3 u_CameraPosition;
uniform vec3 u_LightDirection[listSize];
uniform vec4 u_LightColor[listSize];
uniform float u_LightExponent[listSize];
uniform float u_listSize;
uniform float u_LightRange[listSize];
uniform float u_LightCosOuterAngle[listSize];
uniform float u_LightCosInnerAngle[listSize];
uniform float u_LightAreaLenge[listSize];
uniform float u_LightAreaPower[listSize];

uniform vec4 u_worldAmbient=vec4(0.1f,0.1f,0.1f,1.0f);
uniform vec4 gs_MaterialAmbient;
uniform vec4 gs_MaterialDiffuse;
uniform vec4 gs_MaterialSpecular;
uniform float gs_MaterialShininess;
uniform sampler2D u_DepthTexture0;
uniform sampler2D u_DepthTexture1;
uniform sampler2D u_DepthTexture2;
uniform sampler2D u_DepthTexture3;
uniform sampler2D u_DepthTexture4;
uniform sampler2D u_DepthTexture5;
uniform sampler2D u_BaseMap;

uniform float u_ShadowAmbient;

vec4 GetTexture(int i, vec4 tex)
{
  if(i==0)
    return texture2D( u_DepthTexture0, tex.xy );
  if(i==1)
    return texture2D( u_DepthTexture1, tex.xy );
  if(i==2)
    return texture2D( u_DepthTexture2, tex.xy );
  if(i==3)
    return texture2D( u_DepthTexture3, tex.xy );
  if(i==4)
    return texture2D( u_DepthTexture4, tex.xy );
  if(i==5)
    return texture2D( u_DepthTexture5, tex.xy );

  return texture2D( u_DepthTexture0, tex.xy );
}

float ShadowCoef(int i,float cosTheta)
{
  float lenge=abs(length(v_WorldPosition-u_LightPosition[i]));
  if(u_LightRange[i]<lenge)
  {
    // float shadow_disappearance=abs(u_LightRange[i]-lenge);
    // return shadow_disappearance*0.01f;
    return 1.0f;
  }
  vec4 shadow_coord1=v_ShadowCoords[i]/v_ShadowCoords[i].w;

  float view_d=shadow_coord1.z;

   float bias=0.005*tan(acos(cosTheta));
   bias=0.00;
  float light_d=1.0f;
  if ( GetTexture(i,shadow_coord1).z  <  shadow_coord1.z-bias)
  {
    light_d = 0.5;
  }

  float shadow_coef=1.0f;
  if(v_ShadowCoords[i].w>0.0f)
  {
    shadow_coef=light_d<view_d?0.0:1.0;
  }

  return shadow_coef;
}

float outer_light(vec3 L, int i)
{
  /* code */
  float lightDistance=length(u_LightPosition[i]-v_WorldPosition);
  float attenuation=smoothstep(u_LightRange[i],0.0f,lightDistance);
  float cosDir=dot(-L,u_LightDirection[i]);
  float spotEffect=smoothstep(u_LightCosOuterAngle[i], u_LightCosInnerAngle[i], cosDir);
  if(spotEffect<0.2)
  spotEffect=0.0f;

  spotEffect*=attenuation;
  return  spotEffect;
}

float Attenuation(float start_d,int i)
{
  float D=length(u_LightPosition[i]-v_WorldPosition);
  D+=-start_d;
  if(D<0)
  D=0;
  float A=smoothstep(u_LightAreaLenge[i],0.0f,D);

  if(A>0.75)
  A=0.75;
  return A;
}


void main(void)
{
  vec4 mixcolor=vec4(0.0,0.0,0.0,0.0);
  vec4 mixDiffuse=vec4(0.0,0.0,0.0,0.0);
  vec4 mixSpecular=vec4(0.0,0.0,0.0,0.0);
  vec4 renderColor=vec4(0.0,0.0,0.0,0.0);
  vec4 baseColor=texture(u_BaseMap,v_TexCoord);

  for(int i = 0;  i<int(u_listSize); i++)
  {
    /* code */
    vec3 L=normalize(u_LightPosition[i]-v_WorldPosition);;
    vec3 V=normalize(u_CameraPosition-v_WorldPosition);
    vec3 N=normalize(v_WorldNormal);
    vec3 H=normalize(L+V);
    float cosTheta=max(dot(N,L),0.0);

    float attenuation;

    float spotDot;
    spotDot=dot(-L, normalize(u_LightDirection[i]));
    float shadow_coef=ShadowCoef(i,cosTheta);
    float spotAttenuation;
    spotAttenuation=outer_light(L,i);

    if(length(u_LightPosition[i]-v_WorldPosition)<u_LightAreaLenge[i])
    {
      spotAttenuation+=Attenuation(0.0f,i);
      shadow_coef=1.0;
    }
    // shadow_coef=1.0f;

     mixDiffuse+=abs(u_LightColor[i]*spotAttenuation);
     mixDiffuse=u_ShadowAmbient*shadow_coef*mixDiffuse+(1.0-u_ShadowAmbient)*mixDiffuse;
     mixSpecular+=u_LightColor[i]*spotAttenuation;
     mixSpecular=u_ShadowAmbient*shadow_coef*mixSpecular+(1.0-u_ShadowAmbient)*mixSpecular;
  }
  mixDiffuse.a=1.0f;

  mixcolor=gs_MaterialAmbient*u_worldAmbient*baseColor
  +gs_MaterialDiffuse*mixDiffuse*baseColor
  +gs_MaterialSpecular*mixSpecular;
  mixcolor.a=gs_MaterialDiffuse.a;
  out_FragColor=mixcolor;
}
