
#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "common_type.h"
#include "raylib.h"
#include <sys/types.h>


typedef struct
{
    float velocity;
} Player;

DECLARE_TYPE(Player);

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

DECLARE_TYPE(Shape2D);

typedef struct
{
    Vector2 velocity;
    float gravity;
    float mass;
} PhysicsBody;

DECLARE_TYPE(PhysicsBody);

typedef struct
{
    ShapePrimitive shape;
    union {
        ShapeCircle circle;
        ShapeRectangle rectangle;
    };
} Collider2D;

DECLARE_TYPE(Collider2D);

void registerComponents();

#endif // COMPONENTS_H
