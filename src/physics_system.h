
#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "box2d/id.h"
#include "box2d/types.h"
#include "components.h"
#include "raylib.h"


b2WorldId phyiscsGetWorldID();

void physicsBodyCreateBox(PhysicsBody *physicsBody,
                          Vector2 position,
                          float width,
                          float height,
                          b2BodyType bodyType,
                          bool fixedRotation);

void registerPhysicsSystem();

#endif // PHYSICS_SYSTEM_H
