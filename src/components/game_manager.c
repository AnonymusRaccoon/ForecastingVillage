/*
** EPITECH PROJECT, 2020
** DPR
** File description:
** game_stats
*/

#include "errors_str.h"
#include "xml.h"
#include "component.h"
#include "utility.h"
#include "components/game_manager.h"

static void ctr(void *component, va_list args)
{
}

static void fdctr(gc_entity *entity, gc_scene *scene, void *component, node *n)
{
    if (scene->get_entity_by_cmp(scene, "game_manager"))
        my_printf(MULTIPLE_GAME_MGR_ERROR);
}

static void dtr(void *component)
{
    (void)component;
}

static char *serialize(void *component)
{
    (void)component;
    return (NULL);
}

const struct game_manager game_manager = {
    base: {
        name: "game_manager",
        size: sizeof(struct game_manager),
        dependencies: (char *[]) {
            NULL
        },
        ctr: &ctr,
        fdctr: &fdctr,
        dtr: &dtr,
        serialize: &serialize,
        destroy: &component_destroy
    }
};