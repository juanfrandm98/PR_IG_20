#include "copa.h"
#include "partemodelojerarquico.h"
#include "malla.h"

Copa::Copa() {

  Tupla3f colorVerde = Tupla3f( 0, 1, 0 );
  Material greenPlastic = Material(Tupla4f(0.45,0.55,0.45,1),Tupla4f(0.0,0.0,0.0,1),Tupla4f(0.1,0.35,0.1,1),.25);

  ComponenteMalla c0;
  c0.objeto = new Cono( 10, 10, 100, 35 );
  c0.posicion = Tupla3f( 0, 100, 0 );
  c0.objeto->setColorSolido( colorVerde );
  c0.objeto->setMaterial( greenPlastic );
  componentes.push_back(c0);

}
