// test.cpp : Defines the entry point for the console application.
//
#include <time.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <sstream>
#include <ctime>

using namespace std;

struct VersionItem{int major,minor,build,revision;};

#define SNOWOLF_RC_VERSION_BUILD_WIN32 1000

int lexical_cast(const string & input)
{
	int result;

	stringstream stream;

	stream << input;

	stream >> result;

	return result;
}

VersionItem CreateVersion(const std::string & name)
{
	string versionBodies[4];

	string::size_type index,counter = 0;

	string buffer = name;

	while( string::npos != (index = buffer.find('.')))
	{
		if(counter < 4)
		{
			versionBodies[counter ++ ] = buffer.substr(0,index);
		}
		else
		{
			cout << "Version String Format Error" << endl;

			exit(1);
		}

		buffer = buffer.substr(index + 1);
	}

	if(counter < 4) versionBodies[counter] = buffer;

	VersionItem result = {0};


	result.major = lexical_cast(versionBodies[0]);

	result.minor = lexical_cast(versionBodies[1]);

	if(!versionBodies[2].empty())
	{
		if("*" == versionBodies[2])
		{
			if(!versionBodies[3].empty())
			{
				cout << "Version String Format Error" << endl;

				exit(1);
			}
			
			time_t time;

			std::time(&time);

			tm* t = ::gmtime(&time);

			result.build = (t->tm_year - 110) * 360 + t->tm_yday;

			result.revision = t->tm_hour * 3600 + t->tm_min * 60 + t->tm_sec;
			
			
		}
		else
		{
			result.build = lexical_cast(versionBodies[2]);

			if(!versionBodies[3].empty())
			{
				if("*" == versionBodies[3])
				{
					time_t time;

					std::time(&time);

					tm* t = ::gmtime(&time);

					result.revision = t->tm_hour * 3600 + t->tm_min * 60 + t->tm_sec;
				}
				else
				{
					result.revision = lexical_cast(versionBodies[3]);
				}
			}
		}
	}
	else
	{
		if(!versionBodies[3].empty()) 
		{
			cout << "Version String Format Error" << endl;

			exit(1);
		}
	}

	return result;
}


string StringUpper(const std::string& message)
{

	string result;

	std::transform(message.begin(), message.end(), back_inserter(result), std::toupper);

	return result;
}

int main(int args, char** argv)
{
	if(4 != args)	
	{
		cout << "ghca-library-config [namespace] [version] [path]" << endl;

		return 1;
	}

	vector<string> namespace_;

	char *sp = " .";

	char * token = strtok(argv[1],sp);

	while( 0 != token)
	{
		namespace_.push_back(token);

		token = strtok(0,sp);
	}

	VersionItem version = CreateVersion(argv[2]);

	fstream file(argv[3],ios::trunc | ios_base::out);

	if(!file.is_open())
	{
		cout << "can't create output:" << argv[3] << endl;

		return 1;
	}

	stringstream stream;

	for(size_t index = 0 ; index < namespace_.size() - 1; ++ index)
	{
		stream << StringUpper(namespace_[index]) << "_";
	}

	stream << StringUpper(namespace_.back());

	
	file << "#ifndef " << stream.str() << "_H_HPP" << endl;

	file << "#define " << stream.str() << "_H_HPP" << endl << endl;

	file << "#define " << stream.str() << "_VERSION \t" << "\""

		<< version.major << "." << version.minor << "." << version.build

		<< "." << version.revision << "\"" << endl << endl;
		
	file << "#ifndef " << "EXTERN_C" << endl;
	
	file << "#	ifdef " << "__cplusplus" << endl;
	
	file << "#		define EXTERN_C    extern \"C\" " << endl;
	
	file << "#	else" << endl;
	
	file << "#		define EXTERN_C    extern" << endl;
	
	file << "#	endif" << endl;
	
	file << "#endif" << endl;
		
	file << "#ifdef " << stream.str() << "_SHARE_LIB" << endl;

#ifdef WIN32	
	
	file << "#	define " << stream.str() << "_EXPORT  __declspec(dllexport)" << endl;
	
	file << "#	define " << stream.str() << "_IMPORT  __declspec(dllimport)" << endl;
	
#else
	
	file << "#	define " << stream.str() << "_EXPORT " << endl;
	
	file << "#	define " << stream.str() << "_IMPORT " << endl;
	
#endif
	
	file << "#else" << endl;
	
	file << "#	define " << stream.str() << "_EXPORT " << endl;
	
	file << "#	define " << stream.str() << "_IMPORT " << endl;
	
	file << "#endif" << endl;
	
	file << "#ifdef " << stream.str() << "_BUILD " << endl;
	
	file << "#	define " << stream.str() << "_API EXTERN_C " << stream.str() << "_EXPORT " << endl;
	
	file << "#else" << endl;
	
	file << "#	define " << stream.str() << "_API EXTERN_C " << stream.str() << "_IMPORT " << endl;
	
	file << "#endif" << endl;

	file << "#endif //" << stream.str() << "_H_HPP" << endl;

	return 0;

}



