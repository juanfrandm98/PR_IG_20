#include "aux.h"
#include "malla.h"
#include "material.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato( visualizacion tipoVisualizacion )
{

  glEnableClientState( GL_VERTEX_ARRAY );
  glVertexPointer( 3, GL_FLOAT, 0, v.data() );

  if( glIsEnabled( GL_LIGHTING ) ) {
    glEnableClientState( GL_NORMAL_ARRAY );
    glNormalPointer( GL_FLOAT, 0, nv.data() );
    m->aplicar();
  } else {
    glEnableClientState( GL_COLOR_ARRAY );
  }


  switch( tipoVisualizacion ) {

    case POINTS:
      glColorPointer( 3, GL_FLOAT, 0, c_points.data() );
      glPointSize( 7.5 );
      glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
      glDrawElements( GL_TRIANGLES, 3 * f.size(), GL_UNSIGNED_INT, f.data() );
      break;

    case LINES:
      glColorPointer( 3, GL_FLOAT, 0, c_lines.data() );
      glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
      glDrawElements( GL_TRIANGLES, 3 * f.size(), GL_UNSIGNED_INT, f.data() );
      break;

    case SOLID:
      glColorPointer( 3, GL_FLOAT, 0, c_solid.data() );
      glPolygonMode( GL_FRONT, GL_FILL );
      glDrawElements( GL_TRIANGLES, 3 * f.size(), GL_UNSIGNED_INT, f.data() );
      break;

    case CHESS:
      glColorPointer( 3, GL_FLOAT, 0, c_chess_impar.data() );
      glPolygonMode( GL_FRONT, GL_FILL );
      glDrawElements( GL_TRIANGLES, 3 * f_chess_impar.size(), GL_UNSIGNED_INT, f_chess_impar.data() );

      glColorPointer( 3, GL_FLOAT, 0, c_chess_par.data() );
      glPolygonMode( GL_FRONT, GL_FILL );
      glDrawElements( GL_TRIANGLES, 3 * f_chess_par.size(), GL_UNSIGNED_INT, f_chess_par.data() );
      break;

  }

}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido( visualizacion tipoVisualizacion )
{
  // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
  // completar (práctica 1)

  // Creación de los VBOs (primera vez que se llama a draw_ModoDiferido)
  if( id_vbo_v == 0 )
    id_vbo_v = CrearVBO( GL_ARRAY_BUFFER, 3 * v.size() * sizeof(float), v.data() );

  if( id_vbo_f == 0 )
    id_vbo_f = CrearVBO( GL_ELEMENT_ARRAY_BUFFER, 3 * f.size() * sizeof(int), f.data() );

  if( id_vbo_f_impares == 0 )
    id_vbo_f_impares = CrearVBO( GL_ELEMENT_ARRAY_BUFFER, 3 * f_chess_impar.size() * sizeof(int), f_chess_impar.data() );

  if( id_vbo_f_pares == 0 )
    id_vbo_f_pares = CrearVBO( GL_ELEMENT_ARRAY_BUFFER, 3 * f_chess_par.size() * sizeof(int), f_chess_par.data() );

  if( id_vbo_c_puntos == 0 )
    id_vbo_c_puntos = CrearVBO( GL_ARRAY_BUFFER, 3 * c_points.size() * sizeof(float), c_points.data() );

  if( id_vbo_c_lineas == 0 )
    id_vbo_c_lineas = CrearVBO( GL_ARRAY_BUFFER, 3 * c_lines.size() * sizeof(float), c_lines.data() );

  if( id_vbo_c_solido == 0 )
    id_vbo_c_solido = CrearVBO( GL_ARRAY_BUFFER, 3 * c_solid.size() * sizeof(float), c_solid.data() );

  if( id_vbo_c_chess_impares == 0 )
    id_vbo_c_chess_impares = CrearVBO( GL_ARRAY_BUFFER, 3 * c_chess_impar.size() * sizeof(float), c_chess_impar.data() );

  if( id_vbo_c_chess_pares == 0 )
    id_vbo_c_chess_pares = CrearVBO( GL_ARRAY_BUFFER, 3 * c_chess_par.size() * sizeof(float), c_chess_par.data() );

  glBindBuffer( GL_ARRAY_BUFFER, id_vbo_v ); // Activar VBO de vértices
  glVertexPointer( 3, GL_FLOAT, 0, 0 ); // Especificar formato y offset (0)
  glBindBuffer( GL_ARRAY_BUFFER, 0 );   // Desactivar VBO de vértices
  glEnableClientState( GL_VERTEX_ARRAY );  // Habilitar tabla de vértices
  glEnableClientState( GL_COLOR_ARRAY );   // Habilitar tabla de colores

  switch( tipoVisualizacion ) {

    case POINTS:
      // Color
      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_c_puntos );
      glColorPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0 );

      // Tamaño y modo
      glPointSize( 7.5 );
      glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );

      // Triángulos
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_f );  // Activar VBO de triángulos
      glDrawElements( GL_TRIANGLES, 3 * f.size(), GL_UNSIGNED_INT, 0 );
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );   // Desactivar VBO de triángulos
      break;

    case LINES:
      // Color
      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_c_lineas );
      glColorPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0 );

      // Modo
      glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

      // Triángulos
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_f );  // Activar VBO de triángulos
      glDrawElements( GL_TRIANGLES, 3 * f.size(), GL_UNSIGNED_INT, 0 );
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );   // Desactivar VBO de triángulos
      break;

    case SOLID:
      // Color
      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_c_solido );
      glColorPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0 );

      // Modo
      glPolygonMode( GL_FRONT, GL_FILL );

      // Triángulos
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_f );  // Activar VBO de triángulos
      glDrawElements( GL_TRIANGLES, 3 * f.size(), GL_UNSIGNED_INT, 0 );
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );   // Desactivar VBO de triángulos
      break;

    case CHESS:
      // Color caras impares
      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_c_chess_impares );
      glColorPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0 );

      // Modo caras impares
      glPolygonMode( GL_FRONT, GL_FILL );

      // Triángulos caras impares
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_f_impares );  // Activar VBO de triángulos
      glDrawElements( GL_TRIANGLES, 3 * f_chess_impar.size(), GL_UNSIGNED_INT, 0 );
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );   // Desactivar VBO de triángulos

      // Color caras pares
      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_c_chess_pares );
      glColorPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0 );

      // Modo caras pares
      glPolygonMode( GL_FRONT, GL_FILL );

      // Triángulos caras pares
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_f_pares );  // Activar VBO de triángulos
      glDrawElements( GL_TRIANGLES, 3 * f_chess_par.size(), GL_UNSIGNED_INT, 0 );
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );   // Desactivar VBO de triángulos
      break;

  }

  glDisableClientState( GL_VERTEX_ARRAY );
  glDisableClientState( GL_COLOR_ARRAY );

}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw( dibujado tipoDibujado, visualizacion tipoVisualizacion )
{

  switch( tipoDibujado ) {
    case INMEDIATO:
      draw_ModoInmediato( tipoVisualizacion );
      break;
    case DIFERIDO:
      draw_ModoDiferido( tipoVisualizacion );
  }

}

GLuint Malla3D::CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram ) {

  GLuint id_vbo;    // resultado: identificador del VBO

  glGenBuffers( 1, &id_vbo );   // crear nuevo VBO, obtener identificador
  glBindBuffer( tipo_vbo, id_vbo );   // activar el VBO usando su identificador
  glBufferData( tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW );   // transferencia de datos desde RAM hacia CPU
  glBindBuffer( tipo_vbo, 0 );    // desactivación del VBO

  return id_vbo;

}

void Malla3D::Calcular_normales( std::vector<Tupla3f> normalesCaras ) {

  // Inicializamos las normales de cada vértice a 0
  for( int i = 0; i < v.size(); i++ )
    nv.push_back( Tupla3f( 0.0, 0.0, 0.0 ) );

  // Recorremos el vector de caras, sumándo la normal de dicha cara a la de los
  // tres vértices que la componen
  for( int i = 0; i < f.size(); i++ ) {
    int v1, v2, v3;

    v1 = f[i][0]; v2 = f[i][1]; v3 = f[i][2];

    nv[v1] = nv[v1] + normalesCaras[i];
    nv[v2] = nv[v2] + normalesCaras[i];
    nv[v3] = nv[v3] + normalesCaras[i];
  }

  // Se normalizan las normales finales
  for( int i = 0; i < nv.size(); i++ )
    nv[i] = nv[i].normalized();

}

std::vector<Tupla3f> Malla3D::CalcularNormalesCaras() {

  std::vector<Tupla3f> normalesCaras;

  for( int i = 0; i < f.size(); i++ ) {

    Tupla3f v1, v2, v3;

    // Obtenemos los vértices que forman la cara
    v1 = v[f[i][0]]; v2 = v[f[i][1]]; v3 = v[f[i][2]];

    // Calculamos dos aristas
    Tupla3f a = v2 - v1;
    Tupla3f b = v3 - v1;

    // Calculamos la normal y la normalizamos
    Tupla3f normal = a.cross(b);
    Tupla3f normalizada = normal.normalized();

    normalesCaras.push_back( normalizada );

  }

  return normalesCaras;

}

void Malla3D::setMaterial( Material mat ) {
  m = new Material( mat );
}

void Malla3D::drawLight() {

  glEnableClientState( GL_VERTEX_ARRAY );
  glEnableClientState( GL_NORMAL_ARRAY );
  glVertexPointer( 3, GL_FLOAT, 0, v.data() );
  glNormalPointer( GL_FLOAT, 0, nv.data() );

  m->aplicar();

  glDrawElements( GL_TRIANGLES, 3 * f.size(), GL_UNSIGNED_INT, f.data() );

}

void Malla3D::setColorSolido( Tupla3f nuevoColor ) {
  while( !c_solid.empty() )
    c_solid.pop_back();

  for( int i = 0; i < v.size(); i++ )
    c_solid.push_back( nuevoColor );
}
