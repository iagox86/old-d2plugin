#pragma once
#include <string>
#include <vector>

template <typename T>
class basic_stringtokenizer : public std::vector< std::basic_string< T > >
{
public:
	typedef std::basic_string< T > stringtype;
	typedef std::basic_string< T >::size_type st_t;

public:

	// Credit to: http://www.thecodezone.com/diary/archives/000057.html
	basic_stringtokenizer( const stringtype &str, const stringtype &delimeters = "\n" )
	{
		st_t lastPos = str.find_first_not_of( delimeters, 0 );
		st_t pos = str.find_first_of( delimeters, lastPos );

		while ( stringtype::npos != pos || stringtype::npos != lastPos )
		{
			this->push_back( str.substr( lastPos, pos - lastPos ) );

			lastPos = str.find_first_not_of( delimeters, pos );
			pos = str.find_first_of( delimeters, lastPos );
		}
	}
};

typedef basic_stringtokenizer<char> StringTokenizer;
