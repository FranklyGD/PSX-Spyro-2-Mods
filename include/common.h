#ifndef GAME_COMMON_H
#define GAME_COMMON_H

/*
    Enums
    when we have researched more the game,
    we can group all these in different header files
*/

enum InputFlags {
    INPUT_TRIGGERLEFT =   0x1, // L2
    INPUT_TRIGGERRIGHT =  0x2, // R2
    INPUT_BUMPERLEFT =    0x4, // L1
    INPUT_BUMPERRIGHT =   0x8, // R1
    INPUT_TRIANGLE =      0x10,
    INPUT_CIRCLE =        0x20,
    INPUT_CROSS =         0x40,
    INPUT_SQUARE =        0x80,
    INPUT_SELECT =        0x100,
    INPUT_STICKLEFT =     0x200, // L3
    INPUT_STICKRIGHT =    0x400, // R3
    INPUT_START =         0x800,
    INPUT_DPADUP =        0x1000,
    INPUT_DPADRIGHT =     0x2000,
    INPUT_DPADDOWN =      0x4000,
    INPUT_DPADLEFT =      0x8000
};

enum Levels {
    LEVEL_SUMMER_FOREST = 0,
    LEVEL_GLIMMER = 1,
    LEVEL_IDOL_SPRINGS = 2,
    LEVEL_COLOSSUS = 3,
    LEVEL_HURRICOS = 4,
    LEVEL_AQUARIA_TOWERS = 5,
    LEVEL_SUNNY_BEACH = 6,
    LEVEL_OCEAN_SPEEDWAY = 7,
    LEVEL_CRUSHS_DUNGEON = 8,
    LEVEL_AUTUMN_PLAINS = 9,
    LEVEL_SKELOS_BADLANDS = 10,
    LEVEL_CRYSTAL_GLACIER = 11,
    LEVEL_BREEZE_HARBOR = 12,
    LEVEL_ZEPHYR = 13,
    LEVEL_METRO_SPEEDWAY = 14,
    LEVEL_SCORCH = 15,
    LEVEL_SHADY_OASIS = 16,
    LEVEL_MAGMA_CONE = 17,
    LEVEL_FRACTURE_HILLS = 18,
    LEVEL_ICY_SPEEDWAY = 19,
    LEVEL_GULPS_OVERLOOK = 20,
    LEVEL_WINTER_TUNDRA = 21,
    LEVEL_MYSTIC_MARSH = 22,
    LEVEL_CLOUD_TEMPLES = 23,
    LEVEL_CANYON_SPEEDWAY = 24,
    LEVEL_ROBOTICA_FARMS = 25,
    LEVEL_METROPOLIS = 26,
    LEVEL_DRAGON_SHORES = 27,
    LEVEL_RIPTOS_ARENA = 28
};

enum GameState {
    GAMESTATE_PLAYING = 0, // Normal gameplay
    GAMESTATE_TALKING = 1, // Interactions with Zoe, Moneybags...
    GAMESTATE_TRANSITION_LOAD_TO_PLAYING = 3, // Happens briefly after a loading screen
    GAMESTATE_PAUSED = 4,
    GAMESTATE_LOADING_HUBS = 5, // Book load
    GAMESTATE_CUTSCENE = 6,
    GAMESTATE_LOADING_LEVELS = 7 // Spyro flying skybox animation
};

enum CameraState {
    CAMERASTATE_ALIGN = 0,
    CAMERASTATE_MOVING = 1,
    CAMERASTATE_CHASEFLY = 3,
    CAMERASTATE_CHASESWIM = 4,
    CAMERASTATE_PASSIVE = 6,
    CAMERASTATE_LOOK = 7,
    CAMERASTATE_QUICKALIGN = 8,
    CAMERASTATE_DIALOGUE = 18,
    CAMERASTATE_WHIRLWINDALIGN = 23
};

/*
    Structs
    when we have researched more the game,
    we can group all these in different header files
*/

typedef struct {
    int longitude;
    int latitude;
    int radius;
    int pitch;
    int yaw;
} Orbit;

typedef struct {
    int current;
    int pressed;
    int released;
    unsigned char rightStickAnalogX;
    unsigned char rightStickAnalogY;
    unsigned char leftStickAnalogX;
    unsigned char leftStickAnalogY;
} InputState;

typedef struct {
    unsigned int * tail;
    unsigned int * head;
} LinkedList;

typedef struct {
    int vramYmin;
    int vramYmax;
    int length;
} TextConfig;

/*
    Functions
    when we have researched more the game,
    we can group all these in different header files
*/

void GAME_main();
void GAME_ReadInput();
void GAME_UpdateGame_Normal();
void GAME_InitSound();
void GAME_InitGeometry();

void GAME_memcpyWord(int *dst,int *src,int size);
void GAME_memsetWord(int *buffer,int n,int size);

void GAME_UpdateCameraOrbitPhysics();
void GAME_ProcessInputSpyro();

void GAME_DrawText(char * text, int x, short y, int colorIndex, TextConfig * textConfig);
void GAME_DrawText2(char * text, int x, short y, int colorIndex, TextConfig * textConfig);
int GAME_GetTextWidth(char * text);
void GAME_DrawText_Center(char * text, int x, short y, int colorIndex);
void GAME_DrawText_CenterWithBG(char * text, int x, int y, int colorIndex);
void GAME_DrawText_Right(char * text, int x, short y, int colorIndex);
void GAME_DrawNumberSmall(int value, int x, short y, int colorIndex);
void GAME_DrawNumberSmall_Right(int value, int x, short y, int colorIndex);
void GAME_DrawNumberBig(int x, int y, int value);

// Semi-Transparent, Flat, RGB = (8, 8, 8)
void GAME_DrawSTBlackRect(short left, short right, short top, short bottom);
void GAME_DrawOutlinedBG(short left, short right, short top, short bottom);
void GAME_DrawRoundedBG(short left, short right, short top, short bottom);
// Opaque, Flat, RGB = (0, 0, 0)
void GAME_DrawOpaqueBlackRect(short x1, short x2, short y1, short y2);
// Used during the pause menu
void GAME_DrawGameScreenshot();

/*
    Data
    when we have researched more the game,
    we can group all these in different header files
*/

extern int GAME_levelID;
extern int GAME_levelClock;
extern int GAME_gemCount;
extern int GAME_gemCountHUD;
extern int GAME_cameraState;
extern Orbit GAME_cameraOrbitPosition;
extern Orbit GAME_cameraOrbitVelocity;
extern Orbit GAME_cameraOrbitAccel;
extern InputState GAME_inputStates[5];
extern int GAME_gameState;

#endif