#include "Serializer.h"

namespace glm {
    using json = nlohmann::json;
    void to_json(json& j, const glm::vec2& P) {
        j = { { "x", P.x }, { "y", P.y } };
    };
    
    void from_json(const json& j, glm::vec2& P) {
        P.x = j.at("x").get<double>();
        P.y = j.at("y").get<double>();
    }

    void to_json(json& j, const glm::vec3& P) {
        j = { { "x", P.x }, { "y", P.y }, { "z", P.z } };
    };
    
    void from_json(const json& j, glm::vec3& P) {
        P.x = j.at("x").get<double>();
        P.y = j.at("y").get<double>();
        P.z = j.at("z").get<double>();
    }
    void to_json(json& j, const glm::vec4& P) {
        j = { { "x", P.x }, { "y", P.y }, { "z", P.z }, { "w", P.w } };
    };
    
    void from_json(const json& j, glm::vec4& P) {
        P.x = j.at("x").get<double>();
        P.y = j.at("y").get<double>();
        P.x = j.at("z").get<double>();
        P.w = j.at("w").get<double>();
    }
}

