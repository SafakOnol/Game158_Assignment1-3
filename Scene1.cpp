#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene1.h"
#include "MMath.h"
#include "Debug.h"
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

Scene1::Scene1() :sphere(nullptr), mesh(nullptr), shader(nullptr) {
	Debug::Info("Created Scene1: ", __FILE__, __LINE__);
}

Scene1::~Scene1() {
	Debug::Info("Deleted Scene1: ", __FILE__, __LINE__);
}

bool Scene1::OnCreate() {
	Debug::Info("Loading assets Scene1: ", __FILE__, __LINE__);

	engineFail = false;
	time = 0.0f;
	timeTrack = 0.0f;
	torqueValue = 0.0f;
	Force = Vec3(50000000.0f, 0.0f, 0.0f);

	ship = new PhysicsObject(1000000.0f, 26700000000.0f);
	ship->OnCreate();

	/*sphere = new Actor(nullptr);
	sphere->OnCreate();*/

	mesh = new Mesh(nullptr, "meshes/Rocket.obj");
	if (mesh->OnCreate() == false)
	{
		Debug::Error("Can't load Mesh()", __FILE__, __LINE__);
	}

	shader = new Shader(nullptr, "shaders/textureVert.glsl" , "shaders/textureFrag.glsl");
	if (shader->OnCreate() == false)
	{
		Debug::Error("Shader failed to render", __FILE__, __LINE__);
	}
	
	texture = new Texture();
	if (texture->LoadImage("textures/1001_Base_Color.png") == false)
	{
		Debug::Error("Can't load spaceshuttle texture", __FILE__, __LINE__);
	};

	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), (Vec3(0.0f, 1.0f, 0.0f)));
	modelMatrix.loadIdentity();

	lightPos[0] = Vec3(3.0f, 1.0f, -5.5f);
	lightPos[1] = Vec3(-3.0f, 1.0f, -5.5f);
	lightPos[2] = Vec3(0.0f, 3.0f, -5.5f);
	lightPos[3] = Vec3(0.0f, -3.0f, -5.5f);

	diffuse[0] = Vec4(0.6, 0.6, 0.6, 0.0);
	diffuse[1] = Vec4(0.6, 0.6, 0.6, 0.0);
	diffuse[2] = Vec4(0.6, 0.6, 0.6, 0.0);
	diffuse[3] = Vec4(0.6, 0.6, 0.6, 0.0);

	specular[0] = 0.5 * diffuse[0];
	specular[1] = 0.5 * diffuse[1];
	specular[2] = 0.5 * diffuse[2];
	specular[3] = 0.5 * diffuse[3];


	return true;
}

void Scene1::OnDestroy() {
	Debug::Info("Deleting assets Scene1: ", __FILE__, __LINE__);

	/*sphere->OnDestroy();
	delete sphere;*/

	ship->OnDestroy();
	delete ship;

	mesh->OnDestroy();
	delete mesh;

	shader->OnDestroy();
	delete shader;

	delete texture;
}

void Scene1::HandleEvents(const SDL_Event &sdlEvent) {
	switch( sdlEvent.type ) {
    case SDL_KEYDOWN:
		break;

	case SDL_MOUSEMOTION:          
		break;

	case SDL_MOUSEBUTTONDOWN:              
		break; 

	case SDL_MOUSEBUTTONUP:            
	break;

	default:
		break;
    }
}

void Scene1::Update(const float deltaTime) {
	
	
	//modelMatrix = MMath::rotate(50.0f*totalTime, Vec3(0.707f, 0.707f, 1.0f));

	time += deltaTime;

	timeTrack += deltaTime;
	if (timeTrack >= 0.999) // calling the funcions and print statemens in every 60 frames, apprx in every 1 second.
	{
		ship->csv(time, torqueValue);

		//printf("Time, Torque, AngAccel, AngVel, Angle, Force.x, Force.y, Accel.x, Accel.y, Vel.x, Vel.y, Pos.x, Pos.y\n");			
		std::cout
			<< std::setfill(' ') << std::setw(1) << "|" << std::setw(7) << std::left << "Time" << std::setprecision(2) << std::setw(1) << "|" << std::setw(10)
			<< "Torque" << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << "AngAccel" << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< "AngVel" << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << "Angle" << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< "Force.x" << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << "Force.y" << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< "Accel.x" << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << "Accel.y" << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< "Vel.x" << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << "Vel.y" << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< "Pos.x" << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << "Pos.y" << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< std::endl;

		/*printf("%f %f %f %f %f %f %f %f %f %f %f %f %f\n",Time, "torque", Ship->GetAngularAccel(), Ship->GetAngularVel(), Ship->GetAngle(), Ship->GetForce().x,
			Ship->GetForce().y, Ship->GetAccel().x, Ship->GetAccel().y, Ship->GetVel().x, Ship->GetVel().y, Ship->GetPos().x, Ship->GetPos().y);*/

		std::cout
			<< std::setfill(' ') << std::setw(1) << "|" << std::setw(7) << std::left << time << std::setprecision(2) << std::setw(1) << "|" << std::setw(10)
			<< torqueValue << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << ship->GetAngularAccel() << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< ship->GetAngularVel() << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << ship->GetAngle() << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< ship->GetForce().x << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << ship->GetForce().y << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< ship->GetAccel().x << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << ship->GetAccel().y << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< ship->GetVel().x << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << ship->GetVel().y << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< ship->GetPos().x << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << ship->GetPos().y << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< std::endl;
		timeTrack = 0.0f;
	}

	// Calling all the functions!!!

	Physics::ApplyForce(Force, *ship);
	Physics::SimpleNewtonMotion(*ship, deltaTime);

	if (time >= 5.0 && engineFail == false) { engineFail = true; Force.x *= 0.5; }

	if (engineFail == true)
	{
		torqueValue = 629100000.0f;
		Physics::ApplyTorque(torqueValue, *ship);
		Physics::RigidBodyRotation(*ship, deltaTime);
		Force = Physics::rotateZ(Force, *ship);
	}

	if (time >= 35.0 && engineFail == true) { torqueValue = 0.0; Force = Vec3(0.0f, 0.0f, 0.0f); }

	float scaleValue = 0.001;

	modelMatrix = 
		MMath::translate(Vec3(-3.0f, 0.0f, 0.0f)) *
		MMath::translate(ship->GetPos() * scaleValue)  *
		MMath::rotate(ship->GetAngle() * RADIANS_TO_DEGREES, 0.0, 0.0, 1.0) *
		MMath::rotate(270.0f, Vec3(0.0f, 0.0f, 1.0f))*
		MMath::scale(scaleValue, scaleValue, scaleValue);
		

}

void Scene1::Render() const {
	/// Clear the screen
	glClearColor(0.95f, 0.7f, 0.3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrix);
	glUniform3fv(shader->GetUniformID("lightPos[0]"), 10, *lightPos);
	glUniform4fv(shader->GetUniformID("diffuse[0]"), 10, *diffuse);
	glUniform4fv(shader->GetUniformID("specular[0]"), 10, *specular);
	glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
	mesh->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}



	
