#include "PhysicsObject.h"
#include "MMath.h"
#include "VMath.h"
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

using namespace MATH;


// constructor initialization with no input values
PhysicsObject::PhysicsObject():pos(0.0f, 0.0f, 0.0f), vel(0.0f, 0.0f, 0.0f), accel(0.0f, 0.0f, 0.0f), Actor (nullptr)
{
	angle = angularVel = angularAccel = torque = 0.0f;
}


// constructor initialization for MASS and ROTATIONAL INERTIA
PhysicsObject::PhysicsObject(float mass_, float rotationalInertia_): mass(mass_), rotationalInertia(rotationalInertia_), Actor(nullptr)
{
	mass = mass_;
	rotationalInertia = rotationalInertia_;
}


PhysicsObject::~PhysicsObject()
{

}


void PhysicsObject::Update(const float deltaTime)
{

}

void PhysicsObject::csv(float time, float torque)
{
	string myStringTime = "Time";
	string myStringTorque = "Torque";
	string myStringAngAccel = "AngAccel";
	string myStringAngVel = "AngVel";
	string myStringAngle = "Angle";
	string myStringForceX = "Force.x";
	string myStringForceY = "Force.y";
	string myStringAccelX = "Accel.x";
	string myStringAccelY = "Accel.y";
	string myStringVelX = "Vel.x";
	string myStringVelY = "Vel.y";
	string myStringPosX = "Pos.x";
	string myStringPosY = "Pos.y";
		
	fstream myFile;
	static bool printing = false;

	if (printing == false) // this prints out the first column with titles, just once
	{
		myFile.open("output.csv", ios::out);
		if (myFile.is_open())
		{
			myFile << myStringTime << "," << myStringTorque << "," << myStringAngAccel << "," << myStringAngVel << "," << myStringAngle << "," << myStringForceX << ","
				<< myStringForceY << "," << myStringAccelX << "," << myStringAccelY << "," << myStringVelX << "," << myStringVelY << "," << myStringPosX << ","
				<< myStringPosY << endl;
			printing = true;
		}			
		
	}

	else // this prints out the values as per the update function in Scene1
	{
		myFile.open("output.csv", ios::app);
		myFile << time << "," << torque << "," << angularAccel << "," << angularVel << "," << angle << "," << GetForce().x << ","
			<< GetForce().y << "," << accel.x << "," << accel.y << "," << vel.x << "," << vel.y << ","
			<< pos.x << "," << pos.y << endl;
	}
	myFile.close();
}


