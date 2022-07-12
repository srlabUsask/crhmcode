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

public:
	

	/* The X,Y coordinates of the graph */
	std::vector<std::pair<double, double>> points;

	TSeries()
	{
		points = std::vector<std::pair<double, double>>();
		points.reserve(50000);
	};

	~TSeries()
	{
	};

	std::string getTitle()
	{
		return this->Title;
	};

	void setTitle(std::string title)
	{
		this->Title = title;
	};

	ClassVar* getTag()
	{
		return this->Tag;
	};
	
	void setTag(ClassVar* tag)
	{
		this->Tag = tag;
	};

	void AddXY(double X, double Y)
	{
		points.insert(points.end(), std::pair<double, double>(X, Y));
	};
	
	int Count() 
	{ 
		return points.size(); 
	};
	
	double XValue(int nn) 
	{ 
		return points.at(nn).first;
	};
	
	double YValue(int nn) 
	{ 
		return points.at(nn).second;
	};
};

#endif // !TSERIES
