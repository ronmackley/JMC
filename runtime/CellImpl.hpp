#ifndef _CELLIMPL_HPP_
#define _CELLIMPL_HPP_


#ifndef _ATOM_HPP_
#include "Atom.hpp"
#endif

#include <stdlib.h>
#include <string>

//*******************************************************************
// CellImpl - the guts of the data and structure holding object
// 
// This holds the left and right pointers and the pointer to the
// object that holds data. This is also a reference-counted object.
// Ctors and Dtors are not caled directly. 
//*******************************************************************

class CellImpl
{
private:
	// Nobody should call these	
	CellImpl();
	CellImpl( const CellImpl& a_cellImpl );
	CellImpl& operator=( const CellImpl& a_cellImpl );

public:
	~CellImpl();
	
	// Construct a cell from left or left and right
	CellImpl(CellImpl* a_left, CellImpl* a_right = NULL) : 
		d_left(a_left),d_right(a_right), 
		d_atom(NULL)
	{	(void)addRef(); }
	
	// Construct a cell from an atom
	CellImpl(Atom* a_atom) : 
		d_left(NULL), d_right(NULL), 
		d_atom(new Atom(*a_atom) )
	{	(void)addRef(); }

static const CellImpl* create();
static const CellImpl* allocate( const CellImpl* a_cell);
static void release(const CellImpl* a_cell);

	long refCount() const 			{ return d_refCount; }

	const CellImpl& left( const CellImpl& a_cell);
	const CellImpl& right( const CellImpl& a_cell);
	const Atom& atom( const Atom& a_atom)			{ return *(d_atom = &a_atom); }

	const CellImpl& left() const					{ return *d_left;  }
	const CellImpl& right() const					{ return *d_right; }	
	const Atom& atom() const 						{ return *d_atom; }
	
	std::string& to_s(std::string& a_string) const;
	
	// Tests
	bool isNil()	const;
	bool isLeaf()	const; 
	bool isTrunk()	const;
	
private:
	
	long addRef() const					{ return ++d_refCount; }
	long removeRef() const				{ return --d_refCount; }

	const CellImpl*		d_left;
	const CellImpl*		d_right;
	const Atom* 		d_atom;
	mutable long		d_refCount;
};

#endif //_CELLIMPL_HPP_
