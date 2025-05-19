
#include "camera_system.h"
#include "common_hash.h"
#include "common_type.h"
#include "components.h"
#include "pray_camera.h"
#include "pray_default_components.h"
#include "pray_entity.h"
#include "pray_entity_registry.h"
#include "pray_system.h"
#include "raylib.h"
#include <stdio.h>

static Vector2 cameraTarget;
static const float SCREEN_HEIGHT = 500.0f;
static const float SCREEN_WIDTH = 500.0f;

Vector2 getScreenCenter()
{
    return (Vector2) {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
}

void start()
{
    Camera2D *camera = prayGetCamera();

    cameraTarget = getScreenCenter();
    camera->target = (Vector2) {0, 0};
    camera->offset = (Vector2) {0, 0};
    camera->rotation = 0.0f;
    camera->zoom = 3.0f;
}

void close()
{
}


void gameUpdate()
{
    Camera2D *camera = prayGetCamera();

    Entity *entity = prayEntityLookup(C(typeid(CameraFocus), typeid(Transform2D)), 2);
    if (entity == nullptr)
    {
        return;
    }

    float width = (float) GetScreenWidth();
    float height = (float) GetScreenHeight();

    float marginX = width * 0.25f;
    float marginY = height * 0.25f;

    Transform2D *transform = getComponent(entity, Transform2D);

    Vector2 focusPosition = GetWorldToScreen2D(transform->position, *camera);

    float speed = 1.8f;

    if (focusPosition.x < marginX)
    {
        camera->target.x -= speed;
    }
    else if (focusPosition.x > (width - marginX))
    {
        camera->target.x += speed;
    }

    if (focusPosition.y < marginY)
    {
        camera->target.y -= speed;
    }
    else if (focusPosition.y > (height - marginY))
    {
        camera->target.y += speed;
    }

    camera->offset = (Vector2) {
        width * 0.5f,
        (height * 0.5f) + 600,
    };
}

void registerCameraSystem()
{
    System cameraSystem = {
        .name = "Camera System",
        .start = start,
        .stop = close,
        .gameUpdate = gameUpdate,
    };

    praySystemsRegister(cameraSystem);
}
