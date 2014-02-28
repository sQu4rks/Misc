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
#include <map>
#include <fstream>

using namespace std;

// Define a Replacemap
typedef map<string,string> TOptionMap;
typedef pair<string,string> TOptionPair;
typedef map<string,string>::iterator TIterator;

vector<string> splitString(string str,string delim)
{
	vector<string> retrieved;
	size_t pos = str.find_first_of( delim.c_str() );

	while( !str.empty() )
	{
		string cur = str.substr( 0,pos);
		if( !cur.empty() )
		{
			retrieved.push_back(cur);
		}
		if( pos == string::npos )
		{
			break;
		}
		str = str.substr(pos+1);
		pos = str.find_first_of(delim);
	}
	
	return retrieved;
}

void printMap(TOptionMap map)
{
	for( TIterator iterator = map.begin();iterator != map.end(); iterator++ )
	{
		cout << iterator->first << " --> " << iterator->second << endl; 
	}
}
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
		TOptionMap replaceMap;
		for( int i=0;i<splitVector.size();i++)
		{
			// Split for key-value 
			string delim = ":";
			size_t pos = 0;
			string token;
			vector<string> splitResult;
		
			splitResult = splitString(splitVector[i],":");
			replaceMap.insert(TOptionPair(splitResult[0],splitResult[1]));
		}
		printMap(replaceMap);
		
		// Now read the files 
		ifstream inFile;
		inFile.open(infile.c_str(),ios::in);
		cout << "Opened " << infile << " as Input" << endl;

		ofstream outFile;
		outFile.open(outfile.c_str(),ios::app);
		cout << "Opened " << outfile << " as Output" << endl;

		// Loop over infile
		string line;
		while( getline(inFile,line) )
		{
			for( TIterator iterator = replaceMap.begin();iterator != replaceMap.end(); iterator++ )
			{
				size_t pos = line.find(iterator->first);
				if( pos != string::npos )
				{
					line.replace( pos,iterator->first.length(),iterator->second );
				}
			}
			// Now replace special chars
			size_t pos = line.find("_");
			if( pos != string::npos )
			{
				line.replace( pos,1," " );
			}
			// Writing to new file
			outFile << line;
		}
	}
}
