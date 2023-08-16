#include "stdafx.h"
#include "GameObject.h"

bool GameObject::IsActive() const
{
	return isActive;
}

void GameObject::SetActive(bool active)
{
	if (isActive == active)
	{
		return;
	}
	isActive = active;
	for (auto component : components)
	{
		active ? component->OnGameObjectEnable() : component->OnGameObjectDisable();
	}
}

string GameObject::GetName()
{
	return name;
}

void GameObject::SetName(const std::string& name)
{
	this->name = name;
}

sf::Vector2f GameObject::GetPosition()
{
	return position;
}

void GameObject::SetPosition(const sf::Vector2f& position)
{
	this->position = position;
}

void GameObject::SetPosition(const float& x, const float& y)
{
	this->position.x = x;
	this->position.y = y;
}

bool GameObject::HasTag(const string& tag) const
{
	for (const string& t : tags)
	{
		if (t == tag)
		{
			return true;
		}
	}
	return false;
}

void GameObject::AddTag(const string& tag)
{
	for (string& t : tags)
	{
		if (t == tag)
		{
			return;
		}
	}
	tags.push_back(tag);
}

void GameObject::RemoveTag(const string& tag)
{
	for (string& t : tags)
	{
		if (t == tag)
		{
			tags.remove(tag);
			return;
		}
	}
}

void GameObject::SetOrigin(const sf::Vector2f& origin)
{
	this->origin = origin;
}

void GameObject::Reset()
{
	for (auto component : components)
	{
		component->Reset();
	}
}

void GameObject::UpdateComponent(float dt)
{
	for (auto component : components)
	{
		component->Update(dt);
	}
}

void GameObject::Update(float dt)
{

}

void GameObject::Draw(sf::RenderWindow& window)
{
	for (auto component : components)
	{
		component->Draw(window);
	}
}

void GameObject::OnGUI(sf::RenderWindow& window)
{
	for (auto component : components)
	{
		component->OnGUI(window);
	}
}

GameObject::GameObject(const std::string& name)
	:name(name), scale(1.0f, 1.0f)
{
}

GameObject::~GameObject()
{
	Release();
	for (auto component : components)
	{
		component->Release();
		delete component;
	}
}


Component* GameObject::GetComponent(const ComponentType type)
{
	auto compare = [type](Component* component) {return component->GetComponentType() == type; };
	auto it = std::find_if(components.begin(), components.end(), compare);
	if (it == components.end())
	{
		return nullptr;
	}
	return *it;
	/*
	for (auto go : gameObjects)
	{
		if (go->GetName() == name)
		{
			return go;
		}
	}
	return nullptr;
	*/
}

void GameObject::GetComponents(std::list<Component*>& list, const ComponentType type)
{
	//list.clear();
	for (auto go : components)
	{
		if (go->GetComponentType() == type)
		{
			list.push_back(go);
		}
	}
}

bool GameObject::Exist(Component* component)
{
	return std::find(components.begin(), components.end(), component) != components.end();
}

Component* GameObject::AddComponent(Component* component)
{
	if (!(component->IsUnique() && Exist(component)))
	{
		component->Init();
		components.push_back(component);
		return component;
	}
	else
	{
		cerr << "this component can just one in gameobject" << endl;
	}
	return nullptr;
}

void GameObject::RemoveGameObject(Component* component)
{
	component->Release();
	components.remove(component);
	//delete gameObject;
}
