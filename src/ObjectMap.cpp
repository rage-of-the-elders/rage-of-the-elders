#include "ObjectMap.h"

#include "Sprite.h"
#include "SceneObject.h"

#include <fstream>
#include <iostream>

ObjectMap::ObjectMap(std::string file) {
  this->numberOfObjects = 0;
  this->objects = std::vector<ObjectInfo>();

  this->Load(file);
}

ObjectMap::~ObjectMap() {
  this->objects.clear();
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

std::vector<ObjectInfo> ObjectMap::GetObjectList() {
  return this->objects;
}