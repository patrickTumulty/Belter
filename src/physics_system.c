
#include "physics_system.h"
#include "array_list.h"
#include "components.h"
#include "linked_list.h"
#include "pray_default_components.h"
#include "pray_entity.h"
#include "pray_entity_registry.h"
#include "pray_system.h"
#include "raylib.h"
#include <bits/pthreadtypes.h>

typedef struct
{
    Entity *entity;
    Transform2D *transform;
    PhysicsBody *physicsBody;
    Collider2D *collider;
} PhysicsObject;

static AList physicsBodyEntities;

static void gameUpdate()
{
    LList objects;
    prayEntityLookupAll(&objects, C(typeid(PhysicsBody), typeid(Transform2D), typeid(Collider2D)), 3);
    int count = 0;

    if (objects.size > physicsBodyEntities.length)
    {
        alistResize(&physicsBodyEntities, objects.size);
    }

    LNode *node = nullptr;
    LListForEach(&objects, node)
    {
        auto entity = LListGetEntry(node, Entity);
        auto physicsBody = getComponent(entity, PhysicsBody);
        auto transform = getComponent(entity, Transform2D);
        auto collider = getComponent(entity, Collider2D);

        PhysicsObject *object = alistGet(&physicsBodyEntities, count++);
        object->entity = entity;
        object->physicsBody = physicsBody;
        object->transform = transform;
        object->collider = collider;
    }

    for (int i = 0; i < count; i++)
    {
        PhysicsObject *objA = alistGet(&physicsBodyEntities, i);

        objA->physicsBody->velocity.y += (objA->physicsBody->gravity * GetFrameTime());
        objA->transform->position.x += objA->physicsBody->velocity.x * GetFrameTime();
        objA->transform->position.y += objA->physicsBody->velocity.y * GetFrameTime();

        for (int j = 0; j < count; j++)
        {
            PhysicsObject *objB = alistGet(&physicsBodyEntities, j);

            // if (CheckCollisionRecs(, Rectangle rec2)) 
        }
    }

}

static void start()
{
    alistNew(&physicsBodyEntities, 10, sizeof(PhysicsObject));
}

static void stop()
{
    alistFree(&physicsBodyEntities);
}

void registerPhysicsSystem()
{
    System system = {
        .name = "physics",
        .start = start,
        .stop = stop,
        .gameUpdate = gameUpdate,
    };
    praySystemsRegister(system);
}
