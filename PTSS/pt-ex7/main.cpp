#include <iostream>
#include "iterator.hpp"
#include "array.hpp"

int main()
{
	// Print numbers in normal order
	int nums[] = {1,2,3,4,5};
	for( unsigned i = 0 ; i < 5 ; ++i )
		std::cout << nums[i];
	std::cout << std::endl;

	Array<int> array( 5 );


//	// Load numbers into array
	Array<int>::iterator iter = array.begin();
//	for( unsigned i = 0  ; iter != array.end() ; ++i )
//		*iter++ = nums[ i ];
//
//	// Print numbers in reverse order
//	iter = array.end();
//	do
//	  {
//	    std::cout << *(--iter);
//	  }
//	while( iter != array.begin() );

return 0;
}
