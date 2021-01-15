#ifndef TECHO_H_INCLUDED
#define TECHO_H_INCLUDED

#include "partemodelojerarquico.h"
#include "malla.h"
#include "objrevolucion.h"
#include "cubo.h"
#include "cilindro.h"

class Techo : public ParteModeloJerarquico {

private:
  Cubo * techo             = nullptr;
  Cilindro * tuboIzquierdo = nullptr;
  Cilindro * tuboDerecho   = nullptr;

public:
  Techo();
  void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion );
  void setColorSeleccion( Tupla3f color );

};

#endif
