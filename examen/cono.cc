#include "aux.h"
#include "objrevolucion.h"
#include "cono.h"

Cono::Cono( const int numVertPerfil, const int numInstanciasPerf,
                    const float altura, const float radio ) {

  float alturaActual = - altura / 2;
  float alturaPorPunto = altura / ( numVertPerfil - 1 );
  float ancho = radio;
  float anchoPorPunto = radio / ( numVertPerfil - 1 );

  std::vector<Tupla3f> perfilOriginal;

  for( int i = 0; i < numVertPerfil; i++ ) {

    float x, y, z;

    x = ancho;
    y = alturaActual;
    z = 0;

    perfilOriginal.push_back( Tupla3f( x, y, z ) );

    alturaActual += alturaPorPunto;
    ancho -= anchoPorPunto;

  }

  CrearObjeto( perfilOriginal, numInstanciasPerf, true, true, 360 );

}
