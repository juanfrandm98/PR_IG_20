#include "luz.h"
#include "luzdireccional.h"
#include "material.h"

LuzDireccional::LuzDireccional( const Tupla2f & orientacion, const GLenum & ident,
                                const Tupla4f & camb, const Tupla4f & cesp,
                                const Tupla4f & cdif) {

  alpha          = orientacion[0];
  beta           = orientacion[1];
  posicion(0)       = 0;
  posicion(1)       = 0;
  posicion(2)       = 0;
  posicion(3)       = 0;
  id             = ident;
  colorAmbiente  = camb;
  colorEspecular = cesp;
  colorDifuso    = cdif;

}

void LuzDireccional::variarAnguloAlpha( float incremento ) {
  alpha += incremento;
}

void LuzDireccional::variarAnguloBeta( float incremento ) {
  beta += incremento;
}
