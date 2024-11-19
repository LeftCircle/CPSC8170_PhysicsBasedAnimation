/*
ECS code from https://austinmorlan.com/posts/entity_component_system/
*/
#ifndef SYSTEM_H
#define SYSTEM_H

#include <set>
#include <memory>
#include <unordered_map>

#include "ECSUtility.h"

class System
{
public:
	std::set<Entity> mEntities;
};


class SystemManager
{
public:
	template<typename T>
	std::shared_ptr<T> RegisterSystem();

	template<typename T>
	void SetSignature(Signature signature);

	void EntityDestroyed(Entity entity);

	void EntitySignatureChanged(Entity entity, Signature entitySignature);

private:
	std::unordered_map<const char*, Signature> mSignatures;
	std::unordered_map<const char*, std::shared_ptr<System>> mSystems;
};

#endif