
#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "pray_component.h"
#include "pray_default_components.h"
#include "raylib.h"

#ifdef COMPONENT_OFFSET
#undef COMPONENT_OFFSET
#endif
#define COMPONENT_OFFSET COMPONENT_BANK_A

typedef struct
{
    float velocity;
} Player;

REGISTER_CID(Player);

typedef enum : u8
{
    SHAPE_CIRCLE,
    SHAPE_RECTANGLE
} ShapePrimitive;

typedef struct
{
    float width;
    float height;
} ShapeRectangle;

typedef struct
{
    float radius;
} ShapeCircle;

typedef struct
{
    ShapePrimitive shape;
    union
    {
        ShapeCircle circle;
        ShapeRectangle rectangle;
    };
    Color color;
} Shape2D;

REGISTER_CID(Shape2D);

typedef struct
{
    Vector2 velocity;
    float gravity;
    float mass;
} PhysicsBody;

REGISTER_CID(PhysicsBody);

typedef struct
{
    ShapePrimitive shape;
    union {
        ShapeCircle circle;
        ShapeRectangle rectangle;
    };
} Collider2D;

REGISTER_CID(Collider2D);

void registerComponents();

#endif // COMPONENTS_H
