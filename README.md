cpm-gl-platform
===============

[![Build Status](https://travis-ci.org/iauns/cpm-gl-platform.png)](https://travis-ci.org/iauns/cpm-gl-platform)

Includes OpenGL and OpenGL ES platform specific headers. Header only and
contains several helpful debugging macros. These macros are automatically
disabled in release builds but you can also disable their definition using
`GL_PLATFORM_NO_DEBUGGING`. See below.

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

