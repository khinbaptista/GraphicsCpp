#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Camera.h"

int main(int argc, char *argv[]){
	Camera &camera = * Camera::New2D(800, 600);
	

	return 0;
}