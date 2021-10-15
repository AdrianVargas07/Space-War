
//{{BLOCK(winner)

//======================================================================
//
//	winner, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 53 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 3392 + 2048 = 5952
//
//	Time-stamp: 2020-10-15, 01:34:08
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_WINNER_H
#define GRIT_WINNER_H

#define winnerTilesLen 3392
extern const unsigned int winnerTiles[848];

#define winnerMapLen 2048
extern const unsigned int winnerMap[512];

#define winnerPalLen 512
extern const unsigned int winnerPal[128];

#endif // GRIT_WINNER_H

//}}BLOCK(winner)
