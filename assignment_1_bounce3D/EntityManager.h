/*
ECS From https://austinmorlan.com/posts/entity_component_system/

*/
#ifndef ECS_MANAGER_H
#define ECS_MANAGER_H

#include <queue>
#include <cassert>
#include <array>

#include "ECSUtility.h"

class EntityManager
{
public:
	EntityManager();
	Entity CreateEntity();
	void DestroyEntity(Entity entity);
	void SetSignature(Entity entity, Signature signature);
	Signature GetSignature(Entity entity);

private:
	// Queue of unused entity IDs
	std::queue<Entity> mAvailableEntities{};

	// Array of signatures where the index corresponds to the entity ID
	std::array<Signature, MAX_ENTITIES> mSignatures{};

	// Total living entities - used to keep limits on how many exist
	uint32_t mLivingEntityCount{};
};

#endif