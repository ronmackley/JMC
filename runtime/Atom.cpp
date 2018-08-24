#ifndef _ATOM_HPP_
#include "Atom.hpp"
#endif


Atom::Atom()
{
	throw "Shouldn't call Atom::Atom\n";
}

Atom::Atom( const Atom& a_Atom )
{
	throw "Shouldn't copy Atom\n";
}
Atom& Atom::operator=( const Atom& a_Atom )
{
	throw "Shouldn't assign to Atom\n";
}

Atom::Atom( const std::string& a_string)
{
	d_refCount = 0;
	d_string = new std::string(a_string);
}

Atom::~Atom()
{
	if(d_refCount != 0)
	{
		throw "Delete Atom with non-zero refCount\n";
	}
	delete d_string;
}

