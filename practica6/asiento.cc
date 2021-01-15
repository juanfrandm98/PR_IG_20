#include "asiento.h"
#include "partemodelojerarquico.h"
#include "malla.h"

Asiento::Asiento() {

  Tupla3f colorMarron = Tupla3f( 0.502, 0.251, 0 );
  Material bronze = Material(Tupla4f(0.714,0.4284,0.18144,1),Tupla4f(0.393548,0.271906,0.166721,1),Tupla4f(0.2125,0.1275,0.054,1),.2);

  cojin = new Cubo( 10 );
  cojin->setColorSolido( colorMarron );
  cojin->setMaterial( bronze );

  espalda = new Cubo( 10 );
  espalda->setColorSolido( colorMarron );
  espalda->setMaterial( bronze );

}

void Asiento::draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) {

  glPushMatrix();
    glTranslatef( 0, -5, 0 );
    glScalef( 3, 1.5, 3 );
    cojin->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glTranslatef( 10, 12.5, 0 );
    glScalef( 1, 2.5, 2 );
    espalda->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

}

void Asiento::setColorSeleccion( Tupla3f color ) {
  cojin->setColorSeleccion(color);
  espalda->setColorSeleccion(color);
}
