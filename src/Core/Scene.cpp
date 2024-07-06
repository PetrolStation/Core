#include <PCH.h>
#include <vector>

#include "Components/Entity.h"
#include "Core/DebugTools.h"
#include "Core/Window/Window.h"
#include "Scene.h"
#include "EventStack.h"
#include "Static/Renderer/Renderer.h"
#include "Static/Window/Window.h"

#include "Components/Camera.h"
#include "Components/Entity.h"
#include "Components/Mesh.h"
#include "Components/Properties.h"
#include "Components/Sprite.h"
#include "Components/Transform.h"
#include "GameObject.h"
#include "Serializer.h"

namespace PetrolEngine {
Vector<Scene *> loadedScenes;

uint64_t timeMillisec() {
  using namespace std::chrono;
  uint64_t time =
      duration_cast<milliseconds>(system_clock::now().time_since_epoch())
          .count();
  static const uint64_t f = time;
  return time - f;
}

void Scene::serialize(){
    NJSONOutputArchive json_archive;
    
    entt::basic_snapshot{this->sceneRegistry}.get<entt::entity>(json_archive);//.get<Transform>(json_archive);//.get<MeshRenderer>(json_archive);
    entt::basic_snapshot{this->sceneRegistry}.get<Transform>(json_archive);
    LOG(toString(systemManager->systemsSerialize.size()), 3);
    for(auto system : systemManager->systemsSerialize){
        system(this, json_archive);
    }
    json_archive.Close();
    std::string json_output = json_archive.AsString();
    std::cout<<"JSON: "<<json_output<<std::endl;
    std::ofstream outfile("Resources/newAr.json");
    outfile << json_output << std::endl;
    outfile.close();
}

/*
void Scene::serialize() {
  NJSONOutputArchive json_archive;

  entt::basic_snapshot{this->sceneRegistry}.get<entt::entity>(json_archive);
  entt::basic_snapshot{this->sceneRegistry}.get<Transform>(json_archive);
  json_archive.Close();
  std::string json_output = json_archive.AsString();
  printf("json:%s", json_output.c_str());
}*/

void Scene::deserialize(){
    NJSONInputArchive json_in(ReadFile("Resources/ar.json"));
    entt::basic_snapshot_loader{this->sceneRegistry}.get<entt::entity>(json_in);
    for(auto system : systemManager->systemsDeserialize){
        system(this, json_in);
    }
    //.component<Tower, Walker, Transform>(json_in);
}


//void Scene::deserialize() {}

Entity *Scene::createEntity(String name, Entity *parent) {
  Entity *entity = new Entity(sceneRegistry.create(), this, name);
  entities.push_back(entity);

  entity->addComponent<Properties>(name.c_str());
  entity->parent = parent;
  if (parent != nullptr)
    parent->children.push_back(entity);
  return entity;
}

GameObject *Scene::createGameObject(String name, Entity *parent) {
  GameObject *entity = new GameObject(sceneRegistry.create(), this, name);

  entities.push_back(entity);

  entity->addComponent<Properties>(name.c_str());
  entity->parent = parent;
  if (parent != nullptr)
    parent->children.push_back(entity);

  auto &transform = entity->addComponent<Transform>();
  entity->transform = &transform;

  if (entity->scene == nullptr) {
    LOG("Entity has no scene", 2);
    throw std::runtime_error("Entity has no scene");
  }

  if (parent)
    transform.parent = &parent->getComponent<Transform>();

  return entity;
}

Entity *Scene::getEntityById(uint id) {
  for (auto *entity : entities)
    if (entity->getID() == id)
      return entity;

  return nullptr;
}

Scene::Scene() {
  systemManager = new SystemManager();
  systemManager->scene = this;
  loadedScenes.push_back(this);
}

Scene::~Scene() {
  for (Entity *e : this->entities)
    delete e;
  //TODO: research this shit
  //delete this->systemManager;
}

void Scene::start() {
  if (this->started)
    return;

  deltaTime = timeMillisec();
  systemManager->start();

  this->started = true;
}

void Scene::update() { LOG_FUNCTION();
  static uint64 previousTime = deltaTime;
  uint64 now = timeMillisec();
  deltaTime = (now - previousTime) / 1000.f;
  previousTime = now;

  for (auto a : EventStack::getEvents<WindowApi::WindowResizedEvent>()) {
    Renderer::setViewport(0, 0, a->data.width, a->data.height);
  }

  systemManager->update();
  // std::cout<<"why is "<<toDelete.size()<<" elements here\n";
  for (Entity *entity : toDelete)
    this->sceneRegistry.destroy(entity->entity);
  toDelete.clear();
}

void Scene::render() {
  LOG_FUNCTION();
  auto camerasGroup = sceneRegistry.view<Camera, Transform>();
  auto meshesGroup = sceneRegistry.view<Mesh, Transform>();
  auto spritesGroup = sceneRegistry.view<Sprite, Transform>();

  for (auto cameraID : camerasGroup) {
    LOG_SCOPE("Processing camera view");
    auto &cam = camerasGroup.get<Camera>(cameraID);

    cam.updateView();

    for (auto &entity : meshesGroup) {
      LOG_SCOPE("Rendering mesh");

      auto &mesh = meshesGroup.get<Mesh>(entity);
      auto transform = meshesGroup.get<Transform>(entity);

      Renderer::renderMesh(mesh, transform);
    }

    for (auto &entity : spritesGroup) {
      auto &transform = spritesGroup.get<Transform>(entity);
      auto &sprite = spritesGroup.get<Sprite>(entity);

      Renderer::drawQuad2D(sprite.material.textures[0].get(), &transform,
                           sprite.material.shader.get(), &cam,
                           sprite.texCoords);
    }
  }
}
} // namespace PetrolEngine
