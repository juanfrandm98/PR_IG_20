#include "remolque.h"
#include "partemodelojerarquico.h"
#include "malla.h"

Remolque::Remolque() {

  Tupla3f colorAmarillo = Tupla3f( 1, 1, 0 );
  Tupla3f colorGris = Tupla3f( 0.19, 0.19, 0.19 );
  Material chapa = Material(Tupla4f(0.7,0.7,0.04,1),Tupla4f(0.05,0.05,0.0,1),Tupla4f(0.05,0.05,0.04,1),0.78125);
  Material plata = Material(Tupla4f(0.50754,0.50754,0.50754,1),Tupla4f(0.508273,0.508273,0.508273,1),Tupla4f(0.19225,0.19225,0.19225,1),0.4);

  rodillo = new Rodillo();

  extensor = new Cubo( 10 );
  extensor->setColorSolido( colorGris );
  extensor->setMaterial( plata );

  enganche = new Esfera( 10, 10, 10 );
  enganche->setColorSolido( colorAmarillo );
  enganche->setMaterial( chapa );

}

void Remolque::draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) {

  glPushMatrix();
    enganche->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glRotatef( anguloInclinacion, 0, 0, 1 );
    glRotatef( anguloGiro, 0, 1, 0 );
    glPushMatrix();
      glTranslatef( 40, 0, 0 );
      glScalef( 8, 0.5, 0.5 );
      extensor->draw( tipoDibujado, tipoVisualizacion );
    glPopMatrix();
    glPushMatrix();
      glTranslatef( 75, 0, 0 );
      rodillo->draw( tipoDibujado, tipoVisualizacion );
    glPopMatrix();
  glPopMatrix();

}

void Remolque::rotarRodillo( float angulo ) {

  if( anguloInclinacion == minInclinacionRodillo )
    rodillo->rotarRodillo(angulo);

}

void Remolque::inclinarRemolque( float angulo ) {

  anguloInclinacion += angulo;

  if( anguloInclinacion < minInclinacionRodillo )
    anguloInclinacion = minInclinacionRodillo;

  if( anguloInclinacion > maxInclinacionRodillo )
    anguloInclinacion = maxInclinacionRodillo;

}

void Remolque::girarRemolque( float angulo ) {

  anguloGiro += angulo;

  if( anguloGiro < minGiroRodillo )
    anguloGiro = minGiroRodillo;

  if( anguloGiro > maxGiroRodillo )
    anguloGiro = maxGiroRodillo;

}

bool Remolque::inclinacionAlTope() {

  return ( ( anguloInclinacion == minInclinacionRodillo ) ||
           ( anguloInclinacion == maxInclinacionRodillo ) );

}

bool Remolque::remolqueGiradoAlTope() {

  return ( ( anguloGiro == minGiroRodillo ) ||
           ( anguloGiro == maxGiroRodillo ) );

}

void Remolque::trasladarRodillo( float cantidad ) {

  rodillo->trasladarRodillo(cantidad);

}

bool Remolque::rodilloTrasladadoAlTope() {

  return rodillo->rodilloTrasladadoAlTope();

}

void Remolque::setColorSeleccion( Tupla3f color ) {
  rodillo->setColorSeleccion(color);
  extensor->setColorSeleccion(color);
  enganche->setColorSeleccion(color);
}
