#include <iostream>
#include <vector>
//#include <Eigen/Map>
#include <Eigen/Dense>
#include <boost/python.hpp>
#include <boost/numpy.hpp>


using namespace std;
namespace p = boost::python;
namespace np = boost::numpy;


np::ndarray zeros(const p::tuple& shape) {
	return np::zeros(shape, np::dtype::get_builtin<double>());
}


np::ndarray cumsum(const np::ndarray& arr) {
	int nrows = arr.shape(0);
	int ncols = arr.shape(1);
	// Py_intptr_t const* strides = arr.get_strides();
	np::ndarray py_cumsum = np::zeros(p::make_tuple(ncols), np::dtype::get_builtin<double>());
	Eigen::Map<Eigen::MatrixXd> cumsum(reinterpret_cast<double *>(py_cumsum.get_data()), 1, ncols);

	double const* const data = reinterpret_cast<double const*>(arr.get_data());
	for(int i = 0; i < nrows; i++) {
		for(int j = 0; j < ncols; j++) {
			cumsum(j) += data[i * ncols + j];
		}
	}
	return py_cumsum;
}


int main(int argc, char **argv)
{
	Py_Initialize();
	np::initialize();

	//double[] arr = {0, 1, 2, 3}
	//np::ndarray py_arr = np::from_data(arr, np::dtype::get_builtin<int>())

	p::tuple shape = p::make_tuple(5, 5);
	
	std::cout << "Reshaped array:\n" << p::extract<char const *>(p::str(zeros(shape))) << std::endl;
 
}


BOOST_PYTHON_MODULE(monjan) {
	using namespace boost::python;
	np::initialize();

	def("zeros", zeros);
	def("cumsum", cumsum);
}