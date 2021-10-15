#ifndef LEVELTWO
#define LEVELTWO

#include "sprite.h"
#include "background.h"
#include "spacecraft.h"
#include "song.h"

u8 txt_scrolly2= 8;
int alive2 = 1;
int wait2 = 1;
int winner2 = 0;
int lvl2Points = 0;
int ammo2 = 1;

int sec = 0;

void secondLevel(OBJ_ATTR* buffer){
  oam_init(buffer, 128); //memory is cleaned

  resetPositionBg(); //the background position is reset

  loadBackground(5); 

  Sprite spacecraft;
  initializeSprite(&spacecraft, &buffer[0], 20, 70);
  assignAttributesSprite(&spacecraft); //the sprite is loaded into memory

  Sprite enemy;
  initializeEnemy(&enemy, &buffer[1], 220, 70);
  assignAttributesSpriteEnemy(&enemy);

  Sprite blast = {
      .posY = 1000
  };

  Sprite enemyBlast= {
      .posY = 1000
  };

  int time= 0;
  // // turn sound on
  REG_SNDSTAT= SSTAT_ENABLE;
  // snd1 on left/right ; both full volume
  REG_SNDDMGCNT = SDMG_BUILD_LR(SDMG_SQR1, 7);
  // DMG ratio to 100%
  REG_SNDDSCNT= SDS_DMG100;

  // no sweep
  REG_SND1SWEEP= SSW_OFF;
  //envelope: vol=12, decay, max step time (7) ; 50% duty
  REG_SND1CNT= SSQR_ENV_BUILD(12, 0, 7) | SSQR_DUTY1_2;
  REG_SND1FREQ= 0;

  //shows the start screen start at A to start
  while(wait2){
      vid_vsync();

      key_poll();

      if (key_hit(KEY_A)){
          wait2 = 0;
      }

      //play notes with counter
      if (time <= 24){		//time control of the sound
          time ++;
      }else {
          time = 0;
          note_play2();
      }

  }

  loadBackground(4); // Comentar si se quiere depurar el codigo (por texto)
  loadSprite(spacecraftTiles, spacecraftTilesLen, spacecraftPal, spacecraftPalLen);
  tte_init_se_default(0, BG_CBB(0) | BG_SBB(5));	// Descomentar si se quiere depurar el codigo (por texto)
  int instance = 0;
  int enemyMoves = 0;
  //game battle
  while(alive2){
    char str[100] = {};
    snprintf(str, 100, "#{P:0,0}Lvl 2 Score: %d", lvl2Points);
    tte_write(str);

    vid_vsync(); // vertical sync so that the screen can be seen well

    key_poll(); //detect which key is pressed

    movement(&spacecraft, 2); //function in charge of moving sprites

    tickSpriteAnimationBeam(&blast);
    tickEnemyAnimation(&enemy);
    tickSpriteAnimationEnemyShot(&enemyBlast);

    moveBackground(2);

    //play notes with counter
    if (time <= 20){		//time control of the sound
      time ++;
    }else {
      time = 0;
      note_play3();
    }

    if(key_hit(KEY_A)){
      if (ammo2 > 0) {
        shoot(3);
        beamShot(&blast, buffer, spacecraft.posX, spacecraft.posY);
        ammo2 = 0;
      }
    }
    moveAsteroid(&enemyBlast);

    if(!enemy.isColliding){
      enemyShot(&enemyBlast, buffer, enemy.posX, enemy.posY);
    }

    if(doSpritesOverlap(&spacecraft, &enemy)){
      spacecraft.isColliding = 1;
      enemy.isColliding = 1;
      alive2 = 0;
    }

    if(doSpritesOverlap(&spacecraft, &enemyBlast)){
      spacecraft.isColliding = 1;
      enemyBlast.isColliding = 1;
      alive2 = 0;
    }

    if(doSpritesOverlap(&blast, &enemyBlast)){
      blast.collided = 1;
      blast.isColliding = 1;
      enemyBlast.collided = 1;
      enemyBlast.isColliding = 1;
    }

    if (doSpritesOverlap(&blast, &enemy)) {
      sec = 0;
      REG_TM2D = -0x4000;
      REG_TM2CNT = TM_FREQ_1024 | TM_ENABLE;
      REG_TM3CNT = TM_ENABLE | TM_CASCADE;
      if(REG_TM3D != sec){
        sec = REG_TM3D;
      }
      blast.collided = 1;
      blast.isColliding = 1;
      enemy.isColliding = 1;
      for (int i = 0; i < 4; i++) {
        if(sec == 0){
          lvl2Points += 1;
        }
      }
      if(sec > 1){
        enemy.isColliding = 0;
        moveEnemy(&enemy, 0, 1);
        REG_TM3CNT = -0x4000;
      }
      ammo2 = 1;
    } else {
      enemy.isColliding = 0;
      instance++;
      if (blast.collided) {
        blast.posY = -16;
        blast.collided = 0;
      }
      if (enemyBlast.collided) {
				enemyBlast.posY = -46;
				enemyBlast.collided = 0;
			}
      if (enemyMoves == 6){
        moveEnemy(&enemy, instance, 0);
        enemyMoves = 0;
      } else {
        enemyMoves++;
      }

      if (blast.posX > 240){
        ammo2 = 1;
      } else {
        moveBlasts(&blast);
      }

      blast.isColliding = 0;
      spacecraft.isColliding = 0;
      enemy.isColliding = 0;
    }

    if(lvl2Points == 1000){
      winner2 = 1;
      alive2 = 0;
    }

    oam_copy(oam_mem, buffer, 4); // is copied from oam memory to video memory (it is drawn on screen)
  }

  //shows the end game screen
  while(1){
    oam_init(buffer, 128);

    vid_vsync(); // vertical sync so that the screen can be seen well

    resetPositionBg();

    if(winner2) {
      loadBackground(2);
      // //play notes with counter
      if (time <= 24){		//time control of the sound
        time ++;
      }else {
        time = 0;
        note_play();
      }
    } else {
      loadBackground(3);
      // //play notes with counter
      if (time <= 16){		//time control of the sound
        time ++;
      }else {
        time = 0;
        note_play();
      }
    }
  }
}

#endif
