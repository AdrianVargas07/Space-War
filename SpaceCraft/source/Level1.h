#ifndef LEVELONE
#define LEVELONE

#include "sprite.h"
#include "background.h"
#include "spacecraft.h"
#include "song.h"
#include "Level2.h"

u8 txt_scrolly= 8;
int alive = 1;
int wait = 1;
int winner = 0;
int destroyedAsteroids = 0;
int ammo = 1;
int end = 1;

void firstLevel(OBJ_ATTR* buffer, int *copy_completed){

	loadBackground(0); // Comentar si se quiere depurar el codigo (por texto)

	Sprite spacecraft;
	initializeSprite(&spacecraft, &buffer[0], 20, 70);
	assignAttributesSprite(&spacecraft); //the sprite is loaded into memory

	Sprite asteriod;

	Sprite blast = {
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
	while(wait){
		vid_vsync();

		key_poll();

		if (key_hit(KEY_A)){
			wait = 0;
		}

		//play notes with counter
		if (time <= 32){		//time control of the sound
			time ++;
		}else {
			time = 0;
			note_play();
		}

	}
	tte_init_se_default(0, BG_CBB(0) | BG_SBB(5));	// Descomentar si se quiere depurar el codigo (por texto)

	loadBackground(1); // Comentar si se quiere depurar el codigo (por texto)
	loadSprite(spacecraftTiles, spacecraftTilesLen, spacecraftPal, spacecraftPalLen);

	while(!copy_completed){
		// esperar a que termine de copiarse los datos
	}

	//game battle
	while(alive){

		char str[100] = {};
		snprintf(str, 100, "#{P:0,0}Score:%d", destroyedAsteroids);
		tte_write(str);

		vid_vsync(); // vertical sync so that the screen can be seen well

		key_poll(); //detect which key is pressed

		movement(&spacecraft, 1); //function in charge of moving sprites

		tickSpriteAnimation(&asteriod);

		tickSpriteAnimationBeam(&blast);

		moveBackground(1);

		// //play notes with counter
		if (time <= 24){		//time control of the sound
			time ++;
		}else {
			time = 0;
			note_play();
		}

		if(key_hit(KEY_A)){

			if (ammo > 0) {
				shoot(3);
				beamShot(&blast, buffer, spacecraft.posX, spacecraft.posY);
				ammo = 0;
			}

		}

		if(doSpritesOverlap(&spacecraft, &asteriod)){

			spacecraft.isColliding = 1;
			asteriod.isColliding = 1;
			alive = 0;

		}

		if (doSpritesOverlap(&blast, &asteriod)) {
			blast.collided = 1;
			blast.isColliding = 1;
			asteriod.isColliding = 1;
			for (int i = 0; i < 4; i++) {
				if(i == 1){
					for(int j = 0; j < 40; j++){
						if(j == 39){
							destroyedAsteroids += 5;
						}
					}
				}
				asteroidRain(&asteriod, buffer);
			}
			ammo = 1;

		} else {

			if (blast.collided) {
				blast.posY = -16;
				blast.collided = 0;
			}

			moveAsteroid(&asteriod);
			asteroidRain(&asteriod, buffer);

			if (blast.posX > 240){
				ammo = 1;
			} else {
				moveBlasts(&blast);
			}

			blast.isColliding = 0;
			spacecraft.isColliding = 0;
			asteriod.isColliding = 0;

		}

		if(destroyedAsteroids == 500){
			secondLevel(buffer);
		}

		oam_copy(oam_mem, buffer, 3); // is copied from oam memory to video memory (it is drawn on screen)
	}

	//shows the end game screen
	while(end){
		oam_init(buffer, 128);

		vid_vsync(); // vertical sync so that the screen can be seen well

		resetPositionBg();

		if(winner) {
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
