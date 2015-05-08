#ifndef __KILLER_MATERIAL_HPP__
#define __KILLER_MATERIAL_HPP__

#include <DataTypes.hpp>
#include <string>
#include <vector>

namespace Killer
{
	class Material
	{
	public:
		Material( );
		~Material( );

		KIL_UINT32 CreateFromFile( const std::string &p_FileName );

		KIL_UINT32 SetShaderConstant( const char *p_pConstantName,
			void *p_pData );

		KIL_UINT32 GetHash( ) const;

	private:
		Material( const Material &p_Other );
		Material &operator=( const Material &p_Other );

		KIL_UINT32					m_Hash;
		KIL_UINT32					m_ShaderHash;
		std::vector< KIL_UINT32 >	m_TextureHash;
	};
}

#endif // __KILLER_MATERIAL_HPP__

