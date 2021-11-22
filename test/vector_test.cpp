#include "test.hpp"
# include <ostream>

void	startTest( const std::string &testName ) {
	// std::cout << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	std::cout << BOLDWHITE;
	std::cout << "\n» " << testName << std::endl << std::endl;
	std::cout << RESET;
}

template < class T >
bool	compare( ft::vector<T> &vec, std::vector<T> &orig ) {
	typename ft::vector<T>::iterator it_vec = vec.begin();
	typename std::vector<T>::iterator it_orig = orig.begin();

	for (; it_vec != vec.end(); ++it_vec, ++it_orig ) {
		if ( *it_vec != *it_orig )
			return false;
	}
	if ( vec.size() != orig.size() )
		return false;
	return true;
}

template < class T >
void	result( ft::vector<T> &vec, std::vector<T> &orig ) {
	if ( compare<T>( vec, orig ) )
		std::cout << BOLDGREEN << "[OK]" << RESET << std::endl;
	else
		std::cout << BOLDRED << "[ERROR]" << RESET << std::endl;
}

template < class T >
void	printVector( ft::vector<T> &vec, std::vector<T> &orig ) {
	std::cout << "vec:\t";
	for ( typename ft::vector<T>::iterator it = vec.begin(); it != vec.end(); ++it )
		std::cout << *it << " ";
	std::cout << std::endl << "orig:\t";
	for ( typename std::vector<T>::iterator it = orig.begin(); it != orig.end(); ++it )
		std::cout << *it << " ";
	std::cout << std::endl << std::endl;
}


template < class T, T value >
void	assignTest( void ) {

	startTest( "ASSIGN Test" );

	{
		ft::vector<T>	vec;
		std::vector<T>	orig;

		vec.assign( 10, value );
		orig.assign( 10, value );

		std::cout << MAGENTA << "Value » " << RESET;
		result( vec, orig );
		printVector( vec, orig );
	}

	{
		ft::vector<T>	vec;
		std::vector<T>	orig;

		std::vector<T>	tmp( 10, value );

		vec.assign( tmp.begin(), tmp.end() );
		orig.assign( tmp.begin(), tmp.end() );

		std::cout << MAGENTA << "Range » " << RESET;
		result( vec, orig );
		printVector( vec, orig );
	}


}

template < class T >
void	constructorsTest( void ) {

	startTest( "CONSTRUCTORS Test" );

	{
		ft::vector<T>	vec;
		std::vector<T>	orig;

		std::cout << MAGENTA << "Default Constructor » " << RESET;
		result( vec, orig );
		printVector( vec, orig );
	}

	{
		ft::vector<T>	vec( 10 );
		std::vector<T>	orig( 10 );

		std::cout << MAGENTA << "Count Constructor » " << RESET;
		result( vec, orig );
		printVector( vec, orig );
	}

	{
		ft::vector<T>	tmp( 10 );
		std::vector<T>	tmp_orig( 10 );

		ft::vector<T>	vec( tmp.begin(), tmp.end() );
		std::vector<T>	orig( tmp_orig.begin(), tmp_orig.end() );

		std::cout << MAGENTA << "Range Constructor » " << RESET;
		result( vec, orig );
		printVector( vec, orig );
	}

	{
		ft::vector<T>	tmp( 10 );
		std::vector<T>	tmp_orig( 10 );

		ft::vector<T>	vec( tmp );
		std::vector<T>	orig( tmp_orig );

		std::cout << MAGENTA << "Copy Constructor » " << RESET;
		result( vec, orig );
		printVector( vec, orig );
	}

	{
		ft::vector<T>	tmp( 10 );
		std::vector<T>	tmp_orig( 10 );

		ft::vector<T>	vec = tmp;
		std::vector<T>	orig = tmp_orig;

		std::cout << MAGENTA << "Assignation Overload » " << RESET;
		result( vec, orig );
		printVector( vec, orig );
	}
}

template < class T >
void	resize_test( void ) {

	startTest( "Resize Test" );

	{
		ft::vector<T>	vec( 10 );
		std::vector<T>	orig( 10 );

		std::cout << MAGENTA << "Resize [10 -> 100] » " << RESET;
		vec.resize( 100, 45 );
		orig.resize( 100, 45 );
		result( vec, orig );
		printVector( vec, orig );
	}

	{
		ft::vector<T>	vec( 10 );
		std::vector<T>	orig( 10 );

		std::cout << MAGENTA << "Resize [10 -> 2] » " << RESET;
		vec.resize( 2, 45 );
		orig.resize( 2, 45 );
		result( vec, orig );
		printVector( vec, orig );
	}
}

template < class T >
void	insert_test( void ) {

	startTest( "Insert Test" );

	{
		ft::vector<T>	vec( 10 );
		std::vector<T>	orig( 10 );

		std::cout << MAGENTA << "Insert [0; 3] » " << RESET;
		typename ft::vector<T>::iterator vecIt = vec.insert( vec.begin() + 0, 3 );
		typename std::vector<T>::iterator origIt = orig.insert( orig.begin() + 0, 3 );
		std::cout << "ft: " << *vecIt << "\tstd: " << *origIt << std::endl;

		std::cout << MAGENTA << "Insert [5; 3] » " << RESET;
		vecIt = vec.insert( vec.begin() + 5, 3 );
		origIt = orig.insert( orig.begin() + 5, 3 );
		std::cout << "ft: " << *vecIt << "\tstd: " << *origIt << std::endl;

		std::cout << MAGENTA << "Insert [end(); 3] » " << RESET;
		vecIt = vec.insert( vec.end(), 3 );
		origIt = orig.insert( orig.end(), 3 );
		std::cout << "ft: " << *vecIt << "\tstd: " << *origIt << std::endl;

		result( vec, orig );
		printVector( vec, orig );
	}

	{
		ft::vector<T>	vec( 10 );
		std::vector<T>	orig( 10 );

		std::cout << MAGENTA << "Insert [+10; 4; 3] » " << RESET;
		vec.insert( vec.begin() + 10, 4, 3 );
		orig.insert( orig.begin() + 10, 4, 3 );

		result( vec, orig );
		printVector( vec, orig );
	}

	{
		ft::vector<T>	vec( 10 );
		std::vector<T>	orig( 10 );
		std::vector<int>	tmp;

		for( int i = 0; i < 5; ++i )
			tmp.push_back( i * i );

		std::cout << MAGENTA << "Insert [+10; tmp.begin(); tmp.end()] » " << RESET;
		vec.insert( vec.begin() + 10, tmp.begin(), tmp.end() );
		orig.insert( orig.begin() + 10, tmp.begin(), tmp.end() );

		result( vec, orig );
		printVector( vec, orig );
	}
}


class B {
public:
	char *l;
	int i;
	B():l(nullptr), i(1) {};
	B(const int &ex) {
		this->i = ex;
		this->l = new char('a');
	};
	virtual ~B() {
		delete this->l;
		this->l = nullptr;
	};
};

class A : public B {
public:
	A():B(){};
	A(const B* ex){
		this->l = new char(*(ex->l));
		this->i = ex->i;
		if (ex->i == -1) throw "n";
	}
	~A() {
		delete this->l;
		this->l = nullptr;
	};
};

template <typename T>
std::vector<int> insert_test_1( void ) {
	ft::vector<int>	vector;
    std::vector<int> v;
    vector.assign(26000000, 1);
    v.push_back(*(vector.insert(vector.end() - 8000000, 44)));
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
    ft::vector<A> vv;
    ft::vector<B*> v1;

    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));
    try { 
		vv.insert(vv.begin(), v1.begin(), v1.end());
	}
    catch (...) {
    	v.push_back(vv.size());
    	v.push_back(vv.capacity());
    }
    return v;
}

template <typename T>
std::vector<int> insert_test_2( void ) {
	std::vector<int>	vector;
    std::vector<int> v;
    vector.assign(26000000, 1);
    v.push_back(*(vector.insert(vector.end() - 8000000, 44)));
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
    std::vector<A> vv;
    std::vector<B*> v1;

    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));
    try { 
		vv.insert(vv.begin(), v1.begin(), v1.end());
	}
    catch (...) {
    	v.push_back(vv.size());
    	v.push_back(vv.capacity());
    }
    return v;
}

void	vectorTest( void ) {
	constructorsTest<float>();
	assignTest<int, 70>();
	resize_test<int>();
	insert_test<int>();

	std::cout << MAGENTA << "Insert [A(B), B] » " << RESET;
	std::vector<int> res1 = insert_test_1<int>();
	std::vector<int> res2 = insert_test_2<int>();
	if ( res1 == res2 )
		std::cout << BOLDGREEN "[OK]" RESET << std::endl;
	else {
		std::cout << BOLDRED "[NO]" RESET << std::endl;
		std::cout << "0: " << res1[0] << " " << res2[0] << std::endl;
		std::cout << "1: " << res1[1] << " " << res2[1] << std::endl;
		std::cout << "2: " << res1[2] << " " << res2[2] << std::endl;
	}
}
