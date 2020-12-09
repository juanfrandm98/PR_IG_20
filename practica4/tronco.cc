#include "tronco.h"
#include "partemodelojerarquico.h"
#include "malla.h"

Tronco::Tronco() {

  Tupla3f colorMarron = Tupla3f( 0.502, 0.251, 0 );
  Material bronze = Material(Tupla4f(0.714,0.4284,0.18144,1),Tupla4f(0.393548,0.271906,0.166721,1),Tupla4f(0.2125,0.1275,0.054,1),.2);

  ComponenteMalla c0;
  c0.objeto = new Cilindro( 10, 10, 50, 15 );
  c0.posicion = Tupla3f( 0, 25, 0 );
  c0.objeto->setColorSolido( colorMarron );
  c0.objeto->setMaterial( bronze );
  componentes.push_back(c0);

  ComponenteMalla c1;
  c1.objeto = new Cilindro( 4, 10, 10, 5 );
  c1.posicion = Tupla3f( 17.5, 25, 0 );
  c1.orientacion = Tupla3f( 0, 0, 90 );
  c1.objeto->setColorSolido( colorMarron );
  c1.objeto->setMaterial( bronze );
  componentes.push_back(c1);

}
