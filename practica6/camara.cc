#include "camara.h"

Camara::Camara( Tupla3f e, Tupla3f a, Tupla3f u, tipoCamara ti, float l,
                float r, float t, float b, float n, float f ) {

  eye = e;
  at  = a;
  up  = u;

  tipo = ti;

  left   = l;
  right  = r;
  top    = t;
  bottom = b;
  near   = n;
  far    = f;

}

void Camara::setLeft( float nleft ) {
  left = nleft;
}

void Camara::setRight( float nright ) {
  right = nright;
}

void Camara::setTop( float ntop ) {
  top = ntop;
}

void Camara::setBottom( float nbottom ) {
  bottom = nbottom;
}

void Camara::rotarXExaminar( float angle ) {

}

void Camara::rotarYExaminar( float angle ) {

}

void Camara::rotarZExaminar( float angle ) {

}

void Camara::rotarXFirstPerson( float angle ) {

}

void Camara::rotarYFirstPerson( float angle ) {

}

void Camara::rotarZFirstPerson( float angle ) {

}

void Camara::mover( float x, float y, float z ) {

  eye(0) += x;
  eye(1) += y;
  eye(2) += z;

}

void Camara::zoom( float factor ) {

  // Todos los intrínsecos se disminuyen/aumentan
  left   *= factor;
  right  *= factor;
  top    *= factor;
  bottom *= factor;

}

void Camara::setObservador() {

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt( eye(0), eye(1), eye(2),
              at(0),  at(1),  at(2),
              up(0),  up(1),  up(2) );

}

void Camara::setProyeccion() {

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  switch( tipo ) {

    case PERSPECTIVA:
      glFrustum( left, right, bottom, top, near, far );
      break;

    case ORTOGONAL:
      glOrtho( left, right, bottom, top, near, far );
      break;

  }

}
