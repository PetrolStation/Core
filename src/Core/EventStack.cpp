#include "../PCH.h"
#include "EventStack.h"

namespace PetrolEngine {
    const Vector<Event*> EventStack::emptyEventList = {};

    std::unordered_map<entt::id_type, Vector<Event*>> EventStack::events;
    std::unordered_map<entt::id_type, Vector<void(*)(Event*)>> EventStack::callbacks;
    std::mutex EventStack::eventLock;
}
