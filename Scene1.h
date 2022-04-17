#ifndef SCENE1_H
#define SCENE1_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
#include "Physics.h"
#include "PhysicsObject.h"

using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Actor;
class Mesh;
class Shader;
class Texture;

class Scene1 : public Scene {
private:
	PhysicsObject* ship;
	Vec3 Force;

	float time;
	float timeTrack;
	bool engineFail;

	float torqueValue;

	Actor *sphere;
	Mesh *mesh;
	Shader *shader;
	Texture* texture;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 modelMatrix;

	Vec3 lightPos[10];
	Vec4 diffuse[10];
	Vec4 specular[10];


public:
	explicit Scene1();
	virtual ~Scene1();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE1_H