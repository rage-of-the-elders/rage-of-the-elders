#include "Game.h"

int main(int argc, char **argv) {
  std::string title = "Matheus Richard - 150043023";
  Game& game = Game::GetInstance(title, 1024, 600);

  game.Run();

  return 0;
}