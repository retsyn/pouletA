/*
 * entity.cpp
 * Poulet Poulet A+
 * Functions for adding, removing, and updating entities.
 */

#include "poulet.h"
#include "entity.h"
#include "graphics.h"
#include "physics.h"

// create a new entity in the world.
void create(int type, float x, float y, struct Entity e[]){

  int newIndex = 0;
  int i = 0;
  int elementSize = 0;

  // Iterate through what's still alive and active to not overwrite anything...
  for(i = 0; i <= ENT_MAX; i++){
    if(e[i].alive == 0){
      break;
    }
  }
  // If we can't fit that new enemy on screen, we return and just don't bother.
  if(i >= ENT_MAX) return;

  newIndex = i;
  e[i].alive = true;
  
  // Now we assign values to the new index.
  e[newIndex].x = x;
  e[newIndex].y = y;
  e[newIndex].frame = 0;
  

  // Catch default case:
  e[newIndex].image = cat;
  
  // Cat
  if(type == 1){
    e[newIndex].image = cat;
    e[newIndex].animSpeed = 5;
    e[newIndex].ax = .03;
  }
}


// Tag an entity as not alive, so it's free to be re-written.
void kill(struct Entity *e){

  // Make it dead and free up one of the slots.
  e->alive = 0;
}


// Check for reasons an Entity might need to give up it's slot
void recycle(struct Entity *e, struct Game *g){

  // camera x minus 16 is "off the screen by a margin of 8, offset by sprite size" and camera x plus 136 is off the other side.
  if(e->x < (g->camerax - 16) || e->x > (g->camerax + 136)){
    e->alive = 0; 
  }

  // Checking if falling in a hole or somehow up in the sky:
  if(e->y < -8 || e->y > 64){
    e->alive = 0;
  }
  
}


// Read the spawn list
void readSpawns(int x, int y, struct Spawn s[], struct Entity e[]){
  int i = 0;

  for(i = 0; i < SPAWN_MAX; i++){
    // If the spawn list says it's not on-screen, then have it created.
    if(s[i].x > x && s[i].x < x + 128 && s[i].onscreen == 0){
      create(s[i].kind, s[i].x, s[i].y, e);
      s[i].onscreen = 1;
    }
  }
}


void makeSpawn(int x, int y, struct Spawn s[]){

  int i = 0;

  // Append to the end of the spawn list
}

