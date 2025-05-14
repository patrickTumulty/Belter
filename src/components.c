
#include "components.h"
#include "pray_component.h"
#include "pray_default_components.h"

void registerComponents()
{
    prayRegisterDefaultComponents();

    registerComponent(Player, nullptr, nullptr);
    registerComponent(Shape2D, nullptr, nullptr);
    registerComponent(PhysicsBody, nullptr, nullptr);
    registerComponent(Collider2D, nullptr, nullptr);
}
