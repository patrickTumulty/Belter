
#include "physics_system.h"
#include "components.h"
#include "linked_list.h"
#include "pray_default_components.h"
#include "pray_entity.h"
#include "pray_entity_registry.h"
#include "pray_system.h"
#include "raylib.h"


static void gameUpdate()
{
    LList objects;
    prayEntityLookupAll(&objects, C(CID(PhysicsBody), CID(Transform2D)), 2);

    LNode *node = nullptr;
    LListForEach(&objects, node)
    {
        auto entity = LListGetEntry(node, Entity);
        auto physicsBody = getComponent(entity, PhysicsBody);
        auto transform = getComponent(entity, Transform2D);

        physicsBody->velocity.y += (physicsBody->gravity * GetFrameTime());

        transform->position.x += physicsBody->velocity.x * GetFrameTime();
        transform->position.y += physicsBody->velocity.y * GetFrameTime();

        // Need to iterate over eachother to check for collisions. But need to deal with the linked list issue
    }
}

void registerPhysicsSystem()
{
    System system = {
        .name = "physics",
        .gameUpdate = gameUpdate,
    };
    praySystemsRegister(system);
}
