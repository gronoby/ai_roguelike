#include "rlikeObjects.h"
#include "ecsTypes.h"
#include "dungeonUtils.h"
#include "blackboard.h"

flecs::entity create_hive(flecs::entity e)
{
  e.add<Hive>();
  return e;
}

static Position find_free_dungeon_tile(flecs::world &ecs)
{
  auto findMonstersQuery = ecs.query<const Position, const Hitpoints>();
  bool done = false;
  while (!done)
  {
    done = true;
    Position pos = dungeon::find_walkable_tile(ecs);
    findMonstersQuery.each([&](const Position &p, const Hitpoints&)
    {
      if (p == pos)
        done = false;
    });
    if (done)
      return pos;
  };
  return {0, 0};
}

flecs::entity create_monster(flecs::world &ecs, Color col, const char *texture_src)
{
  Position pos = find_free_dungeon_tile(ecs);

  flecs::entity textureSrc = ecs.entity(texture_src);
  return ecs.entity()
    .set(Position{pos.x, pos.y})
    .set(MovePos{pos.x, pos.y})
    .set(Velocity{ 0.f, 0.f })
    .set(MoveSpeed{ 1.f })
    .set(Hitpoints{200.f})
    .set(Action{EA_NOP})
    .set(Color{col})
    .add<TextureSource>(textureSrc)
    .set(Team{1})
    .set(NumActions{1, 0})
    .set(MeleeDamage{20.f})
    .set(Blackboard{})
    .set(IsHealable{1})
    .set(IsMovable{ 1 })
    ;
}
flecs::entity create_knight(flecs::world& ecs, Color col, const char* texture_src)
{
    Position pos = find_free_dungeon_tile(ecs);

    flecs::entity textureSrc = ecs.entity(texture_src);
    return ecs.entity()
        .set(Position{ pos.x, pos.y })
        .set(MovePos{ pos.x, pos.y })
        .set(Velocity{ 0.f, 0.f })
        .set(MoveSpeed{ 1.f })
        .set(Hitpoints{ 300.f })
        .set(Action{ EA_NOP })
        .set(Color{ col })
        .add<TextureSource>(textureSrc)
        .set(Team{ 0 })
        .set(NumActions{ 1, 0 })
        .set(MeleeDamage{ 10.f })
        .set(Blackboard{})
        .set(IsHealable{ 1 })
        .set(IsMovable{1});
}

flecs::entity create_monster_spawner(flecs::world& ecs, Color col, const char* texture_src, const int team) {
    Position pos = find_free_dungeon_tile(ecs);

    flecs::entity textureSrc = ecs.entity(texture_src);
    return ecs.entity()
        .set(Position{ pos.x, pos.y })
        .set(MovePos{ pos.x, pos.y })
        .set(Hitpoints{ 1000.f })
        .set(Action{ EA_SPAWN })
        .set(Color{ col })
        .add<TextureSource>(textureSrc)
        .set(Team{ team })
        .set(NumActions{ 1, 0 })
        .set(Spawner{})
        .set(MeleeDamage{ 0.f })
        .set(Blackboard{})
        .set(IsMovable{ 0 });
}

flecs::entity create_heal_spawner(flecs::world& ecs, Color col, const char* texture_src, const int team) {
    Position pos = find_free_dungeon_tile(ecs);

    flecs::entity textureSrc = ecs.entity(texture_src);
    return ecs.entity()
        .set(Position{ pos.x, pos.y })
        .set(Hitpoints{ 100.f })
        .set(Action{ EA_SPAWN })
        .set(Color{ col })
        .add<TextureSource>(textureSrc)
        .set(Team{ team })
        .set(NumActions{ 1, 0 })
        .set(Spawner{})
        .set(MeleeDamage{ 0.f })
        .set(Blackboard{})
        .set(IsHealable{ 0 })
        .set(IsMovable{ 0 });
}

void create_player(flecs::world &ecs, const char *texture_src)
{
  Position pos = find_free_dungeon_tile(ecs);

  flecs::entity textureSrc = ecs.entity(texture_src);
  ecs.entity("player")
    .set(Position{pos.x, pos.y})
    .set(MovePos{pos.x, pos.y})
    .set(Velocity{ 0.f, 0.f })
    .set(MoveSpeed{ 3.f })
    .set(Hitpoints{300.f})
    .set(Action{EA_NOP})
    .add<IsPlayer>()
    .set(Team{0})
    .set(PlayerInput{})
    .set(NumActions{2, 0})
    .set(Color{255, 255, 255, 255})
    .add<TextureSource>(textureSrc)
    .set(MeleeDamage{10.f})
    .set(IsHealable{ 1 });
}

void create_heal(flecs::world &ecs,float x, float y, float amount)
{
  ecs.entity()
    .set(Position{x, y})
    .set(HealAmount{amount})
    .set(Color{0x44, 0x44, 0xff, 0xff});
}

void create_powerup(flecs::world &ecs, float x, float y, float amount)
{
  ecs.entity()
    .set(Position{x, y})
    .set(PowerupAmount{amount})
    .set(Color{0xff, 0xff, 0x00, 0xff});
}

