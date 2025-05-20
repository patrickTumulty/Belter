
#include "components.h"
#include "box2d/box2d.h"
#include "common_type.h"
#include "pray_component.h"
#include "pray_default_components.h"
#include <stdio.h>

DEFINE_TYPE(Player);
DEFINE_TYPE(Shape2D);
DEFINE_TYPE(PhysicsBody);
DEFINE_TYPE(Collider2D);
DEFINE_TYPE(CameraFocus);
DEFINE_TYPE(Asteroid);

static void deinitPhysicsBody(void *ptr)
{
    PhysicsBody *physicsBody = ptr;

    if (!b2Body_IsValid(physicsBody->bodyId))
    {
        printf("WARN: body id not valid %d %d %d\n",
               physicsBody->bodyId.index1,
               physicsBody->bodyId.world0,
               physicsBody->bodyId.generation);
        return;
    }
    b2DestroyBody(physicsBody->bodyId);
}

void registerComponents()
{
    prayRegisterDefaultComponents();

    REGISTER_TYPE(Player);
    registerComponent(Player, nullptr, nullptr);

    REGISTER_TYPE(Shape2D);
    registerComponent(Shape2D, nullptr, nullptr);

    REGISTER_TYPE(PhysicsBody);
    registerComponent(PhysicsBody, nullptr, deinitPhysicsBody);

    REGISTER_TYPE(Collider2D);
    registerComponent(Collider2D, nullptr, nullptr);

    REGISTER_TYPE(CameraFocus);
    registerComponent(CameraFocus, nullptr, nullptr);

    REGISTER_TYPE(Asteroid);
    registerComponent(Asteroid, nullptr, nullptr);
}
