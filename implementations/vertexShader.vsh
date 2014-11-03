#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
uniform float loopDuration;
uniform float elapsedTime;
uniform mat4 rotation;
uniform mat4 modelMatrix;

smooth out vec4 theColor;

void main()
{
    float timeScale = 3.14159f * 2.0f / loopDuration;
    
    float currTime = mod(elapsedTime / 1000.0f, loopDuration);
    vec4 totalOffset = vec4(
        cos(currTime * timeScale) * 0.5f,
        sin(currTime * timeScale) * 0.5f,
        0.0f,
        0.0f);
    //gl_Position =  (position + totalOffset) * rotation;
	gl_Position = modelMatrix * position;
	
	//gl_Position = position;
	theColor = color;
	
}