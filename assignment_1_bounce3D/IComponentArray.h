/*
Basic ECS code from https://austinmorlan.com/posts/entity_component_system/
*/

#ifndef I_COMPONENT_ARRAY_H
#define I_COMPONENT_ARRAY_H

#include <array>
#include <unordered_map>
#include <cassert>

#include "ECSUtility.h"


class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
public:
	void InsertData(Entity entity, T component);
	void RemoveData(Entity entity);
	T& GetData(Entity entity);
	void EntityDestroyed(Entity entity) override;

private:
	std::array<T, MAX_ENTITIES> mComponentArray;
	std::unordered_map<Entity, size_t> mEntityToIndexMap;
	std::unordered_map<size_t, Entity> mIndexToEntityMap;
	size_t mSize;
};


#endif
