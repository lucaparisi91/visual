#include "frameBuffer.h"

frameBuffer::frameBuffer()
{
  glGenFrameBuffers(1,&id);
  glBindFrameBuffer(id);
}

void frameBuffer::addColorTextureBuffer(unsigned int width,unsigned int height)
{
  bind();
  glGenTextures(1,&idColorTexture);
  glBindTexture(idColorTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);
  

}
