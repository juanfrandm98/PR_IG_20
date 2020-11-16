#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

typedef enum {DIRECCIONAL, POSICIONAL} tipoLuz;

class Luz
{
   public:
     void aplicar();

   protected:
     Tupla4f posicion;
     GLenum id;
     Tupla4f colorAmbiente;
     Tupla4f colorDifuso;
     Tupla4f colorEspecular;
     tipoLuz tipo;
} ;

#endif
