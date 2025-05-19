
#include "player_controller_system.h"
#include "box2d/box2d.h"
#include "box2d/math_functions.h"
#include "common_hash.h"
#include "components.h"
#include "pray_default_components.h"
#include "pray_entity.h"
#include "pray_entity_registry.h"
#include "pray_system.h"
#include "raylib.h"
#include "tmem.h"
#include <stdio.h>

const float leftStickDeadzoneX = 0.1f;
const float leftStickDeadzoneY = 0.1f;
const float rightStickDeadzoneX = 0.1f;
const float rightStickDeadzoneY = 0.1f;
const float leftTriggerDeadzone = -0.9f;
const float rightTriggerDeadzone = -0.9f;

static int gamepad = 0;

static void gameUpdate()
{
    Entity *entity = prayEntityLookup(C(typeid(Player)), 1);

    PhysicsBody *physicsBody = getComponent(entity, PhysicsBody);
    Transform2D *transform = getComponent(entity, Transform2D);

    SetGamepadMappings("");

    if (IsGamepadAvailable(gamepad))
    {
        if (IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
        {

            float mass = b2Body_GetMass(physicsBody->bodyId);
            b2Vec2 force = {.x = 0, .y = -200.0f * mass};
            // b2Vec2 point = {.x = transform->position.x, .y = transform->position.y};
            b2Vec2 velocity = b2Body_GetLinearVelocity(physicsBody->bodyId);
            velocity.y = 10000;
            // velocity.x = 0;
            // b2Body_SetLinearVelocity(physicsBody->bodyId, velocity);

            // b2Body_ApplyForce(physicsBody->bodyId, force, (b2Vec2) {0, 0}, true);
            b2Body_ApplyLinearImpulseToCenter(physicsBody->bodyId, force, true);
            // b2Body_ApplyForceToCenter(physicsBody->bodyId, force, true);
        }

        // Get axis values
        float leftStickX = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X);
        float leftStickY = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y);
        float rightStickX = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X);
        float rightStickY = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y);
        float leftTrigger = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_TRIGGER);
        float rightTrigger = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_TRIGGER);

        // Calculate deadzones
        if (leftStickX > -leftStickDeadzoneX && leftStickX < leftStickDeadzoneX)
        {
            leftStickX = 0.0f;
        }

        if (leftStickY > -leftStickDeadzoneY && leftStickY < leftStickDeadzoneY)
        {
            leftStickY = 0.0f;
        }

        if (rightStickX > -rightStickDeadzoneX && rightStickX < rightStickDeadzoneX)
        {
            rightStickX = 0.0f;
        }

        if (rightStickY > -rightStickDeadzoneY && rightStickY < rightStickDeadzoneY)
        {
            rightStickY = 0.0f;
        }

        if (leftTrigger < leftTriggerDeadzone)
        {
            leftTrigger = -1.0f;
        }

        if (rightTrigger < rightTriggerDeadzone)
        {
            rightTrigger = -1.0f;
        }


        // float mass = b2Body_GetMass(physicsBody->bodyId);
        b2Vec2 force = {.x = 2000 * leftStickX, .y = 0};
        // b2Vec2 point = {.x = transform->position.x, .y = transform->position.y};
        // b2Vec2 velocity = b2Body_GetLinearVelocity(physicsBody->bodyId);
        // velocity.y = 10000;
        // velocity.x = 0;
        // b2Body_SetLinearVelocity(physicsBody->bodyId, velocity);

        b2Body_ApplyForceToCenter(physicsBody->bodyId, force, true);

        float maxSpeed = 200.0f;
        b2Vec2 velocity = b2Body_GetLinearVelocity(physicsBody->bodyId);

        float speed = b2Length(velocity);
        if (speed > maxSpeed)
        {
            float scale = maxSpeed / speed;
            velocity.x *= scale;
            velocity.y *= scale;
            b2Body_SetLinearVelocity(physicsBody->bodyId, velocity);
        }
    }
}

static void start()
{
    char *buffer = nullptr;
    u64 length = 0;
    FILE *f = fopen("./runtime/gamecontrollerdb.txt", "rb");
    if (f == nullptr)
    {
        printf("unable to open file\n");
        return;
    }

    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);

    buffer = tmemcalloc(1, length);
    if (buffer != nullptr)
    {
        fread(buffer, 1, length, f);
        SetGamepadMappings(buffer);
        tmemfree(buffer);
    }
    fclose(f);
}

void registerPlayerControllerSystem()
{
    System system = {
        .name = "Player Controller",
        .start = start,
        .gameUpdate = gameUpdate,
    };
    praySystemsRegister(system);
}
