#pragma once

struct Vector2 {
  float x, y;
};

struct AABB {
  Vector2 min;
  Vector2 max;
};

class PhysicsEngine {
public:
  static bool CheckCollision(const AABB &a, const AABB &b);
  static void ApplyGravity(Vector2 &velocity, float deltaTime,
                           float gravityScale = 1.0f);
  static void ResolveCollision(Vector2 &position, Vector2 &velocity,
                               const AABB &playerBox, const AABB &platformBox);
};
