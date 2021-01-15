#ifndef HABITACULO_H_INCLUDED
#define HABITACULO_H_INCLUDED

#include "partemodelojerarquico.h"
#include "cubo.h"

class Habitaculo : public ParteModeloJerarquico {

private:
  Cubo * ladoIzquierdo = nullptr;
  Cubo * ladoDerecho   = nullptr;
  Cubo * ladoAtras     = nullptr;

public:
  Habitaculo();
  void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion );
  void setColorSeleccion( Tupla3f color );

};

#endif
