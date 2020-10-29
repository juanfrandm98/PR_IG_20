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

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   // completar ......(práctica 2)

   // En primer lugar, cargamos en perfilOriginal los vértices leídos del archivo argumento
   std::vector<Tupla3f> perfilOriginal;
   ply::read_vertices( archivo, perfilOriginal );

   // Ahora creamos las tablas de vértices y triángulos
   crearMalla( perfilOriginal, num_instancias );

}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)


ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {

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

  // Rellenamos la tabla de triángulos
  for( int i = 0; i < num_instancias; i++ )
    for( int j = 0; j < perfil_original.size() - 1; j++ ) {

      int a = perfil_original.size() * i + j;
      int b = perfil_original.size() * ( ( i + 1 ) % num_instancias ) + j;

      f.push_back( Tupla3i( a, b, b + 1 ) );
      f.push_back( Tupla3i( a, b + 1, a + 1 ) );

    }

}
