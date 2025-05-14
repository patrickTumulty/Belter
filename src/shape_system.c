
#include "shape_system.h"
#include "components.h"
#include "linked_list.h"
#include "pray_default_components.h"
#include "pray_entity.h"
#include "pray_entity_registry.h"
#include "pray_system.h"
#include "raylib.h"
#include <CUnit/CUError.h>


static void renderUpdate()
{
    LList shapes;
    prayEntityLookupAll(&shapes, C(CID(Shape2D)), 1);

    LNode *node = nullptr;
    LListForEach(&shapes, node)
    {
        Entity *entity = LListGetEntry(node, Entity);
        Shape2D *shape2D = getComponent(entity, Shape2D);
        Transform2D *transform = getComponent(entity, Transform2D);
        Vector2 position = {0, 0};
        float rotation = 0;
        if (transform != nullptr)
        {
            rotation = transform->rotation;
            position = transform->position;
        }
        switch (shape2D->shape)
        {
            case SHAPE_CIRCLE:
                DrawCircle((int) position.x,
                           (int) position.y,
                           shape2D->circle.radius,
                           shape2D->color);
                break;
            case SHAPE_RECTANGLE:
                Rectangle rectangle = {
                    .x = position.x - (shape2D->rectangle.width / 2),
                    .y = position.y - (shape2D->rectangle.height / 2),
                    .width = shape2D->rectangle.width,
                    .height = shape2D->rectangle.height,
                };
                DrawRectanglePro(rectangle, (Vector2) {0, 0}, rotation, shape2D->color);
                break;
        }
    }
}

void registerShapeSystem()
{
    System system = {
        .name = "Shape",
        .renderUpdateWorldSpace = renderUpdate,
    };
    praySystemsRegister(system);
}
