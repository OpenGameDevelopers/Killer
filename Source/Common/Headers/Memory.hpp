#ifndef __KILLER_MEMORY_HPP__
#define __KILLER_MEMORY_HPP__

#include <DataTypes.hpp>

namespace Killer
{
	template< typename T >
	void SafeDelete( T *&p_pPointer )
	{
		if( p_pPointer )
		{
			delete p_pPointer;
			p_pPointer = KIL_NULL;
		}
	}

	template< typename T >
	void SafeDeleteArray( T *&p_pPointer )
	{
		if( p_pPointer )
		{
			delete [ ] p_pPointer;
			p_pPointer = KIL_NULL;
		}
	}
}

#endif // __KILLER_MEMORY_HPP__

