/// \author James Hughes
/// \date   November 2013

#ifndef IAUNS_GL_PLATFORM_HPP
#define IAUNS_GL_PLATFORM_HPP

#if defined(USE_CORE_PROFILE_3) && defined(USE_CORE_PROFILE_4)
  #error Both USE_CORE_PROFILE_3 and USE_CORE_PROFILE_4 are defined. Ensure that only one is defined.
#endif

/// \todo Add webgl and emscriptem.

// See: http://stackoverflow.com/questions/5919996/how-to-detect-reliably-mac-os-x-ios-linux-windows-in-c-preprocessor
// and, http://sourceforge.net/p/predef/wiki/OperatingSystems/
// We provide these definitions in ADDITION to cmake directives to cover 
// extensions that need OpenGL system headers and whatnot.
#ifdef _WIN64
  #define GL_PLATFORM_USING_WIN
#elif _WIN32
  #define GL_PLATFORM_USING_WIN
#elif __APPLE__
  #include "TargetConditionals.h"
  #if TARGET_IPHONE_SIMULATOR
    #define GL_PLATFORM_USING_IOS
    #define USE_OPENGL_ES_2
  #elif TARGET_OS_IPHONE
    #define GL_PLATFORM_USING_IOS
    #define USE_OPENGL_ES_2
  #elif TARGET_OS_MAC
    #define GL_PLATFORM_USING_OSX
  #else
    #error Unsupported mac platform.
  #endif
#elif __ANDROID__
  #define GL_PLATFORM_USING_ANDROID
  #define USE_OPENGL_ES_2
#elif __linux
  #define GL_PLATFORM_USING_LINUX
#elif __unix // all unices not caught above
  #error General unix not supported - try defining GL_PLATFORM_USING_LINUX and disabling this error.
#elif __posix
  #error General posix not supported - try defining GL_PLATFORM_USING_LINUX and disabling this error.
#else
  #error Unknown unsupported platform.
#endif

// OpenGL headers
#if defined(GL_PLATFORM_USING_OSX)
  #if defined(GL_PLATFORM_USING_WIN) || defined(GL_PLATFORM_USING_LINUX) || defined(GL_PLATFORM_USING_IOS) || defined(GL_PLATFORM_USING_ANDROID)
    #error Multiple platforms defined.
  #endif

  #include <OpenGL/gl.h>
  #include <OpenGL/glext.h>
  #if defined(USE_CORE_PROFILE_3) || defined(USE_CORE_PROFILE_4)
    // Currently mac places gl4 specific definitions in the gl3 header. Change
    // when they update this.
    #include <OpenGL/gl3.h> 
  #endif
#elif defined(GL_PLATFORM_USING_WIN)

  #if defined(GL_PLATFORM_USING_OSX) || defined(GL_PLATFORM_USING_LINUX) || defined(GL_PLATFORM_USING_IOS) || defined(GL_PLATFORM_USING_ANDROID)
    #error Multiple platforms defined.
  #endif

  #define NOMINMAX
  #include <Windows.h>
  #include <glew/include/GL/glew.h>
  #include <GL/gl.h>
#elif defined(GL_PLATFORM_USING_LINUX)

  #if defined(GL_PLATFORM_USING_OSX) || defined(GL_PLATFORM_USING_WIN) || defined(GL_PLATFORM_USING_IOS) || defined(GL_PLATFORM_USING_ANDROID)
    #error Multiple platforms defined.
  #endif

  #define GL_GLEXT_PROTOTYPES
  #include <GL/gl.h>
  #include <GL/glext.h>
  #include <GL/glx.h>
#elif defined(GL_PLATFORM_USING_IOS)

  #if defined(GL_PLATFORM_USING_OSX) || defined(GL_PLATFORM_USING_WIN) || defined(GL_PLATFORM_USING_LINUX) || defined(GL_PLATFORM_USING_ANDROID)
    #error Multiple platforms defined.
  #endif

  #import <OpenGLES/ES2/gl.h>
  #import <OpenGLES/ES2/glext.h>
#elif defined(GL_PLATFORM_USING_ANDROID)

  #if defined(GL_PLATFORM_USING_OSX) || defined(GL_PLATFORM_USING_WIN) || defined(GL_PLATFORM_USING_LINUX) || defined(GL_PLATFORM_USING_IOS)
    #error Multiple platforms defined.
  #endif

  #include <GLES2/gl2.h>
  #include <GLES2/gl2ext.h>
#else
  /// \todo Look into emscriptem.
  #error OpenGL headers not defined for this platform.
#endif

// Utility definitions for non-ES OpenGL implementations.
#ifndef USE_OPENGL_ES_2
  #define GL_HALF_FLOAT_OES GL_FLOAT
#endif



#ifndef GL_PLATFORM_NO_DEBUGGING
#include <iostream>

// Misc GL debugging.
#define MAX_GL_ERROR_COUNT 10 
#ifdef IAUNS_GLDEBUG_DEBUG
# define GL(stmt)                                                      \
  do {                                                                 \
    GLenum glerr;                                                      \
    unsigned int iCounter = 0;                                         \
    while((glerr = glGetError()) != GL_NO_ERROR) {                     \
      std::cerr << "GL error calling" << #stmt << " before line " << __LINE__ << " (" << __FILE__ << "): " << static_cast<unsigned>(glerr) << std::endl; \
      iCounter++;                                                      \
      if (iCounter > MAX_GL_ERROR_COUNT) break;                        \
    }                                                                  \
    stmt;                                                              \
    iCounter = 0;                                                      \
    while((glerr = glGetError()) != GL_NO_ERROR) {                     \
      std::cerr << "'" << #stmt << "' on line " << __LINE__ << " (" << __FILE__ << ") caused GL error: " << static_cast<unsigned>(glerr) << std::endl; \
      iCounter++;                                                      \
      if (iCounter > MAX_GL_ERROR_COUNT) break;                        \
    }                                                                  \
  } while(0)

# define GL_CHECK()                                                       \
  do {                                                                    \
    GLenum glerr;                                                         \
    unsigned int iCounter = 0;                                            \
    while((glerr = glGetError()) != GL_NO_ERROR) {                        \
      std::cerr << "GL error before line " << __LINE__ << "("   \
                << __FILE__ << "): " << glerr                             \
                << std::endl;                                             \
      iCounter++;                                                         \
      if (iCounter > MAX_GL_ERROR_COUNT) break;                           \
    }                                                                     \
  } while(0)
#else
# define GL(stmt) do { stmt; } while(0)
# define GL_CHECK() 
#endif

#endif // #ifndef GL_PLATFORM_NO_DEBUGGING

namespace CPM_GL_PLATFORM_NS {

} // namespace CPM_GL_PLATFORM_NS

#endif 
