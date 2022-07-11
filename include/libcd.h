#ifndef GAME_LIBCD_H
#define GAME_LIBCD_H

/*
    Functions
*/

int LIBCD_CdRead(int sectors, unsigned int * buf, int mode);
int LIBCD_CdInit();

#endif