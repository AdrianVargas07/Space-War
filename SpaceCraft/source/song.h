#ifndef SONG
#define SONG

#include <stdio.h>
#include <string.h>
#include <tonc.h>


int song[]=
{  3, 4, 5, 6, 7, 5, 6, 7, 9, 8, 7, 5, 6, 7, 8, 9, 8, 7, 6, 5, 6, 7, 5, 6, 7, 9, 8, 7, 6, 5, 5, 5, 3, 5, 5, 5, 3, 5, 5, 5 };

int song2[]=
{  4, 5, 6, 7, 8, 6, 7, 8, 10, 9, 8, 6, 7, 8, 9, 10, 9, 8, 7, 6, 7, 8, 6, 7, 8, 10, 9, 8, 6, 6, 6, 6, 4, 6, 6, 6, 4, 6, 6, 6 };

int song3[]=
{  9, 8, 9, 8, 9, 8, 2, 3, 2, 3, 2, 3, 8, 7, 8, 7, 8, 7, 6, 5, 6, 5, 6, 5, 2, 3, 2, 3, 2, 3, 7, 7, 6, 2, 2, 2, 3, 6, 5, 6 };


int note = 0;
int note3 = 0;
int octave = -2;
int octave2 = -1;

// Play a note and show which one was played
void note_play()
{

    // Play the actual note
    if (note <= 38){	//change the note
        note++;
    }else{
        note = 0;
        /*if (octave < -1){
            octave++;
        }else{
            octave = -2;
        }*/
    }


	int current = song[note];
	REG_SND1FREQ = SFREQ_RESET | SND_RATE(current, octave);
}

void note_play2()
{

    // Play the actual note
    if (note <= 38){	//change the note
        note++;
    }else{
        note = 0;
        /*if (octave < -1){
            octave++;
        }else{
            octave = -2;
        }*/
    }


	int current = song2[note];
	REG_SND1FREQ = SFREQ_RESET | SND_RATE(current, octave);
}

void note_play3()
{

    // Play the actual note
    if (note3 <= 38){	//change the note
        note3++;
    }else{
        note3 = 0;
        /*if (octave < -1){
            octave++;
        }else{
            octave = -2;
        }*/
    }


	int current = song3[note3];
	REG_SND1FREQ = SFREQ_RESET | SND_RATE(current, octave2);
}

// play shooting sound
void shoot(int octave)
{
    REG_SND1FREQ = SFREQ_RESET | SND_RATE(NOTE_D, octave);
}

#endif