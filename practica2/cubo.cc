#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices
   v.push_back( Tupla3f( -lado / 2, 0, - lado / 2 ) );      // 0 - Abajo-Detrás-Izquierda
   v.push_back( Tupla3f( -lado / 2, 0, lado / 2 ) );     // 1 - Abajo-Delante-Izquierda
   v.push_back( Tupla3f( lado / 2, 0, lado / 2 ) );      // 2 - Abajo-Delante-Derecha
   v.push_back( Tupla3f( lado / 2, 0, -lado / 2 ) );       // 3 - Abajo-Detrás-Derecha
   v.push_back( Tupla3f( -lado / 2, lado, -lado / 2 ) );   // 4 - Arriba-Detrás-Izquierda
   v.push_back( Tupla3f( -lado / 2, lado, lado / 2 ) );  // 5 - Arriba-Delante-Izquierda
   v.push_back( Tupla3f( lado / 2, lado, lado / 2 ) );   // 6 - Arriba-Delante-Derecha
   v.push_back( Tupla3f( lado / 2, lado, -lado / 2 ) );    // 7 - Arriba-Detrás-Derecha

   // inicializar la tabla de caras o triángulos:
   f.push_back( Tupla3i( 5, 1, 6 ) ); // 0  - Delante izquierda
   f.push_back( Tupla3i( 6, 1, 2 ) ); // 1  - Delante derecha
   //f.push_back( Tupla3i( 6, 2, 1 ) ); // 1  - Delante derecha mal para probar
   f.push_back( Tupla3i( 6, 2, 7 ) );   // 2 - Derecha izquierda
   f.push_back( Tupla3i( 7, 2, 3 ) ); // 3  - Derecha derecha
   f.push_back( Tupla3i( 7, 3, 0 ) ); // 4  - Detrás izquierda
   f.push_back( Tupla3i( 4, 7, 0 ) ); // 5  - Detrás derecha
   f.push_back( Tupla3i( 4, 0, 1 ) ); // 6  - Izquierda izquierda
   f.push_back( Tupla3i( 5, 4, 1 ) ); // 7  - Izquierda derecha
   f.push_back( Tupla3i( 4, 5, 7 ) ); // 8  - Arriba izquierda
   f.push_back( Tupla3i( 7, 5, 6 ) ); // 9  - Arriba derecha
   f.push_back( Tupla3i( 0, 3, 1 ) ); // 10 - Abajo izquierda
   f.push_back( Tupla3i( 3, 2, 1 ) ); // 11 - Abajo derecha

   // Inicializar las tablas de triángulos para el modo ajedrez:
   f_chess_impar.push_back( Tupla3i( 5, 1, 6 ) ); // 0  - Delante izquierda
   f_chess_impar.push_back( Tupla3i( 6, 2, 7 ) ); // 1 - Derecha izquierda
   f_chess_impar.push_back( Tupla3i( 7, 3, 0 ) ); // 2  - Detrás izquierda
   f_chess_impar.push_back( Tupla3i( 4, 0, 1 ) ); // 3  - Izquierda izquierda
   f_chess_impar.push_back( Tupla3i( 4, 5, 7 ) ); // 4  - Arriba izquierda
   f_chess_impar.push_back( Tupla3i( 0, 3, 1 ) ); // 5 - Abajo izquierda
   f_chess_par.push_back( Tupla3i( 6, 1, 2 ) ); // 0  - Delante derecha
   f_chess_par.push_back( Tupla3i( 7, 2, 3 ) ); // 1  - Derecha derecha
   f_chess_par.push_back( Tupla3i( 4, 7, 0 ) ); // 2  - Detrás derecha
   f_chess_par.push_back( Tupla3i( 5, 4, 1 ) ); // 3  - Izquierda derecha
   f_chess_par.push_back( Tupla3i( 7, 5, 6 ) ); // 4  - Arriba derecha
   f_chess_par.push_back( Tupla3i( 3, 2, 1 ) ); // 5 - Abajo derecha

   // Inicializar colores para el modo sólido
   c_solid.push_back( Tupla3f( 1, 0, 0 ) );
   c_solid.push_back( Tupla3f( 1, 0, 0 ) );
   c_solid.push_back( Tupla3f( 1, 0, 0 ) );
   c_solid.push_back( Tupla3f( 1, 0, 0 ) );
   c_solid.push_back( Tupla3f( 1, 0, 0 ) );
   c_solid.push_back( Tupla3f( 1, 0, 0 ) );
   c_solid.push_back( Tupla3f( 1, 0, 0 ) );
   c_solid.push_back( Tupla3f( 1, 0, 0 ) );

   // Inicializar colores para el modo puntos
   c_points.push_back( Tupla3f( 255, 0, 255 ) );
   c_points.push_back( Tupla3f( 255, 0, 255 ) );
   c_points.push_back( Tupla3f( 255, 0, 255 ) );
   c_points.push_back( Tupla3f( 255, 0, 255 ) );
   c_points.push_back( Tupla3f( 255, 0, 255 ) );
   c_points.push_back( Tupla3f( 255, 0, 255 ) );
   c_points.push_back( Tupla3f( 255, 0, 255 ) );
   c_points.push_back( Tupla3f( 255, 0, 255 ) );

   // Inicializar colores para el modo líneas
   c_lines.push_back( Tupla3f( 0, 0, 0 ) );
   c_lines.push_back( Tupla3f( 0, 0, 0 ) );
   c_lines.push_back( Tupla3f( 0, 0, 0 ) );
   c_lines.push_back( Tupla3f( 0, 0, 0 ) );
   c_lines.push_back( Tupla3f( 0, 0, 0 ) );
   c_lines.push_back( Tupla3f( 0, 0, 0 ) );
   c_lines.push_back( Tupla3f( 0, 0, 0 ) );
   c_lines.push_back( Tupla3f( 0, 0, 0 ) );

   // Inicializar colores para el modo ajedrez
   c_chess_impar.push_back( Tupla3f( 1, 0, 0 ) );
   c_chess_impar.push_back( Tupla3f( 1, 0, 0 ) );
   c_chess_impar.push_back( Tupla3f( 1, 0, 0 ) );
   c_chess_impar.push_back( Tupla3f( 1, 0, 0 ) );
   c_chess_impar.push_back( Tupla3f( 1, 0, 0 ) );
   c_chess_impar.push_back( Tupla3f( 1, 0, 0 ) );
   c_chess_impar.push_back( Tupla3f( 1, 0, 0 ) );
   c_chess_impar.push_back( Tupla3f( 1, 0, 0 ) );
   c_chess_par.push_back( Tupla3f( 0, 1, 0 ) );
   c_chess_par.push_back( Tupla3f( 0, 1, 0 ) );
   c_chess_par.push_back( Tupla3f( 0, 1, 0 ) );
   c_chess_par.push_back( Tupla3f( 0, 1, 0 ) );
   c_chess_par.push_back( Tupla3f( 0, 1, 0 ) );
   c_chess_par.push_back( Tupla3f( 0, 1, 0 ) );
   c_chess_par.push_back( Tupla3f( 0, 1, 0 ) );
   c_chess_par.push_back( Tupla3f( 0, 1, 0 ) );

   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

}
