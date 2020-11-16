#ifndef LUZ_POSICIONAL_H_INCLUDED
#define LUZ_POSICIONAL_H_INCLUDED

#include "luz.h"

class LuzPosicional : public Luz
{

  public:
    // Constructor
    LuzPosicional( const Tupla3f & pos, const GLenum & ident, const Tupla4f & camb,
                   const Tupla4f & cesp, const Tupla4f & cdif);


} ;

#endif
