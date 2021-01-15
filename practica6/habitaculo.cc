#include "habitaculo.h"
#include "partemodelojerarquico.h"
#include "malla.h"

Habitaculo::Habitaculo() {

  Tupla3f colorAmarillo = Tupla3f( 1, 1, 0 );
  Material chapa = Material(Tupla4f(0.7,0.7,0.04,1),Tupla4f(0.05,0.05,0.0,1),Tupla4f(0.05,0.05,0.04,1),0.78125);

  ladoIzquierdo = new Cubo( 10 );
  ladoIzquierdo->setColorSolido( colorAmarillo );
  ladoIzquierdo->setMaterial( chapa );

  ladoDerecho = new Cubo( 10 );
  ladoDerecho->setColorSolido( colorAmarillo );
  ladoDerecho->setMaterial( chapa );

  ladoAtras = new Cubo( 10 );
  ladoAtras->setColorSolido( colorAmarillo );
  ladoAtras->setMaterial( chapa );

}

void Habitaculo::draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) {

  glPushMatrix();
    glTranslatef( 0, 0, 25 );
    glScalef( 5, 3, 1 );
    ladoIzquierdo->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glTranslatef( 0, 0, -25 );
    glScalef( 5, 3, 1 );
    ladoDerecho->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glTranslatef( 20, -5, 0 );
    glScalef( 1, 2, 6 );
    ladoAtras->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

}

void Habitaculo::setColorSeleccion( Tupla3f color ) {
  ladoIzquierdo->setColorSeleccion(color);
  ladoDerecho->setColorSeleccion(color);
  ladoAtras->setColorSeleccion(color);
}
