#include <iostream>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <Sacado.hpp>


using namespace std;
using namespace boost::numeric::ublas;

typedef Sacado::Fad::DFad<double> adouble;
//typedef Eigen::Matrix<adouble, Eigen::Dynamic, Eigen::Dynamic> ADMatrixXd;
typedef matrix<adouble> ADMatrixXd;


// The function to differentiate
template <typename ScalarT>
ScalarT func(const ScalarT& a, const ScalarT& b, const ScalarT& c) {
	ScalarT r = c*std::log(b+1.)/std::sin(a);
	return r;
}

template <typename Scalar>
Scalar obj(matrix<Scalar> X, matrix<Scalar> y, matrix<Scalar> w) {
	matrix<Scalar> pred = prod(X, w);
	// for(int i = 0; i < pred.size1(); i++) {
	// 	pred(i, 0) = 1 / (1 + exp(-pred(i, 0)));
	// }
	pred -= y;
	return prod(trans(pred), pred)(0, 0) / 8;
}


template <typename Scalar>
Scalar obj2(matrix<Scalar> X, matrix<Scalar> y, matrix<Scalar> w) {
	matrix<Scalar> pred = prod(X, w);
	for(int i = 0; i < pred.size1(); i++) {
		pred(i, 0) = 1 / (1 + exp(-pred(i, 0)));
	}
	pred -= y;
	return prod(trans(pred), pred)(0, 0) / 8;
}

void pm(string s, ADMatrixXd m) {
	cout << s << endl;
	for(int i = 0; i < m.size1(); i++) {
		for(int j = 0; j < m.size2(); j++) {
			cout << setw(3) << m(i, j).val() << " ";
		}
		cout << endl;
	}
}


int main(int argc, char **argv) {
	matrix<adouble> X(8, 4);
	for(int i = 0; i < X.size1(); i++) {
		for(int j = 0; j < X.size2(); j++) {
			X(i, j) = i + j;
		}
	}
	pm("X", X);

	matrix<adouble> y(8, 1);
	for(int i = 0; i < y.size1(); i++) {
			y(i, 0) = ((double)i*i) / 64;
	}
	pm("y", y);

	matrix<adouble> w(4, 1);
	int num_deriv = 4;
	for(int i = 0; i < w.size1(); i++)
		w(i, 0).diff(i, num_deriv);
	pm("w", w);


	double l = 0.001;
	std::vector<double> dxs(4);
	adouble o;
	for(int n = 0; n < 10000; n++) {
		o = obj(X, y, w);
		cout << "Objective: " << o << endl;
		// pm("w", w);
		//cout << "Grad: ";
		for(int i = 0; i < w.size1(); i++) {
			dxs[i] = o.dx(i);
			//cout << dxs[i] << " ";
		}
		//cout << endl;
		for(int i = 0; i < w.size1(); i++) {
			w(i, 0) -= l * dxs[i];
		}
	}
	pm("X", X);
	pm("w", w);
	pm("Xw", prod(X, w));
	pm("y", y);

	
	

	// int num_deriv = 1;                                // Number of independent variables
	// m(1, 1).diff(0, num_deriv);
	// adouble r = prod(m, m)(1, 0);
	// cout << r.dx(0) << endl;

	// pm("m", m);
	

	// // Fad objects
	// adouble a(num_deriv, 0, 1.5); // First (0) indep. var
	// adouble b;
	
	// // Compute function and derivative with AD
	// b = func2(a);

	// // Extract value and derivatives
	// // double r_ad = rfad.val();     // r
	// // double drda_ad = rfad.dx(0);  // dr/da
	// // double drdb_ad = rfad.dx(1);  // dr/db
	// pm("m", m);
	// cout << a.val() << " " << b.val() << " " << b.dx(0) << endl;
}