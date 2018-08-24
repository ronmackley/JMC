#ifndef _CELL_HPP_
#define _CELL_HPP_

#ifndef _CELLIMPL_HPP_
#include "CellImpl.hpp"
#endif

#include <string>

#include <stdlib.h>

class Cell
{
public:
	
	// Standard Class Methods
	Cell();
	Cell( const Cell& a_cell );
	Cell& operator=( const Cell& a_cell );


	~Cell();

	const Cell& left() const		{ return *(new Cell(d_impl->left())); }
	const Cell& right() const		{ return *(new Cell(d_impl->right())); }	
	const Atom& atom() const		{ return d_impl->atom(); }

	const Cell& left( const Cell& a_cell );
	const Cell& right( const Cell& a_cell );
	const Atom& atom( const Atom& a_atom ) { return ((CellImpl*)d_impl)->atom(a_atom); }
	
	std::string& to_s(std::string& a_string) const	{ return d_impl->to_s( a_string ); }
	
private:
	Cell( const CellImpl& a_impl ) : d_impl(CellImpl::allocate(&a_impl)) {}

private:
	const CellImpl*	d_impl;

};

#endif //_CELLIMPL_HPP_
