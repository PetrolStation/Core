#pragma once

#include "Core/Aliases.h"

#include "Core/Window/Window.h"

namespace PetrolEngine{
    class WindowApi;

    class WindowResourceCreator {
    public:
        virtual WindowApi* newWindow(int width, int height, const String& title) = 0;
    };

    using WRC = PetrolEngine::WindowResourceCreator;
}