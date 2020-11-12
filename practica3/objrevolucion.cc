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
   int contador;
   const float EPSILON = 0.0000000000000000001;

   // Si el archivo contiene tapa superior, se quita el último punto y se guarda
   if( tapa_sup ) {
     punto = perfilOriginal[ perfilOriginal.size() - 1 ];
     //if( punto(0) != 0 || punto(2) != 0 )
     if( fabs( punto(0) ) > EPSILON || fabs( punto(2) ) > EPSILON )
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
     //if( punto(0) != 0 || punto(2) != 0 )
     if( fabs( punto(0) ) > EPSILON || fabs( punto(2) ) > EPSILON )
        puntoInf = Tupla3f( 0, punto(1), 0 );
      else {
        perfilOriginal.erase( perfilOriginal.begin() );
        puntoInf = punto;
      }
   }

   // Ahora creamos las tablas de vértices y triángulos
   crearMalla( perfilOriginal, num_instancias );

   // Creamos las tablas de triángulos para el modo ajedrez
   for( int i = 0; i < f.size(); i++ )
    if( i % 2 == 0 )
      f_chess_par.push_back( f[i] );
    else
      f_chess_impar.push_back( f[i] );

   // Una vez creada la malla, si el objeto tenía tapa superior, hay que crearla
   if( tapa_inf ) {

     v.push_back( Tupla3f( 0, puntoInf(1), 0 ) );
     contador = 0;

     for( int i = 0; i < num_instancias; i++ ) {
        int index0 = v.size() - 1;
        int index1 = ( i * ( perfilOriginal.size() ) );
        int index2 = ( index1 + perfilOriginal.size() ) % ( v.size() - 1 );
        f_tapa_inf.push_back( Tupla3i( index0, index2, index1 ) );

        if( ( contador % 2 ) == 0 )
          f_chess_par_tapa_inf.push_back( Tupla3i( index0, index2, index1 ) );
        else
          f_chess_impar_tapa_inf.push_back( Tupla3i( index0, index2, index1 ) );

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
     contador = 0;

     for( int i = 0; i < num_instancias; i++ ) {
        int index0 = v.size() - 1;
        int index1 = perfilOriginal.size() - 1 + i * perfilOriginal.size();
        int index2 = ( index1 + perfilOriginal.size() ) % ( v.size() - diferencia );
        f_tapa_sup.push_back( Tupla3i( index0, index1, index2 ) );

        if( ( contador % 2 ) == 0 )
          f_chess_par_tapa_sup.push_back( Tupla3i( index0, index1, index2 ) );
        else
          f_chess_impar_tapa_sup.push_back( Tupla3i( index0, index1, index2 ) );

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

   // Calculamos las normales de los vértices
   CalcularNormalesRev();
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

    }

}

void ObjRevolucion::draw_tapas( visualizacion tipoVisualizacion, bool superior, bool inferior )
{

  glEnableClientState( GL_VERTEX_ARRAY );
  glVertexPointer( 3, GL_FLOAT, 0, v.data() );
  glEnableClientState( GL_COLOR_ARRAY );

  bool tengosup = !f_tapa_sup.empty();
  bool tengoinf = !f_tapa_inf.empty();

  switch( tipoVisualizacion ) {

    case POINTS:
      glColorPointer( 3, GL_FLOAT, 0, c_points.data() );
      glPointSize( 7.5 );
      glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
      if( superior and tengosup )
        glDrawElements( GL_TRIANGLES, 3 * f_tapa_sup.size(), GL_UNSIGNED_INT, f_tapa_sup.data() );
      if( inferior and tengoinf )
        glDrawElements( GL_TRIANGLES, 3 * f_tapa_inf.size(), GL_UNSIGNED_INT, f_tapa_inf.data() );
      break;

    case LINES:
      glColorPointer( 3, GL_FLOAT, 0, c_lines.data() );
      glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
      if( superior and tengosup )
        glDrawElements( GL_TRIANGLES, 3 * f_tapa_sup.size(), GL_UNSIGNED_INT, f_tapa_sup.data() );
      if( inferior and tengoinf )
        glDrawElements( GL_TRIANGLES, 3 * f_tapa_inf.size(), GL_UNSIGNED_INT, f_tapa_inf.data() );
      break;

    case SOLID:
      glColorPointer( 3, GL_FLOAT, 0, c_solid.data() );
      glPolygonMode( GL_FRONT, GL_FILL );
      if( superior and tengosup )
        glDrawElements( GL_TRIANGLES, 3 * f_tapa_sup.size(), GL_UNSIGNED_INT, f_tapa_sup.data() );
      if( inferior and tengoinf )
        glDrawElements( GL_TRIANGLES, 3 * f_tapa_inf.size(), GL_UNSIGNED_INT, f_tapa_inf.data() );
      break;

    case CHESS:
      glColorPointer( 3, GL_FLOAT, 0, c_chess_impar.data() );
      glPolygonMode( GL_FRONT, GL_FILL );
      if( superior and tengosup )
        glDrawElements( GL_TRIANGLES, 3 * f_chess_impar_tapa_sup.size(), GL_UNSIGNED_INT, f_chess_impar_tapa_sup.data() );
      if( inferior and tengoinf )
        glDrawElements( GL_TRIANGLES, 3 * f_chess_impar_tapa_inf.size(), GL_UNSIGNED_INT, f_chess_impar_tapa_inf.data() );

      glColorPointer( 3, GL_FLOAT, 0, c_chess_par.data() );
      glPolygonMode( GL_FRONT, GL_FILL );
      if( superior and tengosup )
        glDrawElements( GL_TRIANGLES, 3 * f_chess_par_tapa_sup.size(), GL_UNSIGNED_INT, f_chess_par_tapa_sup.data() );
      if( inferior and tengoinf )
        glDrawElements( GL_TRIANGLES, 3 * f_chess_par_tapa_inf.size(), GL_UNSIGNED_INT, f_chess_par_tapa_inf.data() );
      break;

  }

}

void ObjRevolucion::CalcularNormalesRev() {

  // Obtenemos las normales de las caras del perfil
  std::vector<Tupla3f> normalesCaras = CalcularNormalesCaras();

  // Obtenemos las normales de las caras de las tapas y las añadimos:
  std::vector<Tupla3f> normalesTapas = CalcularNormalesTapas();
  for( int i = 0; i < normalesTapas.size(); i++ )
    normalesCaras.push_back( normalesTapas[i] );

  // Obtenemos las normales de los vértices
  Calcular_normales( normalesCaras );

}

std::vector<Tupla3f> ObjRevolucion::CalcularNormalesTapas() {

  std::vector<Tupla3f> normalesTapas;

  // Tapa inferior
  for( int i = 0; i < f_tapa_inf.size(); i++ ) {

    Tupla3f v1, v2, v3;

    // Obtenemos los vértices que forman la cara
    v1 = v[f_tapa_inf[i][0]]; v2 = v[f_tapa_inf[i][1]]; v3 = v[f_tapa_inf[i][2]];

    // Calculamos dos aristas
    Tupla3f a = v2 - v1;
    Tupla3f b = v3 - v1;

    // Calculamos la normal y la normalizamos
    Tupla3f normal = a.cross(b);
    Tupla3f normalizada = normal.normalized();

    normalesTapas.push_back( normalizada );

  }

  // Tapa superior
  for( int i = 0; i < f_tapa_sup.size(); i++ ) {

    Tupla3f v1, v2, v3;

    // Obtenemos los vértices que forman la cara
    v1 = v[f_tapa_sup[i][0]]; v2 = v[f_tapa_sup[i][1]]; v3 = v[f_tapa_sup[i][2]];

    // Calculamos dos aristas
    Tupla3f a = v2 - v1;
    Tupla3f b = v3 - v1;

    // Calculamos la normal y la normalizamos
    Tupla3f normal = a.cross(b);
    Tupla3f normalizada = normal.normalized();

    normalesTapas.push_back( normalizada );

  }

  return normalesTapas;

}
