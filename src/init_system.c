
#include "init_system.h"
#include "box2d/box2d.h"
#include "box2d/math_functions.h"
#include "box2d/types.h"
#include "common_type.h"
#include "components.h"
#include "physics_system.h"
#include "pray_component.h"
#include "pray_default_components.h"
#include "pray_entity.h"
#include "pray_entity_registry.h"
#include "pray_system.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getRandomRange(int min, int max)
{
    return (int) (min + (random() % (max - min + 1)));
}

Vector2 getRandomPosition(int xMin, int xMax, int yMin, int yMax)
{
    float x = (float) getRandomRange(xMin, xMax);
    float y = (float) getRandomRange(yMin, yMax);
    return (Vector2) {x, y};
}

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

static void createAsteroid(Vector2 position, float height, float width)
{
    type_id cids[] = {
        typeid(Asteroid),
        typeid(PhysicsBody),
        typeid(Shape2D),
        typeid(Transform2D),
    };

    u32 cidsLen = sizeof(cids) / sizeof(type_id);
    Entity *entity = prayEntityNew(cids, cidsLen);
    auto transform = getComponent(entity, Transform2D);
    auto shape2D = getComponent(entity, Shape2D);
    auto physicsBody = getComponent(entity, PhysicsBody);

    transform->position = position;

    shape2D->color = PURPLE;
    shape2D->shape = SHAPE_RECTANGLE;
    shape2D->rectangle.height = height;
    shape2D->rectangle.width = width;

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.position = (b2Vec2) {
        .x = position.x,
        .y = position.y,
    };
    bodyDef.type = b2_dynamicBody;
    bodyDef.gravityScale = 0;
    int radians = getRandomRange(0, (int)((2.0f * PI) * 1000.0f));
    bodyDef.rotation = b2MakeRot(((float) radians) * 0.001f);
    physicsBody->bodyId = b2CreateBody(phyiscsGetWorldID(), &bodyDef);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    // shapeDef.density = 1.0f / 40.0f;
    b2Polygon boxPolygon = b2MakeBox(width * 0.5f, height * 0.5f);
    b2CreatePolygonShape(physicsBody->bodyId, &shapeDef, &boxPolygon);
    b2Body_SetGravityScale(physicsBody->bodyId, 0);

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

    srand((unsigned) time(nullptr));

    for (int i = 0; i < 20; i++)
    {
        Vector2 pos = getRandomPosition(-1000, 1000, -500, 50);
        float width = (float) getRandomRange(10, 100);
        float height = (float) getRandomRange(10, 100);
        // printf("%.2f,%.2f w=%.2f h=%.2f\n", pos.x, pos.y, width, height);
        createAsteroid(pos, height, width);
    }
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
