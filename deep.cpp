
#include "deep.hpp"

#include <iostream>
#include <fstream>
#include <list>
#include <initializer_list>

#include <chrono>
#include <random>

#include <boost/numeric/ublas/io.hpp>
#include <msgpack.hpp>


using namespace std;

namespace deep {	
	class NeedAtLeastOneLayer:public std::exception {};

	class FeedforwardNetwork {
	public:
		FeedforwardNetwork(std::initializer_list<int> layers) {
			if (layers.size() < 2)
				throw NeedAtLeastOneLayer();
			int last;
			for(auto i = layers.begin(); i != layers.end(); ++i) {
				if (i != layers.begin())
					this->layers.push_back(ADMatrix(last, *i));
				last = *i;
			}
		}

		template<typename Writer>
		void serialise(Writer& writer) {
			std::vector<double> v = {1.4, 2.3, 3, 4, 5, 10};
			msgpack::packer<Writer> pk(writer);
			pk.pack(v);
			writer.close();
		}

		friend std::ostream & operator << (std::ostream& os, const FeedforwardNetwork& fn);

		// MSGPACK_DEFINE(layers);

	protected:
		std::list<ADMatrix> layers;

	};

	std::ostream & operator << (std::ostream& os, const FeedforwardNetwork& fn) {
		os << "FeedforwardNetwork[";
		auto i = fn.layers.cbegin();
		os << (i->size1()) << " -> " << (i->size2());
		i++;
		while(i != fn.layers.end()) {
			os << " -> " << (i->size2());
			i++;
		}
		os << "]";
		return os;
	}

	 // construct a trivial random generator engine from a time-based seed:
  	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  	std::default_random_engine generator(seed);

	template<typename Scalar> 
	Scalar randn() {
		normal_distribution<Scalar> x(0.0,1.0);
		return x(generator);
	}

};




int main(int argc, char **argv) {
	deep::FeedforwardNetwork nn = {2500, 1000, 100, 1000, 2500};

	std::ofstream fout("data.msgpack", ios::out | ios::binary);
	nn.serialise(fout);

	// deep::FeedforwardNetwork nn2(layers)
	cout << nn << endl;
	for(int i = 0; i < 10; ++i) {
		cout << deep::randn<double>() << endl;
	}
	return 0;
}