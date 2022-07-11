#ifndef GAME_VEC3_H
#define GAME_VEC3_H

void GAME_Vec3_Null(int * v);
void GAME_Vec3_Move(int * dst, int * src);
void GAME_Vec3_Sum(int * dst, int * v1, int * v2);
void GAME_Vec3_Sub(int * dst, int * v1, int * v2);
void GAME_Vec3_DivByN(int * dst, int * v, int n);

#endif