/*
 * level.cpp
 * Poulet Poulet A+
 * 
 * Functions for drawing and reading contents of tilemaps.
 */

#include "poulet.h"
#include "tilemap.h"
#include "entity.h"

void drawLevel(int x, int y, Game *game){
  
  // x and y are offsets from the camera.
  int i;
  int tx;
  int ty;
  
  for(i = 0; i < (sizeof(maparray)); i++){
    if (pgm_read_byte(maparray + i) != 0){
      tx = (i % 128) * 8;
      ty = (i / 128) * 8;
        
      Sprites::drawOverwrite(tx - game->camerax, ty, tileset, pgm_read_byte((maparray + i)) -1);
    }
  }
}


int isSolid(int x, int y){

  // return true if something is there.
  int i;
  int tx = x / 8;
  int ty = y / 8;

  // convert i to be the correct place on the 1 dimensional map.
  i = tx + (ty * 128);


  if(pgm_read_byte(maparray + i) != 0){
    if(pgm_read_byte(maparray + i) <= 3){
      return 1;
    } else {
      return 0;   
    }
  } else {
    return 0;
  }
  // x and y converting to tiles.
}


void fillSpawns(struct Spawn s[]){
  // read spawn progmem and populate the spawns list.
  // Might be possible to skip the spawn buffer altogether to save more dynamic memory...

  int i = 0;
  int kind = 0;
  int x = 0;
  int y = 0;
 
  // Move by threes in the outer loop, as each entry is 3 bytes.

  // This loop is presently eternal and puts the machine in an infinite loop.
  
  for(i = 0; i <= 30; i = i + 3){
      kind = pgm_read_byte(spawndata + i);
      x = pgm_read_byte(spawndata + i + 1);
      y = pgm_read_byte(spawndata + i + 2);
      makeSpawn(x, y, kind, s);
  }

}


