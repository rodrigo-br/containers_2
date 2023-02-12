#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <iterator>
#include "vector.hpp"
#include "map.hpp"
#include <fstream>
#include <sys/time.h>

#define NS ft
#define PRINTNS "ft"
#define FILEVECTOR "ftvector.txt"
#define FILEMAP "ftmap.txt"
#ifdef STD
	#undef NS
	#define NS std
	#undef PRINTNS
	#define PRINTNS "std"
	#undef FILEVECTOR
	#define FILEVECTOR "stdvector.txt"
	#undef FILEMAP
	#define FILEMAP "stdmap.txt"
#endif

size_t	time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

namespace NS {

template<typename T>
void write_vector(vector<T> &v, std::ofstream& os) {
	for (typename vector<T>::iterator it = v.begin(); it != v.end(); ++it) {
		os << *it << "\n";
	}
	os << v.size() << "\n"
		<< v.capacity() << "\n"
		<< v.max_size() << "\n"
		<< v.empty() << "\n"
		<< v.front() << "\n"
		<< v.back() << "\n"
		<< v.at(2) << "\n"
		<< v[2] << "\n"
		<< *v.data() << "\n"
		<< *v.begin() << "\n"
		<< *v.end() << "\n"
		<< *v.rbegin() << "\n"
		<< *v.rend() << "\n";
}

void test_vector()
{
	size_t start = time_now();
	std::ofstream os;
	os.open(FILEVECTOR, std::ios::app);
	{
		vector<int> first;                                // empty vector of ints
		vector<int> second (4,100);                       // four ints with value 100
		vector<int> third (second.begin(),second.end());  // iterating through second
		vector<int> fourth (third);                       // a copy of third
		int myints[] = {16,2,77,29};
		vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

		os << "The contents of fifth are:";
		for (vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		os << ' ' << *it;
		os << '\n';
		fifth.pop_back();
		fifth.insert(fifth.begin(), 100);
		os << *fifth.begin() << "\n";
		fifth.erase(fifth.begin());
		os << *fifth.begin() << "\n";
		fifth.resize(50);
		os << fifth.capacity() << "\n";
		ft::vector<int> old_foo (3, 100);
		ft::vector<int> new_bar (3, 100);   // three ints with a value of 100
		ft::vector<int> old_bar (5, 200);
		ft::vector<int> new_foo (5, 200);   // five ints with a value of 200

		old_foo.swap(old_bar);
		os << std::boolalpha;
		os << (old_foo.size() == 5) << "\n";
		os << (old_bar.size() == 3) << "\n";

		for (size_t i = 0; i < new_bar.size(); i++) {
			os << (new_bar[i] == old_bar[i]) << "\n";
		}

		for (size_t i = 0; i < new_foo.size(); i++) {
			os << (new_foo[i] == old_foo[i]) << "\n";
		}
		swap(old_bar, old_foo);
		os << (old_foo.size() == 3) << "\n";
		os << (old_bar.size() == 5) << "\n";

		for (size_t i = 0; i < new_bar.size(); i++) {
			os << (new_bar[i] == old_foo[i]) << "\n";
		}

		for (size_t i = 0; i < new_foo.size(); i++) {
			os << (new_foo[i] == old_bar[i]) << "\n";
		}
	}
	std::cout << PRINTNS << "::vector time: " << (time_now() - start) << std::endl;
	os.close();
}

void test_map()
{
	size_t start = time_now();
	std::ofstream os;
	os.open(FILEMAP, std::ios::app);
	{
		map<char,int> mymap;

		// first insert function version (single parameter):
		mymap.insert ( pair<char,int>('a',100) );
		mymap.insert ( pair<char,int>('z',200) );

		pair<map<char,int>::iterator,bool> ret;
		ret = mymap.insert ( pair<char,int>('z',500) );
		if (ret.second==false) {
			os << "element 'z' already existed";
			os << " with a value of " << ret.first->second << '\n';
		}

		// second insert function version (with hint position):
		map<char,int>::iterator it = mymap.begin();
		mymap.insert (it, pair<char,int>('b',300));  // max efficiency inserting
		mymap.insert (it, pair<char,int>('c',400));  // no max efficiency inserting

		// third insert function version (range insertion):
		map<char,int> anothermap;
		anothermap.insert(mymap.begin(),mymap.find('c'));

		// showing contents:
		os << "mymap contains:\n";
		for (it=mymap.begin(); it!=mymap.end(); ++it)
			os << it->first << " => " << it->second << '\n';
		os << mymap.size() << "\n"
			<< mymap.empty() << "\n"
			<< mymap.begin()->first << "\n"
			<< mymap.begin()->second << "\n"
			<< mymap.end()->second << "\n"
			<< mymap.rbegin()->first << "\n"
			<< mymap.rbegin()->second << "\n"
			<< mymap.rend()->second << "\n";

		os << "anothermap contains:\n";
		for (it=anothermap.begin(); it!=anothermap.end(); ++it)
			os << it->first << " => " << it->second << '\n';
		os << anothermap.size() << "\n"
			<< anothermap.empty() << "\n"
			<< anothermap.begin()->first << "\n"
			<< anothermap.begin()->second << "\n"
			<< anothermap.end()->second << "\n"
			<< anothermap.rbegin()->first << "\n"
			<< anothermap.rbegin()->second << "\n";
	}
	std::cout << PRINTNS <<"::map time: " << (time_now() - start) << std::endl;
}

};

int main(void)
{
	NS::test_vector();
	NS::test_map();

	return 0;
}