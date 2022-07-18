#ifndef __cplusplus
#include <stdbool.h>
#endif

#include <libc.h>
#include <common.h>
#include <gpu.h>
#include <spyro.h>
#include <vec3.h>

#define FRAME_WIDTH 512
#define FRAME_HEIGHT 228

#define SCREEN_LEFT 0
#define SCREEN_RIGHT 512
#define SCREEN_TOP 12
#define SCREEN_BOTTOM 228

#define LINE_HEIGHT 12

typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} Color;

enum BlendMode {
	BLENDMODE_MULTIPLY,
	BLENDMODE_ADD
};

enum AdditionsOptions {
	OPTION_SHOW_LEVEL_TIME,
	OPTION_SHOW_POSITION,
	OPTION_SHOW_PHYSICS_SPEED,
	OPTION_SHOW_PHYSICS_VEL,
	OPTION_SHOW_TRUE_SPEED,
	OPTION_SHOW_TRUE_VEL,
	OPTION_SHOW_INPUT,
	OPTION_ENABLE_RSTICK_CAMERA,
	OPTION_UPDATE_DELAY,
	MAX_OPTIONS
};

enum OptionType {
	OPTIONTYPE_TOGGLE,
	OPTIONTYPE_NUMBER
};

char* str_Options[] = {
	"Show Level Time",
	"Show Position",
	"Show Speed -Phy-",
	"Show Velocity -Phy-",
	"Show Speed -Tru-",
	"Show Velocity -Tru-",
	"Show Input",
	"Enable R-Stick Cam",
	"Update Delay"
};

char optionTypes[] = {
	OPTIONTYPE_TOGGLE,
	OPTIONTYPE_TOGGLE,
	OPTIONTYPE_TOGGLE,
	OPTIONTYPE_TOGGLE,
	OPTIONTYPE_TOGGLE,
	OPTIONTYPE_TOGGLE,
	OPTIONTYPE_TOGGLE,
	OPTIONTYPE_TOGGLE,
	OPTIONTYPE_NUMBER
};

static bool inHUDOptions;
static char optionValues[MAX_OPTIONS];
static char selectedOption;

static unsigned char updateDelay;
static int bufferedInputPressed;
static int bufferedInputReleased;

void DrawLine(short p0x,short p0y, Color p0c, short p1x, short p1y, Color p1c);
void DrawRectST(short left, short right, short top, short bottom, Color color);
void PrintVector(char* label, Vec3 *v, int x, int y);
void DrawInjectedMessage(int x, int y);
int InterpInt(int from, int to, unsigned char t);

void ProcessInput() {
	GAME_ReadInput();

	InputState* currentInput = &GAME_inputStates[0];
	if (
		currentInput->current & STICKLEFT && currentInput->pressed & STICKRIGHT ||
		currentInput->current & STICKRIGHT && currentInput->pressed & STICKLEFT
	) {
		inHUDOptions = !inHUDOptions;
		selectedOption = 0;

		if (!inHUDOptions) {
			updateDelay = optionValues[OPTION_UPDATE_DELAY];
		}
	}

	if (inHUDOptions) {
		if (currentInput->pressed & DPADDOWN) {
			selectedOption++;
			if (selectedOption >= MAX_OPTIONS) {
				selectedOption = 0;
			}
		}
		if (currentInput->pressed & DPADUP) {
			selectedOption--;
			if (selectedOption <= -1) {
				selectedOption = MAX_OPTIONS - 1;
			}
		}
		switch (optionTypes[selectedOption]) {
			case OPTIONTYPE_TOGGLE:
				if (currentInput->pressed & CROSS) {
					optionValues[selectedOption] = !optionValues[selectedOption]; 
				}
				break;
			case OPTIONTYPE_NUMBER:
				if (currentInput->pressed & DPADLEFT) {
					optionValues[selectedOption]--; 
				}
				if (currentInput->pressed & DPADRIGHT) {
					optionValues[selectedOption]++; 
				}
				break;
			default:
				break;
		}
		
		if (optionValues[OPTION_UPDATE_DELAY] < 0) {
			optionValues[OPTION_UPDATE_DELAY] = 0;
		}
	}

	if (optionValues[OPTION_ENABLE_RSTICK_CAMERA]) {
		if (currentInput->rightStickAnalogX != 0x7f || currentInput->rightStickAnalogY != 0x7f) {
			GAME_cameraState = PASSIVE;
		}
	}
}

void SpyroPreprocessInput() {
	if (optionValues[OPTION_UPDATE_DELAY] > 0) {
		GAME_inputStates[0].pressed = bufferedInputPressed;
		GAME_inputStates[0].released = bufferedInputReleased;
		bufferedInputPressed = 0;
		bufferedInputReleased = 0;
	}

	GAME_ProcessInputSpyro();
}

void UpdateGame_Normal_Override() {
	if (!inHUDOptions) {
		if (updateDelay == 0) {
			GAME_UpdateGame_Normal();
			updateDelay = optionValues[OPTION_UPDATE_DELAY];
		} else {
			bufferedInputPressed |= GAME_inputStates[0].pressed;
			bufferedInputReleased |= GAME_inputStates[0].released;

			updateDelay--;
		}
	}
}

void PreUpdateCameraPhysics() {
	InputState* currentInput = &GAME_inputStates[0];
	if (optionValues[OPTION_ENABLE_RSTICK_CAMERA]) {
		int longSpeed = currentInput->rightStickAnalogX - 0x7f;
		int latSpeed = currentInput->rightStickAnalogY - 0x7f;

		GAME_cameraOrbitAccel.longitude = longSpeed * 10;
		GAME_cameraOrbitAccel.latitude = latSpeed * 10;
	}

	GAME_UpdateCameraOrbitPhysics();
}

void DrawDebugger() {
	char buffer[64];

	if (optionValues[OPTION_SHOW_LEVEL_TIME]) {
		int* ptrLoad = (int*)0x800698f0; // portalTransitionState?
		bool isInPortal = *ptrLoad == 0;

		static unsigned int totalFrames;
		static unsigned char centeringAnim; 
		if (!isInPortal) {
			totalFrames = GAME_levelClock;
			centeringAnim = 0;
		} else if (centeringAnim < 0xff) {
			int next = centeringAnim + 0x20;
			if (next > 0xff) {
				next = 0xff;
			}
			centeringAnim = next;
		}

		// Display level time
		int frames = totalFrames % 60;
		int seconds = totalFrames / 60;
		int minutes = seconds / 60;
		seconds %= 60;

		LIBC_sprintf(buffer, "Level Time: %02u:%02u.%02u", minutes, seconds, frames);
		if (!isInPortal) {
			GAME_DrawText_Center(buffer, FRAME_WIDTH / 2, InterpInt(SCREEN_BOTTOM - LINE_HEIGHT, (SCREEN_BOTTOM - LINE_HEIGHT) / 2, centeringAnim), (GAME_levelClock / 30) % 2 ? 1 : 2);
		} else {
			GAME_DrawText_CenterWithBG(buffer, FRAME_WIDTH / 2, InterpInt(SCREEN_BOTTOM - LINE_HEIGHT, (SCREEN_BOTTOM - LINE_HEIGHT) / 2, centeringAnim), 2);
		}
	}

	int linePos = 2 + SCREEN_TOP;

	// Other
	if (optionValues[OPTION_SHOW_POSITION]) {
		Vec3* position = &GAME_spyro.position;
		PrintVector("pos", position, 2, linePos);
		linePos += LINE_HEIGHT;
	}
	
	if (optionValues[OPTION_SHOW_PHYSICS_SPEED]) {
		int magnitude = GAME_Vec3_Len(&GAME_spyro.physicsVelocity, 1);
		int magnitudeDecimal = magnitude % 1000;
		if (magnitudeDecimal < 0) {
			magnitudeDecimal = -magnitudeDecimal;
		} 
		magnitude = magnitude / 1000;

		LIBC_sprintf(buffer, "spd: %d.%03d", magnitude, magnitudeDecimal);
		GAME_DrawText(buffer, 2, linePos, 2, 0);
		linePos += LINE_HEIGHT;
	}

	if (optionValues[OPTION_SHOW_PHYSICS_VEL]) {
		Vec3* velocity = &GAME_spyro.physicsVelocity;
		PrintVector("vel", velocity, 2, linePos);
		linePos += LINE_HEIGHT;
	}

	if (optionValues[OPTION_SHOW_TRUE_SPEED]) {
		int magnitude = GAME_Vec3_Len(&GAME_spyro.trueVelocity, 1);
		int magnitudeDecimal = magnitude % 1000;
		if (magnitudeDecimal < 0) {
			magnitudeDecimal = -magnitudeDecimal;
		} 
		magnitude = magnitude / 1000;

		LIBC_sprintf(buffer, "spd: %d.%03d", magnitude, magnitudeDecimal);
		GAME_DrawText(buffer, 2, linePos, 2, 0);
		linePos += LINE_HEIGHT;
	}

	if (optionValues[OPTION_SHOW_TRUE_VEL]) {
		Vec3* velocity = &GAME_spyro.trueVelocity;
		PrintVector("truvel", velocity, 2, linePos);
		linePos += LINE_HEIGHT;
	}

	if (optionValues[OPTION_SHOW_INPUT]) {
		// Input Display
		InputState* currentInput = &GAME_inputStates[0];

		Color colorUnpressed;
		colorUnpressed.r = 0x20;
		colorUnpressed.g = 0x20;
		colorUnpressed.b = 0x20;
		
		Color colorPressed;
		colorPressed.r = 0x80;
		colorPressed.g = 0x80;
		colorPressed.b = 0x80;

		GAME_GPUChangeTexPage(0xa8);
		DrawRectST(4, 16, FRAME_HEIGHT - 23, FRAME_HEIGHT - 23 + 4, currentInput->current & TRIGGERLEFT ? colorPressed : colorUnpressed);
		DrawRectST(2, 18, FRAME_HEIGHT - 23 + 5, FRAME_HEIGHT - 23 + 9, currentInput->current & BUMPERLEFT ? colorPressed : colorUnpressed);

		DrawRectST(20 + 4, 20 + 16, FRAME_HEIGHT - 23, FRAME_HEIGHT - 23 + 4, currentInput->current & TRIGGERRIGHT ? colorPressed : colorUnpressed);
		DrawRectST(20 + 2, 20 + 18, FRAME_HEIGHT - 23 + 5, FRAME_HEIGHT - 23 + 9, currentInput->current & BUMPERRIGHT ? colorPressed : colorUnpressed);

		DrawRectST(7, 13, FRAME_HEIGHT - 23 + 10, FRAME_HEIGHT - 23 + 14, currentInput->current & DPADUP ? colorPressed : colorUnpressed);
		DrawRectST(13, 19, FRAME_HEIGHT - 23 + 14, FRAME_HEIGHT - 23 + 18, currentInput->current & DPADRIGHT ? colorPressed : colorUnpressed);
		DrawRectST(7, 13, FRAME_HEIGHT - 23 + 18, FRAME_HEIGHT - 23 + 22, currentInput->current & DPADDOWN ? colorPressed : colorUnpressed);
		DrawRectST(1, 7, FRAME_HEIGHT - 23 + 14, FRAME_HEIGHT - 23 + 18, currentInput->current & DPADLEFT ? colorPressed : colorUnpressed);

		colorPressed.r = 0x00;
		colorPressed.g = 0x80;
		colorPressed.b = 0x00;
		DrawRectST(20 + 7, 20 + 13, FRAME_HEIGHT - 23 + 10, FRAME_HEIGHT - 23 + 14, currentInput->current & TRIANGLE ? colorPressed : colorUnpressed);
		colorPressed.r = 0x80;
		colorPressed.g = 0x00;
		colorPressed.b = 0x00;
		DrawRectST(20 + 13, 20 + 19, FRAME_HEIGHT - 23 + 14, FRAME_HEIGHT - 23 + 18, currentInput->current & CIRCLE ? colorPressed : colorUnpressed);
		colorPressed.r = 0x00;
		colorPressed.g = 0x20;
		colorPressed.b = 0x80;
		DrawRectST(20 + 7, 20 + 13, FRAME_HEIGHT - 23 + 18, FRAME_HEIGHT - 23 + 22, currentInput->current & CROSS ? colorPressed : colorUnpressed);
		colorPressed.r = 0x80;
		colorPressed.g = 0x00;
		colorPressed.b = 0x80;
		DrawRectST(20 + 1, 20 + 7, FRAME_HEIGHT - 23 + 14, FRAME_HEIGHT - 23 + 18, currentInput->current & SQUARE ? colorPressed : colorUnpressed);

		colorUnpressed.r = 0x20;
		colorUnpressed.g = 0x20;
		colorUnpressed.b = 0x20;
		colorPressed.r = 0xff;
		colorPressed.g = 0xff;
		colorPressed.b = 0xff;
		DrawLine(
			20 + 10, FRAME_HEIGHT - 23 + 16, colorUnpressed,
			20 + 10 + (currentInput->rightStickAnalogX - 0x7f) * 9 / 0x80, FRAME_HEIGHT - 23 + 16 + (currentInput->rightStickAnalogY - 0x7f) * 6 / 0x80, colorPressed
		);
		DrawLine(
			10, FRAME_HEIGHT - 23 + 16, colorUnpressed,
			10 + (currentInput->leftStickAnalogX - 0x7f) * 9 / 0x80, FRAME_HEIGHT - 23 + 16 + (currentInput->leftStickAnalogY - 0x7f) * 6 / 0x80, colorPressed
		);
	}

	if (inHUDOptions) {
		GAME_DrawOutlinedBG(2 + 0, 4 + 200, 2 + LINE_HEIGHT, 4 + 3 + (MAX_OPTIONS + 1) * LINE_HEIGHT);
		
		for (char i = 0; i < MAX_OPTIONS; i++) {
			int color;
			switch (optionTypes[i]) {
				case OPTIONTYPE_TOGGLE:
					if (i == selectedOption) {
						if (optionValues[i]) {
							color = 3; // White
						} else {
							color = 2; // Yellow
						}
					} else {
						if (optionValues[i]) {
							color = 4; // Green
						} else {
							color = 5; // Red
						}
					}

					GAME_DrawText(str_Options[i], 4 + 2, 4 + 2 + (1 + i) * LINE_HEIGHT, color, 0);
					break;
				case OPTIONTYPE_NUMBER:
					if (i == selectedOption) {
						color = 3; // White
					} else {
						color = 2; // Yellow
					}
					
					LIBC_sprintf(buffer, "%s: %d", str_Options[i], optionValues[i]);
					GAME_DrawText(buffer, 4 + 2, 4 + 2 + (1 + i) * LINE_HEIGHT, color, 0);
					break;
				default:
					break;
			}
		}
	}

	DrawInjectedMessage(FRAME_WIDTH / 2, SCREEN_BOTTOM - LINE_HEIGHT);
}

void DrawLine(short x0, short y0, Color c0, short x1, short y1, Color c1) {
	LINE_G2* ptrPrimitive = (LINE_G2*)GAME_GPUPackets_Next;
	ptrPrimitive->tag = 0x4000000;
	ptrPrimitive->code = 0x50;

	ptrPrimitive->x0 = x0;
	ptrPrimitive->y0 = y0;
	ptrPrimitive->r0 = c0.r;
	ptrPrimitive->g0 = c0.g;
	ptrPrimitive->b0 = c0.b;

	ptrPrimitive->x1 = x1;
	ptrPrimitive->y1 = y1;
	ptrPrimitive->r1 = c1.r;
	ptrPrimitive->g1 = c1.g;
	ptrPrimitive->b1 = c1.b;
	
	GAME_GPUPackets_Insert(ptrPrimitive);
	GAME_GPUPackets_Next = ptrPrimitive + 1;
}

void DrawRectST(short left, short right, short top, short bottom, Color color) {
	POLY_F4* ptrPrimitive = (POLY_F4*)GAME_GPUPackets_Next;
	ptrPrimitive->tag = 0x5000000;
	ptrPrimitive->code = 0x2a;

	ptrPrimitive->x0 = left;
	ptrPrimitive->x2 = left;
	
	ptrPrimitive->x1 = right;
	ptrPrimitive->x3 = right;

	ptrPrimitive->y0 = top;
	ptrPrimitive->y1 = top;
	
	ptrPrimitive->y2 = bottom;
	ptrPrimitive->y3 = bottom;

	ptrPrimitive->r0 = color.r;
	ptrPrimitive->g0 = color.g;
	ptrPrimitive->b0 = color.b;
	
	GAME_GPUPackets_Insert(ptrPrimitive);
	GAME_GPUPackets_Next = ptrPrimitive + 1;
}

void PrintVector(char* label, Vec3 *v, int x, int y) {
	int vX = v->x;
	int vXDecimal = vX % 1000;
	if (vXDecimal < 0) {
		vXDecimal = -vXDecimal;
	} 
	vX = vX / 1000;
	
	int vY = v->y;
	int vYDecimal = vY % 1000;
	if (vYDecimal < 0) {
		vYDecimal = -vYDecimal;
	} 
	vY = vY / 1000;
	
	int vZ = v->z;
	int vZDecimal = vZ % 1000;
	if (vZDecimal < 0) {
		vZDecimal = -vZDecimal;
	} 
	vZ = vZ / 1000;

	char buffer[32];
	LIBC_sprintf(buffer, "%s: %d.%03d %d.%03d %d.%03d",
		label,
		vX, vXDecimal,
		vY, vYDecimal,
		vZ, vZDecimal
	);
	GAME_DrawText(buffer, x, y, 2, 0);
}

void DrawInjectedMessage(int x, int y) {
	static int timer = 60;
	if (timer > 0) {
		GAME_DrawText_CenterWithBG("Injection Loaded", x, y, (timer / 5) % 2 ? 1 : 3);
		timer -= 1;
	}
}

int InterpInt(int from, int to, unsigned char t) {
	return (to * t + from * (0xff - t)) / 0xff;
}