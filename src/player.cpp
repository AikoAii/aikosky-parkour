#include "player.h"
#include <algorithm>

Player::Player()
    : position{0.0f, 0.0f}, velocity{0.0f, 0.0f},
      currentState(PlayerState::IDLE), momentum(1.0f), isGrounded(false) {}

AABB Player::GetAABB() const {
  float height = (currentState == PlayerState::SLIDING) ? 0.5f : 1.8f;
  return AABB{{position.x - 0.4f, position.y},
              {position.x + 0.4f, position.y + height}};
}

void Player::HandleInput(bool moveLeft, bool moveRight, bool jumpPressed,
                         bool slidePressed, bool nearWall) {
  const float BASE_SPEED = 5.0f;
  float currentSpeed = BASE_SPEED * momentum;

  if (moveLeft)
    velocity.x = -currentSpeed;
  else if (moveRight)
    velocity.x = currentSpeed;
  else
    velocity.x = 0.0f;

  switch (currentState) {
  case PlayerState::IDLE:
    if (velocity.x != 0)
      currentState = PlayerState::RUNNING;
    if (jumpPressed && isGrounded) {
      velocity.y = 8.0f;
      currentState = PlayerState::JUMPING;
      isGrounded = false;
    }
    break;

  case PlayerState::RUNNING:
    if (velocity.x == 0)
      currentState = PlayerState::IDLE;
    if (jumpPressed && isGrounded) {
      velocity.y = 8.0f;
      currentState = PlayerState::JUMPING;
      isGrounded = false;
    }
    if (slidePressed) {
      currentState = PlayerState::SLIDING;
      momentum += 0.2f;
    }
    break;

  case PlayerState::JUMPING:
    if (isGrounded)
      currentState = PlayerState::RUNNING;
    if (nearWall && velocity.y < 0) {
      currentState = PlayerState::WALL_RUNNING;
      velocity.y = 1.5f;
    }
    break;

  case PlayerState::WALL_RUNNING:
    if (!nearWall || isGrounded)
      currentState = PlayerState::IDLE;
    if (jumpPressed) {
      velocity.y = 7.0f;
      velocity.x = (velocity.x > 0) ? -5.0f : 5.0f;
      momentum += 0.3f;
      currentState = PlayerState::JUMPING;
    }
    break;

  case PlayerState::SLIDING:
    if (!slidePressed || std::abs(velocity.x) < 1.0f) {
      currentState = PlayerState::RUNNING;
    }
    break;
  }
}

void Player::Update(float deltaTime, const AABB &platformBox) {
  float gravityScale =
      (currentState == PlayerState::WALL_RUNNING) ? 0.2f : 1.0f;
  PhysicsEngine::ApplyGravity(velocity, deltaTime, gravityScale);

  position.x += velocity.x * deltaTime;
  position.y += velocity.y * deltaTime;

  AABB playerBox = GetAABB();
  if (PhysicsEngine::CheckCollision(playerBox, platformBox)) {
    PhysicsEngine::ResolveCollision(position, velocity, playerBox, platformBox);
    if (position.y >= platformBox.max.y) {
      isGrounded = true;
    }
  } else {
    isGrounded = false;
  }

  if (currentState == PlayerState::IDLE) {
    momentum = std::max(1.0f, momentum - deltaTime * 2.0f);
  }
}
