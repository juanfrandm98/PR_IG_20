#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "aux.h"

class Material
{
  public:
    Material( Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float b ) ;
    void aplicar();

  private:
    Tupla4f difuso;
    Tupla4f especular;
    Tupla4f ambiente;
    float brillo;

} ;

#endif
