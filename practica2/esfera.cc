#include "aux.h"
#include "objrevolucion.h"
#include "esfera.h"

Esfera::Esfera( const int numVertPerfil, const int numInstanciasPerf,
                    const float radio ) {

  int anguloInicial = 0;
  int anguloPorVert = M_PI / numVertPerfil;
  //int anguloInicial = 0;
  //int anguloPorVert = 360 / numVertPerfil;
  int anguloAcumulado = anguloInicial;

  std::vector<Tupla3f> perfilOriginal;

  for( int i = 0; i < numVertPerfil; i++ ) {

    float x = cos( anguloAcumulado ) * radio;
    float y = sin( anguloAcumulado ) * radio;

    perfilOriginal.push_back( Tupla3f( x, y, 0 ) );

    anguloAcumulado += anguloPorVert;

  }

  CrearObjeto( perfilOriginal, numInstanciasPerf, true, true );

}
