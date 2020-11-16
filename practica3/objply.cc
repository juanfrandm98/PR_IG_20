#include "objply.h"
#include "ply_reader.h"


// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, this->v, this->f );

   // Separamos las caras en pares e impares
   for( int i = 0; i < f.size(); i++ )
    if( i % 2 == 0 )
      f_chess_par.push_back( f[i] );
    else
      f_chess_impar.push_back( f[i] );

   // Estipulamos los colores como en la P1
   for( int i = 0; i < v.size(); i++ )
      c_solid.push_back( Tupla3f( 1, 0, 0 ) );

   for( int i = 0; i < v.size(); i++ )
      c_points.push_back( Tupla3f( 255, 0, 255 ) );

   for( int i = 0; i < v.size(); i++ )
      c_lines.push_back( Tupla3f( 0, 0, 0 ) );

   for( int i = 0; i < v.size(); i++ )
      c_chess_impar.push_back( Tupla3f( 1, 0, 0 ) );

   for( int i = 0; i < v.size(); i++ )
      c_chess_par.push_back( Tupla3f( 0, 1, 0 ) );

   // Calculamos las normales de los vértices
   Calcular_normales( CalcularNormalesCaras() );
   
}
