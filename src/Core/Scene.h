#pragma once

#include "Core/Aliases.h"
#include "entt/entt.hpp"

namespace PetrolEngine {

class Entity;
class GameObject;
class SystemManager;

uint64_t timeMillisec();

class Scene {
public:
  Entity *createEntity(String name, Entity *parent = nullptr);

  GameObject *createGameObject(String name, Entity *parent = nullptr);

  Entity *getEntityById(unsigned int id);

  template <typename T> Entity *getEntityByComponent() {
    auto group = sceneRegistry.view<T>();

    for (auto &entity : group)
      return getEntityById((unsigned int)entity);

    return nullptr;
  }

  Scene();
  ~Scene();

  Scene(const Scene &) = delete;
  Scene(Scene &&) = default;

  void update();
  void render();
  void start();

  entt::registry sceneRegistry;

  void serialize();
  void deserialize();

  bool isStarted() const { return started; }
  Vector<Entity *> entities;

private:
  Vector<Entity *> toDelete;
  SystemManager *systemManager;
  bool started = false;
  friend class Entity;
  friend class SystemManager;
};

extern Vector<Scene *> loadedScenes;
} // namespace PetrolEngine
