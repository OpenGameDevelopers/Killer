#ifndef __KILLER_MATERIALMANAGER_HPP__
#define __KILLER_MATERIALMANAGER_HPP__

#include <DataTypes.hpp>
#include <map>
#include <string>

namespace Killer
{
	struct MATERIAL_SHADER
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Material;
	class Shader;
	class Texture;

	class MaterialManager
	{
	public:
		MaterialManager( );
		~MaterialManager( );

		KIL_UINT32 CreateMaterial( const std::string &p_FileName,
			KIL_UINT32 &p_Hash );

		KIL_UINT32 Apply( const KIL_UINT32 p_Hash );

		KIL_UINT32 CreateShader( const MATERIAL_SHADER &p_ShaderInfo,
			KIL_UINT32 &p_Hash );

		KIL_UINT32 SetShaderConstant( const KIL_UINT32 p_Hash,
			const char *p_pConstant, void *p_pData );

		KIL_UINT32 LoadTexture( const std::string &p_FileName,
			KIL_UINT32 &p_Hash );

	private:
		MaterialManager( const MaterialManager &p_Other );
		MaterialManager &operator=( const MaterialManager &p_Other );

		std::map< KIL_UINT32, Material * >	m_Materials;
		std::map< KIL_UINT32, Shader * >	m_Shaders;
		std::map< KIL_UINT32, Texture * >	m_Textures;
	};
}

#endif // __KILLER_MATERIALMANAGER_HPP__

