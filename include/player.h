#pragma once
#include "physics.h"

enum class PlayerState { IDLE, RUNNING, JUMPING, WALL_RUNNING, SLIDING };

class Player {
private:
  Vector2 position;
  Vector2 velocity;
  PlayerState currentState;
  float momentum;
  bool isGrounded;

public:
  Player();
  void HandleInput(bool moveLeft, bool moveRight, bool jumpPressed,
                   bool slidePressed, bool nearWall);
  void Update(float deltaTime, const AABB &platformBox);

  Vector2 GetPosition() const { return position; }
  PlayerState GetState() const { return currentState; }
  float GetMomentum() const { return momentum; }
  AABB GetAABB() const;
};
