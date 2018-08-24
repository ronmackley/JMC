#ifndef _CELLIMPL_HPP_
#include "CellImpl.hpp"
#endif


//*******************************************************************
//*******************************************************************
CellImpl::CellImpl()
{
	d_left = d_right = NULL;
	d_atom = NULL;
	d_refCount = 1;
}

//*******************************************************************
//*******************************************************************
CellImpl::CellImpl( const CellImpl& a_cellImpl )
{
	throw "shouldn't copy CellImpls\n";
}

//*******************************************************************
//*******************************************************************
CellImpl& CellImpl::operator=( const CellImpl& a_cellImpl )
{
	throw "shouldn't copy CellImpls\n";
}

//*******************************************************************
//*******************************************************************
const CellImpl* CellImpl::create()
{
	return new CellImpl();
}

//*******************************************************************
//*******************************************************************
const CellImpl* CellImpl::allocate(const CellImpl* a_cell)
{
	if( a_cell->addRef() < 2 )
	{
		// Should have at least one to start and the one we just added
		throw "CellImpl::allocate - unexpected number of references";
	}
	return a_cell;
}


//*******************************************************************
//*******************************************************************
void CellImpl::release(const CellImpl* a_cell)
{
	if( a_cell == NULL ) 
	{
		return;
	}
	
	if( a_cell->removeRef()==0 )
	{
		delete(a_cell);
	}
}

//*******************************************************************
//*******************************************************************
CellImpl::~CellImpl()
{
	if( d_refCount!=0) {	throw "destroy CellImpl with non-zero refcount\n"; }
	delete d_left;
	delete d_right;
	delete d_atom;
}

//*******************************************************************
//*******************************************************************
bool CellImpl::isNil() const 
{
	if (d_left == NULL &&
	 	d_right == NULL &&
	 	d_atom == NULL)
	{ 
		return true; 
	}
	else
	{
		return false;
	}
}

//*******************************************************************
//*******************************************************************
bool CellImpl::isLeaf() const 
{
	// A trunk node has data pointed at by left and 
	// has nothing to the right
	if (d_left != NULL &&
	 	d_right == NULL &&
	 	d_atom == NULL)
	{ 
		return true; 
	}
	else
	{
		return false;
	}
}

//*******************************************************************
//*******************************************************************
bool CellImpl::isTrunk() const 
{
	// A trunk node has data pointed at by left and 
	// has continues through what is pointed at by right
	if (d_left != NULL &&
	 	d_right != NULL &&
	 	d_atom == NULL)
	{ 
		return true; 
	}
	else
	{
		return false;
	}
}

//*******************************************************************
//*******************************************************************
const CellImpl& CellImpl::left(const CellImpl& a_cell)
{ 
	// Release what's already there
	release(d_left);
	
	// Allocate a new reference and assign it
	d_left = allocate(&a_cell);

	// return the object with the new reference.
	return *d_left;
}

//*******************************************************************
//*******************************************************************
const CellImpl& CellImpl::right(const CellImpl& a_cell)
{
	// Release what's already there
	release((CellImpl*)d_right);
	
	// Allocate a new reference and assign it
	d_right = allocate((CellImpl*)&a_cell);

	// return the object with the new reference.
	return *d_right;
}

//*******************************************************************
//*******************************************************************
std::string& CellImpl::to_s(std::string& a_string) const
{
	if(isLeaf() )
	{
		a_string += d_atom->to_s();
	
	}
	//! Need to figure out whether I'm the head of a list or in a list.
	else if(isTrunk())
	{
		a_string += d_left->to_s(a_string);
		a_string += ' ';
		a_string += d_right->to_s(a_string);
	}
	return a_string;
}

