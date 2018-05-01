class frameBruffer
{
  frameBuffer();
  unsigned int getID() const {return id;}
  void bind() {glBindFrameBuffer(id);}
  
  void addColorTextureBuffer(unsigned int width,unsigned int height);
  
private:
  unsigned int id;
};
