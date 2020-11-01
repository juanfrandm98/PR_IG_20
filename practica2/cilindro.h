#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED

#include "aux.h"

class Cilindro : public ObjRevolucion
{
   public:
   Cilindro( const int numVertPerfil, const int numInstanciasPerf,
             const float altura, const float radio ) ;

} ;

#endif
