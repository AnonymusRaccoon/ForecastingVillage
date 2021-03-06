/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** controllable_component
*/

#include "xml.h"
#include "component.h"
#include "components/controllable_component.h"
#include "utility.h"
#include <stdlib.h>

static void controllable_ctr(void *component, va_list args)
{
    struct controllable_component *cmp = (struct controllable_component *)\
component;

    cmp->movement_x = 0;
    cmp->movement_y = 0;
    cmp->can_move = true;
    (void)args;
}

static void controllable_fdctr(gc_entity *entity, gc_scene *scene, \
void *component, node *n)
{
    struct controllable_component *cmp = (struct controllable_component *)\
component;

    cmp->movement_x = 0;
    cmp->movement_y = 0;
    (void)scene;
    (void)entity;
    (void)n;
}

static void controllable_dtr(void *component)
{
    (void)component;
}

static char *controllable_serialize(void *component)
{
    (void)component;
    return (NULL);
}

void controllable_set_can_move(gc_scene *scene, bool value)
{
    gc_list *list = scene->get_entity_by_cmp(scene, "controllable_component");
    struct controllable_component *ctl;

    for (; list; list = list->next) {
        ctl = GETCMP(list->data, controllable_component);
        ctl->can_move = value;
    }
}

const struct controllable_component controllable_component = {
    base: {
        name: "controllable_component",
        size: sizeof(struct controllable_component),
        dependencies: (char *[]){
            "movable_component",
            "transform_component",
            NULL
        },
        ctr: &controllable_ctr,
        fdctr: &controllable_fdctr,
        dtr: &controllable_dtr,
        serialize: &controllable_serialize,
        destroy: &component_destroy
    }
};