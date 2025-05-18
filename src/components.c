
#include "components.h"
#include "common_type.h"
#include "pray_component.h"
#include "pray_default_components.h"

DEFINE_TYPE(Player);
DEFINE_TYPE(Shape2D);
DEFINE_TYPE(PhysicsBody);
DEFINE_TYPE(Collider2D);

void registerComponents()
{
    prayRegisterDefaultComponents();

    REGISTER_TYPE(Player);
    registerComponent(Player, nullptr, nullptr);

    REGISTER_TYPE(Shape2D);
    registerComponent(Shape2D, nullptr, nullptr);

    REGISTER_TYPE(PhysicsBody);
    registerComponent(PhysicsBody, nullptr, nullptr);

    REGISTER_TYPE(Collider2D);
    registerComponent(Collider2D, nullptr, nullptr);
}
