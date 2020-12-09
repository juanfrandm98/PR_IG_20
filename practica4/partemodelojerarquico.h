#ifndef PARTEMODJER_H_INCLUDED
#define PARTEMODJER_H_INCLUDED

#include "malla.h"

struct ComponenteMalla {
  Malla3D * objeto = nullptr;
  Tupla3f posicion = Tupla3f( 0.0, 0.0, 0.0 );
  Tupla3f orientacion = Tupla3f( 0.0, 0.0, 0.0 );
  Tupla3f escalado = Tupla3f( 1.0, 1.0, 1.0 );
};

class ParteModeloJerarquico : public Malla3D {

public:
  void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion );

protected:
  std::vector<ComponenteMalla> componentes;
  std::vector<ParteModeloJerarquico*> partes;

};

#endif
