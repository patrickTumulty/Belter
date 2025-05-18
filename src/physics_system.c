
#include "physics_system.h"
#include "array_list.h"
#include "box2d/box2d.h"
#include "box2d/id.h"
#include "box2d/types.h"
#include "common_hash.h"
#include "common_type.h"
#include "components.h"
#include "linked_list.h"
#include "pray_default_components.h"
#include "pray_entity.h"
#include "pray_entity_registry.h"
#include "pray_system.h"
#include "raylib.h"
#include <bits/pthreadtypes.h>

static b2WorldId worldID;

typedef struct
{
    Entity *entity;
    Transform2D *transform;
    PhysicsBody *physicsBody;
    Collider2D *collider;
} PhysicsObject;

b2WorldId phyiscsGetWorldID()
{
    return worldID;
}

static void gameUpdate()
{
    b2World_Step(worldID, GetFrameTime(), 4);

    LList bodies;
    prayEntityLookupAll(&bodies, C(typeid(PhysicsBody), typeid(Transform2D)), 2);

    LNode *node = nullptr;
    LListForEach(&bodies, node)
    {
        Entity *entity = LListGetEntry(node, Entity);
        PhysicsBody *physicsBody = getComponent(entity, PhysicsBody);
        Transform2D *transform = getComponent(entity, Transform2D);

        b2Vec2 position = b2Body_GetWorldPoint(physicsBody->bodyId, (b2Vec2) {0, 0});
        transform->position.x = position.x;
        transform->position.y = position.y;
        b2Rot rotation = b2Body_GetRotation(physicsBody->bodyId);
        float radians = b2Rot_GetAngle(rotation);
        transform->rotation = RAD2DEG * radians;
    }
}

static void start()
{
    float lengthUnitsPerMeter = 128.0f;
    b2SetLengthUnitsPerMeter(lengthUnitsPerMeter);

    b2WorldDef worldDef = b2DefaultWorldDef();

    // Realistic gravity is achieved by multiplying gravity by the length unit.
    worldDef.gravity.y = 9.8f * lengthUnitsPerMeter;
    worldID = b2CreateWorld(&worldDef);
}

static void stop()
{
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
