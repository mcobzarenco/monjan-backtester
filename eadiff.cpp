#include <iostream>
// #include <cmath>
#include <typeinfo>

#include <Eigen/Dense>
#include "rad/rad.h"

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;


typedef Eigen::Matrix<ADvar, Eigen::Dynamic, Eigen::Dynamic> ADMatrixXd;
typedef Eigen::Matrix<ADvar, Eigen::Dynamic, 1> ADVectorXd;



void pm(string s, Eigen::Matrix<ADvar, -1, -1> m) {
	cout << s << endl;
	for(int i = 0; i < m.rows(); i++) {
		for(int j = 0; j < m.cols(); j++) {
			cout << m(i, j).val() << " ";
		}
		cout << endl;
	}
}

void pv(string s, Eigen::Matrix<ADvar, -1, 1> v) {
	cout << s << endl;
	for(int i = 0; i < v.size(); i++)
		cout << v(i).val() << endl;
}


ADvar obj(MatrixXd X, VectorXd y, ADVectorXd w) {
	ADMatrixXd XX(X.rows(), X.cols());
	for(int i = 0; i < X.rows(); i++)
		for(int j = 0; j < X.cols(); j++)
			XX(i, j) = X(i, j);

	ADVectorXd yy(y.size());
	for(int i = 0; i < yy.size(); i++)
			yy(i) = y(i);

	
	pm("Xw - y", XX * XX);
 	//ADVectorXd pred = (XX * w - yy);
 	// ADvar ss = 0.0;
 	// for(int i = 0; i < pred.size(); i++)
 	// 	ss += pred(i) * pred(i);
 	// return ss;
}




int main(int argc, char ** argv) {
	// Eigen::Matrix<double, 1, 1> one;
	// one(0, 0) = -1;
	// Eigen::AutoDiffScalar<Eigen::VectorXd> a(1.0, 1, 0);
	// Eigen::AutoDiffScalar<Eigen::Matrix<double, 1, 1> > b(std::sin(a) + 8.0 * std::cos(a));
	// cout << "a: " << a.derivatives().cols() << 'x' << a.derivatives().rows() << endl;
	// cout << "b: " << b.derivatives().cols() << 'x' << b.derivatives().rows() << endl;
	// cout << a << endl;
	// cout << (a.derivatives()) << endl;
	// cout << (std::cos(a) - 8.0 * std::sin(a)) << endl;
	// cout << b << endl;
	// cout << (b.derivatives()) << endl;

	MatrixXd X(3, 3);
	X << 1, 2, 3, 4, 5, 6, 7, 8, 9;
	cout << X << endl;

	VectorXd y(3);
	y << -1, 0, 1;
	cout << y << endl;	

	ADVectorXd w(3);
	for(int i = 0; i < 3; i++) {
		w(i) = ADvar(1.0);
	}
	pv("w", w);


	obj(X, y, w);

	


	// ADvar ss;
	// ss = obj(X, y, w);
	//ADcontext::Gradcomp();
	// for(int n = 0; n < 5; ++n) {
	// 	// ss = obj(X, y, w);
	// 	//cout << "fsd"<<endl;
	// 	ADvar ss = obj(X, y, w);
	// 	pm("X", X);
	// 	ADcontext::Gradcomp();
	// 	 pm("X", X);

	// 	cout << "obj: " << ss.val() << " | ";
	// 	for(int i = 0; i < w.size(); ++i) {
	// 		cout << w(i).val() << " ";
	// 	}
	// 	cout << endl;

	// 	for(int i = 0; i < w.size(); ++i) {
	// 		w(i) -= 0.001 * w(i).adj();
	// 	}
		
		
	// }

	
	return 0;
}
