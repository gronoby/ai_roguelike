#include "dmapBeh.h"
#include "ecsTypes.h"

flecs::entity create_player_approacher(flecs::entity e)
{
  e.set(DmapWeights{{{"approach_map", {1.f, 1.f}}}});
  return e;
}

flecs::entity create_player_fleer(flecs::entity e)
{
  e.set(DmapWeights{{{"flee_map", {1.f, 1.f}}}});
  return e;
}

flecs::entity create_hive_follower(flecs::entity e)
{
  e.set(DmapWeights{{{"hive_map", {1.f, 1.f}}}});
  return e;
}

flecs::entity create_monster_logic(flecs::entity e)
{
  e.set(DmapWeights{ {{"hive_map", {1.f, 1.f}}, {"approach_map", {1.8, 0.8f}}}});
  return e;
}

flecs::entity create_knight_logic(flecs::entity e)
{
	e.set(DmapWeights{ { {"monster_approach_map", {1.f, 0.8f}}} });
	return e;
}

flecs::entity create_heal_approacher(flecs::entity e)
{
	e.set(DmapWeights{ { {"heal_map", {1.f, 0.8f}}} });
	return e;
}