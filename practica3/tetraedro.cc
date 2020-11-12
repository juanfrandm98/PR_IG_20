#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro( float lado )
{

  // Cálculo de la posición de los vértices de la base para que el vértice de
  // arriba esté en el (0,0)
  float profundidad = sqrt( lado * lado - ( lado / 2 ) * ( lado / 2 ) );
  float radio = 2 * profundidad / 3;
  float apotema = radio / 2;

  // Cálculo de la altura en función del lado
  float vertice_centro = sqrt( ( lado / 2 ) * ( lado / 2 ) + apotema * apotema );
  float altura = sqrt( lado * lado - vertice_centro * vertice_centro );

   // inicializar la tabla de vértices
   v.push_back( Tupla3f( -lado / 2, 0, apotema ) ); // 0 - Base izquierda
   v.push_back( Tupla3f( lado / 2, 0, apotema ) );  // 1 - Base derecha
   v.push_back( Tupla3f( 0, 0, apotema - profundidad ) );        // 2 - Base arriba
   v.push_back( Tupla3f( 0, altura, 0 ) );           // 3 - Cúspide

   // inicializar la tabla de caras o triángulos:
   f.push_back( Tupla3i( 2, 1, 0 ) ); // 0 - Base
   f.push_back( Tupla3i( 3, 0, 1 ) ); // 1 - Delante
   f.push_back( Tupla3i( 3, 1, 2 ) ); // 2 - Trasera derecha
   f.push_back( Tupla3i( 3, 2, 0 ) ); // 3 - Trasera izquierda

   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   // Inicializar las tablas de triángulos para el modo ajedrez:
   f_chess_impar.push_back( Tupla3i( 2, 1, 0 ) ); // 0 - Base
   f_chess_impar.push_back( Tupla3i( 3, 0, 1 ) ); // 1 - Delante
   f_chess_par.push_back( Tupla3i( 3, 1, 2 ) ); // 0 - Trasera derecha
   f_chess_par.push_back( Tupla3i( 3, 2, 0 ) ); // 1 - Trasera izquierda

   // Inicializar colores para el modo sólido
   c_solid.push_back( Tupla3f( 1, 0, 0 ) ); // 0 - Base izquierda
   c_solid.push_back( Tupla3f( 1, 0, 0 ) ); // 1 - Base derecha
   c_solid.push_back( Tupla3f( 1, 0, 0 ) ); // 2 - Base arriba
   c_solid.push_back( Tupla3f( 1, 0, 0 ) ); // 3 - Cúspide

   // Inicializar colores para el modo puntos
   c_points.push_back( Tupla3f( 255, 0, 255 ) );
   c_points.push_back( Tupla3f( 255, 0, 255 ) );
   c_points.push_back( Tupla3f( 255, 0, 255 ) );
   c_points.push_back( Tupla3f( 255, 0, 255 ) );

   // Inicializar colores para el modo líneas
   c_lines.push_back( Tupla3f( 0, 0, 0 ) );
   c_lines.push_back( Tupla3f( 0, 0, 0 ) );
   c_lines.push_back( Tupla3f( 0, 0, 0 ) );
   c_lines.push_back( Tupla3f( 0, 0, 0 ) );

   // Inicializar colores para el modo ajedrez
   c_chess_impar.push_back( Tupla3f( 1, 0, 0 ) );
   c_chess_impar.push_back( Tupla3f( 1, 0, 0 ) );
   c_chess_impar.push_back( Tupla3f( 1, 0, 0 ) );
   c_chess_impar.push_back( Tupla3f( 1, 0, 0 ) );
   c_chess_par.push_back( Tupla3f( 0, 1, 0 ) );
   c_chess_par.push_back( Tupla3f( 0, 1, 0 ) );
   c_chess_par.push_back( Tupla3f( 0, 1, 0 ) );
   c_chess_par.push_back( Tupla3f( 0, 1, 0 ) );

   // Calculamos las normales de los vértices
   Calcular_normales( CalcularNormalesCaras() );

}
