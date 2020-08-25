#pragma once

#include <random>
#include <ctime>

class Random
{
public:
	Random(int seed = std::time(nullptr)) 
		: engine(seed) 
	{}
	~Random() = default;

	int GetInt(int min, int max)
	{
		std::uniform_int_distribution dist(min, max);
		return dist(engine);
	}
	float GetFloat(float min, float max)
	{
		std::uniform_real_distribution<float> dist(min, max);
		return dist(engine);
	}
	static Random& Get() { return instance; }
private:
	std::mt19937 engine;
	static Random instance;
};

Random Random::instance;
