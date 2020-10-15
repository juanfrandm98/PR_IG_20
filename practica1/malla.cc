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
    //glPolygonOffset( 1, 1 );
    glColorPointer( 3, GL_FLOAT, 0, c_solid.data() );
    glPolygonMode( GL_FRONT, GL_FILL );
    glDrawElements( GL_TRIANGLES, 3 * f.size(), GL_UNSIGNED_INT, f.data() );
  }

}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido( bool puntos, bool lineas, bool solido, bool ajedrez )
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw( bool puntos, bool lineas, bool solido, bool ajedrez )
{
   // completar .....(práctica 1)
   draw_ModoInmediato( puntos, lineas, solido, ajedrez );
}
