/*
Basic ECS code from https://austinmorlan.com/posts/entity_component_system/
*/

#include "ECSCoordinator.h"

void ECSCoordinator::Init()
{
	mComponentManager = std::make_unique<ComponentManager>();
	mEntityManager = std::make_unique<EntityManager>();
	mSystemManager = std::make_unique<SystemManager>();
}

Entity ECSCoordinator::CreateEntity()
{
	return mEntityManager->CreateEntity();
}

void ECSCoordinator::DestroyEntity(Entity entity)
{
	mEntityManager->DestroyEntity(entity);
	mComponentManager->EntityDestroyed(entity);
	mSystemManager->EntityDestroyed(entity);
}

template<typename T>
void ECSCoordinator::RegisterComponent()
{
	mComponentManager->RegisterComponent<T>();
}

template<typename T>
void ECSCoordinator::AddComponent(Entity entity, T component)
{
	mComponentManager->AddComponent<T>(entity, component);

	auto signature = mEntityManager->GetSignature(entity);
	signature.set(mComponentManager->GetComponentType<T>(), true);
	mEntityManager->SetSignature(entity, signature);

	mSystemManager->EntitySignatureChanged(entity, signature);
}

template<typename T>
void ECSCoordinator::RemoveComponent(Entity entity)
{
	mComponentManager->RemoveComponent<T>(entity);

	auto signature = mEntityManager->GetSignature(entity);
	signature.set(mComponentManager->GetComponentType<T>(), false);
	mEntityManager->SetSignature(entity, signature);

	mSystemManager->EntitySignatureChanged(entity, signature);
}

template<typename T>
T& ECSCoordinator::GetComponent(Entity entity)
{
	return mComponentManager->GetComponent<T>(entity);
}

template<typename T>
ComponentType ECSCoordinator::GetComponentType()
{
	return mComponentManager->GetComponentType<T>();
}

template<typename T>
std::shared_ptr<T> ECSCoordinator::RegisterSystem()
{
	return mSystemManager->RegisterSystem<T>();
}

template<typename T>
void ECSCoordinator::SetSystemSignature(Signature signature)
{
	mSystemManager->SetSignature<T>(signature);
}

void ECSCoordinator::update()
{
	mSystemManager->update();
}

void ECSCoordinator::set_system_signatures()
{
	mSystemManager->set_system_signatures();
}

template<typename T>
void ECSCoordinator::udpate_system()
{
	mSystemManager->udpate_system<T>();
}