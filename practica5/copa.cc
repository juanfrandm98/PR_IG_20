#include "copa.h"
#include "partemodelojerarquico.h"
#include "malla.h"
#include "textura.h"

Copa::Copa() {

  Tupla3f colorVerde = Tupla3f( 0, 1, 0 );
  Material greenPlastic = Material(Tupla4f(0.45,0.55,0.45,1),Tupla4f(0.0,0.0,0.0,1),Tupla4f(0.1,0.35,0.1,1),.25);
  Textura grass = Textura( "./images/hierba.jpeg" );

  cono = new Cono( 10, 10, 100, 35 );
  cono->setColorSolido( colorVerde );
  cono->setMaterial( greenPlastic );
  cono->setTextura( grass );

}

void Copa::draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) {

  glPushMatrix();
    cono->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

}
