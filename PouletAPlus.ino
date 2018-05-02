#include <Arduboy2.h>
#include <Tinyfont.h>
#include <math.h>

Arduboy2 arduboy;
Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());

#include "poulet.h"
#include "graphics.h"
#include "animation.h"
#include "tilemap.h"
#include "level.h"
#include "entity.h"
#include "physics.h"
#include "numbers.h"
#include "sprite.h"


// Forward declaration of essential types:
struct Entity;
struct Game;
struct Spawn;


Entity player;
Game game;
Entity ents[ENT_MAX];
Spawn spawns[SPAWN_MAX];


void setup() {

  // Player setup
  player.walkSpeed = 1;
  player.walkAccel = 0.1;
  player.animSpeed = 4;
  player.image = poulet;
 
  game.mode = 1;

  // Arduboy housekeeping;
  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.clear();

  // Begin screen mirroring serial output.
  Serial.begin(9600);

  gameInit(&player, &game, spawns);

}


void loop() {

  // Check is a frame has completed:
  if(!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();

  if(game.mode == 0){
    play(&player, &game, ents, spawns);
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


void play(Entity *p, Game *g, Entity *ents, Spawn s[]){

  int i = 0;

  // Capture player controls
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
    g->score += 10;
    //create(1, p->x, p->y - 10, ents); 
  }

  // Update physics for all entities
  physicsUpdate(p);
  for(i = 0; i < ENT_MAX; i++){
    physicsUpdate(&ents[i]);
  }

  // Update Camera
  camera(&player, &game);

  // Draw everything:
  drawLevel(0, 0, &game);
  playerAnimation(p, g);
  drawSprite(g, p);

  for(i = 0; i < ENT_MAX; i++){
    if(ents[i].alive == false) i++;
    enemyAnimation(&ents[i], g);
    drawSprite(g, &ents[i]);
  }

  // Handle Spawning and Despawning:
  readSpawns(g->camerax, 0, s, ents);
  for(i = 0; i < ENT_MAX; i++){
    recycle(&ents[i], &game);
  }

  if(game.debug) debug(&player, &game, ents);
  
  showHUD(g);

}


void gameInit(Entity *p, Game *g, Spawn *s){

  p->x = 20;
  p->y = 0;

  // Start on title screen.
  g->mode = 1;


  //void create(int type, float x, float y, struct Entity e[]);
  create(1, 10, 10, ents);

  makeSpawn(s);
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


void debug(Entity *p, Game *g, Entity e[]){ 
  int i = 0;

  tinyfont.setCursor(1, 0);
  tinyfont.print("Debug Mode");
  tinyfont.setCursor(1, 5);
  tinyfont.print("p.X:");  
  tinyfont.print(int(p->x));
  tinyfont.print(" p.Y:");  
  tinyfont.print(int(p->y));
  tinyfont.setCursor(1, 10);
  tinyfont.print("Score: ");
  tinyfont.print(g->score);

  tinyfont.setCursor(1,15);
  tinyfont.print("Ents slots in use:");
  for(i = 0; i <= ENT_MAX; i++){
    tinyfont.setCursor(i * 8, 20);
    tinyfont.print(e[i].alive);
  }

  tinyfont.setCursor(1, 25);
  tinyfont.print("Spawns!");
}


void showHUD(Game *g){

  drawScore(g->score);
}


