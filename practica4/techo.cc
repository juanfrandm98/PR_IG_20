#include "techo.h"
#include "partemodelojerarquico.h"
#include "malla.h"

Techo::Techo() {

  Tupla3f colorAmarillo = Tupla3f( 1, 1, 0 );
  Tupla3f colorGris = Tupla3f( 0.19, 0.19, 0.19 );
  Material chapa = Material(Tupla4f(0.7,0.7,0.04,1),Tupla4f(0.05,0.05,0.0,1),Tupla4f(0.05,0.05,0.04,1),0.78125);
  Material plata = Material(Tupla4f(0.50754,0.50754,0.50754,1),Tupla4f(0.508273,0.508273,0.508273,1),Tupla4f(0.19225,0.19225,0.19225,1),0.4);

  techo = new Cubo( 10 );
  techo->setColorSolido( colorAmarillo );
  techo->setMaterial( chapa );

  tuboIzquierdo = new Cilindro( 10, 10, 10, 5 );
  tuboIzquierdo->setColorSolido( colorGris );
  tuboIzquierdo->setMaterial( plata );

  tuboDerecho = new Cilindro( 10, 10, 10, 5 );
  tuboDerecho->setColorSolido( colorGris );
  tuboDerecho->setMaterial( plata );

}

void Techo::draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) {

  glPushMatrix();
    glTranslatef( 0, 12.5, 0 );
    glScalef( 7.5, 0.5, 6 );
    techo->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glTranslatef( 27.5, 0, -25 );
    glScalef( 0.5, 2.5, 0.5 );
    tuboDerecho->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glTranslatef( 27.5, 0, 25 );
    glScalef( 0.5, 2.5, 0.5 );
    tuboIzquierdo->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

}
