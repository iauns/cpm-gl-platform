cpm-gl-platform
===============

[![Build Status](https://travis-ci.org/iauns/cpm-gl-platform.png)](https://travis-ci.org/iauns/cpm-gl-platform)

Includes OpenGL platform specific headers and defines several helpful
debugging macros. These macros are automatically disabled in release builds
but you can also disable their definition using `GL_PLATFORM_NO_DEBUGGING`.
See below.

This exists so that CPM modules don't need to know about the method of context
creation in order to properly use OpenGL. If you're on Windows, it is the
responsibility of the context creator to ensure glew is correctly initialized
and made current. 

If you are looking for a simple way to create a platform independent OpenGL
window with a context OpenGL context, I advise that you look into GLFW instead. 

Usage
-----

Simply include the following:

```c++
#include <gl-platform/GLPlatform.hpp>
```

and OpenGL headers for your platform will be included in your project. On all
systems but Windows, GLEW is not used and the system's OpenGL headers are
imported. GLEW is used on Windows platforms where the system OpenGL headers
have not been updated in a very long time.

### Windows Users

`cpm-gl-platform` uses GLEW to provide better OpenGL support. You should
either issue the appropriate glewInit call yourself, or call `glPlatformInit`.
Be aware of the implications of using multiple rendering contexts with GLEW.
See http://glew.sourceforge.net/advanced.html for more information regarding
using thread-safe multiple rendering contexts with GLEW (in particular, the
section about `GLEW_MX`).

Options
-------

To use the following variables, set them in your CMakeLists.txt before calling
`CPM_AddModule` for cpm-gl-platform.

* `GL_PLATFORM_NO_DEBUGGING` - Disables the debug macros `GL` and `GL_CHECK`.

Planned Options
---------------

* `USE_CORE_PROFILE_3`
* `USE_CORE_PROFILE_4`
* GLEW for Windows.

