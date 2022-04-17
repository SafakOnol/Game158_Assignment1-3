#include "Physics.h"



void Physics::SimpleNewtonMotion(PhysicsObject& object, const float deltaTime)
{
	// posFinal = posInit + velInit * deltaTime + 0.5 * accel * deltaTime * deitaTime
	object.SetPos(object.GetPos() + object.GetVel() * deltaTime + 0.5f * object.GetAccel() * deltaTime * deltaTime);	
	
	// velFinal = velInit + accel * deltaTime
	object.SetVel(object.GetVel() + object.GetAccel() * deltaTime);	
}

void Physics::RigidBodyRotation(PhysicsObject& object, const float deltaTime)
{
	// angPosFinal = angPosInit + angVelIinit * deltaTime + 0.5 * angAccel * deltaTime * deltaTime
	object.SetAngle(object.GetAngle() + object.GetAngularVel() * deltaTime + 0.5f * object.GetAngularAccel() * deltaTime * deltaTime);

	// angVelFinal = angVelInit + angAccel * deltaTime
	object.SetAngularVel(object.GetAngularVel() + object.GetAngularAccel() * deltaTime);	
}

Vec3 Physics::rotateZ(const Vec3 force, PhysicsObject& object) // This is to revise the Force into two components Fx and Fy -> it will update in every frame and will give precise output
{
	double rads = (object.GetAngle() * M_PI / 180);
	double forceX, forceY;
	forceX = (cos(rads) * force.x) - (sin(rads) * force.y);
	forceY = (sin(rads) * force.x) + (cos(rads) * force.y);
	return Vec3(forceX, forceY, 0.0f);
}

void Physics::ApplyTorque(const float torque, PhysicsObject& object)
{
	object.SetAngularAccel(torque / object.GetRotationalInertia());
}

void Physics::ApplyForce(const Vec3 force, PhysicsObject& object)
{
	object.SetAccel(force / object.GetMass());
}

// Collisions

bool Physics::PlaneShphereCollisionDetect(PhysicsObject& object, Plane& p)
{
	float spColDistance = VMath::dot(object.GetPos(), Vec3(p.x, p.y, p.z)) + p.d - object.GetRadius();
	//printf("\n spColDistance: %f", spColDistance);
	object.SetDistance(spColDistance);
	if (0.0f >= spColDistance) { return true;	 } // if true, sphere collided to plane
	else { return false; }	
}

void Physics::PlaneSphereCollisionResponse(PhysicsObject& object1, Plane& p)
{
	Vec3 PVec = VMath::dot(-object1.GetVel(), (VMath::normalize(p))) * VMath::normalize(p); // projection magnitude & prjection Vector
	Vec3 VelF = object1.GetVel() + (2.0f * PVec); // final velocity
	object1.SetVel(VelF); // set velocity to final velocity
}

bool Physics::SphereSphereCollisionDetect(PhysicsObject& object1, PhysicsObject& object2)
{
	float ssColDetection = object1.GetRadius() + object2.GetRadius(); // Distance between spheres at the moment of impact
	float ssRealDisctance = VMath::mag((object1.GetPos() - object2.GetPos())); // Distance between speheres in realtime
	//printf("\n ssRealDisctance: %f", ssRealDisctance);
	object1.SetDistance(ssRealDisctance);
	if (ssColDetection >= ssRealDisctance) { return true; } // if this is true, spheres are collided
	else { return false; }
	
	

}

void Physics::SphereSphereCollisionResponse(PhysicsObject& object1, PhysicsObject& object2)
{
	float e = 1.0f; // coefficient of restitution

	Vec3 NColNormal = VMath::normalize(object1.GetPos() - object2.GetPos());
	Vec3 PVec1 = VMath::dot(-object1.GetVel(), NColNormal) * NColNormal;
	Vec3 PVec2 = VMath::dot(-object2.GetVel(), NColNormal) * NColNormal;
	Vec3 VecF1 = (object1.GetMass() * PVec1 + object2.GetMass() * PVec2 + object1.GetMass() * e * (PVec1 - PVec2)) / (object1.GetMass() - object2.GetMass());
	// V1f - V2f = -e(V1i-V2i)
	// V2f = V1f + e(V1i-V2i)
	Vec3 VecF2 = VecF1 + e * (object1.GetVel() - object2.GetVel());
	object1.SetVel(VecF1);
	object2.SetVel(VecF2);
}

void Physics::SphereStaticSphereCollisionResponse(PhysicsObject& object1, PhysicsObject& object2)
{
	Vec3 ColNormal = object1.GetPos() - object2.GetPos(); // collision normal --- object1->sphere, object2->staticsphere
	float ssRealDistance = VMath::mag(ColNormal); // realtime distance between spheres
	Vec3 NColNormal = VMath::normalize(ColNormal); // normalized Normal
	float pMag = VMath::dot(-object1.GetVel(), NColNormal); //projection magnitude
	Vec3 PVec = pMag * NColNormal; //projection vector
	Vec3 VelF = (object1.GetVel()) + (2 * PVec); //final velocity of sphere
	object1.SetVel(VelF);
}



