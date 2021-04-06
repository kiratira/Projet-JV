#pragma once
#include <memory>
#include <unordered_map>
#include "Scene.h"
#include "SFML/Window.hpp"


class SceneStateMachine
{
public:
	SceneStateMachine();


	void ProcessInput();
	void Update(float deltaTime);
	void LateUpdate(float deltaTime);
	void Draw(Window& window);

	unsigned int Add(std::shared_ptr<Scene> scene);


	void SwitchTo(unsigned int id);
	void Remove(unsigned int id);

private:
	// Stores all of the scenes associated with this state machine.
	std::unordered_map<unsigned int, std::shared_ptr<Scene>> scenes;

	// Stores a reference to the current scene. Used when drawing/updating.
	std::shared_ptr<Scene> curScene;

	// Stores our current scene id. This is incremented whenever 
	// a scene is added.
	unsigned int insertedSceneID;
};

