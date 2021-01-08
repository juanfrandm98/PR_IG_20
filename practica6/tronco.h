#ifndef TRONCO_H_INCLUDED
#define TRONCO_H_INCLUDED

#include "partemodelojerarquico.h"
#include "malla.h"
#include "objrevolucion.h"
#include "cilindro.h"

class Tronco : public ParteModeloJerarquico {

private:
  Cilindro * tronco = nullptr;
  Cilindro * rama   = nullptr;

public:
  Tronco();
  void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion );

};

#endif
