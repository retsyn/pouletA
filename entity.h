#ifndef ENTITY_H
#define ENTITY_H

#include "poulet.h"

void create(int type, float x, float y, struct Entity e[]);
void kill(struct Entity *e);
void readSpawns(int x, int y, struct Spawns s[]);
void recycle(struct Entity *e, struct Game *g);

#endif
