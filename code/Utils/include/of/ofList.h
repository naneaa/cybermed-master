// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2007 LabTEVE (http://www.de.ufpb.br/~labteve),
// Federal University of Paraiba and University of São Paulo.
// All rights reserved.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this program; if not, write to the Free
// Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
// Boston, MA 02110-1301, USA.
// *****************************************************************

#ifndef OFLIST_H
#define OFLIST_H

#include "ofMacros.h"

namespace of
{

/**
@class		ofListNode 
@file		ofList.h 
@short		Node of ofList

@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
@version	1.0 
@date		2007, July
*/
					
template<class T> class ofListNode
{
public:

  	/** Constructor 
	 * 
	 * @param void
	 *  
	 */
	ofListNode();
	
  	/** Destructor
	 * 
	 * @param void
	 *  
	 */
	~ofListNode();
	
	/** 
	 * Define the element in list node 
	 * 
	 * @param T info the element in list node
	 * @return void
	 * 
	 */
	void	setInfo(T info) {atu=info;};
	
	/** 
	 * Return the element in list node
	 * 
	 * @param void
	 * @return T the element in list node
	 * 
	 */
	T getInfo() {return atu;};

	/** 
	 * Define the next node
	 * 
	 * @param ofListNode<T>* prox the next node
	 * @return void
	 * 
	 */
	void	setNext(ofListNode<T> *prox){next=prox;};
	
	/** 
	 * Return the next node
	 * 
	 * @param void
	 * @return ofListNode<T>* the next node
	 * 
	 */
	ofListNode<T>*	getNext(){return next;};

protected:
	T				atu;	/**< the element in list node */
	ofListNode<T>*	next;	/**< the next node */
};

template<class T> ofListNode<T>::ofListNode()
{
	next = NULL;
};

template<class T> ofListNode<T>::~ofListNode()
{
};

/**
@class		ofList 
@file		ofList.h 
@short		Dynamic single linked list
 		 	T is the type of element

@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
@version	1.0 
@date		2007, July
 */

/**	Dynamic single linked list
 * 
 * 	T is the type of element
 */
template<class T> class ofList
{
public:

  	/** Constructor 
	 * 
	 * @param void
	 *  
	 */
	ofList();
	
  	/** Destructor
	 * 
	 * @param void
	 *  
	 */
	~ofList();

	/** 
	 * Return a element of the specified position
	 * 
	 * @param int pos position of the element
	 * @return void 
	 * 
	 */
	T	pos(int pos);

  	/**	Return the first element */
  	T	first();

	/**  
	 * Return the last element (faster than pos(size() - 1) )
	 * 
	 * @param void
	 * @return T the last element
	 * 
	 */
	T	last();
  
	/**	
	 * Return the number of elements in list 
	 * 
	 * @param void
	 * @return int the number of elements in list 
	 * 
	 * */
	int size();
  
	/** 
	 * Insert a element in list (in last position)
	 * 
	 * @param T novo element will be inserted
	 * @return void
	 * 
	 */
	void insert(T novo);

	/** 
	 * Insert a element in list, only if this element isnt in list. (in last position)
	 * 
	 * @param T novo the element that will be inserted
	 */
	bool insertOnlyOne(T novo);
  
	/** 
	 * Insert a element in first position of list
	 * 
	 * 	@param T novo element will be inserted
	 */
	void insertFirst(T novo);
  
	/** 
	 * Insert a element in the specified position of list
	 * 
	 * @param T novo element will be inserted
	 * @param int pos position
	 * 
	 */
	void insert(T novo, int pos);

	/** 
	 * Delete a element
	 * 
	 * @param int pos position of element
	 * @param bool if it was possible to delete the element
	 */
	bool  erase(int pos);

	/** 
	 * Return true if the element is inlist 
	 * 
	 * @param T info the element's info
	 * @return bool if the element is in list 
	 * 
	 */
	bool	inList(T info);

	/**	
	 * Return the position of a element, -1 if isnt in list
	 * 
	 * @param T info the element's info
	 * @return int the position of a element, -1 if isnt in list
	 * 
	 */
	int 	search(T info);

	/** 
	 * Delete all element of list
	 * 
	 * @param void
	 * @return void
	 * 
	 */
	void  clear();

	/* 
	 * Return true if list dont have any element
	 * 
	 * @param void
	 * @return bool if list dont have any element
	 */
	bool  empty();
 
protected:
  int lsize;					/**< list size */
  ofListNode<T>*	lfirst;		/**< pointer to first element */
  ofListNode<T>*  llast;		/**< pointer to last element */
};

template<class T> ofList<T>::ofList() //construtor
{
	lfirst = NULL;
	llast = NULL;
	lsize = 0;
};

template<class T> ofList<T>::~ofList()
{
	clear();
};

template<class T> T ofList<T>::pos(int pos)
{
	OF_ASSERT((pos >=0)&&(pos < lsize));
	
	ofListNode<T> *p = lfirst;
	
	for(int i=0; i<pos; i++)
	{
		OF_ASSERT(p);
		p = p->getNext();
	}
	
	return p->getInfo();
};

template<class T> T ofList<T>::first()
{
	OF_ASSERT(lfirst);
	return lfirst->getInfo();
};

template<class T> T ofList<T>::last()
{
	OF_ASSERT(llast);
	return llast->getInfo();
};

template<class T> int ofList<T>::size()
{
	return lsize;
}

template<class T> void ofList<T>::insert(T novo)
{
	ofListNode<T> *t = new ofListNode<T>();

	OF_ASSERT(t);

	t->setInfo(novo);
	if (lsize==0)
		lfirst = t;
	else
	{
		OF_ASSERT(llast);
		llast->setNext(t);
	}
	llast = t;
	lsize++;
};

template<class T> bool ofList<T>::insertOnlyOne(T novo)
{
	if (lsize==0)
	{
		ofListNode<T> *t = new ofListNode<T>();
		OF_ASSERT(t);
		
		t->setInfo(novo);
		t->setNext(NULL);
		lfirst = t;
		llast = t;
	}
	else
	{
		ofListNode<T> *point = lfirst;
		OF_ASSERT(point);
		
		while((point->getNext()!=NULL)&&(point->getInfo() != novo))
		{
			point = point->getNext();
			OF_ASSERT(point);
		}
		
		if(point->getInfo() != novo)
		{
			ofListNode<T> *t = new ofListNode<T>();
			
			OF_ASSERT(t);
			
			t->setInfo(novo);
			t->setNext(NULL);
			point->setNext(t);
			llast = t;
		}
		else
			return false;
	};
	lsize++;
	
	return true;
};

template<class T> void ofList<T>::insertFirst(T novo)
{
	ofListNode<T> *t = new ofListNode<T>();

	OF_ASSERT(t);

	t->setInfo(novo);
	t->setNext(lfirst);
	lfirst = t;
	if(lsize==0) llast = lfirst;
	lsize++;
};

template<class T> void ofList<T>::insert(T novo, int pos)
{
	OF_ASSERT((pos >=0)&&(pos <= lsize));

	ofListNode<T> *t = new ofListNode<T>();

	OF_ASSERT(t);

	t->setInfo(novo);
	if ((pos==0)||(lsize==0))
	{
		t->setNext(lfirst);
		lfirst = t;
		if (lsize==0) llast = t;
	}
	else
	{
		ofListNode<T> *point=lfirst;
		OF_ASSERT(point);
		int i;
		for(i=1; (i<pos)&&(point->getNext()!=NULL); i++)
		{
			point = point->getNext();
			OF_ASSERT(point);
		}
		t->setNext(point->getNext());
		point->setNext(t);
		if (pos>=lsize) llast = t;
	};
	lsize++;
};

template<class T> bool ofList<T>::erase(int pos)
{
	OF_ASSERT((pos >=0)&&(pos < lsize));

	ofListNode<T> *p,*a;

	if (pos ==0)
	{
		p = lfirst;
		OF_ASSERT(lfirst);
		lfirst = lfirst->getNext();
		if (lsize==1) llast = NULL;
		delete p;
	}
	else
	{
		a = lfirst;
		OF_ASSERT(lfirst);
		p = lfirst->getNext();
		for(int i=1; i<pos; i++)
		{
			a = p;
			OF_ASSERT(p);
			p = p->getNext();
		};
		
		a->setNext(p->getNext());
		if(pos==(lsize-1)) llast = a;
		delete p;
	};
	lsize--;
	return true;
};

template<class T> bool ofList<T>::inList(T info)
{
	if (lsize==0) return false;

	ofListNode<T> *p=lfirst;
	
	OF_ASSERT(p);
	
	for(int i=0; (p->getInfo()!=info)&&(i<lsize);i++)
	{
		if (p->getNext() != NULL) p=p->getNext();
		OF_ASSERT(p);		
	}
	return (p->getInfo()==info);
};

template<class T> int ofList<T>::search(T info)
{
	int i;
	
	if (lsize==0) return -1;

	ofListNode<T> *p=lfirst;
	
	OF_ASSERT(p);
	
	for(i=0; (p->getInfo()!=info)&&(i<lsize);i++)
	{
		if (p->getNext() != NULL) p=p->getNext();
		OF_ASSERT(p);		
	}
	if(p->getInfo()==info)
		return i;
	else
		return -1;
};

template<class T> void ofList<T>::clear()
{
	while(lsize > 0)
		erase(0);
	
	lsize = 0;
	lfirst=NULL;
	llast=NULL;
};

template<class T> bool ofList<T>::empty()
{
	return (lsize == 0);
};

}

#endif
