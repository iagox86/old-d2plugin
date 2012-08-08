#pragma once
#include <string>
#include <vector>

template <typename T>
class basic_stringtokenizer : public std::vector< std::basic_string< T > >
{
public:
	typedef std::basic_string< T > stringtype;

public:

	// Credit to: http://www.thecodezone.com/diary/archives/000057.html
	basic_stringtokenizer( const stringtype &str, const stringtype &delimeters = "\n" )
	{
		std::basic_string< T >::size_type lastPos = str.find_first_not_of( delimeters, 0 );
		std::basic_string< T >::size_type pos = str.find_first_of( delimeters, lastPos );

		while ( stringtype::npos != pos || stringtype::npos != lastPos )
		{
			this->push_back( str.substr( lastPos, pos - lastPos ) );

			lastPos = str.find_first_not_of( delimeters, pos );
			pos = str.find_first_of( delimeters, lastPos );
		}
	}

};
typedef basic_stringtokenizer<char> StringTokenizer;


template <typename T> 
T ParseFromString( const std::string& str ) 
{ 
	std::stringstream ss; 
	ss << str; 
		
	T obj; 
	ss >> obj; 
	return obj; 
}