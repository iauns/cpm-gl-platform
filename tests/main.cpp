
#include <cstdlib>
#include <iostream>
#include <gl-batch-context/Context.hpp>
#include <gl-platform/GLPlatform.hpp>

int main(int /*argc*/, char** /*argv*/)
{
  int width = 640;
  int height = 480;
  CPM_GL_CONTEXT_NS::Context* glContext = 
      CPM_GL_CONTEXT_NS::Context::createBatchContext(
          640, 480, 32, 32, 0, false, false);

  glContext->makeCurrent();

  GL(glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height)));

  // Now that we are finished, delete the context.
  delete glContext;

  return 0;
}

