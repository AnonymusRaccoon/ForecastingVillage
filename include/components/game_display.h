/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** game_loader
*/

#ifndef _TEAMS_COMPONENT_H_
#define _TEAMS_COMPONENT_H_

#include "component.h"

typedef enum display_type
{
    SELECT_TILE_DISPLAY,
    XP_DISPLAY,
    HEALTH_DISPLAY,
    HEALTH_DISPLAY_ENNEMY,
    INVENTORY_SLOT_1,
    INVENTORY_SLOT_2,
    INVENTORY_SLOT_3,
    INVENTORY_SLOT_4
} display_type_enum;

struct game_display
{
    gc_component base;
    display_type_enum type;
};

const struct game_display game_display;
const struct gc_system game_display_system;

#endif //_TEAMS_COMPONENT_H_
