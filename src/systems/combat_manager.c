/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** combat_manager.c
*/

#include <systems/combat_manager.h>
#include <tile.h>
#include <components/player_component.h>
#include <stdlib.h>
#include <prefab.h>
#include "engine.h"
#include "my.h"
#include "components/dialog_holder.h"
#include "enemy.h"

void combat_start(gc_engine *engine, char *enemy_name)
{
    struct combat_manager *this = GETSYS(engine, combat_manager);
    gc_list *li = engine->scene->get_data(engine->scene, "enemies", NULL);
    gc_scene *scene = scene_create(engine, "prefabs/combat.gcprefab");
    struct enemy *enemy = NULL;

    if (!scene) {
        my_printf("The combat scene couldn't be found.\n");
        return;
    }
    this->game_scene = engine->scene;
    engine->scene = NULL;
    engine->change_scene(engine, scene);
    dialog_next(engine);
    for (; li; li = li->next) {
        enemy = li->data;
        if ((!enemy_name && random() % 100 < enemy->spawn_rate)
        || (enemy_name && !my_strcmp(enemy_name, enemy->name)))
            break;
    }
    if (enemy)
        prefab_load(engine, enemy->prefab_src);
}

void entity_moved(gc_engine *engine, va_list args)
{
    gc_entity *entity = va_arg(args, gc_entity *);
    struct tile *tile = va_arg(args, struct tile *);
    struct player_component *cmp = GETCMP(entity, player_component);

    if (!cmp)
        return;
    if (tile->type && my_strcmp(tile->type, "combat"))
        combat_start(engine, NULL);
    if (random() % 100 < cmp->fight_rate)
        combat_start(engine, NULL);
}


static void update_entity(gc_engine *engine, void *system, gc_entity *entity, \
float dtime)
{
}

static void ctr(void *system, va_list list)
{
    gc_engine *engine = va_arg(list, gc_engine *);
    struct combat_manager *this = (struct combat_manager *)system;

    this->game_scene = NULL;
    engine->add_event_listener(engine, "entity_moved", &entity_moved);
}

static void dtr(void *system, gc_engine *engine)
{
    struct combat_manager *sys = system;
    if (sys->game_scene)
        scene_destroy(sys->game_scene);
}

const struct combat_manager combat_manager = {
    base: {
        name: "combat_manager",
        component_name: "player_component",
        size: sizeof(struct combat_manager),
        ctr: &ctr,
        dtr: &dtr,
        check_dependencies: &system_check_dependencies,
        update_entity: &update_entity,
        destroy: &system_destroy
    },
};