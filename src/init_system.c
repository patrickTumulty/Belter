
#include "init_system.h"
#include "box2d/box2d.h"
#include "box2d/collision.h"
#include "box2d/math_functions.h"
#include "box2d/types.h"
#include "common_type.h"
#include "components.h"
#include "physics_system.h"
#include "pray_default_components.h"
#include "pray_entity.h"
#include "pray_entity_registry.h"
#include "pray_system.h"
#include "raylib.h"

static void createGround()
{
    type_id cids[] = {
        typeid(PhysicsBody),
        typeid(Shape2D),
        typeid(Transform2D),
        typeid(Collider2D),
    };

    u32 cidsLen = sizeof(cids) / sizeof(type_id);

    Entity *entity = prayEntityNew(cids, cidsLen);
    auto transform = getComponent(entity, Transform2D);
    transform->position.y = 100;
    transform->position.x = 0;
    auto shape2D = getComponent(entity, Shape2D);
    shape2D->color = RAYWHITE;
    shape2D->shape = SHAPE_RECTANGLE;
    shape2D->rectangle.height = 40;
    shape2D->rectangle.width = 2000;
    auto physicsBody = getComponent(entity, PhysicsBody);

    physicsBodyCreateBox(physicsBody,
                         transform->position,
                         shape2D->rectangle.width,
                         shape2D->rectangle.height,
                         b2_staticBody, 
                         true);

    auto collider = getComponent(entity, Collider2D);
    collider->shape = SHAPE_RECTANGLE;
    collider->rectangle.height = 40;
    collider->rectangle.width = 2000;
    prayEntityRegister(entity);
}

static void start()
{
    type_id cids[] = {
        typeid(Player),
        typeid(PhysicsBody),
        typeid(Shape2D),
        typeid(Transform2D),
        typeid(Collider2D),
        typeid(CameraFocus),
    };

    u32 cidsLen = sizeof(cids) / sizeof(type_id);

    Entity *entity = prayEntityNew(cids, cidsLen);

    Transform2D *transform = getComponent(entity, Transform2D);
    transform->position.y = 0;
    transform->position.x = 0;

    Shape2D *shape2D = getComponent(entity, Shape2D);
    shape2D->color = RED;
    shape2D->shape = SHAPE_RECTANGLE;
    shape2D->rectangle.height = 20;
    shape2D->rectangle.width = 20;

    PhysicsBody *physicsBody = getComponent(entity, PhysicsBody);

    physicsBodyCreateBox(physicsBody,
                         transform->position,
                         shape2D->rectangle.width,
                         shape2D->rectangle.height,
                         b2_dynamicBody,
                         true);

    Collider2D *collider = getComponent(entity, Collider2D);
    collider->shape = SHAPE_RECTANGLE;
    collider->rectangle.height = 20;
    collider->rectangle.width = 20;
    prayEntityRegister(entity);

    createGround();
}


static void stop()
{
}

void registerInitSystem()
{
    System system = {
        .name = "init",
        .start = start,
        .stop = stop,
    };
    praySystemsRegister(system);
}
