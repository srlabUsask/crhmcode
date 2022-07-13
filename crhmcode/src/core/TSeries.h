#pragma once

#ifndef TSERIES
#define TSERIES

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

		for (int i = 0; i < original->Count(); i++)
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
	* @return int number of points in the series. 
	*/
	int Count()
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
	* Returns the XValue of the nth point in the series.
	* 
	* @param n - int the point in the series to retreive the value of.
	* @return double the X value at the nth point.
	*/
	double XValue(int n) 
	{ 
		return points.at(n).first;
	};
	
	/**
	* Sets the X value of the nth point in the series to the passed in value.
	* 
	* @param n - int the point in the series to set the value of.
	* @param value - double the value to set the X value of the nth point in the series to.
	*/
	void setXValue(int n, double value)
	{
		this->points.at(n).first = value;
	};

	/**
	* Returns the Y Value of the nth point in the series.
	*
	* @param n - int the point in the series to retreive the value of.
	* @return double the Y value at the nth point.
	*/
	double YValue(int nn) 
	{ 
		return points.at(nn).second;
	};

	/**
	* Sets the Y value of the nth point in the series to the passed in value.
	*
	* @param n - int the point in the series to set the value of.
	* @param value - double the value to set the Y value of the nth point in the series to.
	*/
	void setYValue(int nn, double value)
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

};

#endif // !TSERIES
