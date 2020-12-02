#ifndef LUZ_DIRECCIONAL_H_INCLUDED
#define LUZ_DIRECCIONAL_H_INCLUDED

#include "luz.h"

class LuzDireccional : public Luz
{

  protected:
    float alpha;
    float beta;

    // Función que actualiza la posición de la luz en función de los ángulos
    // alpha y beta
    void actualizarPosicion();

  public:
    // Constructor
    LuzDireccional( const Tupla2f & orientacion, const GLenum & ident,
                    const Tupla4f & camb, const Tupla4f & cesp, const Tupla4f & cdif ) ;

    // Funciones para el cambio de ángulo
    void variarAnguloAlpha( float incremento );
    void variarAnguloBeta( float incremento );

} ;

#endif
