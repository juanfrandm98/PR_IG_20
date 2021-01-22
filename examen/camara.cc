#include "camara.h"

Camara::Camara( Tupla3f e, Tupla3f a, Tupla3f u, tipoCamara ti, float l,
                float r, float t, float b, float n, float f ) {

  eye = e;
  at  = a;
  up  = u;

  tipo = ti;
  objetoSeleccionado = false;

  left   = l;
  right  = r;
  top    = t;
  bottom = b;
  near   = n;
  far    = f;

}

void Camara::setAt( Tupla3f nat ) {
  at = nat;
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

  Tupla3f nuevo_eye = eye - at;
  angle *= FACTOR_GRAD_RAD;

  float z = nuevo_eye(2);
  float y = nuevo_eye(1);

  nuevo_eye(2) = z * cos(angle) + y * sin(angle);
  nuevo_eye(1) = -z * sin(angle) + y * cos(angle);

  eye = nuevo_eye + at;

}

void Camara::rotarYExaminar( float angle ) {

  Tupla3f nuevo_eye = eye - at;
  angle *= FACTOR_GRAD_RAD;

  float x = nuevo_eye(0);
  float z = nuevo_eye(2);

  nuevo_eye(0) = x * cos(angle) + z * sin(angle);
  nuevo_eye(2) = -x * sin(angle) + z * cos(angle);

  eye = nuevo_eye + at;

}

void Camara::rotarZExaminar( float angle ) {

  Tupla3f nuevo_eye = eye - at;
  angle *= FACTOR_GRAD_RAD;

  float x = nuevo_eye(0);
  float y = nuevo_eye(1);

  nuevo_eye(0) = x * cos(angle) + -y * sin(angle);
  nuevo_eye(1) = x * sin(angle) + y * cos(angle);

  eye = nuevo_eye + at;

}

void Camara::rotarXFirstPerson( float angle ) {

  Tupla3f nuevo_at = at - eye;
  angle *= FACTOR_GRAD_RAD;

  float z = nuevo_at(2);
  float y = nuevo_at(1);

  nuevo_at(2) = z * cos(angle) + y * sin(angle);
  nuevo_at(1) = -z * sin(angle) + y * cos(angle);

  at = nuevo_at + eye;

}

void Camara::rotarYFirstPerson( float angle ) {

  Tupla3f nuevo_at = at - eye;
  angle *= FACTOR_GRAD_RAD;

  float x = nuevo_at(0);
  float z = nuevo_at(2);

  nuevo_at(0) = x * cos(angle) + z * sin(angle);
  nuevo_at(2) = -x * sin(angle) + z * cos(angle);

  at = nuevo_at + eye;

}

void Camara::rotarZFirstPerson( float angle ) {

  Tupla3f nuevo_at = at - eye;
  angle *= FACTOR_GRAD_RAD;

  float x = nuevo_at(0);
  float y = nuevo_at(1);

  nuevo_at(0) = x * cos(angle) + -y * sin(angle);
  nuevo_at(1) = x * sin(angle) + y * cos(angle);

  at = nuevo_at + eye;

}

void Camara::mover( direccionMovimiento dir ) {

  if( !objetoSeleccionado ) {

    Tupla3f movimiento = Tupla3f( 0, 0, 0 );
    Tupla3f direccion  = Tupla3f( 0, 0, 0 );

    switch( dir ) {

      case ARRIBA:
        movimiento(1) = 1;
        break;

      case ABAJO:
        movimiento(1) = -1;
        break;

      case ALANTE:
        movimiento = calcularDireccion();
        break;

      case ATRAS:
        movimiento = calcularDireccion();
        movimiento(0) *= -1;
        movimiento(1) *= -1;
        movimiento(2) *= -1;
        break;

      case IZDA:
        movimiento = calcularDireccion();
        movimiento = rotarDireccion( movimiento, 90 );
        movimiento(1) = 0;
        break;

      case DCHA:
        movimiento = calcularDireccion();
        movimiento = rotarDireccion( movimiento, -90 );
        movimiento(1) = 0;
        break;

    }

    eye(0) += movimiento(0);
    eye(1) += movimiento(1);
    eye(2) += movimiento(2);

    at(0) += movimiento(0);
    at(1) += movimiento(1);
    at(2) += movimiento(2);

  }

}

void Camara::zoom( float factor ) {

  // Los intrínsecos que controlan el plano se disminuyen/aumentan
  left   *= factor;
  right  *= factor;
  top    *= factor;
  bottom *= factor;

}

void Camara::zoomIn() {
  zoom( factorZoomIn );
}

void Camara::zoomOut() {
  zoom( factorZoomOut );
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

void Camara::setObjetoSeleccionado( bool seleccionado ) {

  objetoSeleccionado = seleccionado;

}

void Camara::rotarCamara( ejeRotacion eje, float angle ) {

  if( !objetoSeleccionado ) {

    switch(eje) {
      case ROTX:
        rotarXFirstPerson(angle);
        break;

      case ROTY:
        rotarYFirstPerson(angle);
        break;

      case ROTZ:
        rotarZFirstPerson(angle);
        break;
    }

  } else {

    switch(eje) {
      case ROTX:
        rotarXExaminar(-angle);
        break;

      case ROTY:
        rotarYExaminar(-angle);
        break;

      case ROTZ:
        rotarZExaminar(-angle);
        break;
    }

  }

}

void Camara::girar( int x, int y ) {

  if( objetoSeleccionado ) {
    rotarYExaminar(x);
    rotarXExaminar(y);
  } else {
    rotarYFirstPerson(-x);
    rotarXFirstPerson(-y);
  }

}

Tupla3f Camara::calcularDireccion() {

  Tupla3f direccion = at - eye;

  if( direccion(0) != 0 or direccion(1) != 0 or direccion(2) != 0 )
    return direccion.normalized();
  else
    return direccion;

}

Tupla3f Camara::rotarDireccion( Tupla3f direccionOrignial, float angulo ) {

  Tupla3f direccionRotada;
  angulo *= FACTOR_GRAD_RAD;

  float x = direccionOrignial(0);
  float y = direccionOrignial(1);
  float z = direccionOrignial(2);

  direccionRotada(0) = x * cos(angulo) + z * sin(angulo);
  direccionRotada(1) = y;
  direccionRotada(2) = -x * sin(angulo) + z * cos(angulo);

  return direccionRotada;

}
