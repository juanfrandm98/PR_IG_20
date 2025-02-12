#ifndef EJE_TRASERO_H_INCLUDED
#define EJE_TRASERO_H_INCLUDED

#include "partemodelojerarquico.h"
#include "ruedatrasera.h"

class EjeTrasero : public ParteModeloJerarquico {

private:
  RuedaTrasera * ruedaIzquierda = nullptr;
  RuedaTrasera * ruedaDerecha   = nullptr;

  float anguloRotacion = 0;

public:
  EjeTrasero();
  void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion );
  void rotarRuedas( float angulo );
  void setColorSeleccion( Tupla3f color );
  void setMaterialSeleccion( Material mat );

};

#endif
