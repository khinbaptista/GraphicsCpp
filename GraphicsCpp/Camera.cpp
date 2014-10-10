#include "Camera.h"

using namespace glm;

Camera::Camera(vec3 position, vec3 target, vec3 up)
{
	this->position = position;
	this->target = target;
	this->up = up;

	movementDirection = target - position;
	movementSpeed = 0;
	angularSpeed = 0;

	projection = perspective(radians(45.0f), float(16 / 9), 0.1f, 100.0f);
	view = lookAt(position, target, up);
}

Camera::~Camera(void)
{
}


Camera* Camera::New2D(int width, int height, int layer){
	Camera &camera2d = * new Camera(vec3(0, 0, layer), vec3(0, 0, -1), vec3(0, 1, 0));
	camera2d.Position(vec3(width / 2, height / 2, layer));
	camera2d.projection = ortho(0.0f, float(width), 0.0f, float(height));

	return &camera2d;
}


mat4 Camera::Projection(void){
	return projection;
}

void Camera::Projection(mat4 projection){
	this->projection = projection;
}


mat4 Camera::View(void){
	return view;
}


vec3 Camera::Position(void){
	return position;
}

void Camera::Position(vec3 position){
	this->position = position;
	view = lookAt(position, target, up);
}


vec3 Camera::Direction(void){
	return normalize(target - position);
}

void Camera::Direction(vec3 direction){
	target = position + direction;
	view = lookAt(position, target, up);
}


vec3 Camera::Target(void){
	return target;
}

void Camera::Target(vec3 target){
	this->target = target;
	view = lookAt(position, target, up);
}


float Camera::DistanceToTarget(void){
	return float((target - position).length());
}

void Camera::DistanceToTarget(float distance){
	this->Target(distance * (position + this->Direction()));
}


vec3 Camera::Up(void){
	return up;
}

void Camera::Up(vec3 up){
	this->up = up;
	view = lookAt(position, target, up);
}


vec3 Camera::MovementDirecion(void){
	return movementDirection;
}

void Camera::MovementDirecion(vec3 direction){
	this->movementDirection = direction;
}


float Camera::AngularSpeed(void){
	return angularSpeed;
}

void Camera::AngularSpeed(float speed){
	this->angularSpeed = speed;
}


float Camera::MovementSpeed(void){
	return movementSpeed;
}

void Camera::MovementSpeed(float speed){
	this->movementSpeed = speed;
}


// Methods
mat4 Camera::ModelViewProjection(mat4 model){
	return projection * view * model;
}

void Camera::Rotate(float deltaTime, bool clockwise){
	int direction = clockwise ? -1 : 1;
	Direction(glm::rotate(this->Direction(), angularSpeed * deltaTime * direction, vec3(0, 1, 0)));
}

void Camera::Rotate(float angularSpeed, float deltaTime, bool clockwise){
	int direction = clockwise ? -1 : 1;
	Direction(glm::rotate(this->Direction(), angularSpeed * deltaTime * direction, vec3(0, 1, 0)));
}

void Camera::RotateAroundTarget(float deltaTime, bool clockwise){
	int direction = clockwise ? -1 : 1;
	vec3 buffer = position - target;

	position = position + glm::rotate(buffer, angularSpeed * deltaTime * direction, vec3(0, 1, 0));
	Direction(target - position);
}

void Camera::RotateAroundTarget(float angularSpeed, float deltaTime, bool clockwise){
	int direction = clockwise ? -1 : 1;
	vec3 buffer = position - target;

	position = position + glm::rotate(buffer, angularSpeed * deltaTime * direction, vec3(0, 1, 0));
	Direction(target - position);
}