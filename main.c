#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include <string.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define BORDER_WIDTH 10

#define LEFT_RECT_W 450
#define LEFT_RECT_H WINDOW_HEIGHT - (BORDER_WIDTH * 2)
#define LEFT_RECT_X BORDER_WIDTH
#define LEFT_RECT_Y BORDER_WIDTH

#define RIGHT_RECT_W WINDOW_WIDTH - (LEFT_RECT_W + (BORDER_WIDTH * 3))
#define RIGHT_RECT_H WINDOW_HEIGHT - (BORDER_WIDTH * 2)
#define RIGHT_RECT_X WINDOW_WIDTH - (RIGHT_RECT_W + BORDER_WIDTH)
#define RIGHT_RECT_Y BORDER_WIDTH

#define IMG_RECT_W LEFT_RECT_W - (BORDER_WIDTH * 4)
#define IMG_RECT_H IMG_RECT_W
#define IMG_RECT_X BORDER_WIDTH * 3
#define IMG_RECT_Y (WINDOW_HEIGHT / 2) - (IMG_RECT_H / 2)

#define CHOICE_RECT_W RIGHT_RECT_W - (BORDER_WIDTH * 2)
#define CHOICE_RECT_H 200
#define CHOICE_RECT_X RIGHT_RECT_X + BORDER_WIDTH
#define CHOICE_RECT_Y

#define TXT_RECT_W RIGHT_RECT_W - (BORDER_WIDTH * 2)
#define TXT_RECT_H RIGHT_RECT_H - (CHOICE_RECT_H + (BORDER_WIDTH * 3))
#define TXT_RECT_X RIGHT_RECT_X + BORDER_WIDTH
#define TXT_RECT_Y RIGHT_RECT_Y + BORDER_WIDTH

#define PRINT_FPS true
#define LIMIT_FPS true
#define FPS_PRINT_INTERVAL_MS 1000
#define FPS_LIMIT 60

#define No_PARTICLES WINDOW_WIDTH

// ############################################################################
// STRUCTS & ENUMS
// ############################################################################

typedef struct
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	// SDL_Surface* surface;
	SDL_Texture* texture;

	Uint64 lastFrameTick;
	Uint64 lastLoopTick;
	Uint64 frame;
	float fps;
	float frameIntervalMS;
	
	SDL_FPoint points[No_PARTICLES];
}
State;

// ############################################################################
// INPUT
// ############################################################################

// handle inputs (mouse and keyboard only for now)
SDL_AppResult Input(SDL_Event *event)
{
	if (event->type == SDL_EVENT_QUIT)// quit
	{
		return SDL_APP_SUCCESS;
	}
	else if (event->type == SDL_EVENT_KEY_DOWN)// key press
	{
		SDL_Log("key press detected: %d", event->key.key);
	}
	else if(event->type == SDL_EVENT_MOUSE_MOTION)// mouse movement
	{
		/*
		SDL_Log("Abs: x: %f, y: %f", event->motion.x, event->motion.y);
		SDL_Log("Rel: x: %f, y: %f", event->motion.xrel, event->motion.yrel);
		*/
	}
	else if(event->type == SDL_EVENT_MOUSE_BUTTON_DOWN)// mouse click
	{
		switch (event->button.button)
		{
			case SDL_BUTTON_LEFT:
				SDL_Log("left mouse button clicked");
				break;
				
			case SDL_BUTTON_RIGHT:
				SDL_Log("right mouse button clicked");
				break;

			case SDL_BUTTON_MIDDLE:
				SDL_Log("middle mouse button clicked");
				break;

			default:
				SDL_Log("mystery mouse button clicked");
		}
		
		SDL_Log("%d mouse button depress(es) detected", event->button.clicks);
	}

	return SDL_APP_CONTINUE;
}

// ############################################################################
// FRAME CALCULATIONS & MANAGEMENT
// ############################################################################

float GetFPS(void *appstate)
{
	State* state = (State*) appstate;

	return (state->fps);
}

Uint64 GetMSSinceLastFrame(void *appstate)
{
	State* state = (State*) appstate;
	
	return (SDL_GetTicks() - state->lastFrameTick);
}

void CalculateFPS(void *appstate)
{
	State* state = (State*) appstate;

	// get time since last frame
	float f = (float) (GetMSSinceLastFrame(appstate));

	// convert to seconds then invert to get fps
	f = f / 1000;
	f = 1 / f;

	// record fps
	state->fps = f;

	return;
}

// reset parameters used for frame calculations
void ResetFrameParameters(void *appstate)
{
	State* state = (State*) appstate;

	state->lastFrameTick = SDL_GetTicks();

	return;
}

// check whether a new frame should be rendered as according to the FPS limit
bool AdvanceFrame(void *appstate)
{
	State* state = (State*) appstate;
	
	bool advance = true;
	
	if (LIMIT_FPS)
	{
		(GetMSSinceLastFrame(appstate) > state->frameIntervalMS) ? (advance = true) : (advance = false);
	}

	if (advance)
	{		
		CalculateFPS(appstate);
		ResetFrameParameters(appstate);
	}

	return advance;
}

// ############################################################################
// UPDATE AND RENDER
// ############################################################################

void Update(void *appstate)
{
	State* state = (State*) appstate;

	for (int i = 0; i < No_PARTICLES; i++)
	{
		// state->points[i].x += SDL_rand(10);
		state->points[i].y += SDL_rand(5);

		if (state->points[i].y >= WINDOW_HEIGHT)
		{
			state->points[i].y = (float) (-5);
		}	
	}	
	
	return;
}

void Render(void *appstate)
{
	State* state = (State*) appstate;

	SDL_RenderClear(state->renderer);

	// draw rectangles
	// img rect first
	SDL_FRect imgRect = {10.0f, 10.0f, 450.0f, 700.0f};
	SDL_SetRenderDrawColor(state->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderRect(state->renderer, &imgRect);

	// viewing rect second
	SDL_FRect txtIntRect = {470.0f, 10.0f, 800.0f, 700.0f};
	SDL_SetRenderDrawColor(state->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderRect(state->renderer, &txtIntRect);

	// smaller img rect third
	SDL_FRect imgRectSmol = {35.0f, 160.0f, 400.0f, 400.0f};
	SDL_SetRenderDrawColor(state->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderRect(state->renderer, &imgRectSmol);

	// choice rect fourth
	SDL_FRect optionsRect = {480.0f, 500.0f, 780.0f, 200.0f};
	SDL_SetRenderDrawColor(state->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderRect(state->renderer, &optionsRect);

	SDL_RenderPresent(state->renderer);

	return;

}

void UpdateAndRender(void *appstate)
{
	if (AdvanceFrame(appstate))
	{
		Update(appstate);
		Render(appstate);
	}

	return;
}

// ############################################################################
// INITIALISATION
// ############################################################################

SDL_AppResult InitStructs(State *state)
{
	// set struct vars to arbitrary values
	// most of these don't really matter, so magic it is
	state->lastFrameTick = 1;
	state->lastLoopTick = 1;
	state->frame = 1;
	state->fps = 1.0f;

	state->frameIntervalMS = (1 / ((float) FPS_LIMIT)) * 1000;

	// put all particles above the window out of view so they can fall into view
	for (int i = 0; i < No_PARTICLES; i++)
	{
		SDL_FPoint p = {((float) i), ((float) (-10))};
		state->points[i] = p;
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult InitVideo(State *state)
{
	// initialise video
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Video intialisation failed: %s", SDL_GetError());

		return SDL_APP_FAILURE;
	}
	
	// create window and renderer
	// the 0 is in place of the window flags because none are being used
	if (!SDL_CreateWindowAndRenderer("Hello SDL", WINDOW_WIDTH, WINDOW_HEIGHT, 0,
		&(state->window), &(state->renderer)))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Window/renderer creation failed: %s", SDL_GetError());

		return SDL_APP_FAILURE;
	}

	SDL_Log("Available renderer drivers:");
	for (int i = 0; i < SDL_GetNumRenderDrivers(); i++) {
		    SDL_Log("%d. %s", i + 1, SDL_GetRenderDriver(i));
	}

	// create texture
	SDL_Surface* surf = SDL_LoadBMP("./IMG/image.bmp");
	state->texture = SDL_CreateTextureFromSurface(state->renderer, surf);
	SDL_DestroySurface(surf);

	if (state->texture == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Texture creation failed: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	SDL_Log("Video intialisation complete.");

	return SDL_APP_CONTINUE;
}

// ############################################################################
// CALLBACK FUNCTONS
// ############################################################################

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
	static State state;

	SDL_AppResult result;
	
	result = InitVideo(&state);
	result = InitStructs(&state);

	*appstate = &state;

	return result;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
	return (Input(event));
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
	State* state = (State*) appstate;
	
	Input(appstate);
	UpdateAndRender(appstate);

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
