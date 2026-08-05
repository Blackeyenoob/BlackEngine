#include "bkpch.h"
#include "Entity.h"

namespace Black {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}