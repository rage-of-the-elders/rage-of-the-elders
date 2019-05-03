#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Minion.h"
#include "Game.h"

Alien::Action::Action(ActionType type, float x, float y) {
	this->type = type;
  this->pos = Vec2(x, y);
}

Alien::Alien(GameObject &associated, int nMinions) : Component(associated) {
  this->hp = 100;
  this->speed = Vec2();
  this->taskQueue = std::queue<Action>();
  this->minionArray = std::vector<std::weak_ptr<GameObject>>();
  this->nMinions = nMinions;

  this->associated.AddComponent(new Sprite(associated, "img/alien.png"));
}

Alien::~Alien() {
  this->minionArray.clear();
}

void Alien::Start() {
  for (int i = 0; i < this->nMinions; i++) {
    GameObject *go = new GameObject();
    // go->AddComponent(new Minion(*go, std::make_shared<GameObject>(this->associated), i * (360 / this->nMinions)));

    // printf("nminions %d\n",i);
    // printf("%f\n", i * (360.0 / this->nMinions));
    go->AddComponent(new Minion(*go, this->associated, i * (360.0 / this->nMinions)));
    minionArray.push_back(Game::GetInstance().GetState().AddObject(go));
  }
}

void Alien::Update(float dt) {
  Rect associatedBox = this->associated.box;

  if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
    this->taskQueue.push(Action(Action::SHOOT,
                                (float)InputManager::GetInstance().GetMouseX(),
                                (float)InputManager::GetInstance().GetMouseY()));

  }
  if (InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON)) {
    this->taskQueue.push(Action(Action::MOVE,
                                (float)InputManager::GetInstance().GetMouseX() - associatedBox.w / 2,
                                (float)InputManager::GetInstance().GetMouseY() - associatedBox.h / 2));
  }

  if (this->taskQueue.size() > 0) {
    Vec2 targetPos = this->taskQueue.front().pos;

    switch (this->taskQueue.front().type) {
    case Action::MOVE: {
      this->speed = associatedBox.GetPos().GetSpeed(targetPos) * 200;

      if ((associatedBox.x + speed.x * dt > targetPos.x && targetPos.x > associatedBox.x)
          || (associatedBox.x + speed.x * dt < targetPos.x && targetPos.x < associatedBox.x)) {
        associatedBox.x = targetPos.x;
      } else {
        associatedBox.x += speed.x * dt;
      }
      if ((associatedBox.y + speed.y * dt > targetPos.y && targetPos.y > associatedBox.y) || (associatedBox.y + speed.y * dt < targetPos.y && targetPos.y < associatedBox.y)) {
        associatedBox.y = targetPos.y;
      } else {
        associatedBox.y += speed.y * dt;
      }

      if ((associatedBox.x == targetPos.x) && (associatedBox.y == targetPos.y))
        taskQueue.pop();

      this->associated.box = associatedBox;
    } break;

    case Action::SHOOT: {
        Minion* minion = (Minion*) minionArray[rand() % minionArray.size()].lock()->GetComponent("Minion");
        minion->Shoot(targetPos);
        taskQueue.pop();
      } break;

    default:
      break;
    }
  }

  if(this->IsDead())
    this->associated.RequestDelete();
}


void Alien::Render() {
  
}

bool Alien::Is(std::string type) {
  return type == "Alien";
}

bool Alien::IsDead() {
  return this->hp <= 0;
}
