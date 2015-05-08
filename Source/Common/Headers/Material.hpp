#ifndef __KILLER_MATERIAL_HPP__
#define __KILLER_MATERIAL_HPP__

#include <DataTypes.hpp>
#include <string>
#include <vector>

namespace Killer
{
	class MaterialManager;

	class Material
	{
	public:
		explicit Material( MaterialManager *p_pMaterialManager );
		~Material( );

		KIL_UINT32 CreateFromFile( const std::string &p_FileName );

		KIL_UINT32 GetHash( ) const;

		KIL_UINT32 GetShaderHash( ) const;

		KIL_UINT32 GetTextureHashes(
			std::vector< KIL_UINT32 > &p_Hashes ) const;

		KIL_MEMSIZE GetTextureCount( ) const;

	private:
		Material( const Material &p_Other );
		Material &operator=( const Material &p_Other );

		MaterialManager				*m_pMaterialManager;
		KIL_UINT32					m_Hash;
		KIL_UINT32					m_ShaderHash;
		std::vector< KIL_UINT32 >	m_TextureHashes;
		KIL_MEMSIZE					m_TextureCount;
	};
}

#endif // __KILLER_MATERIAL_HPP__

