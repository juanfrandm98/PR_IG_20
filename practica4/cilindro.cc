#include "aux.h"
#include "objrevolucion.h"
#include "cilindro.h"

Cilindro::Cilindro( const int numVertPerfil, const int numInstanciasPerf,
                    const float altura, const float radio ) {

  float alturaInicial = - altura / 2;
  float alturaPorPunto = altura / ( numVertPerfil - 1 );

  std::vector<Tupla3f> perfilOriginal;

  for( int i = 0; i < numVertPerfil; i++ )
    perfilOriginal.push_back( Tupla3f( radio, alturaInicial + i * alturaPorPunto, 0 ) );

  CrearObjeto( perfilOriginal, numInstanciasPerf, true, true );

}
