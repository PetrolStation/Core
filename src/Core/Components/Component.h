#pragma once

#include "Core/Aliases.h"
#include <Core/Aliases.h>

namespace PetrolEngine {
    class Transform;
    class Entity;

    enum InspectorType{
        Float, Float2, Float3, Float4,
        Int, Int2, Int3, Int4,
        Text
    };

    using InspectorTypes = UnorderedMap<String, Pair<InspectorType, uint>>;

    class InternalComponent {
    public:
        virtual const InspectorTypes inspectorTypes() {return {};};

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
