
#include "GLPlatform.hpp"

void glPlatformInit()
{
#ifdef GL_PLATFORM_USING_WIN
  glewInit();
#endif
}

