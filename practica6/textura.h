#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include "aux.h"

class Textura {

private:
  GLuint textura_id = 0;
  std::vector<unsigned char> data;
  int width, height;

public:
  Textura( std::string archivo );
  void activar();
  int getWidth();
  int getHeight();
  std::vector<unsigned char> getData();

};

#endif
