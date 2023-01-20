#include "PCH.h"

#include "Core/Window/Window.h"

namespace PetrolEngine {

    float WindowApi::getAspectRatio() const {
        return ((float) windowData.width) / ((float)windowData.height);
    }
    
}