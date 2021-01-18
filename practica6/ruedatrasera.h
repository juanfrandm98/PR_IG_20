#ifndef RUEDA_TRASERA_H_INCLUDED
#define RUEDA_TRASERA_H_INCLUDED

#include "partemodelojerarquico.h"
#include "malla.h"
#include "objrevolucion.h"
#include "cilindro.h"

class RuedaTrasera : public ParteModeloJerarquico {

private:
  Malla3D * rueda = nullptr;

public:
  RuedaTrasera();
  void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion );
  void setColorSeleccion( Tupla3f color );
  void setMaterialSeleccion( Material mat );

};

#endif
