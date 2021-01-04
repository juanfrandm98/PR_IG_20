#ifndef ASIENTO_H_INCLUDED
#define ASIENTO_H_INCLUDED

#include "partemodelojerarquico.h"
#include "cubo.h"

class Asiento : public ParteModeloJerarquico {

private:
  Cubo * cojin   = nullptr;
  Cubo * espalda = nullptr;

public:
  Asiento();
  void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion );

};

#endif
