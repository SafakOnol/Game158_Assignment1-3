#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene2.h"
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

Scene2::Scene2() :sphere(nullptr), plane(nullptr), mesh(nullptr), shader(nullptr), texture(nullptr) {
	Debug::Info("Created Scene2: ", __FILE__, __LINE__);
}

Scene2::~Scene2() {
	Debug::Info("Deleted Scene2: ", __FILE__, __LINE__);
}

bool Scene2::OnCreate() {
	Debug::Info("Loading assets Scene2: ", __FILE__, __LINE__);
	
	
	plane = new Plane(Vec3(-0.707f, 0.707f, 0.0f), 0.0f);

	sphere = new PhysicsObject();
	sphere->SetVel(Vec3(1.0f, 0.0f, 0.0f));
	sphere->SetPos(Vec3(-6.0f, 0.0f, 0.0f));
	sphere->SetRadius(1.12f);
	sphere->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	sphere->GetMesh()->OnCreate();
	sphere->SetTexture(new Texture());
	sphere->GetTexture()->LoadImage("textures/evilEye.jpg");
	sphere->OnCreate();

	planePhysObj = new PhysicsObject;
	planePhysObj->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	planePhysObj->GetMesh()->OnCreate();
	planePhysObj->SetTexture(new Texture());
	planePhysObj->OnCreate();

	


	shader = new Shader(nullptr, "shaders/textureVert.glsl" , "shaders/textureFrag.glsl");
	if (shader->OnCreate() == false)
	{
		Debug::Error("Shader failed to render", __FILE__, __LINE__);
	}
	
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 15.0f), Vec3(0.0f, 0.0f, 0.0f), (Vec3(0.0f, 1.0f, 0.0f)));
	
	return true;
}

void Scene2::OnDestroy() {
	Debug::Info("Deleting assets Scene2: ", __FILE__, __LINE__);

	sphere->OnDestroy();
	delete sphere;

	planePhysObj->OnDestroy();
	delete planePhysObj;

	shader->OnDestroy();
	delete shader;

	delete texture;
	
}

void Scene2::HandleEvents(const SDL_Event &sdlEvent) {
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

void Scene2::Update(const float deltaTime) {
	
	time += deltaTime;
	timeTrack += deltaTime;
	
	if (timeTrack >= 0.999) // calling the funcions and print statemens in every 60 frames, apprx in every 1 second.
	{
		
		
		std::cout
			<< std::setfill(' ') << std::setw(1) << "|" << std::setw(7) << std::left << "Time" << std::setprecision(2) << std::setw(1) << "|" << std::setw(12)
			<< "Distance" << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)	<< "Accel.x" << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << "Accel.y" << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< "Vel.x" << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << "Vel.y" << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< "Pos.x" << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << "Pos.y" << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< std::endl;

		std::cout
			<< std::setfill(' ') << std::setw(1) << "|" << std::setw(7) << std::left << time << std::setprecision(2) << std::setw(1) << "|" << std::setw(12)
			<< sphere->GetDistance() << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)	<< sphere->GetAccel().x << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << sphere->GetAccel().y << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< sphere->GetVel().x << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << sphere->GetVel().y << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< sphere->GetPos().x << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << sphere->GetPos().y << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< std::endl;
		timeTrack = 0.0f;
	}


	float sphereScaleValue = sphere->GetRadius();

	sphere->SetModelMatrix(	MMath::translate(sphere->GetPos() * sphereScaleValue) *
							MMath::scale(sphereScaleValue, sphereScaleValue, sphereScaleValue));


	float planeScaleValue = 1.0f;
	planePhysObj->SetModelMatrix(MMath::translate(Vec3(0.0f, 0.0f, 0.0f)) *
								 MMath::rotate(90.0f, Vec3(0.0f, 1.0f, 0.0f)) *
								 MMath::rotate(45.0f, Vec3(1.0f, 0.0f, 0.0f)) *
								 MMath::scale(4.0f, 4.0f, 0.01f));


	Physics::RigidBodyRotation(*sphere, deltaTime);
	Physics::SimpleNewtonMotion(*sphere, deltaTime);
	
	//Physics::PlaneShphereCollisionDetect(*sphere, *plane);
	if (Physics::PlaneShphereCollisionDetect(*sphere, *plane))
	{
		//printf("\n COLLISION!!!");
		Physics::PlaneSphereCollisionResponse(*sphere, *plane);
		Physics::PlaneShphereCollisionDetect(*sphere, *plane) == false;
		
	}
	
}

void Scene2::Render() const {
	/// Clear the screen
	glClearColor(0.95f, 0.7f, 0.3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);

	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, sphere->GetModelMatrix());
	glBindTexture(GL_TEXTURE_2D, sphere->GetTexture()->getTextureID());
	sphere->GetMesh()->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);

	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, planePhysObj->GetModelMatrix());
	glBindTexture(GL_TEXTURE_2D, planePhysObj->GetTexture()->getTextureID());
	planePhysObj->GetMesh()->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgram(0);
}



	
