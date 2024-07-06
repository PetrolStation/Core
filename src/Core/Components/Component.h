#pragma once

#include <Core/Aliases.h>
#include <type_traits>
#include "Core/EventStack.h"
#include "InspectorTypes.h"
#include "../Serializer.h"
#define Serialize
namespace PetrolEngine {
    class Transform;
    class Entity;

    class InternalComponent {
    public:
        // TODO: maybe delete it but for now i like my pointers stable
        static constexpr auto in_place_delete = true;

        Entity* entity = nullptr;
        uint32 typeId = 0;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(InternalComponent, typeId);

    class NativeComponent: public InternalComponent {
    public:

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
extern UnorderedMap<entt::id_type, std::vector<ClassExpose>> exposedElements;
/*
*/
template<class T, typename U>
[[Attr("def", "func",  "call('subject', location)")]]
void __Expose(const char* name, U T::* arg){
    entt::id_type id = entt::type_hash<T>::value();
    //if(exposedElements == nullptr) exposedElements = new UnorderedMap<int32, std::vector<ClassExpose>>();
    auto elem = exposedElements.find(entt::type_hash<T>::value());
    if(elem == exposedElements.end())
        exposedElements.emplace<entt::id_type, std::vector<ClassExpose>>(entt::type_hash<T>::value(), {});
    
    //if(exposedElement == nullptr) exposedElement = new std::vector<ClassExpose>();
    exposedElements[id].push_back({
        name,
        PetrolEngine::inspectTypeInt<U>(),
        (uint32)offsetOf(arg)
    });
}


