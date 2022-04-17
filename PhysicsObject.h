#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "Vector.h"
#include "Sphere.h"
#include "Actor.h"
#include "Texture.h"
#include "Plane.h"

using namespace MATH;


class PhysicsObject : public Actor // inherited from Actor class
{
	friend class Physics; // shares the private variables with Physics class
	friend class Plane;

private:
		Vec3 pos, vel, accel;
		float mass;
		float torque, rotationalInertia;
		float angle, angularVel, angularAccel;
		float radius;
		float e; //coeff of restitution
		float spColDistance;

		class Mesh* mesh;
		class Texture* texture;
		Matrix4 modelMatrix;

public:

		PhysicsObject();
		PhysicsObject(float mass_, float rotationalInertia);
		virtual ~PhysicsObject();

		inline void Update(const float deltaTime);
		
		//csv print function
		void csv(float time, float torque);
	
		
		inline void SetPos(const Vec3 &pos_) { pos = pos_; }
		inline Vec3 GetPos() { return pos; }
		inline void SetMass(const float &mass_) { mass = mass_; }
		inline float GetMass() { return mass; }
		inline void SetRotationalInertia(const float& rotationalInertia_) { rotationalInertia = rotationalInertia_; }
		inline float GetRotationalInertia() { return rotationalInertia; }
		 
		inline void SetVel(const Vec3 &vel_) { vel = vel_; }
		inline Vec3 GetVel() { return vel; }
		inline void SetAccel(const Vec3& accel_) { accel = accel_; }
		inline Vec3 GetAccel() { return accel; }

		inline void SetAngle(const float& angle_) { angle = angle_; }
		inline float GetAngle() { return angle; }
		inline void SetAngularVel(const float &angularVel_) { angularVel = angularVel_; }
		inline float GetAngularVel() { return angularVel; }
		inline void SetAngularAccel(const float& angularAccel_) { angularAccel = angularAccel_; }
		inline float GetAngularAccel() { return angularAccel; }

		inline void SetRadius(const float& radius_) { radius = radius_; }
		inline float GetRadius() { return radius; }

		inline void SetDistance(const float& spColDistance_) { spColDistance = spColDistance_; }
		inline float GetDistance() { return spColDistance; }

		inline Vec3 GetForce() { return mass * accel; }
		inline void SetE(const float& e_) { e = e_; }

		inline Mesh* GetMesh() { return mesh; }
		inline void SetMesh(Mesh* mesh_) { mesh = mesh_; }
		inline Texture* GetTexture() { return texture; }
		inline void SetTexture(Texture* texture_) { texture = texture_; }
		inline Matrix4 GetModelMatrix() { return modelMatrix; }
		inline void SetModelMatrix(const Matrix4& modelMatrix_) { modelMatrix = modelMatrix_; }
		
		

};


#endif // !PHYSICSOBJECT_H