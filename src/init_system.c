
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


static void start()
{
    type_id cids[] = {
        typeid(PhysicsBody),
        typeid(Shape2D),
        typeid(Transform2D),
        typeid(Collider2D),
    };

    Entity *entity = prayEntityNew(cids, 4);

    Transform2D *transform = getComponent(entity, Transform2D);
    transform->position.y = 0;
    transform->position.x = 0;

    Shape2D *shape2D = getComponent(entity, Shape2D);
    shape2D->color = RED;
    shape2D->shape = SHAPE_RECTANGLE;
    shape2D->rectangle.height = 20;
    shape2D->rectangle.width = 20;

    PhysicsBody *physicsBody = getComponent(entity, PhysicsBody);

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.position = (b2Vec2) {
        .x = transform->position.x,
        .y = transform->position.y,
    };
    bodyDef.type = b2_dynamicBody;
    physicsBody->bodyId = b2CreateBody(phyiscsGetWorldID(), &bodyDef);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    b2Polygon boxPolygon = b2MakeBox(shape2D->rectangle.width * 0.5f,
                                     shape2D->rectangle.height * 0.5f);
    b2CreatePolygonShape(physicsBody->bodyId, &shapeDef, &boxPolygon);

    Collider2D *collider = getComponent(entity, Collider2D);
    collider->shape = SHAPE_RECTANGLE;
    collider->rectangle.height = 20;
    collider->rectangle.width = 20;
    prayEntityRegister(entity);

    // Ground
    entity = prayEntityNew(cids, 4);
    transform = getComponent(entity, Transform2D);
    transform->position.y = 100;
    transform->position.x = 100;
    shape2D = getComponent(entity, Shape2D);
    shape2D->color = BLACK;
    shape2D->shape = SHAPE_RECTANGLE;
    shape2D->rectangle.height = 40;
    shape2D->rectangle.width = 2000;
    physicsBody = getComponent(entity, PhysicsBody);

    bodyDef = b2DefaultBodyDef();
    bodyDef.position = (b2Vec2) {
        .x = transform->position.x,
        .y = transform->position.y,
    };
    bodyDef.type = b2_staticBody;
    physicsBody->bodyId = b2CreateBody(phyiscsGetWorldID(), &bodyDef);
    shapeDef = b2DefaultShapeDef();
    boxPolygon = b2MakeBox(shape2D->rectangle.width * 0.5f,
                           shape2D->rectangle.height * 0.5f);
    b2CreatePolygonShape(physicsBody->bodyId, &shapeDef, &boxPolygon);

    collider = getComponent(entity, Collider2D);
    collider->shape = SHAPE_RECTANGLE;
    collider->rectangle.height = 40;
    collider->rectangle.width = 2000;
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
