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
  for(i = 0; i < ENT_MAX; i++){
    if(e[i].alive == 0){
      break;
    }
  }

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
  }
}

