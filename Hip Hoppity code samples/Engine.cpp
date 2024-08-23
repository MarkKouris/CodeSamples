/*
* file: Engine.cpp
*
* info: This is the implementation for the main interface for the engine.
*       Main loops for initialization, updating, 
        and rendering all systems and game objects is done here.
*
*/

#include "Event.h"
#include "Engine.h" 
#include "Log.h"
#include "SystemManager.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"        // imgui backend opengl3 file
#include "backends/imgui_impl_glfw.h"           // imgui backend glfw file
#include <vector>
#include <string>

//default ctor
Engine::Engine() : isRunning(true)
{
#ifdef _DEBUG
    // creates debug console
    AllocConsole();
    /*
    * to access this console you must call GetStdHandle(STD_OUTPUT_HANDLE)
    * to get the output handle to the console
    */
#endif
}

void CloseWindow(const ShutDown* event);    // declaration

//default dtor
Engine::~Engine()
{
    SysManager::DestroySystems();
}

// Initialize all systems in the engine.
void Engine::Initialize()
{
    EventManager::AddEventReceiver<ShutDown>("Shutdown", CloseWindow);
    for (System* sys : SysManager::systems_) sys->Init();
}

// Update all systems in the engine.
void Engine::Update(float dt)
{
    std::vector<float> times;
    std::vector<std::string> names;

    for (System* sys : SysManager::systems_)
    {
        previous = timer.now();
        sys->Update(dt);
        now = timer.now();
        times.push_back(std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(now - previous).count());
        names.push_back(sys->Name());
    }
#ifdef _DEBUG
    ImGui::Begin("System Times");

    for (int i = 0; i < times.size(); ++i)
        ImGui::Text("%s system : %f", names[i].c_str(), times[i]);

    ImGui::Text("FPS %.1f", ImGui::GetIO().Framerate);
    ImGui::End();
#endif
}

// Render all systems in the engine.
void Engine::Render()
{
    for (System* sys : SysManager::systems_) sys->Render();
}

// For while loop in main 
bool Engine::IsRunning() const
{
    return isRunning;
}

void Engine::StopRunning()
{
    isRunning = false;
}

void Engine::OnEvent(const ShutDown* event)
{
    SysManager::GetEngine()->StopRunning();
}

void CloseWindow(const ShutDown* event)
{
    SysManager::GetEngine()->StopRunning();
}
