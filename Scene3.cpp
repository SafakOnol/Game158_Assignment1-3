#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene3.h"
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

Scene3::Scene3() :dSphere(nullptr), sSphere(nullptr), mesh(nullptr), shader(nullptr), texture(nullptr) {
	Debug::Info("Created Scene3: ", __FILE__, __LINE__);
}

Scene3::~Scene3() {
	Debug::Info("Deleted Scene3: ", __FILE__, __LINE__);
}

bool Scene3::OnCreate() {
	Debug::Info("Loading assets Scene3: ", __FILE__, __LINE__);
	
	dSphere = new PhysicsObject();
	dSphere->SetVel(Vec3(0.0f, -4.0f, 0.0f));
	dSphere->SetPos(Vec3(3.0f, 4.0f, 0.0f));
	dSphere->SetRadius(1.12f);
	dSphere->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	dSphere->GetMesh()->OnCreate();
	dSphere->SetTexture(new Texture());
	dSphere->GetTexture()->LoadImage("textures/evilEye.jpg");
	dSphere->OnCreate();

	sSphere = new PhysicsObject();
	sSphere->SetVel(Vec3(0.0f, 0.0f, 0.0f));
	sSphere->SetPos(Vec3(2.0f, -2.0f, 0.0f)); // I changed the position, otherwise it was happening too fast to see
	sSphere->SetRadius(1.12f);
	sSphere->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	sSphere->GetMesh()->OnCreate();
	sSphere->SetTexture(new Texture());
	sSphere->GetTexture()->LoadImage("textures/evilEye.jpg");
	sSphere->OnCreate();	


	shader = new Shader(nullptr, "shaders/textureVert.glsl" , "shaders/textureFrag.glsl");
	if (shader->OnCreate() == false)
	{
		Debug::Error("Shader failed to render", __FILE__, __LINE__);
	}
	
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 15.0f), Vec3(0.0f, 0.0f, 0.0f), (Vec3(0.0f, 1.0f, 0.0f)));
	
	return true;
}

void Scene3::OnDestroy() {
	Debug::Info("Deleting assets Scene3: ", __FILE__, __LINE__);

	sSphere->OnDestroy();
	delete sSphere;

	dSphere->OnDestroy();
	delete dSphere;

	shader->OnDestroy();
	delete shader;

	delete texture;
	
}

void Scene3::HandleEvents(const SDL_Event &sdlEvent) {
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

void Scene3::Update(const float deltaTime) {
	
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
			<< dSphere->GetDistance() << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)	<< dSphere->GetAccel().x << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << dSphere->GetAccel().y << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< dSphere->GetVel().x << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << dSphere->GetVel().y << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< dSphere->GetPos().x << std::setprecision(5) << std::setw(1) << "|" << std::setw(10) << dSphere->GetPos().y << std::setprecision(5) << std::setw(1) << "|" << std::setw(12)
			<< std::endl;
		timeTrack = 0.0f;
	}


	float sphereScaleValue = sSphere->GetRadius();

	sSphere->SetModelMatrix(MMath::translate(sSphere->GetPos() * sphereScaleValue) *
							MMath::scale(sphereScaleValue, sphereScaleValue, sphereScaleValue));

	dSphere->SetModelMatrix(MMath::translate(dSphere->GetPos() * sphereScaleValue) *
							MMath::scale(sphereScaleValue, sphereScaleValue, sphereScaleValue));


	

	Physics::RigidBodyRotation(*dSphere, deltaTime);
	Physics::SimpleNewtonMotion(*dSphere, deltaTime);
	

	if (Physics::SphereSphereCollisionDetect(*dSphere, *sSphere))
	{
		//printf("\n COLLISION!!!\n");
		Physics::SphereStaticSphereCollisionResponse(*dSphere, *sSphere);
		Physics::SphereSphereCollisionDetect(*dSphere, *sSphere) == false;		
	}
	
}

void Scene3::Render() const {
	/// Clear the screen
	glClearColor(0.95f, 0.7f, 0.3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);

	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, sSphere->GetModelMatrix());
	glBindTexture(GL_TEXTURE_2D, sSphere->GetTexture()->getTextureID());
	sSphere->GetMesh()->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);

	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, dSphere->GetModelMatrix());
	glBindTexture(GL_TEXTURE_2D, dSphere->GetTexture()->getTextureID());
	dSphere->GetMesh()->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgram(0);
}



	
