// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2016 LabTEVE (http://www.de.ufpb.br/~labteve),
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

#include "cybAssess.h"

#ifndef _CYB_GAUSSIAN_H_
#define _CYB_GAUSSIAN_H_

/**
 * @class	CybGaussian
 * @file	cybGaussian.h
 * @short	The class for the Gaussian assess method.
 *
 * This class does the specification for Gaussian assess methods.
 *
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.1.1
 * @date	2016, September
 * 
 */
class CybGaussian : public CybAssess
{
	private:
		float* precisionMatrix; /** Stores the precision matrix. **/
		mfList<int>* variables; /** Stores the variables. **/
		float prioriProbability; /** Stores the priori probability. **/
		float determinat; /** Stores the determinant of the precision matrix. **/

	protected:
		float* mean; /** Stores the means of the variables. **/
		float* covariance; /** Stores the matrix of covariance. **/
		
	public:
	
		/**
		 * Constructor.
		 */
		CybGaussian( int variablesNumber, 
				float prioriProbability);
		
		/**
		 * Destructor.
		 */
		~CybGaussian();
		
		/**
		 * This method returns the mean of one determined variable.
		 *
		 * @param node_id id of the variable from which the mean is required.
		 * @return float Mean of one determined variable.
		 */
		float getMean(int node_id);
		
		/**
		 * This method returns a array with all the means.
		 *
		 * @param void
		 * @return float* Array with all the means.
		 */
		float* getMean(); //a fazer
		
		/**
		 * This method sets the mean of a determined variable.
		 *
		 * @param int node_id id of the variable to set the mean.
		 * @param float newMean value of the mean to be set.
		 * @return void.
		 */
		void setMean(float newMean, int node_id);
		
		/**
		 * This method sets the array with all the means.
		 *
		 * @param float* newMean array with values for all the means.
		 * @return void.
		 */
		void setMean(float* newMean); //a fazer
		
		/**
		 * This method returns the variance of one determined variable.
		 *
		 * @param node_id id of the variable from which the variance is required.
		 * @return float Variance of one determined variable.
		 */		
		float getVariance(int node_id);
		
		/**
		 * This method returns a array with all the variances.
		 *
		 * @param void
		 * @return float* Array with all the variances.
		 */
		float* getVariance(); //a fazer

		/**
		 * This method returns the covariance of one determined variable.
		 *
		 * @param node_id id of the variable from which the covariance is required.
		 * @return float Covariance of one determined variable.
		 */			
		float* getCovariance(int node_id); //a fazer
		
		/**
		 * This method returns a array with all the covariances.
		 *
		 * @param void
		 * @return float* Array with all the covariances.
		 */
		float* getCovariance();
		
		/**
		 * This method sets the covariance of a determined variable.
		 *
		 * @param int node_id id of the variable to set the covariance.
		 * @param float newCovariance value of the covariance to be set.
		 * @return void.
		 */
		void setCovariance(float* newCovariance, int node_id); //a fazer

		/**
		 * This method sets the array with all the covariances.
		 *
		 * @param float newCovariance value of the covariance to be set.
		 * @return void.
		 */		
		void setCovariance(float* newCovariance);
		
		/**
		 * This method returns the value of the priori probability.
		 *
		 * @param void
		 * @return float Value of the priori probability.
		 */
		float getPrioriProbability();
				
		/**
		 * This method implements the training
		 * for this assess method.
		 * 
		 * @param void.
		 * @return void.
		 */
		virtual void training();
		
		/**
		 * This method will implement the assessment
		 * for a vector of data.
		 * 
		 * @param CybVectorND<float>* The classified data.
		 * @return void.
		 */
		virtual double assessment(CybVectorND<>* data);

		/**
		 * This method starts some of the attributes.
		 *
		 * @param void.
		 * @return void.
		 */
		void checkVariables();

		
	protected:

		/**
		 * This method calculates all the means and store
		 * them on the attribute 'mean'.
		 * 
		 * @param void.
		 * @return void.
		 */
		void calculateMean();
		
		/**
		 * This method calculates all the covariances and 
		 * store them on the attribute 'covariance'.
		 * 
		 * @param void.
		 * @return void.
		 */
		void calculateCovariance();
		
	private:

		/**
		 * This method return the result of the function.
		 * 
		 * @param float* data data used in the function.
		 * @param mfList<int>* variables list with the variables.
		 * @return double the result of the function.
		 */
		double getFunctionResult(float* data, mfList<int>* variables);
};

#endif /*_CYB_GAUSSIAN_H_*/
