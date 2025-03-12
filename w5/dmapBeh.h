#pragma once
#include <flecs.h>

flecs::entity create_player_approacher(flecs::entity e);
flecs::entity create_player_fleer(flecs::entity e);
flecs::entity create_hive_follower(flecs::entity e);
flecs::entity create_monster_logic(flecs::entity e);
flecs::entity create_knight_logic(flecs::entity e);
flecs::entity create_heal_approacher(flecs::entity e);

