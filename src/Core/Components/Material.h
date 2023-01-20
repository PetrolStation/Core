#pragma once

#include <Core/Aliases.h>

#include "Core/Renderer/Shader.h"
#include "Core/Renderer/Texture.h"

namespace PetrolEngine {
	class Material {
	public:
        Material() = default;
        Material(const Ref<Texture>& tex, const Ref<Shader>& shader){
            this->textures.push_back(tex);
            this->shader = shader;
        }
        Material(const Ref<Shader>& shader){
            this->shader = shader;
        }

		Vector<Ref<Texture>> textures;
        Ref<Shader> shader;
	};
}

