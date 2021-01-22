#include "ejedelantero.h"
#include "partemodelojerarquico.h"
#include "malla.h"

EjeDelantero::EjeDelantero() {

  Tupla3f colorGris = Tupla3f( 0.19, 0.19, 0.19 );
  Material plata = Material(Tupla4f(0.50754,0.50754,0.50754,1),Tupla4f(0.508273,0.508273,0.508273,1),Tupla4f(0.19225,0.19225,0.19225,1),0.4);

  eje = new Cilindro( 10, 10, 10, 5 );
  eje->setColorSolido( colorGris );
  eje->setMaterial( plata );

  ruedaIzquierda = new RuedaDelantera();
  ruedaDerecha   = new RuedaDelantera();

}

void EjeDelantero::draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) {

  glPushMatrix();
    glTranslatef( 0, 0, -45 );
    glRotatef( anguloGiro, 0, 1, 0 );
    glRotatef( anguloRotacion, 0, 0, 1 );
    ruedaDerecha->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glTranslatef( 0, 0, 45 );
    glRotatef( anguloGiro, 0, 1, 0 );
    glRotatef( anguloRotacion, 0, 0, 1 );
    ruedaIzquierda->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glRotatef( 90, 1, 0, 0 );
    glScalef( 1, 8.5, 1 );
    eje->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

}

void EjeDelantero::cambiarAnguloGiro( float angulo ) {

  anguloGiro += angulo;

  if( anguloGiro < minAngulo )
    anguloGiro = minAngulo;

  if( anguloGiro > maxAngulo )
    anguloGiro = maxAngulo;

}

void EjeDelantero::rotarRuedas( float angulo ) {

  anguloRotacion += angulo;

}

bool EjeDelantero::ruedasAlTope() {

  return ( ( anguloGiro == minAngulo ) || ( anguloGiro == maxAngulo ) );

}

void EjeDelantero::setColorSeleccion( Tupla3f color ) {
  eje->setColorSeleccion(color);
  ruedaIzquierda->setColorSeleccion(color);
  ruedaDerecha->setColorSeleccion(color);
}

void EjeDelantero::setMaterialSeleccion( Material mat ) {
  eje->setMaterialSeleccion(mat);
  ruedaIzquierda->setMaterialSeleccion(mat);
  ruedaDerecha->setMaterialSeleccion(mat);
}
