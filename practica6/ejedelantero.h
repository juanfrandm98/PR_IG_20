#ifndef EJE_DELANTERO_H_INCLUDED
#define EJE_DELANTERO_H_INCLUDED

#include "partemodelojerarquico.h"
#include "malla.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "ruedadelantera.h"

class EjeDelantero : public ParteModeloJerarquico {

private:
  RuedaDelantera * ruedaIzquierda = nullptr;
  RuedaDelantera * ruedaDerecha   = nullptr;
  Cilindro * eje                  = nullptr;

  float anguloGiro = 0;
  const float minAngulo  = -25;
  const float maxAngulo  = 25;

  float anguloRotacion = 0;

public:
  EjeDelantero();
  void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion );
  void cambiarAnguloGiro( float angulo );
  void rotarRuedas( float angulo );
  bool ruedasAlTope();
  void setColorSeleccion( Tupla3f color );
  void setMaterialSeleccion( Material mat );

};

#endif
