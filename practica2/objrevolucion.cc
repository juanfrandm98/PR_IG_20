#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

void ObjRevolucion::CrearObjeto( std::vector<Tupla3f> perfilOriginal, int num_instancias,
                                 bool tapa_sup, bool tapa_inf ) {
   // Almacenamiento (si fuera necesario) de los puntos tapa
   Tupla3f punto, puntoSup, puntoInf;

   // Si el archivo contiene tapa superior, se quita el último punto y se guarda
   if( tapa_sup ) {
     punto = perfilOriginal[ perfilOriginal.size() - 1 ];
     if( punto(0) != 0 || punto(2) != 0 )
        puntoSup = Tupla3f( 0, punto(1), 0 );
      else {
        perfilOriginal.pop_back();
        puntoSup = punto;
      }
   }

   // Si el archivo contiene tapa inferior, se quita el primer punto y se guarda
   if( tapa_inf ) {
     //puntoInf = perfilOriginal[0];
     //perfilOriginal.erase( perfilOriginal.begin() );
     punto = perfilOriginal[0];
     if( punto(0) != 0 || punto(2) != 0 )
        puntoInf = Tupla3f( 0, punto(1), 0 );
      else {
        perfilOriginal.erase( perfilOriginal.begin() );
        puntoInf = punto;
      }
   }

   // Ahora creamos las tablas de vértices y triángulos
   crearMalla( perfilOriginal, num_instancias );

   // Una vez creada la malla, si el objeto tenía tapa superior, hay que crearla
   if( tapa_inf ) {

     v.push_back( Tupla3f( 0, puntoInf(1), 0 ) );
     int contador = 0;

     for( int i = 0; i < num_instancias; i++ ) {
        int index0 = v.size() - 1;
        int index1 = ( i * ( perfilOriginal.size() ) );
        int index2 = ( index1 + perfilOriginal.size() ) % ( v.size() - 1 );
        f.push_back( Tupla3i( index0, index2, index1 ) );

        if( ( contador % 2 ) == 0 )
          f_chess_par.push_back( Tupla3i( index0, index2, index1 ) );
        else
          f_chess_impar.push_back( Tupla3i( index0, index2, index1 ) );

        contador++;
      }
   }

   // Lo mismo con la tapa superior
   if( tapa_sup ) {

     int diferencia;
     if( tapa_inf )
      diferencia = 2;
     else
      diferencia = 1;

     v.push_back( Tupla3f( 0, puntoSup(1), 0 ) );
     int contador = 0;

     for( int i = 0; i < num_instancias; i++ ) {
        int index0 = v.size() - 1;
        int index1 = perfilOriginal.size() - 1 + i * perfilOriginal.size();
        int index2 = ( index1 + perfilOriginal.size() ) % ( v.size() - diferencia );
        f.push_back( Tupla3i( index0, index1, index2 ) );

        if( ( contador % 2 ) == 0 )
          f_chess_par.push_back( Tupla3i( index0, index1, index2 ) );
        else
          f_chess_impar.push_back( Tupla3i( index0, index1, index2 ) );

        contador++;
      }
   }

   // Finalmente, colocamos los colores para que sean como los de la P1
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
}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   // completar ......(práctica 2)

   // En primer lugar, cargamos en perfilOriginal los vértices leídos del archivo argumento
   std::vector<Tupla3f> perfilOriginal;
   ply::read_vertices( archivo, perfilOriginal );

   CrearObjeto( perfilOriginal, num_instancias, tapa_sup, tapa_inf );

}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)


ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {

  CrearObjeto( archivo, num_instancias, tapa_sup, tapa_inf );

}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {

  // Rellenamos la tabla de vértices
  for( int i = 0; i < num_instancias; i++ )
    for( int j = 0; j < perfil_original.size(); j++ ) {

      float x, y, z;
      float radio = sqrt( perfil_original[j](0) * perfil_original[j](0) + perfil_original[j](2) * perfil_original[j](2) );

      x = cos( 2 * M_PI * i / num_instancias ) * radio;
      y = perfil_original[j](1);
      z = -( sin( 2 * M_PI * i / num_instancias ) * radio );

      v.push_back( Tupla3f( x, y, z ) );

    }

  int contador = 0;

  // Rellenamos la tabla de triángulos
  for( int i = 0; i < num_instancias; i++ )
    for( int j = 0; j < perfil_original.size() - 1; j++ ) {

      int a = perfil_original.size() * i + j;
      int b = perfil_original.size() * ( ( i + 1 ) % num_instancias ) + j;

      f.push_back( Tupla3i( a, b, b + 1 ) );
      f.push_back( Tupla3i( a, b + 1, a + 1 ) );

      if( ( contador % 2 ) == 0 ) {
        f_chess_par.push_back( Tupla3i( a, b, b + 1 ) );
        f_chess_par.push_back( Tupla3i( a, b, b + 1 ) );
      } else {
        f_chess_impar.push_back( Tupla3i( a, b, b + 1 ) );
        f_chess_impar.push_back( Tupla3i( a, b, b + 1 ) );
      }

      contador ++;

    }

}
