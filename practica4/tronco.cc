#include "tronco.h"
#include "partemodelojerarquico.h"
#include "malla.h"

Tronco::Tronco() {

  Tupla3f colorMarron = Tupla3f( 0.502, 0.251, 0 );
  Material bronze = Material(Tupla4f(0.714,0.4284,0.18144,1),Tupla4f(0.393548,0.271906,0.166721,1),Tupla4f(0.2125,0.1275,0.054,1),.2);

  tronco = new Cilindro( 10, 10, 50, 15 );
  tronco->setColorSolido( colorMarron );
  tronco->setMaterial( bronze );

  rama = new Cilindro( 4, 10, 10, 5 );
  rama->setColorSolido( colorMarron );
  rama->setMaterial( bronze );

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
