#ifndef RIGID_OBJECT_H
#define RIGID_OBJECT_H

typedef struct {
  double altitude; // meters
  double velocity; // meters per second
  double mass;     // kilograms
  double gravity;  // meters per second squared
} RigidObject;

#endif // RIGID_OBJECT_H