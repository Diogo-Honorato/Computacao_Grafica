#pragma once

#include "../dep/json/json.hpp"
#include "../dep/glm/gtc/quaternion.hpp"


using json = nlohmann::json;

namespace glm {
    inline void to_json(json& j, const glm::vec3& v) { j = json{v.x, v.y, v.z}; }
    inline void from_json(const json& j, glm::vec3& v) { v.x = j.at(0); v.y = j.at(1); v.z = j.at(2); }

    inline void to_json(json& j, const glm::quat& q) { j = json{q.x, q.y, q.z, q.w}; }
    inline void from_json(const json& j, glm::quat& q) { q.x = j.at(0); q.y = j.at(1); q.z = j.at(2); q.w = j.at(3); }
}