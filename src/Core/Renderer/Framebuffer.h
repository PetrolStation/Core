#pragma once

#include <Core/Aliases.h>
#include "Texture.h"

namespace PetrolEngine {

	class FramebufferImageFormat {
	public:
		enum class Formats{
			None,

			// Depth
			DEPTH16,
			DEPTH24,
			DEPTH32,
			DEPTH32F,

			// Stencil
			STENCIL8,
			
			// Depth and stencil
			DEPTH24_STENCIL8,
			DEPTH32F_STENCIL8

		} format;
	};

    struct FramebufferSpecification {
        int width;
        int height;
        //FramebufferImageFormat::Formats format;
        //bool swapChainTarget = false;
    };

	class Framebuffer {
	public:
        Vector<Texture*> attachments;

        virtual void addAttachment(Texture* texture) = 0;

        NO_DISCARD uint getID () const { return  id; }
        NO_DISCARD uint getTID() const { return tid; }
        NO_DISCARD uint getDID() const { return did; }

        virtual ~Framebuffer() = default;
    protected:
        FramebufferSpecification spec;
        uint id;
        uint tid;
        uint did;
    };
}
