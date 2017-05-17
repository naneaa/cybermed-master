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

#ifndef	OFKDTREE_H
#define	OFKDTREE_H

#include "ofMacros.h"
#include "ofList.h"

namespace of
{

/**
@class		ofKdTreeNode 
@file		ofKdTreeNode.h 
@short		OF interator

@author		ICMC-USP (http://www.icmc.usp.br),University of São Paulo
@version	1.0 
@date		2007, July
*/
	
template<class sObject> struct ofKdTreeNode
{
    sObject	ptr;
    ofKdTreeNode *p[2];
};


template <class sObject, class sObjectCompare> class ofKdTree 
{
public:	

    ofKdTree(int dim);
    ~ofKdTree();

    void insert(sObject obj);   
	//bool erase(sObject obj);
	
	sObject nearest(sObject obj);	
	sObject nearestAndInsert(sObject obj);
    
    int size();
    
private:
    
	ofKdTreeNode<sObject> *add(sObject obj);
	ofKdTreeNode<sObject> *nearestSearch(sObject obj);
    
    sObjectCompare comp;
	
	ofKdTreeNode<sObject> *root;
    int n, ndim;
};

template <class sObject, class sObjectCompare> ofKdTree<sObject,sObjectCompare>::ofKdTree(int dim) 
{
	OF_ASSERT(dim);
	
	root = NULL;
	ndim = dim;
	n = 0;
}

template <class sObject, class sObjectCompare> ofKdTree<sObject,sObjectCompare>::~ofKdTree()
{
	ofList< ofKdTreeNode<sObject> * > lista;
		
	ofKdTreeNode<sObject> *node = root;
		
	while(node)
	{
		if(node->p[0])
			lista.insert(node->p[0]);
		if(node->p[1])
			lista.insert(node->p[1]);
			
		delete node;
		
		lista.erase(0);
				
		if(!lista.empty())
			node = lista.first();
		else
			node = NULL;
	}
}

template <class sObject, class sObjectCompare> void ofKdTree<sObject,sObjectCompare>::insert(sObject obj)
{
	add(obj);	
}


template <class sObject, class sObjectCompare> sObject ofKdTree<sObject,sObjectCompare>::nearest(sObject obj)
{
	ofKdTreeNode<sObject> *node = nearestSearch(obj);
	
//	OF_ASSERT(node);
	if (node)
		return node->ptr;
	else
		return NULL;
}

template <class sObject, class sObjectCompare> sObject ofKdTree<sObject,sObjectCompare>::nearestAndInsert(sObject obj)
{
	ofKdTreeNode<sObject> *node = nearestSearch(obj);
	
	add(obj);
	
	OF_ASSERT(node);

	return node->ptr;
}

template <class sObject, class sObjectCompare> ofKdTreeNode<sObject>*ofKdTree<sObject,sObjectCompare>::add(sObject obj)
{
	ofKdTreeNode<sObject> *leaf = root, *ant = NULL;
	int ld = 0, dim = 0;
	
	while(leaf)
	{
		if(comp.greater(leaf->ptr, obj, dim))
		{
			ant = leaf;
			ld = 0;
		}
		else
		{
			ant = leaf;
			ld = 1;
		}

		leaf = ant->p[ld];

		if(++dim == ndim)
			dim = 0;
	}
	
	leaf = new ofKdTreeNode<sObject>;
    
	leaf->ptr = obj;
    leaf->p[0]  = NULL;
    leaf->p[1] = NULL;
	
	if(ant)
		ant->p[ld] = leaf;
	else
	{
		root = leaf;
		ant = root;
	}
		
	n++;
	
	return ant;
}

template <class sObject, class sObjectCompare> ofKdTreeNode<sObject>* ofKdTree<sObject,sObjectCompare>::nearestSearch(sObject obj)
{
	ofKdTreeNode<sObject> *leaf = root, *ant = NULL;
	int ld, dim = 0;
	
	while(leaf)
	{
		if(comp.greater(leaf->ptr, obj, dim))
		{
			ant = leaf;
			ld = 0;
		}
		else
		{
			ant = leaf;
			ld = 1;
		}

		leaf = ant->p[ld];
	
		if(++dim == ndim)
			dim = 0;
	}
	
	if(ant)
		return ant;
	else
		return NULL;
}

template <class sObject, class sObjectCompare> int ofKdTree<sObject,sObjectCompare>::size()
{
	return n;
}

}
#endif
