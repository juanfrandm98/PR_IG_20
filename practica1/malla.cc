#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato( bool puntos, bool lineas, bool solido, bool ajedrez )
{
  glEnableClientState( GL_VERTEX_ARRAY );
  glVertexPointer( 3, GL_FLOAT, 0, v.data() );
  glEnableClientState( GL_COLOR_ARRAY );

  if( !ajedrez ) {
    // PUNTOS
    if( puntos ) {
    	glColorPointer( 3, GL_FLOAT, 0, c_points.data() );
      glPointSize( 7.5 );
      glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
      glDrawElements( GL_TRIANGLES, 3 * f.size(), GL_UNSIGNED_INT, f.data() );
    }

    // LINEAS
    if( lineas ) {
    	glColorPointer( 3, GL_FLOAT, 0, c_lines.data() );
      glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
      glDrawElements( GL_TRIANGLES, 3 * f.size(), GL_UNSIGNED_INT, f.data() );
    }

    // SOLIDO
    if( solido ) {
      glColorPointer( 3, GL_FLOAT, 0, c_solid.data() );
      glPolygonMode( GL_FRONT, GL_FILL );
      glDrawElements( GL_TRIANGLES, 3 * f.size(), GL_UNSIGNED_INT, f.data() );
    }
  } else {

    glColorPointer( 3, GL_FLOAT, 0, c_chess_impar.data() );
    glPolygonMode( GL_FRONT, GL_FILL );
    glDrawElements( GL_TRIANGLES, 3 * f_chess_impar.size(), GL_UNSIGNED_INT, f_chess_impar.data() );

    glColorPointer( 3, GL_FLOAT, 0, c_chess_par.data() );
    glPolygonMode( GL_FRONT, GL_FILL );
    glDrawElements( GL_TRIANGLES, 3 * f_chess_par.size(), GL_UNSIGNED_INT, f_chess_par.data() );

  }

}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido( bool puntos, bool lineas, bool solido, bool ajedrez )
{
  // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
  // completar (práctica 1)
  /*
  if( id_vbo_v == 0 )
    id_vbo_v = CrearVBO( GL_ARRAY_BUFFER, 3 * v.size() * sizeof(float), v.data() );

  if( id_vbo_f == 0 )
    id_vbo_f = CrearVBO( GL_ELEMENT_ARRAY_BUFFER, 3 * f.size() * sizeof(int), f.data() );

  if( id_vbo_f_impares == 0 )
    id_vbo_f_impares = CrearVBO( GL_ELEMENT_ARRAY_BUFFER, 3 * f_chess_impar.size() * sizeof(int), f_chess_impar.data() );

  if( id_vbo_f_pares == 0 )
    id_vbo_f_pares = CrearVBO( GL_ELEMENT_ARRAY_BUFFER, 3 * f_chess_par.size() * sizeof(int), f_chess_par.data() );
    */

  glBindBuffer( GL_ARRAY_BUFFER, id_vbo_v ); // Activar VBO de vértices
  glVertexPointer( 3, GL_FLOAT, 0, 0 ); // Especificar formato y offset (0)
  glBindBuffer( GL_ARRAY_BUFFER, 0 );   // Desactivar VBO de vértices
  glEnableClientState( GL_VERTEX_ARRAY );  // Habilitar tabla de vértices

  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_f );  // Activar VBO de triángulos
  glDrawElements( GL_TRIANGLES, 3 * f.size(), GL_UNSIGNED_INT, 0 );
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );   // Desactivar VBO de triángulos

  glDisableClientState( GL_VERTEX_ARRAY );

}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw( bool modoInmediato, bool puntos, bool lineas, bool solido, bool ajedrez )
{
  // completar .....(práctica 1)
  if( modoInmediato )
    draw_ModoInmediato( puntos, lineas, solido, ajedrez );
  else
    draw_ModoDiferido( puntos, lineas, solido, ajedrez );
}

GLuint CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram ) {

  GLuint id_vbo;    // resultado: identificador del VBO

  glGenBuffers( 1, &id_vbo );   // crear nuevo VBO, obtener identificador
  glBindBuffer( tipo_vbo, id_vbo );   // activar el VBO usando su identificador
  glBufferData( tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW );   // transferencia de datos desde RAM hacia CPU
  glBindBuffer( tipo_vbo, 0 );    // desactivación del VBO

  return id_vbo;

}
