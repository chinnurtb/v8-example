#include <iostream>
#include <v8\v8.h>
#include "console.hpp"
#include "point.hpp"

using namespace std;
using namespace v8;

const char* SCRIPT_PATH = "script.js";

//
// Reads a file. (Taken from Google's example.)
//
// @return The file contents.
//
Handle< String > ReadFile( const char* name ) {
  // Try to open file
	FILE* file;
	fopen_s( &file, name, "rb" );
	if ( file == NULL ) return Handle< String >();

	// Get file size
	fseek( file, 0, SEEK_END );
	int size = ftell( file );
	rewind( file );

	// Read file
	char* chars = new char[ size + 1 ];
	chars[ size ] = '\0';
	for ( int idx = 0; idx < size; ) {
		int read = static_cast< int >( fread( &chars[ idx ], 1, size - idx, file ) );
		idx += read;
	}

	// Close file and wrap content
	fclose( file );
	Handle< String > content = String::New( chars, size );
	delete[] chars;

	// Return content
	return content;
}

//
// Main entry point.
//
// @param argc - Argument count.
// @param argv - Argument values.
//
int main(int argc, char* argv[]) {
	// Initialization Pt. I (creating the global scope)
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope handleScope( isolate );
	cout << "V8 version: " << V8::GetVersion() <<
		endl << "--------------------------------------------" <<
		endl << endl;

	// Global and other static objects
	Handle< ObjectTemplate > global = ObjectTemplate::New();
	Console::Bind( &global );

	// Initialization Pt. II (creating the global execution contexts)
	Handle< Context > hContext = Context::New( isolate, NULL, global );
	Persistent< Context > pContext( isolate, hContext );
	Context::Scope ctxScope( hContext );

	// Instance objects
	Point::Bind( isolate, hContext );

	// Read file and run it
	Handle< Script > script;
	Handle< String > source = ReadFile( SCRIPT_PATH );
	{
		// Compilation scope

		TryCatch tryCatch;
		script = Script::Compile( source );
		if ( script.IsEmpty() ) {
			String::Utf8Value error( tryCatch.Exception() );
			cout << *error << endl;
			return 1;
		}
	}
	{
		// Execution scope

		TryCatch tryCatch;
		script->Run();
		if ( tryCatch.HasCaught() ) {
			String::Utf8Value error( tryCatch.Exception() );
			cout << *error << endl;
			return 1;
		}
	}
	
	cout << endl << "--------------------------------------------" << endl;
	return 0;
}
