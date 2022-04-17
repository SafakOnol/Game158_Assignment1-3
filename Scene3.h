#ifndef SCENE3_H
#define SCENE3_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
#include "Physics.h"
#include "PhysicsObject.h"
#include "Plane.h"

using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Actor;
class Mesh;
class Shader;
class Texture;

class Scene3 : public Scene {
private:
		
	PhysicsObject *dSphere, *sSphere;
	Mesh *mesh;
	Shader *shader;
	Texture* texture;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 modelMatrix;
	float time;
	float timeTrack;

public:
	explicit Scene3();
	virtual ~Scene3();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE3_H