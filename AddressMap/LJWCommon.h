#pragma once
#include <random>

namespace LJWCode {
	class LJWCommon{
	public:
		static LJWCommon* Instance();
		static void ReleaseInstance();

		//LJWCommon();
		// uniform possible return random integer contain left but not contain right
		int Random(int left, int right);
	
	private:
		static LJWCommon* _instance;
		std::random_device dev;
		std::mt19937 rng;
		std::uniform_real_distribution<float> dist;
	};
}

