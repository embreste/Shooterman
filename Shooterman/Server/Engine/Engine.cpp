#include "Engine.h"

Engine::Engine() :
  mInputSystem(InputSystem()),
  mEntityManager(EntityManager()),
  mRenderComponentManager(ComponentManager<RenderComponent>()),
  mVelocityComponentManager(ComponentManager<VelocityComponent>()),
  mSolidComponentManager(ComponentManager<SolidComponent>()),
  mCollisionSystem(CollisionSystem(&mRenderComponentManager, &mSolidComponentManager, &mVelocityComponentManager)),
  mMovementSystem(MovementSystem(&mVelocityComponentManager, &mRenderComponentManager, &mCollisionSystem, &mEntityManager)),
  mRenderSystem(RenderSystem(&mRenderComponentManager))
{
  mInputSystem.attach(&mMovementSystem);
}

Engine::~Engine() {
}

void Engine::update() {
  mInputSystem.handleInput();
  mMovementSystem.ownUpdate();

  mRenderSystem.render();
}

InputSystem* Engine::getInputSystem() {
  return &mInputSystem;
}

MovementSystem* Engine::getMovementSystem() {
  return &mMovementSystem;
}

EntityManager* Engine::getEntityManager() {
  return &mEntityManager;
}

Entity* Engine::createPlayer(float xStartPos, float yStartPos, float xMaxVelocity, float yMaxVelocity, float maxHealth) {
  Entity* player = mEntityManager.createEntity();
  VelocityComponent* vc = mVelocityComponentManager.addComponent(player->id);
  vc->currentVelocity.x = 0;
  vc->currentVelocity.y = 0;
  vc->maxVelocity.x = xMaxVelocity;
  vc->maxVelocity.y = yMaxVelocity;
  vc->moveOnce = true;

  mSolidComponentManager.addComponent(player->id);

  RenderComponent* rc = mRenderComponentManager.addComponent(player->id);
  rc->texture = sf::Texture();
  if (!Collision::CreateTextureAndBitmask(rc->texture, "Client/Resources/Sprites/Player.png")) {
    std::cout << "[SERVER: ENGINE] ERROR could not load file " << "Client/Resources/Sprites/Player.png" << std::endl;
  }
  rc->visible = true;
  rc->sprite.setPosition(xStartPos, yStartPos);
  rc->sprite.setTexture(rc->texture);
  rc->textureId = 33;
  return player;
}

Entity* Engine::createBall(float xStartPos, float yStartPos, float xMaxVelocity, float yMaxVelocity) {
  Entity* ball = mEntityManager.createEntity();
  VelocityComponent* vc = mVelocityComponentManager.addComponent(ball->id);
  vc->currentVelocity.x = 0;
  vc->currentVelocity.y = 0;
  vc->maxVelocity.x = xMaxVelocity;
  vc->maxVelocity.y = yMaxVelocity;
  vc->moveOnce = false;

  mSolidComponentManager.addComponent(ball->id);

  RenderComponent* rc = mRenderComponentManager.addComponent(ball->id);
  rc->texture = sf::Texture();
  if (!Collision::CreateTextureAndBitmask(rc->texture, "Client/Resources/Sprites/Player.png")) {
    std::cout << "[SERVER: ENGINE] ERROR could not load file " << "Client/Resources/Sprites/Player.png" << std::endl;
  }
  rc->visible = true;
  rc->sprite.setPosition(xStartPos, yStartPos);
  rc->sprite.setTexture(rc->texture);
  rc->textureId = 33;
  return ball;
}