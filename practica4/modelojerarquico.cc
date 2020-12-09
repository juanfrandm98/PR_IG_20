#include "modelojerarquico.h"

void ModeloJerarquico::draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) {

  for( int i = 0; i < componentes.size(); i++ )
    componentes[i]->draw( tipoDibujado, tipoVisualizacion );

}
