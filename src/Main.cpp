#include "Game.h"
#include "TitleState.h"

int main(int argc, char **argv) {
  Game& game = Game::GetInstance();
  game.Push(new TitleState(false));
  game.Run();
  delete &game;

  return 0;
}