#ifndef ENTITY_H
#define ENTITY_H


void entPhysicsUpdate(struct Entity *e){

  // Process the entity physics.
  
  int i; // iterator to check
  bool blocked; // State if a wall is found during a check.

  // lock the velocity to the set walkspeed.
  if(e->ax > 0){
    if(e->ax > e->walkSpeed){
      e->ax = e->walkSpeed; 
    }
  } else {  
    if(e->ax < -e->walkSpeed){
      e->ax = -e->walkSpeed; 
    }
  }

  // Apply gravity:
  e->ay += gravity;


  // Collision checks:
  // Right
  blocked = false;
  if(e->ax > 0){
    for(i = floor(e->x); i <= floor(e->x + e->ax); i++){
      if((isSolid(i + 9, e->y)) || (isSolid(i + 9, floor(e->y + 7)))){
        e->x = i;
        blocked = true;
        e->ax = 0;
        break;
      }
    }
    if(!blocked) e->x += e->ax;
  }

  // Left
  blocked = false;
  if(e->ax < 0){
    for(i = floor(e->x); i >= floor(e->x + e->ax); i--){
      if((isSolid(i-1, e->y)) || (isSolid(i-1, floor(e->y + 7)))){
        e->x = i;
        blocked = true;
        e->ax = 0;
        break;
      }
    }
    if(!blocked) e->x += e->ax;
  }

  // Down
  blocked = false;
  if(e->ay > 0){
    for(i = floor(e->y); i <= floor(e->y + e->ay); i++){
      if((isSolid(e->x , i + 8)) || (isSolid(e->x + 8, i + 8))){
        e->y = i;
        blocked = true;
        e->grounded = true;
        e->ay = 0;
        break;
      } else {
        e->grounded = false;
      }
    }
    if(!blocked) e->y += e->ay;
  }

  // Up
  blocked = false;
  if(e->ay < 0){
    for(i = floor(e->y); i >= floor(e->y + e->ay); i--){
      if((isSolid(e->x, i-1)) || (isSolid(e->x + 8, i-1))){
        e->y = i;
        blocked = true;
        e->ay = -e->ay;
        break;
      }
    }
    if(!blocked) e->y += e->ay;
  }


  // Handle falling out of world:
  if(e->y > 128) e->y = -8;

  // Add friction:
  if(e->ax > 0){
    e->ax -= groundFriction;
  }
  if(e->ax < 0){
    e->ax += groundFriction;
  }
  if(abs(e->ax) < groundFriction){
    e->ax = 0;
  }
}

  



#endif
