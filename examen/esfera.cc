#include "aux.h"
#include "objrevolucion.h"
#include "esfera.h"

Esfera::Esfera( const int numVertPerfil, const int numInstanciasPerf,
                    const float radio ) {

  float anguloPorVert = ( M_PI / ( numVertPerfil - 1 ) );
  //int anguloAcumulado = 3 * M_PI / 2;   // Ahora mismo es el ángulo inicial
  float anguloAcumulado = 0;

  float altura = -radio;                  // Ahora mismo es la altura inicial
  float alturaPorPunto = ( 2 * radio ) / ( numVertPerfil - 1 );

  std::vector<Tupla3f> perfilOriginal;

  for( int i = 0; i < numVertPerfil; i++ ) {
    float x, y, z;

    x = sin( anguloAcumulado ) * radio;
    y = -cos( anguloAcumulado ) * radio;
    z = 0;

    perfilOriginal.push_back( Tupla3f( x, y, z ) );
    altura += alturaPorPunto;
    anguloAcumulado += anguloPorVert;
  }

  CrearObjeto( perfilOriginal, numInstanciasPerf, true, true );

}
