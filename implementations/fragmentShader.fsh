#version 330

smooth in vec4 theColor;
out vec4 outputColor;

uniform float fragLoopDuration;
uniform float elapsedTime;

const vec4 firstColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
const vec4 secondColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);

void main()
{
	float timeScale = 3.14159f;
	float currLerp = mod(elapsedTime/1000, fragLoopDuration)/ fragLoopDuration;

    //outputColor = mix(firstColor, secondColor, sin(currLerp * timeScale));
	outputColor = theColor;
}