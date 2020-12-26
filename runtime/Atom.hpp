	#ifndef _ATOM_HPP_
#define _ATOM_HPP_


#include <stdlib.h>
#include <string>

class Atom
{
public:

	Atom();
	Atom( const Atom& a_Atom );
	Atom( const std::string& a_string);
	Atom& operator=( const Atom& a_Atom );
	~Atom();

	long addRef() 						{ return ++d_refCount; }
	long removeRef() 					{ return --d_refCount; }
	long refCount(  ) const 			{ return d_refCount; }

	const std::string& to_s() const 	{ return *d_string; }
	const long to_l() const 	{ return atol(d_string->c_str() ); }
	const double to_d() const 	{ return atof(d_string->c_str() ); }

private:
	std::string*	d_string;
	long		d_refCount;
};

#endif //_ATOM_HPP_
