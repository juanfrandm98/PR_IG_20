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

  int anguloGiro = 0;
  const int minAngulo  = -25;
  const int maxAngulo  = 25;

  int anguloRotacion = 0;

public:
  EjeDelantero();
  void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion );
  void cambiarAnguloGiro( int angulo );
  void rotarRuedas( int angulo );

};

#endif
