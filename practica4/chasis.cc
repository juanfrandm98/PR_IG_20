#include "chasis.h"
#include "partemodelojerarquico.h"
#include "malla.h"

Chasis::Chasis() {

  Tupla3f colorAmarillo = Tupla3f( 1, 1, 0 );
  Material chapa = Material(Tupla4f(0.7,0.7,0.04,1),Tupla4f(0.05,0.05,0.0,1),Tupla4f(0.05,0.05,0.04,1),0.78125);

  chasisDelantero = new Cubo( 10 );
  chasisDelantero->setColorSolido( colorAmarillo );
  chasisDelantero->setMaterial( chapa );

  chasisTrasero = new Cubo( 10 );
  chasisTrasero->setColorSolido( colorAmarillo );
  chasisTrasero->setMaterial( chapa );

  munionDelantero = new Cubo( 10 );
  munionDelantero->setColorSolido( colorAmarillo );
  munionDelantero->setMaterial( chapa );

  ejeDelantero = new EjeDelantero();
  ejeTrasero   = new EjeTrasero();

}

void Chasis::draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) {

  glPushMatrix();
    glTranslatef( -40, -10, 0 );
    ejeDelantero->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glTranslatef( 40, -5, 0 );
    ejeTrasero->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glTranslatef( -28.75, 12.5, 0 );
    glScalef( 5.75, 5.5, 4.5 );
    chasisDelantero->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glTranslatef( 32.5, 0, 0 );
    glScalef( 6.5, 3, 6 );
    chasisTrasero->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glTranslatef( -65, 0, 0 );
    glScalef( 1.5, 2, 2 );
    munionDelantero->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

}

void Chasis::cambiarAnguloGiro( int angulo ) {

  ejeDelantero->cambiarAnguloGiro(angulo);

}

void Chasis::rotarRuedas( int angulo ) {

  ejeDelantero->rotarRuedas(angulo);
  ejeTrasero->rotarRuedas(angulo);

}
