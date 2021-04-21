#pragma once

#ifndef TOBJECT
#define TOBJECT
typedef void TObject;
#endif // !TOBJECT

#ifndef STRING_AND_OBJECT
#define STRING_AND_OBJECT

using namespace std;

/**
* StringandObject Class couples a TObject reference with a String name.
*/
class StringandObject {

public:
	
	string Name; //!< The name of the Object
	TObject* Object; //!< Reference to the Object


	/**
	* Default constructor sets StringandObject::Name to empty string and StringandObject::Object to NULL
	*/
	StringandObject() { Name = ""; Object = NULL; }


	/**
	* Constructor 
	* 
	* @param Name_ The name to initalize the object with.
	* @param Object_ The TObject to initalize the object with.
	*/
	StringandObject(string Name_, TObject* Object_) { Name = Name_; Object = Object_; }
	

	/**
	* Returns StringandObject::Name of this object. 
	* 
	* @return String - The name of this object.
	*/
	string get_Name() { return Name; }
	

	/*
	* Returns StringandObject::Object.
	* 
	* @return a reference to the contained TObject.
	*/
	TObject* get_Object() { return Object; }
};


#endif // !STRING_AND_OBJECT