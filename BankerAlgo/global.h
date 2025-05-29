#pragma once
#include <vector>
#include <istream>

typedef std::vector<size_t> source;

source operator+ (source const& s01, source const& s02);

source operator- (source const& s01, source const& s02);

bool operator< (source const& s01, source const& s02);

bool operator<= (source const& s01, source const& s02);

bool operator> (source const& s01, source const& s02);

bool operator>= (source const& s01, source const& s02);

std::ostream& operator<< (std::ostream& out, source source);

class Info {
public:
	size_t pIx;
	source work;
	source need;
	source alloc;
	source workAndAlloc;
};

inline std::vector<Info> infos = std::vector<Info>();