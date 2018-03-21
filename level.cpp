/*
 * level.cpp
 * Poulet Poulet A+
 * 
 * Functions for drawing and reading contents of tilemaps.
 */

#include "poulet.h"
#include "tilemap.h"

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
  int tx = floor(x / 8);
  int ty = floor(y / 8);

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


