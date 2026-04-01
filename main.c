/*
* Author: Abdullah Bouteldja
* Made using the fantastic SDL3 library under the CC BY 4.0 license
* Also using the separate SDL3_ttf library for text handling under the same license
*/

#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <stdbool.h>
#include <string.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define BORDER_WIDTH 10

#define LEFT_RECT_W 450
#define LEFT_RECT_H (WINDOW_HEIGHT - (BORDER_WIDTH * 2))
#define LEFT_RECT_X BORDER_WIDTH
#define LEFT_RECT_Y BORDER_WIDTH

#define RIGHT_RECT_W (WINDOW_WIDTH - (LEFT_RECT_W + (BORDER_WIDTH * 3)))
#define RIGHT_RECT_H (WINDOW_HEIGHT - (BORDER_WIDTH * 2))
#define RIGHT_RECT_X (WINDOW_WIDTH - (RIGHT_RECT_W + BORDER_WIDTH))
#define RIGHT_RECT_Y BORDER_WIDTH

#define IMG_RECT_W (LEFT_RECT_W - (BORDER_WIDTH * 4))
#define IMG_RECT_H IMG_RECT_W
#define IMG_RECT_X (BORDER_WIDTH * 3)
#define IMG_RECT_Y (WINDOW_HEIGHT / 2) - (IMG_RECT_H / 2)

#define CHOICE_RECT_W (RIGHT_RECT_W - (BORDER_WIDTH * 2))
#define CHOICE_RECT_H 200
#define CHOICE_RECT_X (RIGHT_RECT_X + BORDER_WIDTH)
#define CHOICE_RECT_Y (WINDOW_HEIGHT - (CHOICE_RECT_H + BORDER_WIDTH * 2))

#define TXT_RECT_W (RIGHT_RECT_W - (BORDER_WIDTH * 2))
#define TXT_RECT_H (RIGHT_RECT_H - (CHOICE_RECT_H + (BORDER_WIDTH * 3)))
#define TXT_RECT_X (RIGHT_RECT_X + BORDER_WIDTH)
#define TXT_RECT_Y (RIGHT_RECT_Y + BORDER_WIDTH)

#define PRINT_FPS true
#define LIMIT_FPS true
#define FPS_PRINT_INTERVAL_MS 1000
#define FPS_LIMIT 60

#define No_PARTICLES WINDOW_WIDTH

// ################################################################################################
// ENUMS & STRUCTS
// ################################################################################################

// ############################################################################
// GAME LOGIC ENUMS & STRUCTS
// ############################################################################

typedef enum
{
	CAP_1_OPENING,
	CAP_2_ATTACK,
	CAP_3_CHOOSING_FLAG,
	CAP_3_CHOOSING_DEFENCE,
	END_CAPTAIN,
	SMITH_1_CHOOSING_CANNONS,
	SMITH_2_CHOOSING_FIRE_REPAIRS,
	SURGEON_1_WHO_WHERE_TREAT,
	END_SURGEON,
	CAP_4_CHOOSING_DUEL,
	CAP_5_DUEL,
	CAP_6_END,
	CONCLUSION
}
StoryState;

typedef enum
{
	WINNING,
	LOSING
}
BattleState;

typedef enum
{
	READING,
	CHOOSING2,
	CHOOSING3
}
PlayerState;

typedef enum
{
	BLACK,
	RED,
	FALSE
}
Flag;

typedef enum
{
	BOARDING,
	CANNONS,
	FIFTYFIFTY
}
BattleStrategy;

typedef enum
{
	RELOCATE,
	DIRECT_RELOCATION,
	LEAVE_IT
}
PowderRelocation;

typedef enum
{
	PUMPS,
	IGNORE
}
PumpRepair;

typedef enum
{
	DOWN,
	STRAIGHT,
	UP
}
CannonAngle;

typedef enum
{
	TREAT,
	LEAVE_HIM_TO_DIE_LIKE_SOME_SORT_OF_MONSTER
}
TreatQuartermaster;

typedef enum
{
	ABOVE,
	BELOW
}
SurgeonPosition;

typedef enum
{
	SWORD,
	GUN,
	ESCAPE
}
Duel;

typedef struct
{
	Flag flag;
	BattleStrategy battleStrategy;
	PowderRelocation powderRelocation;
	PumpRepair pumpRepair;
	CannonAngle cannonAngle;
	TreatQuartermaster treatQM;
	SurgeonPosition surgeonPosition;
	Duel duel;
}
Choice;

typedef struct
{
	Choice choice;
	StoryState sState;
	BattleState bState;
	PlayerState pState;

}
GameState;

// ############################################################################
// GAME ENGINE ENUMS & STRUCTS
// ############################################################################

typedef enum
{
	LEFT,
	RIGHT,
	IMG,
	CHOICE,
	TXT
}
RectType;

typedef struct
{
	Uint64 lastFrameTick;
	float fps;
	float frameIntervalMS;
}
FrameParameters;

// ############################################################################
// MAIN STATE STRUCT
// ############################################################################

typedef struct
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;

	FrameParameters frame;

	GameState gState;
}
State;


// ################################################################################################
// GAME LOGIC
// ################################################################################################



// ################################################################################################
// GAME ENGINE FUNCTIONS
// ################################################################################################

// ############################################################################
// INPUT
// ############################################################################

// handle inputs (mouse left click only)
SDL_AppResult input(SDL_Event *event)
{
	if (event->type == SDL_EVENT_QUIT)// quit
	{
		return SDL_APP_SUCCESS;
	}
	else 
	{
		if (1/* currently accepting inputs*/)
		{
			if(event->type == SDL_EVENT_MOUSE_BUTTON_DOWN
				&& event->button.button == SDL_BUTTON_LEFT)// left mouse click detected
			{
				if (1/* accepting choice of two inputs */)
				{
					if (1/* mouse is in correct position */)
					{
						 
					}
					else if (1/* mouse is in correct position*/)
					{

					}
				}
				else if (1/* acccepting choice of three inputs */)
				{
					if (1/* mouse is in correct position */)
					{
						// TODO: accept 
					}
					else if (1/* mouse is in correct position*/)
					{

					}
					else if (1/* mouse is in correct position*/)
					{

					}
				}
			}
		}
	}

	return SDL_APP_CONTINUE;
}

// ############################################################################
// FRAME CALCULATIONS & MANAGEMENT
// ############################################################################

float getFPS(void *appstate)
{
	State* state = (State*) appstate;

	return (state->frame.fps);
}

Uint64 getMSSinceLastFrame(void *appstate)
{
	State* state = (State*) appstate;
	
	return (SDL_GetTicks() - state->frame.lastFrameTick);
}

void calculateFPS(void *appstate)
{
	State* state = (State*) appstate;

	// get time since last frame
	float f = (float) (getMSSinceLastFrame(appstate));

	// convert to seconds then invert to get fps
	f = f / 1000;
	f = 1 / f;

	// record fps
	state->frame.fps = f;

	return;
}

// reset parameters used for frame calculations
void resetFrameParameters(void *appstate)
{
	State* state = (State*) appstate;

	state->frame.lastFrameTick = SDL_GetTicks();

	return;
}

// check whether a new frame should be rendered as according to the FPS limit
bool advanceFrame(void *appstate)
{
	State* state = (State*) appstate;
	
	bool advance = true;
	
	if (LIMIT_FPS)
	{
		(getMSSinceLastFrame(appstate) > state->frame.frameIntervalMS) ?
			(advance = true) : (advance = false);
	}

	if (advance)
	{		
		calculateFPS(appstate);
		resetFrameParameters(appstate);
	}

	return advance;
}

// ############################################################################
// UPDATE & RENDER FUNCTIONS
// ############################################################################

void updateTexture(void *appstate)
{


	return;
}

SDL_FRect generateFRect(RectType rt)
{
	SDL_FRect rect;
	
	switch (rt)
	{
		case LEFT:
			rect.x = LEFT_RECT_X;
			rect.y = LEFT_RECT_Y;
			rect.w = LEFT_RECT_W;
			rect.h = LEFT_RECT_H;
			break;

		case RIGHT:
			rect.x = RIGHT_RECT_X;
			rect.y = RIGHT_RECT_Y;
			rect.w = RIGHT_RECT_W;
			rect.h = RIGHT_RECT_H;
			break;

		case IMG:
			rect.x = IMG_RECT_X;
			rect.y = IMG_RECT_Y;
			rect.w = IMG_RECT_W;
			rect.h = IMG_RECT_H;
			break;

		case CHOICE:
			rect.x = CHOICE_RECT_X;
			rect.y = CHOICE_RECT_Y;
			rect.w = CHOICE_RECT_W;
			rect.h = CHOICE_RECT_H;
			break;

		case TXT:
			rect.x = TXT_RECT_X;
			rect.y = TXT_RECT_Y;
			rect.w = TXT_RECT_W;
			rect.h = TXT_RECT_H;
			break;

		default:
	}

	return rect;
}

void update(void *appstate)
{
	State* state = (State*) appstate;
	
	return;
}

void render(void *appstate)
{
	State* state = (State*) appstate;
	SDL_FRect rect;

	SDL_SetRenderDrawColor(state->renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(state->renderer);

	// draw rectangles
	// left rect first
	SDL_SetRenderDrawColor(state->renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	rect = generateFRect(LEFT);
	SDL_RenderRect(state->renderer, &rect);

	// right rect second
	SDL_SetRenderDrawColor(state->renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	rect = generateFRect(RIGHT);
	SDL_RenderRect(state->renderer, &rect);

	// img rect third
	SDL_SetRenderDrawColor(state->renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	rect = generateFRect(IMG);
	SDL_RenderRect(state->renderer, &rect);

	// choice rect fourth
	SDL_SetRenderDrawColor(state->renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	rect = generateFRect(CHOICE);
	SDL_RenderRect(state->renderer, &rect);

	// text rect fifth
	SDL_SetRenderDrawColor(state->renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	rect = generateFRect(TXT);
	SDL_RenderRect(state->renderer, &rect);

	SDL_RenderPresent(state->renderer);

	return;

}

void updateAndRender(void *appstate)
{
	if (advanceFrame(appstate))
	{
		update(appstate);
		render(appstate);
	}

	return;
}

// ############################################################################
// INITIALISATION
// ############################################################################

bool initFrameParameters(State* state)
{
	// set struct vars to arbitrary values
	// most of these don't really matter, so magic it is
	state->frame.lastFrameTick = 1;
	state->frame.fps = 1.0f;
	state->frame.frameIntervalMS = (1 / ((float) FPS_LIMIT)) * 1000;

	return true;
}

bool initStructs(State *state)
{
	SDL_Log("Initialising structs...");

	initFrameParameters(state);

	SDL_Log("Struct initialisation complete");

	return true;
}

bool initVideo(State *state)
{
	SDL_Log("Initialising video...");
	
	// initialise video
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Video intialisation failed: %s", SDL_GetError());

		return false;
	}
	
	// create window and renderer
	// the 0 is in place of the window flags because none are being used
	if (!SDL_CreateWindowAndRenderer("get windowed", WINDOW_WIDTH, WINDOW_HEIGHT, 0,
		&(state->window), &(state->renderer)))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Window/renderer creation failed: %s", SDL_GetError());

		return false;
	}

	SDL_Log("Available renderer drivers:");
	for (int i = 0; i < SDL_GetNumRenderDrivers(); i++) {
		    SDL_Log("%d. %s", i + 1, SDL_GetRenderDriver(i));
	}

	// set window icon
	SDL_Surface* icon = SDL_LoadBMP("./img/image.bmp");
	if (!SDL_SetWindowIcon(state->window, icon))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Error setting window icon: %s", SDL_GetError());
		return false;
	}

	SDL_Log("Video initialisation complete");

	return true;
}

// ############################################################################
// CALLBACK FUNCTONS
// ############################################################################

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
	static State state;

	SDL_AppResult result;
	
	if (!initVideo(&state))
	{
		return SDL_APP_FAILURE;
	}
	else if (!initStructs(&state))
	{
		return SDL_APP_FAILURE;
	}

	*appstate = &state;

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
	return (input(event));
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
	State* state = (State*) appstate;
	
	input(appstate);
	updateAndRender(appstate);

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
	State* state = (State*) appstate;
	
	// destroy what was created
	SDL_DestroyTexture(state->texture);
	// SDL_DestroySurface(state->surface);
	SDL_DestroyRenderer(state->renderer);
	SDL_DestroyWindow(state->window);
	
	return;
}
