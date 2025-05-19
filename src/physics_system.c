
#include "physics_system.h"
#include "array_list.h"
#include "box2d/box2d.h"
#include "box2d/collision.h"
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

b2WorldId phyiscsGetWorldID()
{
    return worldID;
}

void physicsBodyCreateBox(PhysicsBody *physicsBody,
                          Vector2 position,
                          float width,
                          float height,
                          b2BodyType bodyType, 
                          bool fixedRotation)
{
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.position = (b2Vec2) {
        .x = position.x,
        .y = position.y,
    };
    bodyDef.type = bodyType;
    bodyDef.fixedRotation = fixedRotation;
    physicsBody->bodyId = b2CreateBody(phyiscsGetWorldID(), &bodyDef);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f / 40.0f;
    b2Polygon boxPolygon = b2MakeBox(width * 0.5f, height * 0.5f);
    b2CreatePolygonShape(physicsBody->bodyId, &shapeDef, &boxPolygon);
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
    float lengthUnitsPerMeter = 20.0f;
    b2SetLengthUnitsPerMeter(lengthUnitsPerMeter);

    b2WorldDef worldDef = b2DefaultWorldDef();

    // Realistic gravity is achieved by multiplying gravity by the length unit.
    worldDef.gravity.y = 9.8f * lengthUnitsPerMeter;
    worldID = b2CreateWorld(&worldDef);
}

static void stop()
{
    b2DestroyWorld(worldID);
}

static void renderUpdate()
{
    // LList bodies;
    // prayEntityLookupAll(&bodies, C(typeid(PhysicsBody)), 1);
    //
    // LNode *node = nullptr;
    // LListForEach(&bodies, node)
    // {
    //     Entity *entity = LListGetEntry(node, Entity);
    //     PhysicsBody *physicsBody = getComponent(entity, PhysicsBody);
    //     b2Vec2 position = b2Body_GetWorldPoint(physicsBody->bodyId, (b2Vec2) {0, 0});
    //     DrawCircle((int) position.x, (int) position.y, 10, BLUE);
    // }
}

void registerPhysicsSystem()
{
    System system = {
        .name = "physics",
        .start = start,
        .stop = stop,
        .gameUpdate = gameUpdate,
        .renderUpdateWorldSpace = renderUpdate,
    };
    praySystemsRegister(system);
}
