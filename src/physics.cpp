#include "../include/physics.h"
#include <algorithm>

bool PhysicsEngine::CheckCollision(const AABB &a, const AABB &b) {
  return (a.min.x < b.max.x && a.max.x > b.min.x) &&
         (a.min.y < b.max.y && a.max.y > b.min.y);
}

void PhysicsEngine::ApplyGravity(Vector2 &velocity, float deltaTime,
                                 float gravityScale) {
  const float GRAVITY = -19.62f;
  velocity.y += GRAVITY * gravityScale * deltaTime;
}

void PhysicsEngine::ResolveCollision(Vector2 &position, Vector2 &velocity,
                                     const AABB &playerBox,
                                     const AABB &platformBox) {
  float overlapX = std::min(playerBox.max.x, platformBox.max.x) -
                   std::max(playerBox.min.x, platformBox.min.x);
  float overlapY = std::min(playerBox.max.y, platformBox.max.y) -
                   std::max(playerBox.min.y, platformBox.min.y);

  if (overlapX < overlapY) {
    if (playerBox.min.x < platformBox.min.x) {
      position.x -= overlapX;
    } else {
      position.x += overlapX;
    }
    velocity.x = 0;
  } else {
    if (playerBox.min.y < platformBox.min.y) {
      position.y -= overlapY;
      velocity.y = 0;
    } else {
      position.y += overlapY;
      velocity.y = 0;
    }
  }
}
