/*
 * level.h
 * Poulet Poulet A+
 * Forward declarations for level.cpp functions.
 */

#ifndef LEVEL_H
#define LEVEL_H

#include "poulet.h"

void drawLevel(int x, int y, Game *game);
int isSolid(int x, int y);
void fillSpawns(struct Spawn s[]);

#endif
