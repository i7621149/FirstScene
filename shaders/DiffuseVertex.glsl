#version 400 core

//inputs
layout(location = 0) in vec3 inVert;
layout(location = 2) in vec3 inNormal;

//uniform int mode;
uniform mat4 MVP;
//uniform int time;

//outputs
out vec3 fragmentNormal;
//flat out int timeOffset;
//flat out int fragMode;

void main()
{

  fragmentNormal = inNormal;

//  timeOffset = time;

  vec4 position = MVP *vec4(inVert, 1.0);

/*
  switch(mode){
    case 1: //sin wave
      position.y += sin(position.x * 0.5 + 0.1 * (time));
      break;
    case 2: //toon
      break;
    case 3:
      break;
    default:
      break;
  }

  fragMode = mode;
  */
  gl_Position = position;
}

/*

#version 400 core

layout (location = 0) in vec3  inPosition;
layout (location = 1) in vec3 inColour;
out vec3 vertColour;
void main()
{
   gl_Position = vec4(inPosition, 1.0);
   if (inPosition.x >0.0 && inPosition.y<0.5)
    vertColour = inColour;
   else vertColour=vec3(1,1,1);
}
*/
