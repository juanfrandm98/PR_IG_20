#ifndef TRACTORREMOLQUE_H_INCLUDED
#define TRACTORREMOLQUE_H_INCLUDED

#include "modelojerarquico.h"
#include "chasis.h"

class TractorRemolque : public ModeloJerarquico {

private:
  Chasis * chasis = nullptr;

public:
  TractorRemolque();
  void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion );

};

#endif
