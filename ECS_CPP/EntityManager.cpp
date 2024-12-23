/*
Basic ECS code from https://austinmorlan.com/posts/entity_component_system/
*/

#include "EntityManager.h"

EntityManager::EntityManager()
{
	// Initialize the queue with all possible entity IDs
	for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
	{
		mAvailableEntities.push(entity);
	}
}

Entity EntityManager::CreateEntity()
{
	assert(mLivingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

	// Take an ID from the front of the queue
	Entity id = mAvailableEntities.front();
	mAvailableEntities.pop();
	++mLivingEntityCount;

	return id;
}

void EntityManager::DestroyEntity(Entity entity)
{
	assert(entity < MAX_ENTITIES && "Entity out of range.");

	// Invalidate the destroyed entity's signature
	mSignatures[entity].reset();

	// Put the destroyed ID at the back of the queue
	mAvailableEntities.push(entity);
	--mLivingEntityCount;
}

void EntityManager::SetSignature(Entity entity, Signature signature)
{
	assert(entity < MAX_ENTITIES && "Entity out of range.");

	// Put this entity's signature into the array
	mSignatures[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity)
{
	assert(entity < MAX_ENTITIES && "Entity out of range.");

	// Get this entity's signature from the array
	return mSignatures[entity];
}

