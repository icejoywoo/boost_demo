#include <iostream>
#include <cstring>
#include <string>
#include <vector>

#include <boost/smart_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

boost::shared_array<char> get(const char *s) {
	int size = std::strlen(s);
	boost::shared_array<char> text(new char[size + 1]);
	std::strncpy(text.get(), s, size + 1);
	return text;
}

void print(char *text) {
	std::cout << text << std::endl;
}

template<typename T>
T *create() {
	return new T;
}

int main(int argc, char *argv[]) {
	boost::shared_array<char> text = get("test abcdddddd");
	print(text.get());

	boost::ptr_vector<int> v;
	v.push_back(create<int>());
}
