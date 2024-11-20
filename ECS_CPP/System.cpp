/*
Basic ECS code from https://austinmorlan.com/posts/entity_component_system/
*/

#include "System.h"

template<typename T>
std::shared_ptr<T> SystemManager::RegisterSystem()
{
	const char* typeName = typeid(T).name();

	assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");

	auto system = std::make_shared<T>();
	mSystems.insert({ typeName, system });
	return system;
}

template<typename T>
void SystemManager::SetSignature(Signature signature)
{
	const char* typeName = typeid(T).name();

	assert(mSignatures.find(typeName) == mSignatures.end() && "Signature not found.");
	mSignatures.insert({ typeName, signature });
}

void SystemManager::EntityDestroyed(Entity entity)
{
	// Erase a destroyed entity from all system lists
	for (auto const& pair : mSystems)
	{
		auto const& system = pair.second;
		system->mEntities.erase(entity);
	}
}

void SystemManager::EntitySignatureChanged(Entity entity, Signature entitySignature)
{
	// Notify each system that an entity's signature changed
	for (auto const& pair : mSystems)
	{
		auto const& type = pair.first;
		auto const& system = pair.second;
		auto const& systemSignature = mSignatures[type];

		// Entity signature matches system signature - insert into set
		if ((entitySignature & systemSignature) == systemSignature)
		{
			system->mEntities.insert(entity);
		}
		// Entity signature does not match system signature - erase from set
		else
		{
			system->mEntities.erase(entity);
		}
	}
}

void SystemManager::update()
{
	// Update all systems
	for (auto const& pair : mSystems)
	{
		auto const& system = pair.second;
		system->update();
	}
}

void SystemManager::set_system_signatures()
{
	// Set the signatures for all systems
	for (auto const& pair : mSystems)
	{
		auto const& system = pair.second;
		system->set_signature();
	}
}

template<typename T>
void SystemManager::udpate_system()
{
	const char* typeName = typeid(T).name();

	assert(mSystems.find(typeName) != mSystems.end() &&
	 							"System not registered before use.");

	auto system = std::static_pointer_cast<T>(mSystems[typeName]);
	system->update();
}