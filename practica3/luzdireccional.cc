#include "luz.h"
#include "luzdireccional.h"

LuzDireccional::LuzDireccional( const Tupla2f & orientacion, const GLenum & ident,
                                const Tupla4f & camb, const Tupla4f & cesp,
                                const Tupla4f & cdif) {

  alpha          = orientacion[0];
  beta           = orientacion[1];
  posicion(0)    = 0;
  posicion(1)    = 0;
  posicion(2)    = 1;
  posicion(3)    = 0;  // Característica de las luces direccionales
  id             = ident;
  colorAmbiente  = camb;
  colorEspecular = cesp;
  colorDifuso    = cdif;

}

void LuzDireccional::variarAnguloAlpha( float incremento ) {
  alpha += incremento;
  using namespace std;
  cout << "ALPHA: " << alpha << endl;
  actualizarPosicion();
}

void LuzDireccional::variarAnguloBeta( float incremento ) {
  beta += incremento;
  actualizarPosicion();
}

void LuzDireccional::actualizarPosicion() {
  posicion(0) = sin( alpha * 2*M_PI/360 ) * 10;
  posicion(1) = sin( beta * 2*M_PI/360) * 10;
  posicion(2) = cos( alpha *2*M_PI/360) * cos( beta *2*M_PI/360) * 10;
}
