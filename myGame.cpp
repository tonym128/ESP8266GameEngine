#include "myGame.hpp"

GameState gameState;

void processInput(GameState *gameState, byte buttonVals)
{
	gameState->p1keys.up = processKey(buttonVals, P1_Top);
	gameState->p1keys.down = processKey(buttonVals, P1_Bottom);
	gameState->p1keys.left = processKey(buttonVals, P1_Left);
	gameState->p1keys.right = processKey(buttonVals, P1_Right);
	gameState->p1keys.a = processKey(buttonVals, P2_Right);
	gameState->p1keys.b = processKey(buttonVals, P2_Left);

	// This is only monitoring for a keypress on false
	if (processKey(buttonVals, P2_Top))
	{
		gameState->running = false;
		gameState->restart = true;
	}
}

void resetGameState(ScreenBuff *screenBuff)
{
}

bool updateScroller(GameState *gameState, ScreenBuff *screenBuff)
{
	return true;
}

bool displayScroller(GameState *gameState, ScreenBuff *screenBuff)
{
	gameState->frameCounter += 1;
	char scrollerText[9][17];
	strcpy(scrollerText[0], "The longest");
	strcpy(scrollerText[1], "journey starts");
	strcpy(scrollerText[2], "with a single");
	strcpy(scrollerText[3], "step.");
	strcpy(scrollerText[4], "");
	strcpy(scrollerText[5], "  Or Asteroid  ");
	strcpy(scrollerText[6], "   Good Luck!  ");
	strcpy(scrollerText[7], "");
	strcpy(scrollerText[8], " -= Asteroid =-  ");

	return drawScroller(screenBuff, gameState->frameCounter, scrollerText);
}

bool updateOutroScroller(GameState *gameState, ScreenBuff *screenBuff)
{
	return true;
}

bool displayOutroScroller(GameState *gameState, ScreenBuff *screenBuff)
{
	gameState->frameCounter += 1;
	char scrollerText[9][17];
	strcpy(scrollerText[0], "Well done on");
	strcpy(scrollerText[1], "completing the");
	strcpy(scrollerText[2], "first leg of");
	strcpy(scrollerText[3], "your journey.");
	strcpy(scrollerText[4], "");
	strcpy(scrollerText[5], "Keep your head");
	strcpy(scrollerText[6], "high & go onward");
	strcpy(scrollerText[7], "");
	strcpy(scrollerText[8], " -= Congrats =- ");

	return drawScroller(screenBuff, gameState->frameCounter, scrollerText);
}

void updateGame(GameState *gameState, ScreenBuff *screenBuff)
{
}

void displayGame(GameState *gameState, ScreenBuff *screenBuff)
{
}

void processAttractMode(GameState *gameState, ScreenBuff *screenBuff)
{
	// Press A or B to starts
	if (gameState->p1keys.a || gameState->p1keys.b)
	{
		gameState->scene = 1;
	}
}

void updateAttractMode(GameState *gameState, ScreenBuff *screenBuff)
{
	// Draw some asteroids floating in the background
	gameState->asteroids[0].dim.x = gameState->asteroids[0].dim.x % screenBuff->WIDTH + 1;
	gameState->asteroids[0].dim.y = gameState->asteroids[0].dim.y % screenBuff->HEIGHT + 1;
	gameState->asteroids[0].dim.width = 20;
	gameState->asteroids[0].dim.height = 20;
}

void displayAttractMode(GameState *gameState, ScreenBuff *screenBuff)
{
	// Clear the screen
	displayClear(screenBuff,1,false);
	
	//Draw asteroids
	drawObjectWrap(screenBuff,gameState->asteroids[0].dim ,Asteroid20x20);

	// Alternate press button text on and off every second
	if (getTimeInMillis() / 1000 % 2 == 0) {
		char scrollerText[17] = "Press a button";
		drawString(screenBuff, scrollerText, 8, 38, false);
		char scrollerText2[17] = "to start";
		drawString(screenBuff, scrollerText2, 32, 45, false);
	}
}

bool myGameLoop(ScreenBuff *screenBuff, byte buttonVals)
{
	processInput(&gameState, buttonVals);

	switch (gameState.scene)
	{
	case 0: // Attract screen
		if (gameState.lastscene != gameState.scene)
		{
			gameState.lastscene = gameState.scene;
			gameState.frameCounter = 0;

			gameState.asteroids[0].dim.height = 20;
			gameState.asteroids[0].dim.width = 20;
			
		}


		processAttractMode(&gameState, screenBuff);
		updateAttractMode(&gameState, screenBuff);
		displayAttractMode(&gameState, screenBuff);
		break;
	case 1: // Intro
		if (gameState.lastscene != gameState.scene)
		{
			gameState.lastscene = gameState.scene;
			gameState.frameCounter = 0;
		}

		updateScroller(&gameState, screenBuff);
		if (!displayScroller(&gameState, screenBuff))
		{
			gameState.scene = 3;
		}

		break;
	case 3: // Asteroid!
		if (gameState.lastscene != gameState.scene)
		{
			gameState.lastscene = gameState.scene;
		}

		updateGame(&gameState, screenBuff);
		displayGame(&gameState, screenBuff);
		break;
	case 2: // Outro
		if (gameState.lastscene != gameState.scene)
		{
			gameState.lastscene = gameState.scene;
			gameState.frameCounter = 0;
		}

		updateOutroScroller(&gameState, screenBuff);
		if (!displayOutroScroller(&gameState, screenBuff))
		{
			gameState.frameCounter = 0;
			gameState.level = 1;
			gameState.scene = 1;
			return true;
		}

		break;
	}

	return false;
}
