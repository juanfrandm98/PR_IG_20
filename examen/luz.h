#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

typedef enum {DIRECCIONAL, POSICIONAL} tipoLuz;

class Luz
{
   public:
     void aplicar();
     Tupla3f getPosicion();
     void setColores( Tupla4f colorAmb, Tupla4f colorDif, Tupla4f colorEsp );

   protected:
     Tupla4f posicion;
     GLenum id;
     Tupla4f colorAmbiente;
     Tupla4f colorDifuso;
     Tupla4f colorEspecular;
     tipoLuz tipo;
} ;

#endif
