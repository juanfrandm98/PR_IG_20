#include "ruedadelantera.h"
#include "partemodelojerarquico.h"
#include "malla.h"

RuedaDelantera::RuedaDelantera() {

  Tupla3f colorNegro = Tupla3f( 0, 0, 0 );
  Material obsidiana = Material(Tupla4f(0.18275,0.17,0.22525,1),Tupla4f(0.332741,0.328634,0.346435,1),Tupla4f(0.05375,0.05,0.06625,1),0.3);

  rueda = new Cilindro( 4, 20, 10, 5 );
  rueda->setColorSolido( colorNegro );
  rueda->setMaterial( obsidiana );

}

void RuedaDelantera::draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) {

  glPushMatrix();
    glRotatef( 90, 1, 0, 0 );
    glScalef( 5, 1.5, 5 );
    rueda->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

}

void RuedaDelantera::setColorSeleccion( Tupla3f color ) {
  rueda->setColorSeleccion(color);
}
