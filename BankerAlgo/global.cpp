#include "global.h"

source operator+ (source const& s01, source const& s02) {
	source s03;
	if (s01.size() != s02.size()) {
		throw "s01'size is different form s02";
	}

	for (int i = 0; i < s01.size(); i++) {
		s03.emplace_back(s01[i] + s02[i]);
	}
	return s03;
}

source operator- (source const& s01, source const& s02) {
	source s03;
	if (s01.size() != s02.size()) {
		throw "s01'size is different form s02";
	}

	for (int i = 0; i < s01.size(); i++) {
		s03.emplace_back(s01[i] - s02[i]);
	}
	return s03;
}

bool operator< (source const& s01, source const& s02) {
	if (s01.size() != s02.size()) {
		throw "s01'size is different form s02";
	}

	for (int i = 0; i < s01.size(); i++) {
		if (s01[i] >= s02[i]) {
			return false;
		}
	}
	return true;
}

bool operator<= (source const& s01, source const& s02) {
	if (s01.size() != s02.size()) {
		throw "s01'size is different form s02";
	}

	for (int i = 0; i < s01.size(); i++) {
		if (s01[i] > s02[i]) {
			return false;
		}
	}
	return true;
}

bool operator> (source const& s01, source const& s02) {
	if (s01.size() != s02.size()) {
		throw "s01'size is different form s02";
	}

	for (int i = 0; i < s01.size(); i++) {
		if (s01[i] <= s02[i]) {
			return false;
		}
	}
	return true;
}

bool operator>= (source const& s01, source const& s02) {
	if (s01.size() != s02.size()) {
		throw "s01'size is different form s02";
	}

	for (int i = 0; i < s01.size(); i++) {
		if (s01[i] < s02[i]) {
			return false;
		}
	}
	return true;
}

std::ostream& operator<<(std::ostream& out, source source)
{
	for (int i = 0; i < source.size(); i++) {
		out << " " << source[i];
	}
	out << " ";
	return out;
}
