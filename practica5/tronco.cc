#include "tronco.h"
#include "partemodelojerarquico.h"
#include "objrevolucion.h"
#include "malla.h"

Tronco::Tronco() {

  Tupla3f colorMarron = Tupla3f( 0.502, 0.251, 0 );
  Tupla3f colorBlanco = Tupla3f( 1, 1, 1 );
  Material bronze = Material(Tupla4f(0.714,0.4284,0.18144,1),Tupla4f(0.393548,0.271906,0.166721,1),Tupla4f(0.2125,0.1275,0.054,1),.2);
  Textura madera = Textura( "./images/text-madera.jpg" );
  Textura lata = Textura( "./images/text-lata-1.jpg" );

  tronco = new Cilindro( 10, 10, 50, 15 );
  tronco->setColorSolido( colorBlanco );
  tronco->setMaterial( bronze );
  tronco->setTextura( madera );

  rama = new Cilindro( 4, 10, 10, 5 );
  rama->setColorSolido( colorBlanco );
  rama->setMaterial( bronze );
  rama->setTextura( madera );

}

void Tronco::draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) {

  glPushMatrix();
    tronco->draw( tipoDibujado, tipoVisualizacion );
    glPushMatrix();
      glTranslatef( 17.5, 0, 0 );
      glRotatef( 90, 0, 0, 1 );
      rama->draw( tipoDibujado, tipoVisualizacion );
    glPopMatrix();
  glPopMatrix();

}
