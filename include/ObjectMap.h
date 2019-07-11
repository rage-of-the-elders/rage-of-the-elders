#ifndef OBJECTMAP_H
#define OBJECTMAP_H

#include <string>
#include <vector>
#include <utility>

struct ObjectInfo {
  int x;
  int y;
  int objectType;
  std::string environment;
};

class ObjectMap {
private:
  int numberOfObjects;
  std::vector<ObjectInfo> objects;

public:
  ObjectMap(std::string file);
  ~ObjectMap();

  void Load(std::string file);

  std::vector<ObjectInfo> GetObjectList();
};

#endif
