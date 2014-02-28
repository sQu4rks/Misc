/*
 * =====================================================================================
 *
 *       Filename:  replace.cpp
 *
 *    Description:  Replacement tool 
 *
 *        Version:  1.0
 *        Created:  28.02.2014 15:56:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Marcel Neidinger (mn), neidinger@phaenovum.de
 *        Company:  phaenovum Schülerforschungszentrum, Lörrach
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main(int argc, char** argv)
{
	// Check amount of arguments
	if( argc < 2 )
	{
		cerr << "Too few arguments" << endl;
		cerr << "Use --help for help" << endl;
		exit(-1);
	}
	// Parse arguments
	string actionArg = argv[1];
	
	if( actionArg == "--help" || actionArg == "-h" )
	{
		cout << "replaceIT (c) Copyright 2014 - Marcel Neidinger" << endl;
		cout << "--help \t -h \t \t \t \t Prints this help message" << endl;
		cout << "--version \t -v \t \t \t Prints version information" << endl;
		cout << "--replace \t -r REPLACEOPTIONS INFILE OUTFILE \t \t Replaces all REPLACEOPTIONS FROM INFILE and writes to OUTFILE" << endl;
		cout << "Replaceoptions format: src1:target1,src2:target2 ...." << endl;
		cout << "ATTENTION: Whitespace in target needs to be escaped as _" << endl;
		exit(0);
	} 
	else if( actionArg == "--version" || actionArg == "-v" )
	{
		cout << "replaceIT (c) Copyright 2014 - Marcel Neidinger" << endl;
		cout << "contact: neidinger@phaenovum.de" << endl;
		cout << "Version 0.1 alpha" << endl;
		exit(0);
	}
	else if ( actionArg == "--replace" || actionArg == "-r" )
	{
		// Lets start some replacement
		string outfile = argv[argc - 1];
		cout << "Setting " << outfile << " as output" << endl;
	
		string infile = argv[argc - 2];
		cout << "Setting " << infile << " as input" << endl;
		
		// Concat options
		stringstream ss;
		for(int i = 2;i<argc-2;i++)
		{
			ss << argv[i];
		}	
		string replaceString = ss.str();
		cout << "Using " << replaceString << " as the replaceoptions string" << endl;
		
		// Parsing the replaceString	
		vector<string> splitVector;
		size_t pos=0;
		string token;
		string delimeter = ",";

		while( (pos = replaceString.find(",")) != string::npos )
		{
			token = replaceString.substr(0,pos);
			// Add to vector
			splitVector.push_back( token );
			cout << "Found source-target pair " << token << endl;

			replaceString.erase( 0,pos + delimeter.length() );
		}	
		
		// Now split these options and write them to an map
	}
}
