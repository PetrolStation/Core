#pragma once

#include <string>
#include <Core/Aliases.h>

namespace PetrolEngine {
    class Image {
    public:
        static Image* create(const String& path) { return new Image(path); }
        static Image* create(const void* data, int width, int height, int bpc = 8, int components = 3, bool hdr = false) { return new Image(data, width, height, bpc, components, hdr); }

        ~Image();

        static void flipImages(bool flip);

        NO_DISCARD unsigned char* getData() const { return data; }

        NO_DISCARD uint8 getComponentsNumber() const { return componentsNumber; }
        NO_DISCARD uint8 getBitsPerChannel  () const { return bitsPerChannel  ; }
        NO_DISCARD bool  isHDR              () const { return HDR             ; }
        NO_DISCARD int   getWidth           () const { return width           ; }
        NO_DISCARD int   getHeight          () const { return height          ; }

    public:
        explicit Image(const String&  path);
	explicit Image(const void* data, int width, int height, int bpc, int components, bool hdr);

    private:
        int  width  = 0;
        int  height = 0;
        bool HDR    = false;

        int componentsNumber = 0;
        int bitsPerChannel   = 0;

        unsigned char* data = nullptr;
    };
}
