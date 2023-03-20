#pragma once

#include <PCH.h>
#include <string>

namespace PetrolEngine {
	String ReadFile (const String& filepath);
	String WriteFile(const String& filepath, const String& content);	
}
