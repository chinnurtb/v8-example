#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <iostream>
#include <v8\v8.h>

using namespace v8;

//
// The console class used to bind the console object to v8.
//
class Console {

private:
  //
	// Logs a message to the console.
	//
	// @param args - Function arguments.
	//
	static void Log( const FunctionCallbackInfo< Value >& args );

	//
	// Checks to make sure an expression is true. If not, then
	// a specified error message is displayed.
	//
	// @param args - Function arguments.
	//
	static void Assert( const FunctionCallbackInfo< Value >& args );

	//
	// Current test method. (Provide a point as an argument to display info.)
	//
	// @param args - Function arguments.
	//
	static void Test( const FunctionCallbackInfo< Value >& args );

public:
	//
	// Binds the console to a parent object handle.
	//
	static void Bind( Handle< ObjectTemplate >* parent );

};	// class

#endif
