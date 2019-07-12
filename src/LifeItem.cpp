#include "LifeItem.h"
#include "Playable.h"
#include "Collider.h"
#include "GameData.h"
#include "Veteran.h"
#include "Teacher.h"

LifeItem::LifeItem(GameObject &associated, float x, float y) : Component(associated) {
  std::vector<std::string> itensNames;

  this->x = x;
  this->y = y;

  int randNumber = floor(Math::GetRand(0, 10));
  if( randNumber % 2 == 0) {
    this->associated.AddComponent(new Sprite(this->associated, "img/itens/drugs.png"));
  }
  else {
    this->associated.AddComponent(new Sprite(this->associated, "img/itens/box.png"));
  }
  this->associated.AddComponent(new Collider(this->associated));
  this->associated.box.SetPos(x,y);

  itemPickup = new Sound(associated, "audio/item-pickup.ogg");
}

void LifeItem::Update(float dt) {

}
void LifeItem::Render() {

}
bool LifeItem::Is(std::string type) {
  return(type == "LifeItem");
}
void LifeItem::NotifyCollision(GameObject &other) {
  if(other.Has("Playable")) {
    if (GameData::choosedCharacter == "veteran")
      Playable::player->SetHp(VETERAN_HP);
    else
      Playable::player->SetHp(TEACHER_HP);

    itemPickup->Play(1);

    this->associated.RequestDelete();
  }
}