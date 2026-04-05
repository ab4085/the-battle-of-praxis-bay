/*
* Author: Abdullah Bouteldja
* Made using the fantastic SDL3 library under the CC BY 4.0 license
* Also using the separate SDL3_ttf library for text handling under the same license
*/

#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define BORDER_WIDTH 10

#define FILE_PATH_MAX_LENGTH 40
#define FILE_NAME_MAX_LENGTH 10

#define No_CHOICES_MAX 6
#define No_CREDITS_FILES 6

#define TXT_START_FILE_NAME "/a.txt"
#define CHOICE_TXT_FILE_NAME "/ac.txt"

// txt file locations (loc is short for location dummy)
// root location
#define TXT_BASE_LOC "./txt"

// credits text
#define TXT_CREDITS "/CREDITS"

// story text
// first level folders
#define TXT_LOSE_LOC "/LOSE"
#define TXT_WIN_LOC "/WIN"
#define TXT_DUEL_LOC "/DUEL"
#define TXT_VICTORY_LOC "/VICTORY"
#define TXT_END_LOC "/END"

// second level folders
#define TXT_PART_1_LOC "/CAPTN1"
#define TXT_PART_2_LOC "/CAPTN2"
#define TXT_PART_3_LOC "/CAPTN31FLAG"
#define TXT_PART_4_LOC "/CAPTN32BATTLESTRATEGY"
#define TXT_PART_5_LOC "/CAPTN4"
#define TXT_PART_6_LOC "/SMITH51CANNONS"
#define TXT_PART_7_LOC "/SMITH52FIREREPAIR"
#define TXT_PART_8_LOC "/SURGN6WHOWHERETREAT"
#define TXT_PART_9_LOC "/SURGN7BELOW"
#define TXT_PART_9_ALTERNATE_LOC "/SURGN7NOTBELOW"
#define TXT_PART_10_LOC "/CAPTN8DUELSTRATEGY"

// some of these won't start with slashes
// that is intentional
// just look at the file structure and you'll understand why
// if you still don't understand after looking I diagnose you with stupid
#define TXT_DUEL_SWORD_LOC "/SWORD"
#define TXT_DUEL_SWORD_SMITH_LOC "SMITH"
#define TXT_DUEL_SWORD_CREW_LOC "CREW"
#define TXT_DUEL_SWORD_LOSE_LOC "LOSE"
#define TXT_DUEL_GUN_LOC "/GUN"
#define TXT_DUEL_GUN_BLACK_LOC "BLACK"
#define TXT_DUEL_GUN_NOTBLACK_LOC "RED"
#define TXT_DUEL_ESCAPE_LOC "/ESCAPE"
#define TXT_DUEL_ESCAPE_SMITH_LOC "SMITH"
#define TXT_DUEL_ESCAPE_SURGN_LOC "SURGN"
#define TXT_DUEL_ESCAPE_CREW_LOC "CREW"
#define TXT_DUEL_ESCAPE_LOSE_LOC "LOSE"

#define TXT_VICT_PART_1_LOC "/FLAG1"
#define TXT_VICT_PART_1_BLACK_LOC "BLACK"
#define TXT_VICT_PART_1_NOTBLACK_LOC "RED"
#define TXT_VICT_PART_2_LOC "/SINKING2"
#define TXT_VICT_PART_2_PYTHON_LOC "PYTHON"
#define TXT_VICT_PART_2_PROTO_LOC "PROTO"
#define TXT_VICT_PART_2_NEITHER_LOC "NEITHER"

#define TXT_END_DIED_QM_LOC "/DIED1QM"
#define TXT_END_DIED_SURGN_LOC "/DIED1SURGN"
#define TXT_END_ALIVE_LOC "/DIED1NEITHER"
#define TXT_END_SANK_PROTO_LOC "/SANK2PROTO"
#define TXT_END_SANK_PYTHON_LOC "/SANK2PYTHON"
#define TXT_END_AFLOAT_LOC "/SANK2NEITHER"

// font stuff
#define FONT_LOC "./font/one47.ttf"
#define FONT_PT_SIZE 18.0f

// images
#define ICON_LOC "./img/icon.bmp"
#define LOGO_LOC "./img/logo.bmp"
#define IMG_DEATH_LOC "./img/captnhat.bmp"
#define IMG_1_LOC "./img/captn1ship.bmp"
#define IMG_2_LOC "./img/captn2vignette.bmp"
#define IMG_3_LOC "./img/captn3flags.bmp"
#define IMG_4_LOC "./img/captn4boarding.bmp"
#define IMG_5_LOC "./img/captn5birdseye.bmp"
#define IMG_6_LOC "./img/smith6powder.bmp"
#define IMG_7_WIN_LOC "./img/smith7cannons.bmp"
#define IMG_7_LOSE_LOC "./img/smith7pumps.bmp"
#define IMG_8_LOC "./img/surgn8operatingtable.bmp"
#define IMG_9_LOC "./img/surgn9caduceus.bmp"
#define IMG_10_LOC "./img/captn10challenge.bmp"
#define IMG_11_LOC "./img/captn11victory.bmp"
#define IMG_12_BODIES_LOC "./img/end12bodies.bmp"
#define IMG_12_SINKING_LOC "./img/end12sinking.bmp"
#define IMG_12_TRUE_LOC "./img/end12temeraire.bmp"

// destination rectangle dimensions and positions
// dimensions are mostly designed to scale with window size
// first are the in-game rects
#define LEFT_RECT_W 450.0f
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
#define CHOICE_RECT_H 150.0f
#define CHOICE_RECT_X (RIGHT_RECT_X + BORDER_WIDTH)
#define CHOICE_RECT_Y (WINDOW_HEIGHT - (CHOICE_RECT_H + BORDER_WIDTH * 2))

#define TXT_RECT_W (RIGHT_RECT_W - (BORDER_WIDTH * 2))
#define TXT_RECT_H ((RIGHT_RECT_H - (CHOICE_RECT_H + (BORDER_WIDTH * 3))) / 10)
#define TXT_RECT_START_X (RIGHT_RECT_X + BORDER_WIDTH)
#define TXT_RECT_START_Y (RIGHT_RECT_Y + BORDER_WIDTH)

// start screen rects
#define CENTRE_IMG_RECT_W 450.0f
#define CENTRE_IMG_RECT_H CENTRE_IMG_RECT_W
#define CENTRE_IMG_RECT_X (WINDOW_WIDTH / 2) - (CENTRE_IMG_RECT_W / 2)
#define CENTRE_IMG_RECT_Y (WINDOW_HEIGHT / 2) - (CENTRE_IMG_RECT_H / 2)

#define START_TXT_RECT_Y (CENTRE_IMG_RECT_Y + CENTRE_IMG_RECT_H + BORDER_WIDTH)

// credits screen rects
#define CREDITS_TXT_RECT_W 150
#define CREDITS_TXT_RECT_H 75
#define CREDITS_TXT_START_RECT_X BORDER_WIDTH
#define CREDITS_TXT_RECT_Y BORDER_WIDTH

// button dimensions
#define CREDITS_BUTTON_W 75
#define CREDITS_BUTTON_H 30

#define CHOICE_1OF2_BUTTON_W ((CHOICE_RECT_W / 2) - (BORDER_WIDTH * 2))
#define CHOICE_1OF2_BUTTON_H (CHOICE_RECT_H - (BORDER_WIDTH * 2))
#define CHOICE_1OF2_BUTTON_X (CHOICE_RECT_X + BORDER_WIDTH)
#define CHOICE_1OF2_BUTTON_Y (CHOICE_RECT_Y + BORDER_WIDTH)

#define CHOICE_2OF2_BUTTON_W CHOICE_1OF2_BUTTON_W
#define CHOICE_2OF2_BUTTON_H CHOICE_1OF2_BUTTON_H
#define CHOICE_2OF2_BUTTON_X (CHOICE_1OF2_BUTTON_X + CHOICE_1OF2_BUTTON_W + (BORDER_WIDTH * 2))
#define CHOICE_2OF2_BUTTON_Y CHOICE_1OF2_BUTTON_Y

#define CHOICE_1OF3_BUTTON_W ((CHOICE_RECT_W / 3) - (BORDER_WIDTH * 2))
#define CHOICE_1OF3_BUTTON_H (CHOICE_RECT_H - (BORDER_WIDTH * 2))
#define CHOICE_1OF3_BUTTON_X (CHOICE_RECT_X + BORDER_WIDTH)
#define CHOICE_1OF3_BUTTON_Y (CHOICE_RECT_Y + BORDER_WIDTH)

#define CHOICE_2OF3_BUTTON_W CHOICE_1OF3_BUTTON_W
#define CHOICE_2OF3_BUTTON_H CHOICE_1OF3_BUTTON_H
#define CHOICE_2OF3_BUTTON_X (CHOICE_1OF3_BUTTON_X + CHOICE_1OF3_BUTTON_W + (BORDER_WIDTH * 2))
#define CHOICE_2OF3_BUTTON_Y CHOICE_1OF3_BUTTON_Y

#define CHOICE_3OF3_BUTTON_W CHOICE_1OF3_BUTTON_W
#define CHOICE_3OF3_BUTTON_H CHOICE_1OF3_BUTTON_H
#define CHOICE_3OF3_BUTTON_X (CHOICE_2OF3_BUTTON_X + CHOICE_1OF3_BUTTON_W + (BORDER_WIDTH * 2))
#define CHOICE_3OF3_BUTTON_Y CHOICE_1OF3_BUTTON_Y

#define LIMIT_FPS true
#define FPS_LIMIT 60

// ################################################################################################
// ENUMS & STRUCTS
// ################################################################################################

// ############################################################################
// GAME LOGIC ENUMS & STRUCTS
// ############################################################################

typedef enum
{
	S,
	A,
	B,
	C,
	D,
	F
}
Ranking;

// ########################################################
// GAME STATE ENUMS
// ########################################################

typedef enum
{
	DEAD,
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
	CAP_6_VICTORY_PART_1,
	CAP_6_VICTORY_PART_2,
	CONCLUSION_PART_1,
	CONCLUSION_PART_2,
	RANKING
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
	START_MENU,
	PLAYING,
	CREDITS,
	DEATH_SCREEN,
	RANK_SCREEN
}
ViewState;

// ########################################################
// CHOICE ENUMS
// ########################################################

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

// ########################################################
// MAIN GAME STRUCT
// ########################################################

// to hold current story text
typedef struct
{
	char currentText[10][5000];// split into up to 10 paragraphs of up to 5000 characters each
	char choiceText[6][50];// split into up to 3 choice with two texts each
	int paragraphs;
	int words[10];
}
Text;

typedef struct
{
	Choice choice;
	StoryState sState;
	BattleState bState;
	PlayerState pState;
	ViewState vState;
	Ranking rank;

	Text txt;

	bool textLoaded;
	bool textTextured;
	bool textRendered;
	bool sceneRendered;
}
GameState;

// ############################################################################
// GAME ENGINE ENUMS & STRUCTS
// ############################################################################

typedef enum
{
	CREDITS_BUTTON,
	CHOICE_1_OF_2,
	CHOICE_2_OF_2,
	CHOICE_1_OF_3,
	CHOICE_2_OF_3,
	CHOICE_3_OF_3
}
Range;

typedef enum
{
	STANDARD,
	CHOOSE
}
TextType;

typedef enum
{
	LEFT,
	RIGHT,
	IMG,
	CHOICE,
	CHOICE1OF2,
	CHOICE2OF2,
	CHOICE1OF3,
	CHOICE2OF3,
	CHOICE3OF3,
	PLAYING_TXT,
	START_TXT,
	CREDITS_TXT
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
	SDL_Texture* imgTexture;
	SDL_Texture* txtTexture[2][10];// one for story text, one for choice text
	SDL_Surface* txtSurface;

	TTF_Font* font;

	FrameParameters frame;

	GameState gState;
}
State;

// ################################################################################################
// FILE HANDLING
// ################################################################################################

void getThirdLevelTxtFolder(void *appstate, char* fileName)
{
	State* state = (State*) appstate;

	// all you need to know is that the correct directory is appened by this mess somehow
	switch (state->gState.sState)
	{
		case CAP_1_OPENING:
			strcat(fileName, TXT_PART_1_LOC);
			break;

		case CAP_2_ATTACK:
			strcat(fileName, TXT_PART_2_LOC);
			break;

		case CAP_3_CHOOSING_FLAG:
			strcat(fileName, TXT_PART_3_LOC);
			break;

		case CAP_3_CHOOSING_DEFENCE:
			strcat(fileName, TXT_PART_4_LOC);
			break;

		case END_CAPTAIN:
			strcat(fileName, TXT_PART_5_LOC);
			break;

		case SMITH_1_CHOOSING_CANNONS:
			strcat(fileName, TXT_PART_6_LOC);
			break;

		case SMITH_2_CHOOSING_FIRE_REPAIRS:
			strcat(fileName, TXT_PART_7_LOC);
			break;

		case SURGEON_1_WHO_WHERE_TREAT:
			strcat(fileName, TXT_PART_8_LOC);
			break;

		case END_SURGEON:
			if (state->gState.choice.surgeonPosition == BELOW)
			{
				strcat(fileName, TXT_PART_9_LOC);
			}
			else
			{
				strcat(fileName, TXT_PART_9_ALTERNATE_LOC);
			}

			break;

		case CAP_4_CHOOSING_DUEL:
			strcat(fileName, TXT_PART_10_LOC);
			break;

		case CAP_5_DUEL:
			switch (state->gState.choice.duel)
			{
				case SWORD:
					strcat(fileName, TXT_DUEL_SWORD_LOC);

					if (state->gState.choice.cannonAngle == UP)
					{
						strcat(fileName, TXT_DUEL_SWORD_SMITH_LOC);
					}
					else if (state->gState.choice.battleStrategy == BOARDING)
					{
						strcat(fileName, TXT_DUEL_SWORD_CREW_LOC);
					}
					else
					{
						strcat(fileName, TXT_DUEL_SWORD_LOSE_LOC);
					}

					break;

				case GUN:
					strcat(fileName, TXT_DUEL_GUN_LOC);

					if (state->gState.choice.flag == BLACK)
					{
						strcat(fileName, TXT_DUEL_GUN_BLACK_LOC);
					}
					else
					{
						strcat(fileName, TXT_DUEL_GUN_NOTBLACK_LOC);
					}

					break;

				case ESCAPE:
					strcat(fileName, TXT_DUEL_ESCAPE_LOC);

					if (state->gState.choice.cannonAngle == UP)
					{
						strcat(fileName, TXT_DUEL_ESCAPE_SMITH_LOC);
					}
					else if (state->gState.choice.surgeonPosition == ABOVE)
					{
						strcat(fileName, TXT_DUEL_ESCAPE_SURGN_LOC);
					}
					else if (state->gState.choice.battleStrategy == CANNONS)
					{
						strcat(fileName, TXT_DUEL_ESCAPE_CREW_LOC);
					}
					else
					{
						strcat(fileName, TXT_DUEL_ESCAPE_LOSE_LOC);
					}

					break;

				default:
			}

			break;

		case CAP_6_VICTORY_PART_1:
			strcat(fileName, TXT_VICT_PART_1_LOC);

			if (state->gState.choice.flag == BLACK)
			{
				strcat(fileName, TXT_VICT_PART_1_BLACK_LOC);
			}
			else
			{
				strcat(fileName, TXT_VICT_PART_1_NOTBLACK_LOC);
			}

			break;

		case CAP_6_VICTORY_PART_2:
			strcat(fileName, TXT_VICT_PART_2_LOC);

			if (state->gState.choice.pumpRepair == IGNORE)
			{
				strcat(fileName, TXT_VICT_PART_2_PROTO_LOC);
			}
			else if (state->gState.choice.cannonAngle == DOWN)
			{
				strcat(fileName, TXT_VICT_PART_2_PYTHON_LOC);
			}
			else
			{
				strcat(fileName, TXT_VICT_PART_2_NEITHER_LOC);
			}

			break;

		case CONCLUSION_PART_1:
			if (state->gState.choice.treatQM ==
				LEAVE_HIM_TO_DIE_LIKE_SOME_SORT_OF_MONSTER)
			{
				strcat(fileName, TXT_END_DIED_QM_LOC);
			}
			else if (state->gState.choice.surgeonPosition == ABOVE
				&& state->gState.choice.cannonAngle == UP)
			{
				strcat(fileName, TXT_END_DIED_SURGN_LOC);
			}
			else
			{
				strcat(fileName, TXT_END_ALIVE_LOC);
			}

			break;

		case CONCLUSION_PART_2:
			if (state->gState.choice.pumpRepair == IGNORE)
			{
				strcat(fileName, TXT_END_SANK_PROTO_LOC);
			}
			else if (state->gState.choice.cannonAngle == DOWN)
			{
				strcat(fileName, TXT_END_SANK_PYTHON_LOC);
			}
			else
			{
				strcat(fileName, TXT_END_AFLOAT_LOC);
			}

		default:
	}

	return;
}

void getSecondLevelTxtFolder(void *appstate, char* fileName)
{
	State* state = (State*) appstate;

	switch (state->gState.sState)
	{
		case CAP_1_OPENING:
		case CAP_2_ATTACK:
		case CAP_3_CHOOSING_FLAG:
		case CAP_3_CHOOSING_DEFENCE:
		case END_CAPTAIN:
		case SMITH_1_CHOOSING_CANNONS:
		case SMITH_2_CHOOSING_FIRE_REPAIRS:
		case SURGEON_1_WHO_WHERE_TREAT:
		case END_SURGEON:
		case CAP_4_CHOOSING_DUEL:
			if (state->gState.bState == LOSING)
			{
				strcat(fileName, TXT_LOSE_LOC);
			}
			else if (state->gState.bState == WINNING)
			{
				strcat(fileName, TXT_WIN_LOC);
			}

			break;

		case CAP_5_DUEL:
			strcat(fileName, TXT_DUEL_LOC);
			break;

		case CAP_6_VICTORY_PART_1:
		case CAP_6_VICTORY_PART_2:
			strcat(fileName, TXT_VICTORY_LOC);
			break;

		case CONCLUSION_PART_1:
		case CONCLUSION_PART_2:
			strcat(fileName, TXT_END_LOC);
			break;

		default:
	}

	return;
}

void txtFileLocBuilder(void *appstate, char* fileName)
{
	State* state = (State*) appstate;

	// start with base file location (root folder for all files)
	strcpy(fileName, TXT_BASE_LOC);

	// can be credits or story
	if (state->gState.vState == CREDITS)
	{
		strcat(fileName, TXT_CREDITS);
	}
	else
	{
		getSecondLevelTxtFolder(state, fileName);
		getThirdLevelTxtFolder(state, fileName);
	}

	return;
}

void readTextFromFiles(void *appstate, TextType type)
{
	State* state = (State*) appstate;

	FILE* f;

	char fileLoc[FILE_PATH_MAX_LENGTH];
	char filePath[FILE_PATH_MAX_LENGTH];
	char currentFile[FILE_NAME_MAX_LENGTH];
	//char text[10][2000][15];
	char currentWord[20];
	bool fileFound = true;
	int words = 0;
	int count = 0;

	txtFileLocBuilder(state, fileLoc);

	if (type == STANDARD)
	{
		strcpy(currentFile, TXT_START_FILE_NAME);
	}
	else if (type == CHOOSE)
	{
		strcpy(currentFile, CHOICE_TXT_FILE_NAME);
	}

	if (type == STANDARD)
	{
		state->gState.txt.paragraphs = 0;
	}
	else if (type == CHOOSE)
	{
		count = 0;
	}

	// open, read and close files in succession
	do
	{
		strcpy(filePath, fileLoc);
		
		// append actual file to location
		strcat(filePath, currentFile);
		
		if ((f = fopen(filePath, "r")) == NULL)
		{
			fileFound = false;
			break;
		}

		// reset destination
		if (type == STANDARD)
		{
			strcpy(state->gState.txt.currentText[state->gState.txt.paragraphs], "");
		}
		else if (type == CHOOSE)
		{
			strcpy(state->gState.txt.choiceText[count], "");
		}

		// read each word of file and add to struct
		words = 0;
		while ((fscanf(f, "%s", currentWord)) == 1)
		{			
			if (type == STANDARD)
			{
				strcat(state->gState.txt.currentText[state->gState.txt.paragraphs], currentWord);
				strcat(state->gState.txt.currentText[state->gState.txt.paragraphs], " ");
			}
			else if (type == CHOOSE)
			{
				strcat(state->gState.txt.choiceText[count], currentWord);
				strcat(state->gState.txt.choiceText[count], " ");
			}

			words++;
		}

		if (type == STANDARD)
		{
			// record number of words
			state->gState.txt.words[state->gState.txt.paragraphs] = words;
			state->gState.txt.paragraphs++;
		}
		else if (type == CHOOSE)
		{
			count++;
		}

		fclose(f);

		currentFile[1]++;// goes from "/a.txt" to "/b.txt" or whatever is next
	}
	while (fileFound);

	return;
}

void loadImgFromFiles(void *appstate)
{
	State* state = (State*) appstate;

	SDL_Surface* img;
	
	if (state->gState.vState == START_MENU)
	{
		img = SDL_LoadBMP(LOGO_LOC);
	}
	else if (state->gState.vState == PLAYING)
	{
		// load image based off current story state
		switch (state->gState.sState)
		{
			case DEAD:
				img = SDL_LoadBMP(IMG_DEATH_LOC);
				break;

			case CAP_1_OPENING:
				img = SDL_LoadBMP(IMG_1_LOC);
				break;

			case CAP_2_ATTACK:
				img = SDL_LoadBMP(IMG_2_LOC);
				break;

			case CAP_3_CHOOSING_FLAG:
				img = SDL_LoadBMP(IMG_3_LOC);
				break;

			case CAP_3_CHOOSING_DEFENCE:
				img = SDL_LoadBMP(IMG_4_LOC);
				break;

			case END_CAPTAIN:
				img = SDL_LoadBMP(IMG_5_LOC);
				break;

			case SMITH_1_CHOOSING_CANNONS:
				img = SDL_LoadBMP(IMG_6_LOC);
				break;

			case SMITH_2_CHOOSING_FIRE_REPAIRS:
				if (state->gState.bState == LOSING)
				{
					img = SDL_LoadBMP(IMG_7_LOSE_LOC);
				}
				else if (state->gState.bState == WINNING)
				{
					img = SDL_LoadBMP(IMG_7_WIN_LOC);
				}

				break;

			case SURGEON_1_WHO_WHERE_TREAT:
				img = SDL_LoadBMP(IMG_8_LOC);
				break;

			case END_SURGEON:
				img = SDL_LoadBMP(IMG_9_LOC);
				break;

			case CAP_4_CHOOSING_DUEL:
				img = SDL_LoadBMP(IMG_10_LOC);
				break;

			case CAP_5_DUEL:
				img = SDL_LoadBMP(IMG_DEATH_LOC);
				break;

			case CAP_6_VICTORY_PART_1:
			case CAP_6_VICTORY_PART_2:
				img = SDL_LoadBMP(IMG_11_LOC);
				break;

			case CONCLUSION_PART_1:
				img = SDL_LoadBMP(IMG_12_BODIES_LOC);
				break;

			case CONCLUSION_PART_2:
				// if a ship is sinking, one image
				// if not, the other
				if (state->gState.choice.cannonAngle == DOWN
					|| state->gState.choice.pumpRepair == IGNORE)
				{
					img = SDL_LoadBMP(IMG_12_SINKING_LOC);
				}
				else
				{
					img = SDL_LoadBMP(IMG_12_TRUE_LOC);
				}

				break;

			default:
		}
	}

	state->imgTexture = SDL_CreateTextureFromSurface(state->renderer, img);
	if (state->imgTexture)
	SDL_DestroySurface(img);

	return;
}

// ################################################################################################
// INITIALISATION
// ################################################################################################

bool initGameLogic(State* state)
{
	state->gState.sState = CAP_1_OPENING;
	state->gState.bState = LOSING;
	state->gState.pState = READING;
	state->gState.vState = START_MENU;
	state->gState.textLoaded = false;
	state->gState.textTextured = false;
	state->gState.textRendered = false;
	state->gState.sceneRendered = false;

	return true;
}

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
	// SDL_Log("Initialising structs...");

	initFrameParameters(state);
	initGameLogic(state);

	// SDL_Log("Struct initialisation complete");

	return true;
}

bool initFont(State *state)
{
	// SDL_Log("Initialising font...");
	
	// initialise ttf library
	if (!TTF_Init())
	{
		/*
		SDL_LogError(SDL_Log_CATEGORY_APPLICATION,
			"TTF intialisation failed: %s", SDL_GetError());
		*/

		return false;
	}

	state->font = TTF_OpenFont(FONT_LOC, FONT_PT_SIZE);

	if (state->font == NULL)
	{
		/*
		SDL_LogError(SDL_Log_CATEGORY_APPLICATION,
			"Failed to load font: %s", SDL_GetError());
		*/

		return false;
	}

	// SDL_Log("Font initialisation complete");

	return true;
}

bool initVideo(State *state)
{
	// SDL_Log("Initialising video...");
	
	// initialise video
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		/*
		SDL_LogError(SDL_Log_CATEGORY_APPLICATION,
			"Video intialisation failed: %s", SDL_GetError());
		*/

		return false;
	}
	
	// create window and renderer
	// the 0 is in place of the window flags because none are being used
	if (!SDL_CreateWindowAndRenderer("The Battle of Praxis Bay", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE,
		&(state->window), &(state->renderer)))
	{
		/*
		SDL_LogError(SDL_Log_CATEGORY_APPLICATION,
			"Window/renderer creation failed: %s", SDL_GetError());
		*/

		return false;
	}

	// set logical presentation to allow window to be resized
	if (!SDL_SetRenderLogicalPresentation(state->renderer, WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_LOGICAL_PRESENTATION_LETTERBOX))
	{
		/*
		SDL_LogError(SDL_Log_CATEGORY_APPLICATION,
			"Failed to set logical presentation: %s", SDL_GetError());
		*/

		return false;
	}

	// print available render drivers
	// SDL_Log("Available renderer drivers:");
	for (int i = 0; i < SDL_GetNumRenderDrivers(); i++)
	{
		    // SDL_Log("%d. %s", i + 1, SDL_GetRenderDriver(i));
	}

	// set window icon
	SDL_Surface* icon = SDL_LoadBMP(ICON_LOC);
	if (!SDL_SetWindowIcon(state->window, icon))
	{
		/*
		SDL_LogError(SDL_Log_CATEGORY_APPLICATION,
			"Error setting window icon: %s", SDL_GetError());
		*/
	
		return false;
	}
	SDL_DestroySurface(icon);

	// SDL_Log("Video initialisation complete");

	return true;
}

// ################################################################################################
// GAME LOGIC
// ################################################################################################

void determineBattleState(void *appstate)
{
	State* state = (State*) appstate;
	
	if (((state->gState.choice.flag == FALSE || state->gState.choice.flag == BLACK)
		&& state->gState.choice.battleStrategy == CANNONS
		&& state->gState.choice.powderRelocation == RELOCATE)
		||
		(state->gState.choice.flag == FALSE
		&& (state->gState.choice.battleStrategy == CANNONS || state->gState.choice.battleStrategy == FIFTYFIFTY)
		&& state->gState.choice.powderRelocation == DIRECT_RELOCATION)
		||
		(state->gState.choice.flag == BLACK
		&& state->gState.choice.battleStrategy == BOARDING
		&& state->gState.choice.powderRelocation == LEAVE_IT))
	{
		// only in those circumstances do you win
		state->gState.bState = WINNING;
	}
	else
	{
		state->gState.bState = LOSING;
	}

	return;
}

void determinePlayerRanking(void *appstate)
{
	State* state = (State*) appstate;

	state->gState.rank = F;

	// rank D requirements
	if (state->gState.choice.treatQM != TREAT
		|| state->gState.choice.cannonAngle == UP && state->gState.choice.surgeonPosition == ABOVE)
	{
		state->gState.rank = D;
	}

	// rank C requirements
	if (state->gState.bState == WINNING)
	{
		if (state->gState.choice.cannonAngle != UP
			|| state->gState.choice.surgeonPosition != ABOVE)
		{
			if (state->gState.choice.cannonAngle == DOWN)
			{
				state->gState.rank = C;
			}
		}
	}

	// rank B requirements
	if (state->gState.bState == LOSING)
	{
		if (state->gState.choice.pumpRepair != PUMPS)
		{
			state->gState.rank = B;
		}
	}
	
	// rank S requriements
	if (state->gState.choice.flag != RED)
	{
		if (state->gState.bState == WINNING)
		{
			if (state->gState.choice.cannonAngle != UP
				|| state->gState.choice.surgeonPosition != ABOVE)
			{
				if (state->gState.choice.cannonAngle != DOWN)
				{
					state->gState.rank = S;
				}
			}
		}
		else if (state->gState.bState == LOSING)
		{
			if (state->gState.choice.pumpRepair == PUMPS)
			{
				if (state->gState.choice.treatQM == TREAT)
				{
					state->gState.rank = S;
				}
			}
		}
	}
	else// rank A requirements
	{
		if (state->gState.bState == WINNING)
		{
			if (state->gState.choice.cannonAngle != UP
				|| state->gState.choice.surgeonPosition != ABOVE)
			{
				if (state->gState.choice.cannonAngle != DOWN)
				{
					state->gState.rank = A;
				}
			}
		}
		else if (state->gState.bState == LOSING)
		{
			if (state->gState.choice.pumpRepair == PUMPS)
			{
				if (state->gState.choice.treatQM == TREAT)
				{
					state->gState.rank = A;
				}
			}
		}
	}

	return;
}

void recordChoice(void *appstate, Range choice)
{
	State* state = (State*) appstate;

	switch (state->gState.sState)
	{
		case CAP_3_CHOOSING_FLAG:
			switch (choice)
			{
				case CHOICE_1_OF_3:
					state->gState.choice.flag = FALSE;
					break;

				case CHOICE_2_OF_3:
					state->gState.choice.flag = BLACK;
					break;

				case CHOICE_3_OF_3:
					state->gState.choice.flag = RED;
					break;

				default:
			}

			break;

		case CAP_3_CHOOSING_DEFENCE:
			switch (choice)
			{
				case CHOICE_1_OF_3:
					state->gState.choice.battleStrategy = BOARDING;
					break;

				case CHOICE_2_OF_3:
					state->gState.choice.battleStrategy = CANNONS;
					break;

				case CHOICE_3_OF_3:
					state->gState.choice.battleStrategy = FIFTYFIFTY;
					break;

				default:
			}

			break;

		case SMITH_1_CHOOSING_CANNONS:
			switch (choice)
			{
				case CHOICE_1_OF_3:
					state->gState.choice.powderRelocation = RELOCATE;
					break;

				case CHOICE_2_OF_3:
					state->gState.choice.powderRelocation = DIRECT_RELOCATION;
					break;

				case CHOICE_3_OF_3:
					state->gState.choice.powderRelocation = LEAVE_IT;
					break;

				default:
			}

			break;

		case SMITH_2_CHOOSING_FIRE_REPAIRS:
			if (state->gState.bState == LOSING)
			{
				switch (choice)
				{
					case CHOICE_1_OF_2:
						state->gState.choice.pumpRepair = PUMPS;
						break;

					case CHOICE_2_OF_2:
						state->gState.choice.pumpRepair = IGNORE;
						break;

					default:
				}
			}
			else if (state->gState.bState == WINNING)
			{
				switch (choice)
				{
					case CHOICE_1_OF_3:
						state->gState.choice.cannonAngle = UP;
						break;

					case CHOICE_2_OF_3:
						state->gState.choice.cannonAngle = DOWN;
						break;

					case CHOICE_3_OF_3:
						state->gState.choice.cannonAngle = STRAIGHT;
						break;

					default:
				}
			}

			break;

		case SURGEON_1_WHO_WHERE_TREAT:
			if (state->gState.bState == LOSING)
			{
				switch (choice)
				{
					case CHOICE_1_OF_2:
						state->gState.choice.treatQM = TREAT;
						break;

					case CHOICE_2_OF_2:
						state->gState.choice.treatQM = LEAVE_HIM_TO_DIE_LIKE_SOME_SORT_OF_MONSTER;
						break;

					default:
				}
			}
			else if (state->gState.bState == WINNING)
			{
				switch (choice)
				{
					case CHOICE_1_OF_2:
						state->gState.choice.surgeonPosition = ABOVE;
						break;

					case CHOICE_2_OF_2:
						state->gState.choice.surgeonPosition = BELOW;
						break;

					default:
				}
			}

			break;

		case CAP_4_CHOOSING_DUEL:
			switch (choice)
			{
				case CHOICE_1_OF_3:
					state->gState.choice.duel = SWORD;
					break;

				case CHOICE_2_OF_3:
					state->gState.choice.duel = GUN;
					break;

				case CHOICE_3_OF_3:
					state->gState.choice.duel = ESCAPE;

				default:
			}

			break;

		default:
	}

	return;
}

bool youDie(void *appstate)
{
	State* state = (State*) appstate;
	
	if (((state->gState.choice.duel == SWORD)
		&& (state->gState.bState == LOSING
			&& state->gState.choice.battleStrategy != BOARDING)
		&& (state->gState.choice.cannonAngle != UP))
		|| ((state->gState.choice.duel == SWORD)
		&& (state->gState.bState == WINNING
			&& state->gState.choice.battleStrategy != CANNONS)
		&& (state->gState.choice.cannonAngle != UP))
		|| ((state->gState.choice.duel == ESCAPE)
		&& (state->gState.choice.cannonAngle == UP))
		|| ((state->gState.choice.duel == ESCAPE)
		&& (state->gState.choice.surgeonPosition != ABOVE)
		&& (state->gState.bState == LOSING)
		&& (state->gState.choice.battleStrategy != CANNONS))
		|| ((state->gState.choice.duel == ESCAPE)
		&& (state->gState.choice.surgeonPosition != ABOVE)
		&& (state->gState.bState == WINNING)
		&& (state->gState.choice.battleStrategy != BOARDING)))
	{
		return true;
	}

	return false;
}

void advanceStoryState(void *appstate)
{
	State* state = (State*) appstate;
	
	// advance game state to next stage
	// also update player state accordingly to reflect current options
	switch (state->gState.sState)
	{
		case DEAD:
			state->gState.sState = CAP_1_OPENING;
			state->gState.vState = START_MENU;
		
		case CAP_1_OPENING:
			state->gState.sState = CAP_2_ATTACK;
			break;

		case CAP_2_ATTACK:
			state->gState.sState = CAP_3_CHOOSING_FLAG;
			state->gState.pState = CHOOSING3;
			break;

		case CAP_3_CHOOSING_FLAG:
			state->gState.sState = CAP_3_CHOOSING_DEFENCE;
			state->gState.pState = CHOOSING3;
			break;

		case CAP_3_CHOOSING_DEFENCE:
			state->gState.sState = END_CAPTAIN;
			state->gState.pState = READING;
			break;

		case END_CAPTAIN:
			state->gState.sState = SMITH_1_CHOOSING_CANNONS;
			state->gState.pState = CHOOSING3;
			break;

		case SMITH_1_CHOOSING_CANNONS:
			state->gState.sState = SMITH_2_CHOOSING_FIRE_REPAIRS;

			// now is the time when the battle state is determined
			determineBattleState(appstate);

			if (state->gState.bState == LOSING)
			{
				state->gState.pState = CHOOSING2;
			}
			else if (state->gState.bState == WINNING)
			{
				state->gState.pState = CHOOSING3;
			}

			break;

		case SMITH_2_CHOOSING_FIRE_REPAIRS:
			state->gState.sState = SURGEON_1_WHO_WHERE_TREAT;
			state->gState.pState = CHOOSING2;
			break;

		case SURGEON_1_WHO_WHERE_TREAT:
			state->gState.sState = END_SURGEON;
			state->gState.pState = READING;
			break;

		case END_SURGEON:
			state->gState.sState = CAP_4_CHOOSING_DUEL;
			state->gState.pState = CHOOSING3;
			break;

		case CAP_4_CHOOSING_DUEL:
			state->gState.sState = CAP_5_DUEL;
			state->gState.pState = READING;
			break;

		case CAP_5_DUEL:
			// this is the point where you could die
			if (youDie(appstate))
			{
				state->gState.sState = DEAD;
				state->gState.vState = DEATH_SCREEN;
			}
			else
			{
				state->gState.sState = CAP_6_VICTORY_PART_1;
			}

			break;

		case CAP_6_VICTORY_PART_1:
			state->gState.sState = CAP_6_VICTORY_PART_2;
			break;

		case CAP_6_VICTORY_PART_2:
			state->gState.sState = CONCLUSION_PART_1;
			break;

		case CONCLUSION_PART_1:
			state->gState.sState = CONCLUSION_PART_2;
			break;

		case CONCLUSION_PART_2:
			state->gState.sState = RANKING;
			state->gState.vState = RANK_SCREEN;
			determinePlayerRanking(appstate);
			break;

		case RANKING:
			state->gState.sState = CAP_1_OPENING;
			state->gState.vState = START_MENU;
			break;

		default:		
	}

	return;
}

// ################################################################################################
// GAME ENGINE
// ################################################################################################

// ############################################################################
// INPUT
// ############################################################################

bool mouseInRange(void *appstate, Range range)
{
	State* state = (State*) appstate;
	
	bool inRange = false;
	float x, y;
	float xMin, xMax, yMin, yMax;
	int windowW, windowH;

	SDL_GetMouseState(&x, &y);

	switch (range)
	{
		case CREDITS_BUTTON:
			xMin = (WINDOW_WIDTH / 2) - (CREDITS_BUTTON_W / 2);
			xMax = (WINDOW_WIDTH / 2) + (CREDITS_BUTTON_W / 2);
			yMin = 0;
			yMax = CREDITS_BUTTON_H;
			break;

		case CHOICE_1_OF_2:
			xMin = CHOICE_1OF2_BUTTON_X;
			xMax = CHOICE_1OF2_BUTTON_X + CHOICE_1OF2_BUTTON_W;
			yMin = CHOICE_1OF2_BUTTON_Y;
			yMax = CHOICE_1OF2_BUTTON_Y + CHOICE_1OF2_BUTTON_H;
			break;

		case CHOICE_2_OF_2:
			xMin = CHOICE_2OF2_BUTTON_X;
			xMax = CHOICE_2OF2_BUTTON_X + CHOICE_2OF2_BUTTON_W;
			yMin = CHOICE_2OF2_BUTTON_Y;
			yMax = CHOICE_2OF2_BUTTON_Y + CHOICE_2OF2_BUTTON_H;
			break;

		case CHOICE_1_OF_3:
			xMin = CHOICE_1OF3_BUTTON_X;
			xMax = CHOICE_1OF3_BUTTON_X + CHOICE_1OF3_BUTTON_W;
			yMin = CHOICE_1OF3_BUTTON_Y;
			yMax = CHOICE_1OF3_BUTTON_Y + CHOICE_1OF3_BUTTON_H;
			break;

		case CHOICE_2_OF_3:
			xMin = CHOICE_2OF3_BUTTON_X;
			xMax = CHOICE_2OF3_BUTTON_X + CHOICE_2OF3_BUTTON_W;
			yMin = CHOICE_2OF3_BUTTON_Y;
			yMax = CHOICE_2OF3_BUTTON_Y + CHOICE_2OF3_BUTTON_H;
			break;

		case CHOICE_3_OF_3:
			xMin = CHOICE_3OF3_BUTTON_X;
			xMax = CHOICE_3OF3_BUTTON_X + CHOICE_3OF3_BUTTON_W;
			yMin = CHOICE_3OF3_BUTTON_Y;
			yMax = CHOICE_3OF3_BUTTON_Y + CHOICE_3OF3_BUTTON_H;
			break;

		default:
	}

	// scale values so they match the current resolution if window was resized
	SDL_GetWindowSize(state->window, &windowW, &windowH);
	xMin = xMin * ((float) windowW) / WINDOW_WIDTH;
	xMax = xMax * ((float) windowW) / WINDOW_WIDTH;
	yMin = yMin * ((float) windowH) / WINDOW_HEIGHT;
	yMax = yMax * ((float) windowH) / WINDOW_HEIGHT;

	if ((x > xMin) && (x < xMax) && (y > yMin) && (y < yMax))
	{
		inRange = true;

		// record choice if one was made
		if (state->gState.pState == CHOOSING2 || state->gState.pState == CHOOSING3)
		{
			recordChoice(appstate, range);
		}
	}

	return (inRange);
}

// handle inputs (mouse left click only)
SDL_AppResult input(void *appstate, SDL_Event *event)
{
	State* state = (State*) appstate;
	bool stateChange = false;
	
	if (event->type == SDL_EVENT_QUIT)// quit
	{
		return SDL_APP_SUCCESS;
	}
	else 
	{
		// if mouse press detected
		if(event->type == SDL_EVENT_MOUSE_BUTTON_DOWN
			&& event->button.button == SDL_BUTTON_LEFT)
		{
			switch (state->gState.vState)
			{
				case CREDITS:
				case DEATH_SCREEN:
				case RANK_SCREEN:
					// reset game
					initGameLogic(state);
					stateChange = true;
					break;

				case START_MENU:
					// start playing or go to credits
					if (mouseInRange(appstate, CREDITS_BUTTON))
					{
						// go to credits
						state->gState.vState = CREDITS;
						stateChange = true;
					}
					else
					{
						state->gState.vState = PLAYING;
						stateChange = true;
					}
					
					break;

				case PLAYING:
					// check if choice available
					switch (state->gState.pState)
					{
						case READING:
							// advance story (no choice)
							advanceStoryState(appstate);
							stateChange = true;
							break;

						case CHOOSING2:
							if (mouseInRange(appstate, CHOICE_1_OF_2))
							{
								recordChoice(appstate, CHOICE_1_OF_2);
								advanceStoryState(appstate);
								stateChange = true;
							}
							else if (mouseInRange(appstate, CHOICE_2_OF_2))
							{
								recordChoice(appstate, CHOICE_2_OF_2);
								advanceStoryState(appstate);
								stateChange = true;
							}

							break;

						case CHOOSING3:
							if (mouseInRange(appstate, CHOICE_1_OF_3))
							{
								recordChoice(appstate, CHOICE_1_OF_3);
								advanceStoryState(appstate);
								stateChange = true;
							}
							else if (mouseInRange(appstate, CHOICE_2_OF_3))
							{
								recordChoice(appstate, CHOICE_2_OF_2);
								advanceStoryState(appstate);
								stateChange = true;
							}
							else if (mouseInRange(appstate, CHOICE_3_OF_3))
							{
								recordChoice(appstate, CHOICE_3_OF_3);
								advanceStoryState(appstate);
								stateChange = true;
							}
					}
					break;

				default:
			}

			if (stateChange)
			{
				// need to reread from file if click detected
				state->gState.textLoaded = false;
				state->gState.textTextured = false;
				state->gState.textRendered = false;
				state->gState.sceneRendered = false;
			}
		}
	}

	return SDL_APP_CONTINUE;
}

// ############################################################################
// FRAME CALCULATION & MANAGEMENT
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
// UPDATE & RENDER
// ############################################################################

void updateTxtTexture(void *appstate, int paragraph, TextType type)
{
	State* state = (State*) appstate;

	SDL_Color colour = {0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE};
	const char* renderText;

	// load text into surface and create texture from surface
	if (type == STANDARD)
	{
		renderText = state->gState.txt.currentText[paragraph];
		state->txtSurface = TTF_RenderText_Solid_Wrapped(state->font, renderText, 0, colour, TXT_RECT_W);

		state->txtTexture[0][paragraph] = SDL_CreateTextureFromSurface(state->renderer, state->txtSurface);

		SDL_SetTextureScaleMode(state->txtTexture[0][paragraph], SDL_SCALEMODE_LINEAR);
	}
	else if (type == CHOOSE)
	{
		renderText = state->gState.txt.choiceText[paragraph];
		state->txtSurface = TTF_RenderText_Solid_Wrapped(state->font, renderText, 0, colour, TXT_RECT_W);

		state->txtTexture[1][paragraph] = SDL_CreateTextureFromSurface(state->renderer, state->txtSurface);

		SDL_SetTextureScaleMode(state->txtTexture[1][paragraph], SDL_SCALEMODE_LINEAR);
	}

	return;
}

void update(void *appstate)
{
	State* state = (State*) appstate;

	// update textures if necessary
	if (!(state->gState.textTextured))
	{
		// update story text textures
		for (int i = 0; i < state->gState.txt.paragraphs; i++)
		{
			updateTxtTexture(appstate, i, STANDARD);
		}

		// update choice text textures
		for (int i = 0; i < No_CHOICES_MAX; i++)
		{
			updateTxtTexture(appstate, i, CHOOSE);
		}

		state->gState.textTextured = true;
	}
	
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

		case CHOICE1OF2:
			rect.x = CHOICE_1OF2_BUTTON_X;
			rect.y = CHOICE_1OF2_BUTTON_Y;
			rect.w = CHOICE_1OF2_BUTTON_W;
			rect.h = CHOICE_1OF2_BUTTON_H;
			break;
			
		case CHOICE2OF2:
			rect.x = CHOICE_2OF2_BUTTON_X;
			rect.y = CHOICE_2OF2_BUTTON_Y;
			rect.w = CHOICE_2OF2_BUTTON_W;
			rect.h = CHOICE_2OF2_BUTTON_H;
			break;

		case CHOICE1OF3:
			rect.x = CHOICE_1OF3_BUTTON_X;
			rect.y = CHOICE_1OF3_BUTTON_Y;
			rect.w = CHOICE_1OF3_BUTTON_W;
			rect.h = CHOICE_1OF3_BUTTON_H;
			break;

		case CHOICE2OF3:
			rect.x = CHOICE_2OF3_BUTTON_X;
			rect.y = CHOICE_2OF3_BUTTON_Y;
			rect.w = CHOICE_2OF3_BUTTON_W;
			rect.h = CHOICE_2OF3_BUTTON_H;
			break;

		case CHOICE3OF3:
			rect.x = CHOICE_3OF3_BUTTON_X;
			rect.y = CHOICE_3OF3_BUTTON_Y;
			rect.w = CHOICE_3OF3_BUTTON_W;
			rect.h = CHOICE_3OF3_BUTTON_H;
			break;

		case PLAYING_TXT:
			rect.x = TXT_RECT_START_X;
			rect.y = TXT_RECT_START_Y;
			rect.w = TXT_RECT_W;
			rect.h = TXT_RECT_H;
			break;

		case START_TXT:
			rect.y = START_TXT_RECT_Y;
			// width and height tbd later
			break;

		default:
	}

	return rect;
}

void renderStartScreen(void *appstate)
{
	State* state = (State*) appstate;

	float w, h;
	
	// TODO: just render the logo and some text
	// correct image should be loaded at this point
	SDL_FRect rect = generateFRect(IMG);

	// centre image first
	rect.x = CENTRE_IMG_RECT_X;
	rect.y = CENTRE_IMG_RECT_Y;

	// render image
	SDL_RenderTexture(state->renderer, state->imgTexture, NULL, &rect);

	// place start text below image
	rect.y = START_TXT_RECT_Y;

	// load text
	SDL_Color colour = {0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE};
	state->txtSurface = TTF_RenderText_Solid(state->font, "Click to begin", 0, colour);
	state->txtTexture[0][0] = SDL_CreateTextureFromSurface(state->renderer, state->txtSurface);

	// centre text
	SDL_GetTextureSize(state->txtTexture[0][0], &w, &h);
	rect.w = w + BORDER_WIDTH;
	rect.h = h;
	rect.x = (WINDOW_WIDTH / 2) - (w / 2);

	// render text
	SDL_RenderTexture(state->renderer, state->txtTexture[0][0], NULL, &rect);

	// now credits button
	rect.y = BORDER_WIDTH;

	// load text
	state->txtSurface = TTF_RenderText_Solid(state->font, "Credits", 0, colour);
	state->txtTexture[0][0] = SDL_CreateTextureFromSurface(state->renderer, state->txtSurface);

	// centre text
	SDL_GetTextureSize(state->txtTexture[0][0], &w, &h);
	rect.x = (WINDOW_WIDTH / 2) - (w / 2);
	rect.w = w;
	rect.h = h;

	// render text
	SDL_RenderTexture(state->renderer, state->txtTexture[0][0], NULL, &rect);

	return;
}

void renderDeathScreen(void *appstate)
{
	State* state = (State*) appstate;

	SDL_Color colour = {0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE};
	SDL_FRect rect;
	int windowW, windowH;

	// just tell the dumbass player that he died
	state->txtSurface = TTF_RenderText_Solid(state->font, "YOU DIED", 0, colour);
	state->txtTexture[0][0] = SDL_CreateTextureFromSurface(state->renderer, state->txtSurface);

	SDL_GetTextureSize(state->txtTexture[0][0], &(rect.w), &(rect.h));
	
	// centre text
	SDL_GetWindowSize(state->window, &windowW, &windowH);

	rect.x = (((float) windowW) / 2) - (rect.w / 2);
	rect.y = (((float) windowH) / 2) - (rect.h / 2);

	// render away
	SDL_RenderTexture(state->renderer, state->txtTexture[0][0], NULL, &rect);

	// also display "click to return to start screen"
	state->txtSurface = TTF_RenderText_Solid(state->font, "Click to continue to start screen", 0, colour);
	state->txtTexture[0][1] = SDL_CreateTextureFromSurface(state->renderer, state->txtSurface);

	SDL_GetTextureSize(state->txtTexture[0][1], &(rect.w), &(rect.h));
	
	// centre text
	SDL_GetWindowSize(state->window, &windowW, &windowH);

	rect.x = (((float) windowW) / 2) - (rect.w / 2);
	rect.y = 2 * (((float) windowH) / 3) - (rect.h / 2);

	// render again
	SDL_RenderTexture(state->renderer, state->txtTexture[0][1], NULL, &rect);
	
	return;
}

void renderCreditsScreen(void* appstate)
{
	State* state = (State*) appstate;
	
	float w, h;
	int windW, windH;
	SDL_GetWindowSize(state->window, &windW, &windH);

	// build first rectangle
	SDL_FRect rect;
	rect.x = BORDER_WIDTH;
	rect.y = BORDER_WIDTH;

	// load text
	if (!(state->gState.textLoaded))
	{
		readTextFromFiles(appstate, STANDARD);

		state->gState.textLoaded = true;
	}

	SDL_Log(state->gState.txt.currentText[0]);

	// render
	for (int i = 0; i < No_CREDITS_FILES; i++)
	{
		SDL_GetTextureSize(state->txtTexture[0][i], &w, &h);
		rect.h = h;
		rect.w = w;

		SDL_RenderTexture(state->renderer, state->txtTexture[0][i], NULL, &rect);
	
		rect.y = rect.y + rect.h + BORDER_WIDTH;
	}

	return;
}

void renderChoice(void *appstate, Range range, SDL_FRect boxRect)
{
	State* state = (State*) appstate;
	
	SDL_Texture* texture[2];
	SDL_FRect rect;
	float x, y, w, h;
	
	// determine which text to render
	switch (range)
	{
		case CHOICE_1_OF_2:
			texture[0] = state->txtTexture[1][0];
			texture[1] = state->txtTexture[1][1];
			break;

		case CHOICE_2_OF_2:
			rect = generateFRect(CHOICE2OF2);
			texture[0] = state->txtTexture[1][2];
			texture[1] = state->txtTexture[1][3];
			break;

		case CHOICE_1_OF_3:
			rect = generateFRect(CHOICE1OF3);
			texture[0] = state->txtTexture[1][0];
			texture[1] = state->txtTexture[1][1];
			break;

		case CHOICE_2_OF_3:
			rect = generateFRect(CHOICE2OF3);
			texture[0] = state->txtTexture[1][2];
			texture[1] = state->txtTexture[1][3];
			break;

		case CHOICE_3_OF_3:
			rect = generateFRect(CHOICE3OF3);
			texture[0] = state->txtTexture[1][4];
			texture[1] = state->txtTexture[1][5];
			break;

		default:
	}

	// render rectangle around text
	SDL_RenderRect(state->renderer, &boxRect);

	// resize rect to text size to prevent stretching
	SDL_GetTextureSize(texture[0], &w, &h);

	// align text in centre of box
	rect.x = boxRect.x + ((boxRect.w / 2) - (w / 2));
	rect.y = boxRect.y + ((boxRect.h / 3) - (h / 2));
	rect.w = w;
	rect.h = h;

	// do the same for the bottom text
	SDL_RenderTexture(state->renderer, texture[0], NULL, &rect);

	SDL_GetTextureSize(texture[1], &w, &h);

	rect.x = boxRect.x + ((boxRect.w / 2) - (w / 2));
	rect.y = boxRect.y + (2 * ((boxRect.h / 3) - (h / 2)));
	rect.w = w;
	rect.h = h;

	SDL_RenderTexture(state->renderer, texture[1], NULL, &rect);

	return;
}

void renderPlaying(void *appstate)
{
	State* state = (State*) appstate;
	SDL_FRect rect;
	float x, y, w, h;

	// draw rectangles
	// left rect first
	rect = generateFRect(LEFT);
	SDL_RenderRect(state->renderer, &rect);

	// right rect second
	rect = generateFRect(RIGHT);
	SDL_RenderRect(state->renderer, &rect);

	// render image  third
	rect = generateFRect(IMG);
	SDL_RenderTexture(state->renderer, state->imgTexture, NULL, &rect);

	// then render options if need be
	if (state->gState.pState == CHOOSING2 || state->gState.pState == CHOOSING3)
	{
		// first render one big rectangle around choices
		rect = generateFRect(CHOICE);
		SDL_RenderRect(state->renderer, &rect);

		// next render a rectangle around each option then render the text itself
		if (state->gState.pState == CHOOSING2)
		{
			// choice 1
			rect = generateFRect(CHOICE1OF2);
			renderChoice(appstate, CHOICE_1_OF_2, rect);

			// choice 2
			rect = generateFRect(CHOICE2OF2);
			renderChoice(appstate, CHOICE_2_OF_2, rect);
		}
		else if (state->gState.pState == CHOOSING3)
		{
			// choice 1
			rect = generateFRect(CHOICE1OF3);
			renderChoice(appstate, CHOICE_1_OF_3, rect);

			// choice 2
			rect = generateFRect(CHOICE2OF3);
			renderChoice(appstate, CHOICE_2_OF_3, rect);

			// choice 1
			rect = generateFRect(CHOICE3OF3);
			renderChoice(appstate, CHOICE_3_OF_3, rect);
		}
	}

	// render story text
	rect = generateFRect(PLAYING_TXT);

	for (int i = 0; i < state->gState.txt.paragraphs; i++)
	{
		// resize text rect so it doesn't stretch the text
		SDL_GetTextureSize(state->txtTexture[0][i], &w, &h);
		rect.h = h;
		rect.w = w;

		SDL_RenderTexture(state->renderer, state->txtTexture[0][i], NULL, &rect);

		// lower next rect so text doesn't overlap
		rect.y = rect.y + rect.h + BORDER_WIDTH;
	}

	return;
}

void renderRankScreen(void *appstate)
{
	State* state = (State*) appstate;

	SDL_Color colour = {0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE};
	SDL_FRect rect;
	int windowW, windowH;
	char rankText[15];

	strcpy(rankText, "Your rank: ");

	// figure out rank
	switch (state->gState.rank)
	{
		case S:
			strcat(rankText, "S");
			break;

		case A:
			strcat(rankText, "A");
			break;

		case B:
			strcat(rankText, "B");
			break;

		case C:
			strcat(rankText, "C");
			break;

		case D:
			strcat(rankText, "D");
			break;

		case F:
			strcat(rankText, "F");
			break;

		default:
			strcat(rankText, "ERROR");
	}


	// create rank texture
	state->txtSurface = TTF_RenderText_Solid(state->font, rankText, 0, colour);
	state->txtTexture[0][0] = SDL_CreateTextureFromSurface(state->renderer, state->txtSurface);

	SDL_GetTextureSize(state->txtTexture[0][0], &(rect.w), &(rect.h));
	
	// centre text
	SDL_GetWindowSize(state->window, &windowW, &windowH);

	rect.x = (((float) windowW) / 2) - (rect.w / 2);
	rect.y = (((float) windowH) / 3) - (rect.h / 2);

	// render the thing
	SDL_RenderTexture(state->renderer, state->txtTexture[0][0], NULL, &rect);

	// also display "click to return to start screen"
	state->txtSurface = TTF_RenderText_Solid(state->font, "Click to continue to start screen", 0, colour);
	state->txtTexture[0][0] = SDL_CreateTextureFromSurface(state->renderer, state->txtSurface);

	SDL_GetTextureSize(state->txtTexture[0][0], &(rect.w), &(rect.h));
	
	// centre text
	SDL_GetWindowSize(state->window, &windowW, &windowH);

	rect.x = (((float) windowW) / 2) - (rect.w / 2);
	rect.y = 2 * (((float) windowH) / 3) - (rect.h / 2);

	// render away
	SDL_RenderTexture(state->renderer, state->txtTexture[0][0], NULL, &rect);
	
	return;
}

void render(void* appstate)
{
	State* state = (State*) appstate;

	// clear screen
	SDL_SetRenderDrawColor(state->renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(state->renderer);

	// render scene
	SDL_SetRenderDrawColor(state->renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	
	switch (state->gState.vState)
	{
		case START_MENU:
			renderStartScreen(appstate);
			break;

		case PLAYING:
			renderPlaying(appstate);
			break;

		case CREDITS:
			renderCreditsScreen(appstate);
			break;

		case DEATH_SCREEN:
			renderDeathScreen(appstate);
			break;

		case RANK_SCREEN:
			renderRankScreen(appstate);
			break;

		default:
			// SDL_Log("Error");
	}

	SDL_RenderPresent(state->renderer);

	return;
}

void updateAndRender(void *appstate)
{
	State* state = (State*) appstate;
	
	// load files if not done yet
	if (!(state->gState.textRendered))
	{
		readTextFromFiles(state, STANDARD);
		readTextFromFiles(state, CHOOSE);
		loadImgFromFiles(state);
		state->gState.textRendered = true;
	}
	
	if (advanceFrame(appstate))
	{
		update(appstate);
		render(appstate);
	}

	return;
}

// ################################################################################################
// CALLBACK FUNCTONS
// ################################################################################################

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
	static State state;
	
	if (!initVideo(&state))
	{
		return SDL_APP_FAILURE;
	}
	else if (!initFont(&state))
	{
		return SDL_APP_FAILURE;
	}
	else if (!initStructs(&state))
	{
		return SDL_APP_FAILURE;
	}

	*appstate = &state;

	// SDL_Log("Initialisation complete");

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
	return (input(appstate, event));
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
	State* state = (State*) appstate;
	
	updateAndRender(appstate);

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
	State* state = (State*) appstate;

	if (state->font)
	{
		TTF_CloseFont(state->font);
	}

	TTF_Quit();

	SDL_DestroySurface(state->txtSurface);	
	SDL_DestroyTexture(state->imgTexture);
	
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			SDL_DestroyTexture(state->txtTexture[i][j]);
		}
	}

	SDL_DestroyRenderer(state->renderer);
	SDL_DestroyWindow(state->window);
	
	return;
}
