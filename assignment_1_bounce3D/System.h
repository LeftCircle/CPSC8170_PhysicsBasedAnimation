/*
ECS code from https://austinmorlan.com/posts/entity_component_system/
*/
#ifndef SYSTEM_H
#define SYSTEM_H

#include <set>
#include <memory>
#include <unordered_map>
#include <cassert>

#include "ECSUtility.h"

class System
{
public:
	virtual ~System() = default;
	std::set<Entity> mEntities;
	virtual void update() = 0;
	virtual void set_signature() = 0;
};


class SystemManager
{
public:
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		const char* typeName = typeid(T).name();

		assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");

		// Create a pointer to the system and return it so it can be used externally
		auto system = std::make_shared<T>();
		mSystems.insert({typeName, system});
		return system;
	}

	template<typename T>
	void SetSignature(Signature signature)
	{
		const char* typeName = typeid(T).name();

		assert(mSystems.find(typeName) != mSystems.end() && "System used before registered.");

		// Set the signature for this system
		mSignatures.insert({typeName, signature});
	}

	void EntityDestroyed(Entity entity)
	{
		// Erase a destroyed entity from all system lists
		// mEntities is a set so no check needed
		for (auto const& pair : mSystems)
		{
			auto const& system = pair.second;

			system->mEntities.erase(entity);
		}
	}

	void EntitySignatureChanged(Entity entity, Signature entitySignature)
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

private:
	// Map from system type string pointer to a signature
	std::unordered_map<const char*, Signature> mSignatures{};

	// Map from system type string pointer to a system pointer
	std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};

public:
	void update()
	{
		// Update all systems
		for (auto const& pair : mSystems)
		{
			auto const& system = pair.second;
			system->update();
		}
	}
	void set_system_signatures()
	{
		// Set the signatures for all systems
		for (auto const& pair : mSystems)
		{
			auto const& system = pair.second;
			system->set_signature();
		}
	}

	
	template<typename T>
	void update_system()
	{
		const char* typeName = typeid(T).name();

		assert(mSystems.find(typeName) != mSystems.end() &&
									"System not registered before use.");

		auto system = std::static_pointer_cast<T>(mSystems[typeName]);
		system->update();
	}

};

#endif