/*
The basic ECS code is from https://austinmorlan.com/posts/entity_component_system/
*/
#ifndef ECS_UTILITY_H
#define ECS_UTILITY_H

#include <cstdint>
#include <bitset>

using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 5000;

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;


#endif