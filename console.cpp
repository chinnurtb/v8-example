#include "console.hpp"
#include "point.hpp"

using namespace std;
using namespace v8;

/// ------------------------------------------------------------
/// HELPER METHODS
/// ------------------------------------------------------------

//
// Outputs arguments to the console.
//
// @param args - V8 passed arguments.
// @param begin - Argument begin position.
//
void OutputArgs( const FunctionCallbackInfo< Value >& args, int begin ) {
  HandleScope scope;
	
	for ( int idx = begin; idx < args.Length(); idx++ ) {
		String::Utf8Value item( args[ idx ] );
		cout << *item;
	}

	cout << endl;
}

/// ------------------------------------------------------------
/// STATIC METHODS
/// ------------------------------------------------------------

void Console::Log( const FunctionCallbackInfo< Value >& args ) {
	OutputArgs( args, 0 );
}

void Console::Assert( const FunctionCallbackInfo< Value >& args ) {
	// We need at least two arguments.
	if ( args.Length() < 2 )
		return;

	// Make sure first arg is an expression
	if ( !args[ 0 ]->IsBoolean() )
		return;

	// Perform assert operation
	bool expr = args[ 0 ]->BooleanValue();
	if ( !expr )
		OutputArgs( args, 1 );
}

void Console::Test( const FunctionCallbackInfo< Value >& args ) {
	// Enter new scope
	HandleScope scope;

	// Get wrapped object
	Local< Object > obj = args[ 0 ]->ToObject();
	if ( obj->InternalFieldCount() != 1 )
		return;
	Local< External > wrap = Local< External >::Cast( obj->GetInternalField( 0 ) );

	// Get actual point and print info
	Point* p = static_cast< Point* >( wrap->Value() );
	cout << "X = " << p->GetX() << ", Y = " << p->GetY() << endl;
}

void Console::Bind( Handle< ObjectTemplate >* parent ) {
	// Create object reference
	HandleScope scope;
	Handle< ObjectTemplate > hConsole = ObjectTemplate::New();

	// Bind methods
	hConsole->Set( String::New( "log" ),    FunctionTemplate::New( Log ) );
	hConsole->Set( String::New( "assert" ), FunctionTemplate::New( Assert ) );
	hConsole->Set( String::New( "test" ),   FunctionTemplate::New( Test ) );

	// Set parent object
	( *parent )->Set( String::New( "console" ), hConsole );
}
