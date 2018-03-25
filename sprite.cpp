/*
 * sprite.cpp
 */
 
#include <Arduboy2.h>

#include "poulet.h"


 void drawSprite(Game *g, Entity *e){
  
  Sprites::drawPlusMask(e->x - g->camerax, e->y, e->image, e->frame + e->flip);
}

