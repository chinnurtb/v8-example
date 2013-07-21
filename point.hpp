#ifndef _POINT_H
#define _POINT_H

#include <iostream>
#include <v8\v8.h>

using namespace v8;

//
// A sample point class for binding.
//
class Point {
  
private:
	double pX;
	double pY;
	
	//
	// Constructor function for a point.
	//
	static void Construct( const FunctionCallbackInfo< Value >& args );

	//
	// Prints the points info to the screen.
	//
	static void Print( const FunctionCallbackInfo< Value >& args );

	//
	// The get method for the X property of a point.
	//
	static void GetX( Local< String > prop, const PropertyCallbackInfo<Value>& info );

	//
	// The set method for the X property of a point.
	//
	static void SetX( Local< String > prop, Local< Value > value, const PropertyCallbackInfo< void > &info );

	//
	// The get method for the Y property of a point.
	//
	static void GetY( Local< String > prop, const PropertyCallbackInfo< Value >& info );

	//
	// The set method for the Y property of a point.
	//
	static void SetY( Local< String > prop, Local< Value > value, const PropertyCallbackInfo< void > &info );

public:
	//
	// Constructs a new point
	//
	// @param x - The point's X value.
	// @param y - The point's Y value.
	//
	Point(double x, double y);

	//
	// Gets the point's X value.
	//
	inline double GetX() { return pX; }

	//
	// Sets the point's X value.
	//
	inline void SetX( double x ) { pX = x; }

	//
	// Gets the point's Y value
	//
	inline double GetY() { return pY; }

	//
	// Sets the point's Y value.
	//
	inline void SetY( double y ) { pY = y; }

	//
	// Binds the point object to a global template.
	//
	// @param isolate - The scope isolate.
	// @param context - The execution context to register in.
	//
	static void Bind( Isolate* isolate, Handle< Context > context );

};	// point

#endif
