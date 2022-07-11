#ifndef GAME_GPU_H
#define GAME_GPU_H

#include "common.h"

/*
    Functions
*/

void GAME_GPU_ChangeTexPage(int texPage);
void GAME_GPUPackets_Insert(unsigned int * gpuCommand);

/*
    Data
*/

extern LinkedList GAME_GPUPackets;
extern unsigned int * GAME_GPUPackets_Next;

#endif