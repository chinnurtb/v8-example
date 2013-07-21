#include "point.hpp"

using namespace std;
using namespace v8;

Point::Point( double x, double y ) {
  pX = x;
	pY = y;
}

void Point::Bind( Isolate* isolate, Handle< Context > context ) {
	// Get creation scope
	HandleScope scope( isolate );

	// Create constructor function and object template
	Local< FunctionTemplate > constructor = FunctionTemplate::New( Construct );
	Local< ObjectTemplate > templ = constructor->InstanceTemplate();
	templ->SetInternalFieldCount( 1 );

	// Set properties and methods
	templ->SetAccessor( String::New( "x" ), GetX, SetX );
	templ->SetAccessor( String::New( "y" ), GetY, SetY );
	templ->Set( String::New( "print" ), FunctionTemplate::New( Print ) );

	// Register constructor
	context->Global()->Set( String::New( "Point" ), constructor->GetFunction() );
}

void Point::Construct( const FunctionCallbackInfo< Value >& args ) {
	// Enter new scope
	HandleScope scope;

	// new Point()
	if ( args.Length() == 0 ) {
		Point* p = new Point( 0, 0 );
		args.This()->SetInternalField( 0, External::New( p ) );
	}
	// new Point(##, ##)
	else if ( args.Length() == 2 ) {
		// Ensure params are numbers
		if ( !args[ 0 ]->IsNumber() || !args[ 1 ]->IsNumber() ) {
			Local< Value > ex = Exception::SyntaxError( String::New( "Both parameters must be numbers." ) );
			ThrowException( ex );
		}
		else {
			double x = args[ 0 ]->NumberValue();
			double y = args[ 1 ]->NumberValue();
			Point* p = new Point( x, y );
			args.This()->SetInternalField( 0, External::New( p ) );
		}
	}
	// Invalid constructor
	else {
		Local< Value > ex = Exception::SyntaxError( String::New( "Invalid point constructor." ) );
		ThrowException( ex );
	}
}

void Point::Print( const FunctionCallbackInfo< Value >& args ) {
	// Enter a new scope
	HandleScope scope;

	// Ensure no parameters
	if ( args.Length() != 0 ) {
		Handle< Value > ex = Exception::SyntaxError( String::New( "Too many parameters." ) );
		ThrowException( ex );
	}
	else {
		// Get wrapped object
		Local< Object > self = args.Holder();
		Local< External > wrap = Local< External >::Cast( self->GetInternalField( 0 ) );

		// Print formatted object data
		Point* point = static_cast< Point* >( wrap->Value() );
		cout << "[x=" << point->pX << ",y=" << point->pY << "]" << endl;
	}
}

void Point::GetX( Local< String > prop, const PropertyCallbackInfo< Value > &info ) {
	// Enter new scope
	HandleScope scope;

	// Get wrapped object
	Local< Object > self = info.Holder();
	Local< External > wrap = Local< External >::Cast( self->GetInternalField( 0 ) );

	// Set return value
	Point* point = static_cast< Point* >( wrap->Value() );
	info.GetReturnValue().Set( Number::New( point->GetX() ) );
}

void Point::SetX( Local< String > prop, Local< Value > value, const PropertyCallbackInfo< void > &info ) {
	// Enter new scope
	HandleScope scope;

	// Get wrapped object
	Local< Object > self = info.Holder();
	Local< External > wrap = Local< External >::Cast( self->GetInternalField( 0 ) );

	// Set internal value
	static_cast< Point* >( wrap->Value() )->SetX( value->NumberValue() );
}

void Point::GetY( Local< String > prop, const PropertyCallbackInfo< Value > &info ) {
	// Enter new scope
	HandleScope scope;

	// Get wrapped object
	Local< Object > self = info.Holder();
	Local< External > wrap = Local< External >::Cast( self->GetInternalField( 0 ) );

	// Set return value
	Point* point = static_cast< Point* >( wrap->Value() );
	info.GetReturnValue().Set( Number::New( point->GetY() ) );
}

void Point::SetY( Local< String > prop, Local< Value > value, const PropertyCallbackInfo< void > &info ) {
	// Enter new scope
	HandleScope scope;

	// Get wrapped object
	Local< Object > self = info.Holder();
	Local< External > wrap = Local< External >::Cast( self->GetInternalField( 0 ) );

	// Set internal value
	static_cast< Point* >( wrap->Value() )->SetY( value->NumberValue() );
}
