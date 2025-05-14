
#include "init_system.h"
#include "components.h"
#include "pray_default_components.h"
#include "pray_entity.h"
#include "pray_entity_registry.h"
#include "pray_system.h"
#include "raylib.h"


static void start()
{
    cid cids[] = {
        CID(PhysicsBody),
        CID(Shape2D),
        CID(Transform2D),
        CID(Collider2D)};

    Entity *entity = prayEntityNew(cids, 4);
    Shape2D *shape2D = getComponent(entity, Shape2D);
    shape2D->color = RED;
    shape2D->shape = SHAPE_RECTANGLE;
    shape2D->rectangle.height = 20;
    shape2D->rectangle.width = 20;
    PhysicsBody *physicsBody = getComponent(entity, PhysicsBody);
    physicsBody->mass = 1;
    physicsBody->gravity = 9.81f;
    physicsBody->velocity = (Vector2) {0, 0};
    Collider2D *collider = getComponent(entity, Collider2D);
    collider->shape = SHAPE_RECTANGLE;
    collider->rectangle.height = 20;
    collider->rectangle.width = 20;
    Transform2D *transform = getComponent(entity, Transform2D);
    transform->position.y = 0;
    transform->position.x = 100;
    prayEntityRegister(entity);

    // Ground
    entity = prayEntityNew(cids, 4);
    shape2D = getComponent(entity, Shape2D);
    shape2D->color = BLACK;
    shape2D->shape = SHAPE_RECTANGLE;
    shape2D->rectangle.height = 40;
    shape2D->rectangle.width = 2000;
    physicsBody = getComponent(entity, PhysicsBody);
    physicsBody->mass = 1;
    physicsBody->gravity = 0;
    physicsBody->velocity = (Vector2) {0, 0};
    collider = getComponent(entity, Collider2D);
    collider->shape = SHAPE_RECTANGLE;
    collider->rectangle.height = 40;
    collider->rectangle.width = 2000;
    transform = getComponent(entity, Transform2D);
    transform->position.y = 100;
    transform->position.x = 100;
    prayEntityRegister(entity);
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
