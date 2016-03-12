#version 400 core

//inputs
in vec3 fragmentNormal;
//flat in int timeOffset;
//flat in int fragMode;

uniform vec4 color;
uniform vec3 lightPos;
uniform vec4 lightDiffuse;
//uniform vec3 ambientLightDirection;

//uniform int matID;

//outputs
out vec4 fragmentColor;
/*
float raySphere(vec3 rpos, vec3 rdir, vec3 sp, float radius, inout vec3 point, inout vec3 normal) {
  radius = radius * radius;
  float dt = dot(rdir, sp - rpos);
  if (dt < 0.0) {
    return -1.0;
  }
  vec3 tmp = rpos - sp;
  tmp.x = dot(tmp, tmp);
  tmp.x = tmp.x - dt*dt;
  if (tmp.x >= radius) {
    return -1.0;
  }
  dt = dt - sqrt(radius - tmp.x);
  point = rpos + rdir * dt;
  normal = normalize(point - sp);
  return dt;
}
*/
void main()
{

  //float luminance = 1;
  vec3 normal = normalize(fragmentNormal);
  vec3 light = normalize(lightPos);

  //vec3 ambLightDirection = normalize(ambientLightDirection);
  //float intensity;

 // bool flatShading = false;
  /*
  vec4 newColor = color;
  switch(matID){
    case 0 :
      newColor.g = sin(timeOffset * 0.1);
      newColor.b = cos(timeOffset * 0.1);
      luminance = 0;
      break;
    case 1 :
      newColor = vec4(1.0);
      luminance = 0.8;
      break;
    case 2 :
      newColor = vec4(0.0);
      luminance = 0;
      break;
    default :
      newColor = vec4(0.0, 1.0, 0.0, 1.0);
      luminance = 0;

      break;
  }

  switch(fragMode){
    case 1 :
      break;
    case 2 :
      intensity = dot(ambientLightDirection, normal);
      flatShading = true;
      break;
    case 3 :
      break;
    default:
      newColor = vec4(0.0, 0.0, 1.0, 1.0);
      break;
  }
  */
/*
  if(!flatShading)
    fragmentColor = newColor * lightDiffuse*dot(light, normal) + luminance;
  else{
    if (intensity > 0.95)
      newColor = vec4(1.0, 0.5, 0.5, 1.0);
      //newColor *= 1.0;
    else if (intensity > 0.5)
      newColor = vec4(0.6, 0.3, 0.3, 1.0);
      //newColor *= 0.6;
    else if (intensity > 0.25)
      newColor = vec4(0.4, 0.2, 0.2, 1.0);
      //newColor *= 0.4;
    else
      newColor = vec4(0.2, 0.1, 0.1, 1.0);
      //newColor *= 0.2;
    */
  fragmentColor = color * lightDiffuse*dot(light, normal);
  //}
}
/*

#version 400 core
in vec3 vertColour;
out vec4 fragColour;
void main()
{
  fragColour = vec4(vertColour,1.0);
}
*/
