#include "physics.h"

void physicsUpdate (struct Entity *p){

  int i; // iterator to check
  bool blocked; // State if a wall is found during a check.

  // lock the velocity to the set walkspeed.
  if(p->ax > 0){
    if(p->ax > p->walkSpeed){
      p->ax = p->walkSpeed; 
    }
  } else {  
    if(p->ax < -p->walkSpeed){
      p->ax = -p->walkSpeed; 
    }
  }

  // Apply gravity:
  p->ay += gravity;


  // Collision checks:
  // Right
  blocked = false;
  if(p->ax > 0){
    for(i = floor(p->x); i <= floor(p->x + p->ax); i++){
      if((isSolid(i + 9, p->y)) || (isSolid(i + 9, floor(p->y + 7)))){
        p->x = i;
        blocked = true;
        p->ax = 0;
        break;
      }
    }
    if(!blocked) p->x += p->ax;
  }

  // Left
  blocked = false;
  if(p->ax < 0){
    for(i = floor(p->x); i >= floor(p->x + p->ax); i--){
      if((isSolid(i-1, p->y)) || (isSolid(i-1, floor(p->y + 7)))){
        p->x = i;
        blocked = true;
        p->ax = 0;
        break;
      }
    }
    if(!blocked) p->x += p->ax;
  }

  // Down
  blocked = false;
  if(p->ay > 0){
    for(i = floor(p->y); i <= floor(p->y + p->ay); i++){
      if((isSolid(p->x , i + 8)) || (isSolid(p->x + 8, i + 8))){
        p->y = i;
        blocked = true;
        p->grounded = true;
        p->ay = 0;
        break;
      } else {
        p->grounded = false;
      }
    }
    if(!blocked) p->y += p->ay;
  }

  // Up
  blocked = false;
  if(p->ay < 0){
    for(i = floor(p->y); i >= floor(p->y + p->ay); i--){
      if((isSolid(p->x, i-1)) || (isSolid(p->x + 8, i-1))){
        p->y = i;
        blocked = true;
        p->ay = -p->ay;
        break;
      }
    }
    if(!blocked) p->y += p->ay;
  }


  // Handle falling out of world:
  if(p->y > 128) p->y = -8;

  // Add friction:
  if(p->ax > 0){
    p->ax -= groundFriction;
  }
  if(p->ax < 0){
    p->ax += groundFriction;
  }
  if(abs(p->ax) < groundFriction){
    p->ax = 0;
  }
}


