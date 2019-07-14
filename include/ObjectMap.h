#ifndef OBJECTMAP_H
#define OBJECTMAP_H

#include <string>
#include <vector>
#include <utility>

#include "Vec2.h"

struct ObjectInfo {
  int x;
  int y;
  int objectType;
  std::string environment;
};

class ObjectMap {
private:
  int rows;
  int columns;
  int rowSize;
  int colSize;
  int numberOfObjects;
  std::vector<ObjectInfo> objects;
  std::vector<int> objectsMatrix;

public:
  ObjectMap(std::string file, int stageSize, int rowSize, int colSize);
  ~ObjectMap();

  void BuildMatrix();
  void Load(std::string file);

  int &At(int x, int y);
  Vec2 GetObjectPosition(int x, int y);

  std::vector<ObjectInfo> GetObjectList();
};

#endif
