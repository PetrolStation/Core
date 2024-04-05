#pragma once

#include "Core/Aliases.h"
#include "glm/detail/qualifier.hpp"
#include <PCH.h>
#include <unordered_map>
#include <unordered_set>

#define Attr(...)
#define MacroAttr(...)
#define AttributeSum
#define Expose

//MacroAttr("dec", "#include <cstdint>")
//MacroAttr("dec", "#include <unordered_map>")
//MacroAttr("dec", "#include <vector>")
//MacroAttr("dec", "struct ClassExpose{const char* name;std::uint32_t type;std::uint32_t offset;};")
//MacroAttr("dec", "extern const std::unordered_map<std::uint32_t, std::vector<ClassExpose>> ExposedElements;")
//MacroAttr("global", "sum", "subject")
//#define __Expose(...) const std::unordered_map<std::uint32_t, std::vector<ClassExpose>> ExposedElements = _Expose(__VA_ARGS__);

struct ClassExpose{
    const char* name;
    std::uint32_t type;
    std::uint32_t offset;
    //int a;
};

namespace PetrolEngine{
 
    class Component;
    class Entity;

    enum class InspectorType: uint8 {
        //  n=11+1=4   typeId
        //     --     ------
        // 0b  11      010101
        Float     = 0b00000001,
        Float2    = 0b01000001,
        Float3    = 0b10000001,
        Float4    = 0b11000001,
        Double    = 0b00000010,
        Int       = 0b00000011,
        Int2      = 0b01000011,
        Int3      = 0b10000011,
        Int4      = 0b11000011,
        String    = 0b00000100,
        Text      = 0b00000101,
        Bool      = 0b00000110,
        Vector    = 0b00000111,
        Component = 0b00001000, // * pointer to it
        Entity    = 0b00001001, // * pointer to it
        None      = 0b11111111
    };
    

    using InspectorTypes = UnorderedMap<String, Pair<uint32, uint>>;

    constexpr std::string_view __sp1__(std::string_view str) {
    std::string_view res;
    std::size_t start = 0, end = 0;

    for (;end != std::string_view::npos;) {
        end = std::string_view::npos;
        
        for (std::size_t j = start; j < str.length(); j++)
            if (str[j] == ':'){ end = j; break; }
        
        res = str.substr(start, end - start);
        start = end + 1;
    }

    return res;
}

    constexpr std::string_view __sp2__(std::string_view str) {
        std::string_view res;
        std::size_t start = 0, end = 0;
    
        end = std::string_view::npos;
        
        for (std::size_t j = start; j < str.length(); j++)
            if (str[j] == '>') { end = j; break; }
        
        res = str.substr(start, end - start);        
    
        return res;
    }

    #define inspect(x) std::pair<std::string, Pair<uint32, uint>>(__sp2__(__sp1__(#x)), inspectType(&x))

    template<typename T> struct is_vector : public std::false_type {typedef void type;};

    template<typename T, typename A>
    struct is_vector<std::vector<T, A>> : public std::true_type {typedef T type;};

    constexpr uint8 getTypeSize(InspectorType type){
        switch (type) {
            case InspectorType::Float : { return sizeof(  float  ); }
            case InspectorType::Float2: { return sizeof(glm::vec2); }
            case InspectorType::Float3: { return sizeof(glm::vec3); }
            case InspectorType::Float4: { return sizeof(glm::vec4); }

            case InspectorType::Int : { return sizeof(    int   ); }
            case InspectorType::Int2: { return sizeof(glm::ivec2); }
            case InspectorType::Int3: { return sizeof(glm::ivec3); }
            case InspectorType::Int4: { return sizeof(glm::ivec4); }

            case InspectorType::Double: { return sizeof(double); }
            case InspectorType::String: { return sizeof(String); }
            case InspectorType::Bool  : { return sizeof( bool ); }
     
            case InspectorType::Component: { return sizeof(Component*); }
            case InspectorType::Entity   : { return sizeof(Entity   *); }

            case InspectorType::Vector   : { return sizeof(Vector<char>); }

            default: { return 0; }
        }
    }

    template<typename U>
    constexpr uint32 inspectTypeInt(uint8 depth = 0){
        uint32 type = 0xFFFFFFFF;

        using namespace glm;

        if constexpr (std::is_same_v<U,        int               >) { type = (uint32)InspectorType::Int ; }
        if constexpr (std::is_same_v<U, vec<2, int, packed_highp>>) { type = (uint32)InspectorType::Int2; }
        if constexpr (std::is_same_v<U, vec<3, int, packed_highp>>) { type = (uint32)InspectorType::Int3; }
        if constexpr (std::is_same_v<U, vec<4, int, packed_highp>>) { type = (uint32)InspectorType::Int4; }

        if constexpr (std::is_same_v<U,        float               >) { type = (uint32)InspectorType::Float ; }
        if constexpr (std::is_same_v<U, vec<2, float, packed_highp>>) { type = (uint32)InspectorType::Float2; }
        if constexpr (std::is_same_v<U, vec<3, float, packed_highp>>) { type = (uint32)InspectorType::Float3; }
        if constexpr (std::is_same_v<U, vec<4, float, packed_highp>>) { type = (uint32)InspectorType::Float4; }

        if constexpr (std::is_same_v<U, glm::quat>) { type = (uint32)InspectorType::Float4; }

        if constexpr (std::is_same_v<U, double>) { type = (uint32)InspectorType::Double; }
        if constexpr (std::is_same_v<U, String>) { type = (uint32)InspectorType::String; }
        if constexpr (std::is_same_v<U, bool  >) { type = (uint32)InspectorType::Bool  ; }

        if constexpr(std::is_same_v<U, Component*>) { type = (uint32)InspectorType::Component; }
        if constexpr(std::is_same_v<U, Entity*   >) { type = (uint32)InspectorType::Entity   ; }

        //
        // containers
        //
        
        if (depth == 3) { return 0xFFFFFFFF; }
        
        if constexpr (is_vector<U>{}) {
          type  = (uint32)InspectorType::Vector;
          type |= inspectTypeInt<typename is_vector<U>::type>(depth+1);
        }
        
        return type << (depth > 0 ? 8 : 0);
    }

    template<typename T, typename U>
    constexpr auto inspectType(U T::*member) {
        Pair<uint32, uint> x;

        x.first = inspectTypeInt<U>();
        x.second = (char*)&((T*)nullptr->*member) - (char*)nullptr;

        return x;
    }
}

