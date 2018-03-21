#include <Arduboy2.h>

Arduboy2 arduboy;

#include "poulet.h"
#include "graphics.h"
#include "tilemap.h"
#include "level.h"
#include "entity.h"
#include "physics.h"
#include "numbers.h"


// Forward declaration of essential types:
struct Entity;
struct Game;

Entity player;
Game game;

// later I'll init this as zero size
Entity ents[4];


// Init player



void setup() {

  // Player setup
  player.walkSpeed = 1;
  player.walkAccel = 0.1;
  player.animSpeed = 4;
  
  game.mode = 1;

  // Arduboy housekeeping;
  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.clear();

  // Begin screen mirroring serial output.
  Serial.begin(9600);

  gameInit(&player, &game);

}


void loop() {

  // Check is a frame has completed:
  if(!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();

  if(game.mode == 0){
    play(&player, &game);
  }

  if(game.mode == 1){
    title(&game);
  }
 
  // Write screen contents to serial port for screen mirroring:
  Serial.write(arduboy.getBuffer(), 128 * 64 / 8);
 
  arduboy.display();
  
}


void title(Game *g){
  Sprites::drawOverwrite(0, -10, titlescreen, 0);
  arduboy.setCursor(40, 40);
  arduboy.print("Start");
  arduboy.setCursor(40, 48);
  if(g->debug == false){
    arduboy.print("Debug: Off");
  } else {
    arduboy.print("Debug: On");
  }
  arduboy.setCursor(40, 56);
  arduboy.print("Sound: Off");

  
  if(arduboy.justPressed(B_BUTTON) && g->menuItem == 0){
    g->mode = 0;
  }

  if(arduboy.justPressed(UP_BUTTON)) g->menuItem -= 1;
  if(arduboy.justPressed(DOWN_BUTTON)) g->menuItem += 1;
  if(g->menuItem > 2) g->menuItem = 0;
  if(g->menuItem < 0) g->menuItem = 2;
  
  arduboy.setCursor(30, (40 + (g->menuItem * 8)));
  arduboy.print(">");
  

  if(arduboy.justPressed(LEFT_BUTTON) || arduboy.justPressed(RIGHT_BUTTON)){
    if(g->menuItem == 1){
      if(g->debug){
        g->debug = false;
      } else {
        g->debug = true;
      }
    }
    // When sound is ready the switch shall get made here.
  } 
}


void play(Entity *p, Game *g){

  if (arduboy.pressed(LEFT_BUTTON)){
    p->ax -= p->walkAccel; 
  }
  if (arduboy.pressed(RIGHT_BUTTON)){
    p->ax += p->walkAccel;
  }
  if (arduboy.justPressed(B_BUTTON) && p->grounded){
    p->ay = -pJumpPower;
    p->grounded = false;
  }
  if (arduboy.justPressed(A_BUTTON)){
    // YOU WIN!
    g->score += 1000;
  }

  physicsUpdate(&player);
  camera(&player, &game);
  if(game.debug) debug(&player, &game);
  drawLevel(0, 0, &game);
  showHUD(&game);
  animation(p, g);

}


void gameInit(Entity *p, Game *g){

  p->x = 20;
  p->y = 0;

  if(arduboy.pressed(A_BUTTON) && arduboy.pressed(UP_BUTTON)){
    g->debug = true;
  }

  g->mode = 1;
  
}


void animation(Entity *p, Game *game){

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

  Sprites::drawPlusMask(p->x - game->camerax, p->y, poulet, p->frame + p->flip);

}


void camera(Entity *p, Game *game){

  if(p->x > (game->camerax + 70)){
    game->camerax += 1;
  }
  if(p->x < (game->camerax + 58)){
    game->camerax -= 1;
  }

  if(game->camerax < 0) game->camerax = 0;

}


void debug(Entity *p, Game *game){ 
  arduboy.print("X: ");
  arduboy.print(p->x);
  arduboy.print("  Y: ");
  arduboy.print(p->y);
  arduboy.print("\nTX: ");
  arduboy.print(floor(p->x / 8));
  arduboy.print("  TY: ");
  arduboy.print(floor(p->y / 8));
  arduboy.print("\nAX: ");
  arduboy.print(p->ax);
  arduboy.print("  AY: ");
  arduboy.print(p->ay);
}


void showHUD(Game *g){

  drawScore(g->score);
}


