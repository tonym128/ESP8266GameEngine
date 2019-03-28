// #define FPS 1
#define ANALOG 1
// #define AUDIO 1

#include "game.hpp"
ScreenBuff screenBuff;
byte buttonVals;

#ifdef __EMSCRIPTEN__
#include "platform/plat_emscripten.h"
#elif SDL2_FOUND
#include "platform/sdl.h"
#elif _WIN32
#include "platform/win32.h"
#elif __linux
#include "platform/linux.h"
#elif ARDUINO
#include "platform/arduino.h"
#endif

void showLogo(const bool logo[])
{
  Dimensions dim;
  dim.height = logo_height;
  dim.width = logo_width;
  dim.x = 0;
  dim.y = 0;

  drawObject(&screenBuff, dim, logo);
  initTime();
  sendToScreen();
  updateMinTime(2000);
}

void audioSetup()
{
  audioInit();
}

void gameSetup()
{
  showLogo(logo_image);
  //gameInit();
}

void gameLoop()
{
  audioLoop();

  // put your main code here, to run repeatedly:
  buttonVals = getReadShift();

  if (myGameLoop(&screenBuff, buttonVals))
  {
    gameSetup();
  }

  calcFPS();
#ifdef FPS // Define this to show the FPS for the game
  drawFPS(&screenBuff);
#endif

  sendToScreen();
  updateMinTime(33);
}
