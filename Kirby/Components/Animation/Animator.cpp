#include "stdafx.h"
#include "Animator.h"
#include <rapidcsv.h>

Animator::Animator(SpriteGO& spriteGO, const string& dataPath, const string& defaultState)
	:Animation(spriteGO), dataPath(dataPath), defaultState(defaultState)
{
}

Animator::~Animator()
{
}

void Animator::AddTransition(const std::string& stateName, const std::string& transitionName, Transition transition)
{
	if (transition.enterAnimationState == nullptr)
	{
		std::cout << "Invalid Animation State :: " << stateName << " "  << transitionName << std::endl;
		return;
	}

	auto it = states.find(stateName);
	if (it == states.end())
	{
		std::cout << "undefined state :: " << stateName << std::endl;
		return;
	}
	AnimationState* state = it->second;
	if (state->transitions.find(transitionName) == state->transitions.end())
	{
		state->transitions.insert({ transitionName, transition});
	}
}

void Animator::AddState(const std::string& stateName, AnimationClip* newClip)
{
	if (states.find(stateName) == states.end())
	{
		states.insert({ stateName, new AnimationState({ newClip }) });
	}
}

AnimationState* Animator::GetState(const std::string& stateName)
{
	auto it = states.find(stateName);
	if (it == states.end())
	{
		return nullptr;
	}
	return it->second;
}

void Animator::SetEvent(std::string eventID)
{
	currentEvent = eventID;
	auto find = currentState->transitions.find(currentEvent);
	if (find == currentState->transitions.end())
	{
 		currentEvent = "";
		return;
	}
	if (find->second.notAllowQuitTime)
	{
		currentEvent = "";
		currentState = find->second.enterAnimationState;
		SetClip(currentState->clip);
		Seek(find->second.enterTime);
	}
}

void Animator::SetState(std::string stateID)
{
	auto find = states.find(stateID);
	if (find == states.end())
	{
		std::cout << "Undefined state :: " << stateID << std::endl;
		return;
	}
	currentState = find->second;
	SetClip(currentState->clip);
}

void Animator::Reset()
{
	Animation::Reset();
	states.clear();
	LoadFromFile(dataPath);
	SetState(defaultState);
	Play();
}

void Animator::Update(float dt)
{
	Animation::Update(dt);
	if (!isEnable || !isPlaying || accumTime != 0.0f)
		return;


	if (currentEvent == "noneEvent")
	{
		return;
	}
	auto find = currentState->transitions.find(currentEvent);
	if (find == currentState->transitions.end())
	{
		currentEvent = "noneEvent";
		return;
	}

	if (find->second.quitTime == currentFrame)
	{
		currentEvent = "";
		currentState = find->second.enterAnimationState;
		SetClip(currentState->clip);
		Seek(find->second.enterTime);
	}
}

void Animator::LoadFromFile(std::string path)
{
	rapidcsv::Document states(path + "_States.csv");
	std::vector<std::string> keys = states.GetColumn<std::string>(0);
	std::vector<std::string> paths = states.GetColumn<std::string>(1);
	for (int i = 0; i < keys.size(); i++)
	{
		AddState(keys[i], Resources.GetAnimationClip(paths[i]));
	}

	rapidcsv::Document transitions(path + "_Transition.csv");
	std::vector<std::string> clipKeys = transitions.GetColumn<std::string>(0);
	std::vector<std::string> transitionKeys = transitions.GetColumn<std::string>(1);
	std::vector<int> notAllowQuitTime = transitions.GetColumn<int>(2);
	std::vector<int> quitTime = transitions.GetColumn<int>(3);
	std::vector<std::string> enterAnimationState = transitions.GetColumn<std::string>(4);
	std::vector<int> enterTime = transitions.GetColumn<int>(5);
	for (int i = 0; i < clipKeys.size(); i++)
	{
		AddTransition(clipKeys[i], transitionKeys[i], { (bool)notAllowQuitTime[i], quitTime[i], GetState(enterAnimationState[i]), enterTime[i]});
	}
}

void Animator::OnGameObjectEnable()
{
}

void Animator::OnGameObjectDisable()
{
}
