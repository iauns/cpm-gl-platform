
#include "GLPlatform.hpp"
#include <stdexcept>

namespace CPM_GL_PLATFORM_NS {

void glPlatformInit()
{
#ifdef GL_PLATFORM_USING_WIN
  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    throw std::runtime_error("GLEW failed to initialize.");
  }
#endif
}

} // namespace CPM_GL_PLATFORM_NS

