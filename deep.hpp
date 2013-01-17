
#ifndef __DEEP_H
#define __DEEP_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <Sacado.hpp>

namespace ublas = boost::numeric::ublas;

typedef Sacado::Fad::DFad<double> adouble;
typedef ublas::matrix<adouble> ADMatrix;



#endif // __DEEP_H