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

float Camara::angulo( Tupla2f a, Tupla2f b ) {

  float ab = a(0) * b(0) + a(1) * b(1);
  if( ab == 0 )
    return 0;
  float moda = sqrt( a(0) * a(0) + a(1) * a(1) );
  float modb = sqrt( b(0) * b(0) + b(1) * b(1) );
  float cosang = ab / ( moda * modb );
  return acos( cosang );

}

std::vector<Tupla3f> Camara::deshacerEjes( std::vector<Tupla3f> ejes, float alpha, float beta, float gamma ) {

  Tupla3f n = ejes[0]; Tupla3f u = ejes[1]; Tupla3f v = ejes[2];
  float x,y,z;

  x = n(0); y = n(1);
  n(0) = x * cos(-gamma) + -y * sin(-gamma); n(1) = x * sin(-gamma) + y * cos(-gamma);
  x = u(0); y = u(1);
  u(0) = x * cos(-gamma) + -y * sin(-gamma); u(1) = x * sin(-gamma) + y * cos(-gamma);
  x = v(0); y = v(1);
  v(0) = x * cos(-gamma) + -y * sin(-gamma); v(1) = x * sin(-gamma) + y * cos(-gamma);

  x = n(0); y = n(1);
  n(0) = x * cos(-beta) + -y * sin(-beta); n(1) = x * sin(-beta) + y * cos(-beta);
  x = u(0); y = u(1);
  u(0) = x * cos(-beta) + -y * sin(-beta); u(1) = x * sin(-beta) + y * cos(-beta);
  x = v(0); y = v(1);
  v(0) = x * cos(-beta) + -y * sin(-beta); v(1) = x * sin(-beta) + y * cos(-beta);

  y = n(1); z = n(2);
  n(1) = -z * sin(-alpha) + y * cos(-alpha); n(2) = z * cos(-alpha) + y * sin(-alpha);
  y = u(1); z = u(2);
  u(1) = -z * sin(-alpha) + y * cos(-alpha); u(2) = z * cos(-alpha) + y * sin(-alpha);
  y = v(1); z = v(2);
  v(1) = -z * sin(-alpha) + y * cos(-alpha); v(2) = z * cos(-alpha) + y * sin(-alpha);

  std::cout << "N final sin mover: [" << n(0) << "," << n(1) << "," << n(2) << "]\n";

  // SACAR EL NUEVO VRP Y SUMARLO A CADA COMPONENTE

  std::vector<Tupla3f> devolver;

  Tupla3f nuevo_eye = n + at;
  devolver.push_back( nuevo_eye );

  // SACAR EL NUEVO UP CON PRODUCTO VECTORIAL INVERSO Y AÑADIRLO A DEVOLVER

  return devolver;

}

std::vector<Tupla3f> Camara::colocarEjes( float & alpha, float & beta, float & gamma ) {

  float x,y,z;
  float proyec_x, proyec_y, proyec_z;

  Tupla3f vrp = eye;
  Tupla3f vpn = eye - at;
  Tupla3f vup = up;

  Tupla3f n = vpn;
  Tupla3f u = vup.cross( vpn );
  Tupla3f v = n.cross(u);

  std::cout << "N inicial: [" << n(0) << "," << n(1) << "," << n(2) << "]\n";

  n(0) -= vrp(0); n(1) -= vrp(1); n(2) -= vrp(2);
  u(0) -= vrp(0); u(1) -= vrp(1); u(2) -= vrp(2);
  v(0) -= vrp(0); v(1) -= vrp(1); v(2) -= vrp(2);

  std::cout << "N inicial movido: [" << n(0) << "," << n(1) << "," << n(2) << "]\n";

  proyec_y = n(1);
  proyec_z = n(2);
  alpha = angulo( Tupla2f( proyec_z, proyec_y ), Tupla2f( 1, 0 ) );
  if( n(0) > 0 )
    alpha = -alpha;

  y = n(1); z = n(2);
  n(1) = -z * sin(alpha) + y * cos(alpha); n(2) = z * cos(alpha) + y * sin(alpha);
  y = u(1); z = u(2);
  u(1) = -z * sin(alpha) + y * cos(alpha); u(2) = z * cos(alpha) + y * sin(alpha);
  y = v(1); z = v(2);
  v(1) = -z * sin(alpha) + y * cos(alpha); v(2) = z * cos(alpha) + y * sin(alpha);

  proyec_x = n(0);
  proyec_z = n(2);
  beta = angulo( Tupla2f( proyec_z, proyec_x ), Tupla2f( 1, 0 ) );
  if( n(1) > 0 )
    beta = -beta;

  x = n(0); y = n(1);
  n(0) = x * cos(beta) + -y * sin(beta); n(1) = x * sin(beta) + y * cos(beta);
  x = u(0); y = u(1);
  u(0) = x * cos(beta) + -y * sin(beta); u(1) = x * sin(beta) + y * cos(beta);
  x = v(0); y = v(1);
  v(0) = x * cos(beta) + -y * sin(beta); v(1) = x * sin(beta) + y * cos(beta);

  proyec_x = u(0);
  proyec_y = u(1);
  gamma = angulo( Tupla2f( proyec_x, proyec_y ), Tupla2f( 1, 0 ) );
  if( u(1) > 0 )
    gamma = -gamma;

  x = n(0); y = n(1);
  n(0) = x * cos(gamma) + -y * sin(gamma); n(1) = x * sin(gamma) + y * cos(gamma);
  x = u(0); y = u(1);
  u(0) = x * cos(gamma) + -y * sin(gamma); u(1) = x * sin(gamma) + y * cos(gamma);
  x = v(0); y = v(1);
  v(0) = x * cos(gamma) + -y * sin(gamma); v(1) = x * sin(gamma) + y * cos(gamma);

  std::vector<Tupla3f> ejes;
  ejes.push_back(n), ejes.push_back(u), ejes.push_back(v);

  return ejes;

}

void Camara::rotarXExaminar( float angle ) {

  Tupla3f nuevo_eye = eye - at;
  angle *= FACTOR_GRAD_RAD;

  float z = nuevo_eye(2);
  float y = nuevo_eye(1);

  nuevo_eye(2) = z * cos(angle) + y * sin(angle);
  nuevo_eye(1) = -z * sin(angle) + y * cos(angle);

  eye = nuevo_eye + at;
/*
  float alpha, beta, gamma;
  float y, z;

  std::vector<Tupla3f> ejesColocados = colocarEjes( alpha, beta, gamma );
  std::vector<Tupla3f> ejesColocadosGirados;

  Tupla3f n_colocado = ejesColocados[0];
  std::cout << "N colocado: [" << n_colocado(0) << "," << n_colocado(1) << "," << n_colocado(2) << "]\n";
  y = n_colocado(1);
  z = n_colocado(2);
  n_colocado(1) = -z * sin(angle) + y * cos(angle);
  n_colocado(2) = z * cos(angle) + y * sin(angle);
  std::cout << "N colocado y girado: [" << n_colocado(0) << "," << n_colocado(1) << "," << n_colocado(2) << "]\n";
  ejesColocadosGirados.push_back( n_colocado );

  Tupla3f u_colocado = ejesColocados[1];
  y = u_colocado(1);
  z = u_colocado(2);
  u_colocado(1) = -z * sin(angle) + y * cos(angle);
  u_colocado(2) = z * cos(angle) + y * sin(angle);
  ejesColocadosGirados.push_back( u_colocado );

  Tupla3f v_colocado = ejesColocados[2];
  y = v_colocado(1);
  z = v_colocado(2);
  v_colocado(1) = -z * sin(angle) + y * cos(angle);
  v_colocado(2) = z * cos(angle) + y * sin(angle);
  ejesColocadosGirados.push_back( v_colocado );

  std::vector<Tupla3f> ejesNuevaPosicion = deshacerEjes( ejesColocadosGirados, alpha, beta, gamma );
*/
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
        movimiento = rotarDireccion( movimiento, -90 );
        break;

      case DCHA:
        movimiento = calcularDireccion();
        movimiento = rotarDireccion( movimiento, 90 );
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
