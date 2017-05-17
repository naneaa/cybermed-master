// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2012 LabTEVE (http://www.de.ufpb.br/~labteve),
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

#ifndef _CYB_MATRIX_H_
#define _CYB_MATRIX_H_

#include <iostream>
#include <cstdlib>
#include <vector>
#include "cybVector3D.h"

/**
 * @class CybMatrix
 * @file cybMatrix.h 
 * @short This class implements a template for matrices and the basic operations.
 *
 * This class stores a matrix-like object and implements access methods and basic
 * operations. 
  * 
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 3.1
 * @date 2012, June
 * 
 */

using namespace std;

template <class type>
class CybMatrix
{
	public:
		/*
		* Constructor 1.
		* This method constructs a matrix object with dimensions specified in the parameters.
		*
		* @param int dim1: the first dimension of the matrix.
		* @param int dim2: the second dimension of the matrix.
		*/
		CybMatrix(int dim1, int dim2, bool initWith0 = true){
			this->dim1 = dim1;
			this->dim2 = dim2;
			for(int i = 0; i < dim1; ++i){
				matrix.push_back(vector<type>());
				matrix[i].resize(dim2);					
			}
		}

		/*
		* Constructor 2.
		* This method constructs a matrix object with dimensions specified in the parameters.
		* The matrix is filled with the values passed as parameter.
		*
		* @param int dim1: the first dimension of the matrix.
		* @param int dim2: the second dimension of the matrix.
		* @param type* values: an array containing the values that will be put in the matrix.
		*		       It must be of size dim1 * dim2.
		*/
		CybMatrix(int dim1, int dim2, type* values)
		{
			this->dim1 = dim1;
			this->dim2 = dim2;
			for(int i = 0; i < dim1; ++i){
				matrix.push_back(*(new vector<type>()));
				for(int j = 0; j < dim2; ++j){
					matrix[i].push_back(values[dim1 * i + j]);
				}
			}
		}

		/*
		* Constructor 3.
		* This method build a 1x3 matrix from the vector passed as parameter.
		*
		* @param CybVector3D<type> v: a vector (3D) from which the matrix will be built.
		*/
		CybMatrix(CybVector3D<type> v)
		{
			dim1 = 1;
			dim2 = 3;
			matrix.push_back(*(new vector<type>()));
			for(int i = 0; i < 3; ++i) matrix[0].push_back(v[i]);
		}
		
		/*
		* Destructor.
		* Destructs this object, but first deallocates the matrix.
		*/		
		~CybMatrix()
		{
			this->deallocateMatrix();
		}

		/*
		* Overloaded assignment operator for CybMatrix objects.
		*
		* @param const CybMatrix<type>& m: the matrix that will be assigned to this object.
		* @return CybMatrix<type>&: a reference to this object (with the new values). Allows cascading.
		*/
		CybMatrix<type>& operator=(const CybMatrix<type>& m)
		{
			this->dim1 = m.dim1;
			this->dim2 = m.dim2;
			for(int i = 0; i < dim1; ++i){
				for(int j = 0; j < dim2; ++j){
					this->matrix[i][j] = m.matrix[i][j];
				}
			}
			return *this;
		}


		/*
		* Overloaded addition operator for CybMatrix objects. Implements matrix addition.
		*
		* @param const CybMatrix<type>& m: the matrix that will be added to this object.
						   It must have the same dimensions this object has.
		* @return CybMatrix<type>&: a reference to the result of the sum. Allows cascading.
		*/
		CybMatrix<type>& operator+(const CybMatrix<type>& m)
		{
			if((this->dim1 != m.dim1) || (this->dim2 != m.dim2)){
				cout << "Invalid operation with operator +. Terminating." << endl;
				exit(1);
			}
			CybMatrix<type>* v = new CybMatrix<type>(this->dim1, this->dim2);
			for(int i = 0; i < this->dim1; ++i){
				for(int j = 0; j < this->dim2; ++j){
					v->matrix[i][j] = matrix[i][j] + m.matrix[i][j];
				}
			}
			return *v; 
		}

		/*
		* Overloaded subtraction operator for CybMatrix objects. Implements matrix subtraction.
		*
		* @param const CybMatrix<type>& m: the matrix that will be subtracted from this object.
						   It must have the same dimensions this object has.
		* @return CybMatrix<type>&: a reference to the result of the subtraction. Allows cascading.
		*/
		CybMatrix<type>& operator-(const CybMatrix<type>& m)
		{
			if((this->dim1 != m.dim1) || (this->dim2 != m.dim2)){
				cout << "Invalid operation with operator -. Terminating." << endl;
				exit(1);
			}
			CybMatrix<type>* v = new CybMatrix<type>(this->dim1, this->dim2);
			for(int i = 0; i < this->dim1; ++i){
				for(int j = 0; j < this->dim2; ++j){
					v->matrix[i][j] = this->matrix[i][j] - m.matrix[i][j];
				}
			}
			return *v; 
		}

		/*
		* Overloaded multiplication operator for CybMatrix objects. Implements matrix product.
		*
		* @param const CybMatrix<type>& m: the matrix that will be multiplicated by this object.
						   Its first dimension must be the same as this object's second.
		* @return CybMatrix<type>&: a reference to the result of the multiplication. Allows cascading.
		*/
		CybMatrix<type>& operator*(const CybMatrix<type>& m)
		{
			if(this->dim2 != m.dim1){
				cout << "Invalid operation with operator *. Terminating." << endl;
				exit(1);
			}
        		CybMatrix* result = new CybMatrix(this->dim1, m.dim2);
        		for(int i = 0; i < this->dim1; ++i){
            			for(int j = 0; j < m.dim2; ++j){
               				for(int k = 0; k < this->dim2; ++k){
                    				result->matrix[i][j] += this->matrix[i][k] * m.matrix[k][j];
                			}
            			}
        		}
        		return *result;
		}

		
		/*
		* Overloaded module operator for CybMatrix objects. Implements matrix times scalar operations.
		*
		* @param const double scalar: the scalar that will be multiplicated by this object.
		* @return CybMatrix<type>&: a reference to the result of the multiplication. Allows cascading.
		*/
		CybMatrix<type>& operator%(const double scalar)
		{
			CybMatrix<type>* v = new CybMatrix<type>(this->dim1, this->dim2);
			for(int i = 0; i < this->dim1; ++i){
				for(int j = 0; j < this->dim2; ++j){
					v->matrix[i][j] = this->matrix[i][j] * scalar;
				}
			}
			return *v; 
		}
	
		/*
		* Overloaded division operator for CybMatrix objects. Implements matrix divided by scalar operations.
		*
		* @param const double scalar: the scalar by which this object will be divided.
		* @return CybMatrix<type>&: a reference to the result of the division. Allows cascading.
		*/	
		CybMatrix<type>& operator/(const double scalar)
		{
			CybMatrix<type>* v = new CybMatrix<type>(this->dim1, this->dim2);
			for(int i = 0; i < this->dim1; ++i){
				for(int j = 0; j < this->dim2; ++j){
					v->matrix[i][j] = this->matrix[i][j] / scalar;
				}
			}
			return *v;
		}

		/*
		* Overloaded square brackets operator for CybMatrix objects.
		* Implements row access to this object's matrix.
		*
		* @param int x: the number of the row that needs to be accessed. This number must be in the 
		*		interval [0, dim1 - 1].
		* @return vector<type>&: a reference to the row of the matrix that corresponds to the parameter index.
		*/
		vector<type>& operator[](int x)
		{
			if(x < 0 || x >= this->dim1){
				cout << "Invalid operation with operator [" << x << "]. Terminating." << endl;
				exit(1);
			}
			return this->matrix[x];
		}

		/*
		* Overloaded parenthesis operator for CybMatrix objects.
		* Implements element access to this object's matrix.
		*
		* @param int i: the number of the row that needs to be accessed. This number must be in the 
		*		interval [0, dim1 - 1].
		* @param int j: the number of the column that needs to be accessed. This number must be in the
		*		interval [0, dim2 - 1].
		* @return type&: a reference to the element of the matrix that corresponds to the parameter indices.
		*/
		type& operator()(int i, int j)
	 	{
	 		if(i < 0|| i >= dim1 || j < 0 || j >= dim2){
				cout << "Invalid operation with operator (" << i << "," << j << "). Terminating." << endl;
				exit(1);
			}
			return matrix[i][j];
	 	}	

		/*
		* Getter for this object's first dimension.
		*
		* @param void
		* @return int: the first dimension of this matrix.
		*/
		int getDimension1(){ return this->dim1; }
		
		/*
		* Getter for this object's second dimension.
		*
		* @param void
		* @return int: the second dimension of this matrix.
		*/
		int getDimension2(){ return this->dim2; }

		/*
		* This method prints the current values inside this matrix.
		*
		* @param void
		* @return void
		*/
		void printMatrix()
		{
			for(int i = 0; i < dim1; ++i){
				for(int j = 0; j < dim2; ++j){
					cout << matrix[i][j] << "   ";
				}
				cout << endl;
			}
			cout << "\n" << endl;
		}

		/*
		* This method sets this matrix as an identity one.
		* 
		* @param void
		* @return void
		*/
		void setIdentity()
		{
			for(int i = 0; i < this->dim1; ++i){
				for(int j = 0; j < this->dim2; ++j){
					if(i == j) this->matrix[i][j] = 1;
					else this->matrix[i][j] = 0;
				}
			}
		}

		/*
		* This method sets the matrix's elements according to the array passed as paramater.
		*
		* @param type* array: the array that will be used to set the elements. It must be of size dim1 * dim2.
		* @return void
		*/
		void setMatrix(type* array)
		{
			int contador = 0;
			for(int	i = 0; i < this->dim1; ++i){
				for(int j = 0; j < this->dim2; ++j){
					this->matrix[i][j] = array[contador++];
				}
			}
		}

		/*
		* This method sets the matrix's elements based on the array of vectors passed as parameter.
		*
		* @param CybVector3D<type>* array: an array of 3D vector. Its values will be transferred to the matrix.
		* @return void
		*/
		void setMatrix(CybVector3D<type>* array)
		{
			if(this->dim2 > 3){
				cout << "Invalid setMatrix operation. Terminating." << endl;
				exit(1);
			}
			for(int i = 0; i < this->dim1; ++i){
				for(int j = 0; j < this->dim2; ++j){
					this->matrix[i][j] = array[i][j];
				}
			}
		}

		/*
		* This method sets the matrix's values from the parameter vector.
		* This must only be used on 1x3 matrices.
		*
		* @param  CybVector3D<type>& vetor: the vector whose values will be put in the matrix.
		* @return void
		*/
		void setMatrix(CybVector3D<type>& vetor)
		{
			if(this->dim1 != 1 || this->dim2 != 3) exit(1);
			for(int i = 0; i < 3; ++i) this->matrix[0][i] = vetor[i];
		}

		/*
		* This method creates a new matrix that is the tranposed form of this object's matrix.
		*
		* @param void
		* @return CybMatrix<type>&: a reference to the new transposed matrix.
		*/
		CybMatrix<type>& transpose()
		{
			CybMatrix<type>* transp = new CybMatrix(this->dim2, this->dim1);
			for(int i = 0; i < this->dim2; ++i){
				for(int j = 0; j < this->dim1; ++j){
					transp->matrix[i][j] = this->matrix[j][i];
				}
			}
			return *transp;
		}

		/*
		* This method transforms this matrix into an equivalent upper triangular matrix using 
		* Gauss' elimination method.
		*
		* @param void
		* @return void
		*/
		void toUpperTriangular()
		{
        		for(int i = 0; i < this->dim1; ++i){
				for(int j = 0; j != i; ++j){
					if(this->matrix[i][j]){
						double* aux = new double[this->dim2];
						double prod = -(this->matrix[i][j]/this->matrix[j][j]);
						for(int k = 0; k < this->dim2; ++k){
							aux[k] = prod * this->matrix[j][k];
						}
						for(int l = 0; l < dim2; ++l){
							this->matrix[i][l] += aux[l];
						}
					}
				}
			}
		}
	
	private:

		/*
		* This method is used by the destrcutor to release the memory used by the matrix object.
		*
		* @param void
		* @return void
		*/
		void deallocateMatrix()
		{
			for(int i = 0; i < this->dim1; ++i){
				matrix[i].clear();
			}
			matrix.clear();
		}

		int dim1, dim2;					//The dimensions of the matrix.
		vector< vector<type> > matrix;			//The physical implementation of the matrix.

};

#endif //_CYB_MATRIX_H_

