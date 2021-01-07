#include "textura.h"
#include "jpg_imagen.hpp"

Textura::Textura( std::string archivo ) {

  // Declaración del puntero a la imagen
  jpg::Imagen * pimg = nullptr;

  // Cargar la imagen
  pimg = new jpg::Imagen(archivo);

  width  = pimg->tamX();   // Número de columnas (unsigned)
  height = pimg->tamY();   // Número de filas (unsigned)
/*
  for( int i = 0; i < width; i++ )
    for( int j = 0; j < height; j++ ) {
      unsigned char * pixel = pimg->leerPixel( i, height - i );
      data.push_back( pixel[0] ); // R
      data.push_back( pixel[1] ); // G
      data.push_back( pixel[2] ); // B
    }*/

  unsigned char * pixeles = pimg-> leerPixels();
  for( int i = 0; i < 3 * width * height; ++i )
    data.push_back(*(pixeles+i));

  // Asignamos un valor nulo a la textura
  textura_id = -1;

}

void Textura::activar() {

  glEnable( GL_TEXTURE_2D );

  // Si la textura tiene un valor nulo (no está configurada)
  if( textura_id == -1 ) {
    // Generamos el identificador de la textura
    glGenTextures( 1, &textura_id );
    // Definimos esta textura como activa ...
    glBindTexture( GL_TEXTURE_2D, textura_id );
    // ... para luego asignarle la textura al identificador activo
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB,
                       GL_UNSIGNED_BYTE, data.data() );
  }

  glBindTexture( GL_TEXTURE_2D, textura_id );

}

int Textura::getWidth() {
  return width;
}

int Textura::getHeight() {
  return height;
}
