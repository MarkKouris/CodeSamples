/*
* file: Engine.h
* name: Mark Kouris
*
* info: This is the interface for the overall engine for the game.
*       Main loops for initialization, updating,
		and rendering all systems and game objects is done here.
*
*/


#pragma once
//#include "System.h"
//#include "framework.h"

#include <chrono>

class Event;
class ShutDown;

class Engine
{
	// Public Functions:
public:
	//default constructor
	Engine();

	//default destructor
	~Engine();

	// Initialize all systems in the engine.
	void Initialize();

	// Update all systems in the engine.
	void Update(float dt);

	// Render all systems in the engine.
	void Render();

	// check if the Engine is currently running
	bool IsRunning() const;

	// stops engine and exit clean
	void StopRunning();

	void OnEvent(const ShutDown*);
private:

	// private variables
	bool isRunning;

	std::chrono::high_resolution_clock timer;
	std::chrono::steady_clock::time_point previous, now;
};
