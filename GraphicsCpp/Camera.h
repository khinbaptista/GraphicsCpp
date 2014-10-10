#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

using namespace glm;

class Camera
{
protected:
	mat4 projection;
	mat4 view;

	vec3 position;
	vec3 target;
	vec3 up;

	vec3 movementDirection;
	float angularSpeed;
	float movementSpeed;

public:
	// Creates a new camera
	Camera(vec3 position, vec3 target, vec3 up);

	~Camera(void);
	
	// Camera 2D (suitable for sprites and GUI)
	static Camera* New2D(int width, int height, int layer = 5);

	// Gets the projection matrix of this camera
	mat4 Projection(void);

	// Sets the projection matrix of this camera
	void Projection(mat4 projection);

	// Gets the view matrix of this camera
	mat4 View(void);
	
	// Gets the position of this camera
	vec3 Position(void);

	// Sets the position of this camera
	void Position(vec3 position);

	// Gets the direction of this camera (note: direction is a unit vector pointing towards the target of the camera)
	vec3 Direction(void);

	// Sets the direction of this camera (note: direction is a unit vector pointing towards the target of the camera)
	void Direction(vec3 direction);

	// Gets the target of this camera (the point in the world where the camera points towards)
	vec3 Target(void);

	// Sets the target of this camera (the point in the world where the camera points towards)
	void Target(vec3 target);

	// Gets the distance between the camera and its target
	float DistanceToTarget(void);

	// Sets the distance between the camera and its target
	void DistanceToTarget(float distance);

	// Gets the up vector of this camera
	vec3 Up(void);

	// Sets the up vector of this camera
	void Up(vec3 up);

	// Gets the movement direction of this camera (does not affect the image rendered)
	vec3 MovementDirecion(void);
	
	// Sets the movement direction of this camera (does not affect the image rendered)
	void MovementDirecion(vec3 direction);

	// Gets the angular speed of this camera (speed with which this camera rotates)
	float AngularSpeed(void);

	// Sets the angular speed of this camera (speed with which this camera rotates)
	void AngularSpeed(float speed);

	// Gets the movement speed of this camera (speed with which this camera moves)
	float MovementSpeed(void);
	
	// Sets the movement speed of this camera (speed with which this camera moves)
	void MovementSpeed(float speed);

	// Given a model matrix, returns the MVP matrix
	mat4 ModelViewProjection(mat4 model);

	// Rotate this camera around itself in the Y-axis
	void Rotate(float deltaTime = 1, bool clockwise = true);

	// Rotate this camera around itself in the Y-axis using the specified angular speed
	void Rotate(float angularSpeed, float deltaTime = 1, bool clockwise = true);

	// Rotate this camera around its target in the Y-axis
	void RotateAroundTarget(float deltaTime = 1, bool clockwise = true);

	// Rotate this camera around its target in the Y-axis with the specified angular speed
	void RotateAroundTarget(float angularSpeed, float deltaTime = 1, bool clockwise = true);
};

