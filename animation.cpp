/*
 * animation.cpp
 * Decides what frame should be played for any ent.
 */

#include "poulet.h"
#include "animation.h"

// For the player.
void playerAnimation(Entity *p, Game *g){
  int i = 0;

  p->ticker += abs(p->ax);
  if(p->ticker >= p->animSpeed){
    p->frame++;
    p->ticker = 0;
    if(p->frame > 3){
      p->frame = 0;
    }
  }  

  if(p->ax > 0) p->flip = 0;
  if(p->ax < 0) p->flip = 8;
  if(p->ax == 0) p->frame = 0;


  if(p->grounded == false){
    if(p->ay <= 0) p->frame = 6;
    if(p->ay > 0) p->frame = 7;
  }
}


// For enemies.
void enemyAnimation(Entity *e, Game *g){
  int i = 0;

  i++;
}

