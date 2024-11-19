/*
Basic ECS code from https://austinmorlan.com/posts/entity_component_system/
*/
#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <memory>

#include "ECSUtility.h"
#include "ComponentManager.h"
#include "System.h"
#include "EntityManager.h"


class ECSCoordinator
{
public:
	void Init();

	// Entity Methods
	Entity CreateEntity();
	void DestroyEntity(Entity entity);

	// Component Methods
	template<typename T>
	void RegisterComponent();

	template<typename T>
	void AddComponent(Entity entity, T component);

	template<typename T>
	void RemoveComponent(Entity entity);

	template<typename T>
	T& GetComponent(Entity entity);

	template<typename T>
	ComponentType GetComponentType();

	// System Methods
	template<typename T>
	std::shared_ptr<T> RegisterSystem();

	template<typename T>
	void SetSystemSignature(Signature signature);

private:
	std::unique_ptr<ComponentManager> mComponentManager;
	std::unique_ptr<EntityManager> mEntityManager;
	std::unique_ptr<SystemManager> mSystemManager;
};

#endif