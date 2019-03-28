#ifndef MYGAME_H
#define MYGAME_H 1

#ifndef GAMECOMMON_H
#include "gameCommon.hpp"
#endif

struct Player1Keys {
  bool up = false;
  bool down = false;
  bool right = false;
  bool left = false;
  bool a = false;
  bool b = false;
};

struct Player {
  Dimensions dim;
  FIXPOINT thrust,direction,size;
  FIXPOINT fixX,fixY, movX, movY;
  double rotation;
  bool collision = 0;
  bool inPlay = true;
};

struct Asteroid {
  Dimensions dim;
  FIXPOINT speed,direction,size;
  FIXPOINT fixX,fixY;
  double rotateAmount;
  double rotation;
};

struct Fire {
  Dimensions dim;
  FIXPOINT speed;
  FIXPOINT direction;
  int life;
};

static const int ASTEROIDS =  90;

struct GameState {
  int hiScore = 0;
  int score = 0;
  int level = 1;

  int scene = 0;
  int lastscene = -1;
  int frameCounter = 0;

  Player1Keys p1keys;
  Player player1;
  Asteroid asteroids[ASTEROIDS];

  bool running = true;
  bool restart = false;
};

bool myGameLoop(ScreenBuff*, byte);

const static bool Asteroid20x20[400] = {
  0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
  0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
  0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,
  0,0,0,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,
  0,0,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,0,0,0,
  0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,
  0,0,1,0,1,1,1,0,1,1,1,1,0,1,1,0,1,1,1,1,
  0,0,1,0,1,1,1,0,1,1,1,1,0,1,1,0,1,1,1,1,
  0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  0,0,1,1,1,1,1,0,1,0,1,1,0,1,1,1,1,1,1,1,
  0,0,1,1,1,1,1,1,0,0,1,1,0,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,0,
  0,1,1,1,0,0,1,0,1,1,1,1,1,1,0,0,1,1,1,0,
  0,0,0,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,0,
  0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,
  0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
  0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
  0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,
  0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0
};

const static bool Asteroid10x10[100] = {
  0,0,0,1,1,1,0,0,0,0,
  0,0,0,1,1,1,1,0,0,0,
  0,0,1,1,1,1,1,1,0,0,
  0,1,1,1,1,1,0,1,1,0,
  1,1,1,0,1,1,1,1,1,1,
  1,1,1,1,1,1,1,0,1,1,
  1,1,1,1,1,1,1,1,1,1,
  0,1,0,1,0,0,1,0,1,0,
  1,1,1,1,1,1,1,1,0,0,
  1,1,0,1,1,1,1,0,0,0
};

const static bool Asteroid5x5[25] = {
  0,0,0,0,0,
  0,0,1,0,0,
  1,1,1,1,1,
  0,1,1,1,0,
  0,0,1,0,0
};

const static bool Alien10x10[100] = {
  0,0,0,0,1,1,0,0,0,0,
  0,0,0,1,1,1,1,0,0,0,
  0,0,0,1,1,1,1,0,0,0,
  0,1,0,0,1,1,0,0,1,0,
  1,1,1,0,0,0,0,1,1,1,
  1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,
  0,1,0,1,0,0,1,0,1,0,
  0,0,1,1,1,1,1,1,0,0,
  0,0,0,1,1,1,1,0,0,0
};

const static bool Ship10x10[100] = {
  0,0,0,0,1,1,0,0,0,0,
  0,0,1,1,1,1,1,1,0,0,
  0,0,1,1,1,1,1,1,0,0,
  0,0,1,1,0,0,1,1,1,0,
  0,1,1,1,0,0,1,1,1,0,
  0,1,1,1,1,1,1,1,1,0,
  0,1,1,1,1,1,1,1,1,0,
  0,1,1,0,0,0,0,1,1,0,
  0,1,1,0,0,0,0,1,1,0,
  0,0,0,0,0,0,0,0,0,0
};

#endif
