#ifndef PHYSICS_H
#define PHYSICS_H

#include "PhysicsObject.h"
#include "Plane.h"
#include "Vmath.h"

class Physics
{
	friend class PhysicsObject;

public:

	static Vec3 rotateZ(const Vec3 force, PhysicsObject& object);

	static void SimpleNewtonMotion(PhysicsObject& object, const float deltaTime);
	static void RigidBodyRotation(PhysicsObject& object, const float deltaTime);

	static void ApplyTorque(const float torque, PhysicsObject& object);
	static void ApplyForce(const Vec3 force, PhysicsObject& object);

	static bool PlaneShphereCollisionDetect(PhysicsObject& object, Plane& p);
	static void PlaneSphereCollisionResponse(PhysicsObject& object1, Plane& p);
	static bool SphereSphereCollisionDetect(PhysicsObject& object1, PhysicsObject& object2);
	static void SphereSphereCollisionResponse(PhysicsObject& object1, PhysicsObject& object2);
	static void SphereStaticSphereCollisionResponse(PhysicsObject& object1, PhysicsObject& object2);

};

#endif