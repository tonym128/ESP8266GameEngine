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
	strcpy(scrollerText[8], " -= Asteroid =- ");

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

void initAttractMode(GameState *gameState) {
	gameState->asteroids[0].speed= FLOAT_TO_FIXP(1);
	gameState->asteroids[0].size= FLOAT_TO_FIXP(20);
	gameState->asteroids[0].direction = INT_TO_FIXP(135);
	gameState->asteroids[0].rotateAmount = 2000;
	gameState->asteroids[0].dim.width = 20;
	gameState->asteroids[0].dim.height = 20;

	gameState->asteroids[1].speed= FLOAT_TO_FIXP(0.5);
	gameState->asteroids[1].size= FLOAT_TO_FIXP(10);
	gameState->asteroids[1].direction = INT_TO_FIXP(68);
	gameState->asteroids[1].rotateAmount = 1000;
	gameState->asteroids[1].dim.width = 10;
	gameState->asteroids[1].dim.height = 10;

	gameState->asteroids[2].speed= FLOAT_TO_FIXP(0.5);
	gameState->asteroids[2].size= FLOAT_TO_FIXP(5);
	gameState->asteroids[2].direction = INT_TO_FIXP(245);
	gameState->asteroids[2].rotateAmount = 500;
	gameState->asteroids[2].dim.width = 5;
	gameState->asteroids[2].dim.height = 5;

	gameState->asteroids[3].speed= FLOAT_TO_FIXP(0.5);
	gameState->asteroids[3].size= FLOAT_TO_FIXP(10);
	gameState->asteroids[3].direction = INT_TO_FIXP(38);
	gameState->asteroids[3].rotateAmount = 500;
	gameState->asteroids[3].dim.width = 10;
	gameState->asteroids[3].dim.height = 10;
}

void updateAttractMode(GameState *gameState, ScreenBuff *screenBuff)
{

	// Draw some asteroids floating in the background
	for (int i = 0; i < 10; i++) {
		gameState->asteroids[i].fixX += xVec(gameState->asteroids[i].speed,gameState->asteroids[i].direction);
		gameState->asteroids[i].fixY += yVec(gameState->asteroids[i].speed,gameState->asteroids[i].direction);

		if (gameState->asteroids[i].fixX < INT_TO_FIXP(0)) gameState->asteroids[i].fixX += INT_TO_FIXP(screenBuff->WIDTH);
		if (gameState->asteroids[i].fixX > INT_TO_FIXP(screenBuff->WIDTH)) gameState->asteroids[i].fixX -= INT_TO_FIXP(screenBuff->WIDTH);

		if (gameState->asteroids[i].fixY < INT_TO_FIXP(0)) gameState->asteroids[i].fixY += INT_TO_FIXP(screenBuff->HEIGHT);
		if (gameState->asteroids[i].fixY > INT_TO_FIXP(screenBuff->HEIGHT)) gameState->asteroids[i].fixY -= INT_TO_FIXP(screenBuff->HEIGHT);

		gameState->asteroids[i].dim.x = FIXP_TO_INT(gameState->asteroids[i].fixX) % screenBuff->WIDTH;
		gameState->asteroids[i].dim.y = FIXP_TO_INT(gameState->asteroids[i].fixY) % screenBuff->HEIGHT;
		gameState->asteroids[i].rotation = ((double)getTimeInMillis()) / gameState->asteroids[i].rotateAmount;
	}
}

void displayAttractMode(GameState *gameState, ScreenBuff *screenBuff)
{
	// Clear the screen
	displayClear(screenBuff,1,false);
	
	//Draw asteroids
	bool rotAst[400];
	for (int i = 0; i < 10; i++) {
		if (gameState->asteroids[i].dim.height > 0) {
			switch (gameState->asteroids[i].dim.height) {
				case 20 :
					rotateObject(gameState->asteroids[i].dim,gameState->asteroids[i].rotation,1, Asteroid20x20, rotAst);
					break;
				case 10 : 
					rotateObject(gameState->asteroids[i].dim,gameState->asteroids[i].rotation,1, Asteroid10x10, rotAst);
					break;
				case 5 : 
					rotateObject(gameState->asteroids[i].dim,gameState->asteroids[i].rotation,1, Asteroid5x5, rotAst);
					break;
			} 
			drawObjectWrap(screenBuff,gameState->asteroids[i].dim , rotAst);
		}
	}

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
			initAttractMode(&gameState);
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
