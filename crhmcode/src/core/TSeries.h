/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
#pragma once

#ifndef TSERIES
#define TSERIES

#include "StandardConverterUtility.h"

/** 
* Stores a series of data that represents a line graph with a vector of 
* X,Y coordinate points that are stored as pairs of doubles.
*/
class TSeries {
private:

	/* Title of the series of data */
	std::string Title;

	/* Refrence to the variable object this data is related to */
	ClassVar* Tag{ NULL };

	/* The X,Y coordinates of the graph */
	std::vector<std::pair<double, double>> points;

	/**
	* Recursive helper for findPointOnXAxis
	* Recursively performs binary search between minIndex and maxIndex looking for key
	*
	* @param minIndex long - The smallest index that is still a valid candidate to hold key
	* @param pivot long - The halfway point between the min and max Index
	* @param maxIndex long - The largest index that is still a valid candidate to hold key
	* @return long after recursion finishes the index that holds key or -1 if key is not in series
	*/
	long findPointOnXAxisRecurse(long minIndex, long pivot, long maxIndex, double key)
	{
		double pivotValue = this->XValue(pivot);
		std::string keyString = StandardConverterUtility::GetDateTimeInStringForOutput(key);
		std::string pivotString = StandardConverterUtility::GetDateTimeInStringForOutput(pivotValue);

		if (keyString == pivotString)
		{
			return pivot;
		}
		else if (minIndex == pivot || maxIndex == pivot)
		{
			return -1;
		}
		else if (key > pivotValue)
		{
			long newMinIndex = pivot;
			long newMaxIndex = maxIndex;
			long newPivot = (newMinIndex + newMaxIndex) / 2;

			return findPointOnXAxisRecurse(newMinIndex, newPivot, newMaxIndex, key);
		}
		else if (key < pivotValue)
		{
			long newMindex = minIndex;
			long newMaxIndex = pivot;
			long newPivot = (newMindex + newMaxIndex) / 2;

			return findPointOnXAxisRecurse(newMindex, newPivot, newMaxIndex, key);
		}
		else
		{
			return -1;
		}
	};

public:
	
	/**
	* Standard Constructor
	* 
	* Reserves 50,000 spaces in the points vector
	*/
	TSeries()
	{
		points = std::vector<std::pair<double, double>>();
		points.reserve(50000);
	};

	/**
	* Copy Constructor
	*/
	TSeries(TSeries* original)
	{
		this->Title = original->getTitle();
		this->Tag = original->getTag();

		for (long i = 0; i < original->Count(); i++)
		{
			this->AddXY(original->XValue(i), original->YValue(i));
		}
	};

	/**
	* Standard Deconstructor
	*/
	~TSeries()
	{
	};

	/**
	* Gets the series title
	* 
	* @return std::string - the series title
	*/
	std::string getTitle()
	{
		return this->Title;
	};

	/**
	* Sets the series title
	* 
	* @param title - std::string the string to set the series title to.
	*/
	void setTitle(std::string title)
	{
		this->Title = title;
	};

	/**
	* Gets the series tag
	* 
	* @return ClassVar* - reference to the variable object this series refers to.
	*/
	ClassVar* getTag()
	{
		return this->Tag;
	};
	
	/**
	* Sets the series tag
	* 
	* @param tag - ClassVar* reference to the variable object to set as the series tag.
	*/
	void setTag(ClassVar* tag)
	{
		this->Tag = tag;
	};

	/*
	* Returns the number of points in the series
	* 
	* @return long number of points in the series. 
	*/
	long Count()
	{
		return points.size();
	};

	/**
	* Adds a point to the series.
	* 
	* @param X - double the X-axis value for the point to be added.
	* @param Y - double the Y-axis value for the point to be added.
	*/
	void AddXY(double X, double Y)
	{
		points.insert(points.end(), std::pair<double, double>(X, Y));
	};

	/**
	* Inserts the point X,Y after the specified point in the series
	* 
	* @param pos long - the index of the position to place this point after
	* @param X double - the X value of the point to be inserted.
	* @param Y double - the Y value of the point to be inserted.
	*/
	void InsertXY(long pos, double X, double Y)
	{
		points.insert(points.begin()+pos, std::pair<double, double>(X, Y));
	};
	
	/**
	* Returns the XValue of the nth point in the series.
	* 
	* @param n - long the point in the series to retreive the value of.
	* @return double the X value at the nth point.
	*/
	double XValue(long n) 
	{ 
		return points.at(n).first;
	};
	
	/**
	* Sets the X value of the nth point in the series to the passed in value.
	* 
	* @param n - long the point in the series to set the value of.
	* @param value - double the value to set the X value of the nth point in the series to.
	*/
	void setXValue(long n, double value)
	{
		this->points.at(n).first = value;
	};

	/**
	* Returns the Y Value of the nth point in the series.
	*
	* @param n - long the point in the series to retreive the value of.
	* @return double the Y value at the nth point.
	*/
	double YValue(long nn) 
	{ 
		return points.at(nn).second;
	};

	/**
	* Sets the Y value of the nth point in the series to the passed in value.
	*
	* @param n - long the point in the series to set the value of.
	* @param value - double the value to set the Y value of the nth point in the series to.
	*/
	void setYValue(long nn, double value)
	{
		this->points.at(nn).second = value;
	};

	/**
	* Clears all the points in the series.
	*/
	void clearSeries()
	{
		this->points.clear();
	};

	/**
	* Performs a binary search for an X value within the series. 
	* If the value is found return the index of that point. 
	* If not found return -1.
	* 
	* @param X - double the value to search for on the X Axis
	* @return long the index of the point if found, -1 if the x value is not found
	*/
	long findPointOnXAxis(double x)
	{
		long minIndex = 0;
		long maxIndex = this->Count();
		long pivot = (minIndex + maxIndex) / 2;
		
		return this->findPointOnXAxisRecurse(minIndex, pivot, maxIndex, x);
	};

	

};

#endif // !TSERIES
