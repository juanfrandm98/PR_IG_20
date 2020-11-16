#include "luz.h"
#include "luzposicional.h"

LuzPosicional::LuzPosicional( const Tupla3f & pos, const GLenum & ident,
                              const Tupla4f & camb, const Tupla4f & cesp,
                              const Tupla4f & cdif) {

  posicion(0)       = pos(0);
  posicion(1)       = pos(1);
  posicion(2)       = pos(2);
  posicion(3)       = 1;
  id             = ident;
  colorAmbiente  = camb;
  colorEspecular = cesp;
  colorDifuso    = cdif;
  tipo           = POSICIONAL;

}
