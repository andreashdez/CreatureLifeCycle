#include <random>
#include "Random.h"

namespace {
	std::mt19937& Engine() {
		static std::random_device device;
		static std::mt19937 engine(device());
		return engine;
	}
}

double Random::Probability() {
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	return distribution(Engine());
}

int Random::Int(int min, int max) {
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(Engine());
}
