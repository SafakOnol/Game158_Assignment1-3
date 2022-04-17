#ifndef SCENE2_H
#define SCENE2_H
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

class Scene2 : public Scene {
private:
		
	PhysicsObject *sphere;
	PhysicsObject* planePhysObj;
	Plane *plane;
	Mesh *mesh;
	Shader *shader;
	Texture* texture;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 modelMatrix;
	float timeTrack;
	float time;

public:
	explicit Scene2();
	virtual ~Scene2();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE2_H