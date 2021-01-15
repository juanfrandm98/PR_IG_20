#ifndef REMOLQUE_H_INCLUDED
#define REMOLQUE_H_INCLUDED

#include "partemodelojerarquico.h"
#include "malla.h"
#include "rodillo.h"
#include "objrevolucion.h"
#include "esfera.h"
#include "cubo.h"

class Remolque : public ParteModeloJerarquico {

private:
  Rodillo * rodillo = nullptr;
  Cubo * extensor   = nullptr;
  Esfera * enganche = nullptr;

  float anguloInclinacion = 0;
  const float maxInclinacionRodillo = 40;
  const float minInclinacionRodillo = -11;

  float anguloGiro = 0;
  const float maxGiroRodillo = 20;
  const float minGiroRodillo = -20;

public:
  Remolque();
  void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion );
  void rotarRodillo( float angulo );
  void girarRemolque( float angulo );
  void inclinarRemolque( float angulo );
  bool inclinacionAlTope();
  bool remolqueGiradoAlTope();
  void trasladarRodillo( float cantidad );
  bool rodilloTrasladadoAlTope();
  void setColorSeleccion( Tupla3f color );

};

#endif
