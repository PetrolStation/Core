#pragma once

#include "Core/Aliases.h"

namespace PetrolEngine {
    class Transform;
    class Entity;

    class InternalComponent {
    public:
        // TODO: maybe delete it but for now i like my pointers stable
        static constexpr auto in_place_delete = true;
        Entity* entity = nullptr;
    };

    class NativeComponent: public InternalComponent {
    public:
        uint64 typeId = 0;
    };

    class Component: public InternalComponent {
    public:
        Transform* transform = nullptr;

        virtual void onStart()  {};
        virtual void onUpdate() {};

        // function used in debug mode to check if entity has required components
        virtual void preValidate() {};
        Component() = default;
        virtual ~Component() {};
    };
}
