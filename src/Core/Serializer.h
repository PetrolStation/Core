#pragma once

// TODO: move json lib to deps folder
#include "json.hpp"
#include <entt/entt.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/quaternion.hpp>
#define MacroAttr(...)
#include "Aliases.h"
#include "Logger.h"
#define Serialize
MacroAttr("global", "perClass", "call(namespace, scope, subject)")
#define __Serialize(n, ...) namespace n{ NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(__VA_ARGS__); }

namespace glm {
    using json = nlohmann::json;
    
    void from_json(const json& j, glm::vec2& P);
    void from_json(const json& j, glm::vec3& P);
    void from_json(const json& j, glm::vec4& P);
    void to_json(json& j, const glm::vec2& P);
    void to_json(json& j, const glm::vec3& P);
    void to_json(json& j, const glm::vec4& P);
}

class NJSONOutputArchive {
public:
    NJSONOutputArchive(){
        root = nlohmann::json::array();
    };

    void operator()(std::underlying_type_t<entt::entity> size){
        int a=0; 
        if (!current.empty()){
            root.push_back(current);
        }
        current = nlohmann::json::array();
        current.push_back(size);
    }

    void operator()(entt::entity entity){
        current.push_back((uint32_t)entity);
    }

        template<typename T>
    void operator()(const T &t){
        nlohmann::json json = t;
        current.push_back(json);
    }

    void Close(){
        if (!current.empty()){
            root.push_back(current);
        }
    }

    const std::string AsString() {
        std::string output = root.dump();
        return output;
    }

    const std::vector<uint8_t> AsBson(){
        std::vector<std::uint8_t> as_bson = nlohmann::json::to_bson(root);
        return as_bson;
    }

private:
    nlohmann::json root;
    nlohmann::json current;
};

class NJSONInputArchive {
private:
    nlohmann::json root;
    nlohmann::json current;

    int root_idx=-1;
    int current_idx=0;

public:
    NJSONInputArchive(const std::string& json_string)
    {
        root = nlohmann::json::parse(json_string);
    };

    ~NJSONInputArchive(){
    }

    void next_root(){
        root_idx++;
        if (root_idx >= root.size()){
            // ERROR
            return;
        }
        current = root[root_idx];
        current_idx = 0;
    }

    void operator()(std::underlying_type_t<entt::entity> &s){
        next_root();
        int size = current[0].get<int>();
        current_idx++;
        s = (std::underlying_type_t<entt::entity>)size; // pass amount to entt
    }

    void operator()(entt::entity &entity){
        uint32_t ent = current[current_idx].get<uint32_t>();
        entity = entt::entity(ent);
        current_idx++;
    }

    template<typename T>
    void operator()(T &t){
        nlohmann::json component_data = current[current_idx];

        t = component_data.get<T>();

        current_idx++;
    }
};
