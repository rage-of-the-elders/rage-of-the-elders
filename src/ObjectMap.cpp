#include "ObjectMap.h"

#include "Game.h"
#include "Sprite.h"
#include "SceneObject.h"

#include <fstream>
#include <iostream>

ObjectMap::ObjectMap(std::string file, int stageSize, int rowSize, int colSize) {
  this->numberOfObjects = 0;
  this->rowSize = rowSize;
  this->colSize = colSize;
  this->columns = (stageSize / this->colSize);
  this->rows = (Game::screenHeight / this->rowSize);
  this->objects = std::vector<ObjectInfo>();
  this->objectsMatrix = std::vector<int>();

  this->BuildMatrix();

  this->Load(file);
}

ObjectMap::~ObjectMap() {
  this->objects.clear();
}

void ObjectMap::BuildMatrix() {
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->columns; j++) {
      this->objectsMatrix.emplace_back(0);
    }
  }
}

void ObjectMap::Load(std::string file) {
   std::ifstream objectsList(("assets/map/" + file).c_str(), std::ios::in);

  if (objectsList.good()) {
    char comma;

    objectsList >> this->numberOfObjects >> comma;

    for(int i = 0; i < this->numberOfObjects; i++) {
      ObjectInfo newObject;

      objectsList >> newObject.environment >> newObject.objectType >> comma >> newObject.x >> comma >> newObject.y >> comma;
      newObject.environment.pop_back();

      this->objects.emplace_back(newObject);
    }
  }
  else {
    printf("ERROR: Could not open '%s'", file.c_str());
    exit(-1);
  }
  objectsList.close();
}

int &ObjectMap::At(int x, int y) {
  return this->objectsMatrix[ x + (this->columns * y)];
}

Vec2 ObjectMap::GetObjectPosition(int x, int y) {
  return Vec2((x - 1) * this->colSize, (y - 1) * this->rowSize);
}

std::vector<ObjectInfo> ObjectMap::GetObjectList() {
  return this->objects;
}
