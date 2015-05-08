#include <MaterialManager.hpp>
#include <Memory.hpp>
#include <Material.hpp>
#include <Shader.hpp>
#include <Texture.hpp>
#include <iostream>
#include <vector>

namespace Killer
{
	MaterialManager::MaterialManager( )
	{
	}

	MaterialManager::~MaterialManager( )
	{
		for( auto Itr = m_Shaders.begin( ); Itr != m_Shaders.end( ); ++Itr )
		{
			SafeDelete< Shader >( Itr->second );
		}

		for( auto Itr = m_Textures.begin( ); Itr != m_Textures.end( ); ++Itr )
		{
			SafeDelete< Texture >( Itr->second );
		}

		for( auto Itr = m_Materials.begin( ); Itr != m_Materials.end( );
			++Itr )
		{
			SafeDelete< Material >( Itr->second );
		}
	}

	KIL_UINT32 MaterialManager::CreateMaterial( const std::string &p_FileName,
		KIL_UINT32 &p_Hash )
	{
		Material *pNewMaterial = new Material( this );

		if( pNewMaterial->CreateFromFile( p_FileName ) != KIL_OK )
		{
			std::cout << "[Killer::MaterialManager::CreateMaterial] <ERROR> "
				"Failed to create material: \"" << p_FileName << "\"" <<
				std::endl;

			return KIL_FAIL;
		}

		KIL_UINT32 Hash = pNewMaterial->GetHash( );

		std::pair< std::map< KIL_UINT32, Material * >::iterator, bool > Insert;

		Insert = m_Materials.insert( std::pair< KIL_UINT32, Material * >(
			Hash, pNewMaterial ) );

		if( Insert.second == false )
		{
			std::cout << "[Killer::MaterialManager::CreateMaterial] <INFO> "
				"Material \"" << p_FileName << "\" already exists" <<
				std::endl;

			SafeDelete< Material >( pNewMaterial );

			return KIL_FAIL;
		}

		p_Hash = Hash;

		return KIL_OK;
	}

	KIL_UINT32 MaterialManager::Apply( const KIL_UINT32 p_Hash )
	{
		auto MaterialItr = m_Materials.begin( );

		while( MaterialItr != m_Materials.end( ) )
		{
			if( MaterialItr->first == p_Hash )
			{
				break;
			}

			++MaterialItr;
		}

		if( MaterialItr == m_Materials.end( ) )
		{
			std::cout << "[Killer::MaterialManager::Apply] <ERROR> "
				"Failed to find material with the hash: " << p_Hash <<
				std::endl;

			return KIL_FAIL;
		}

		KIL_UINT32 ShaderHash = MaterialItr->second->GetShaderHash();

		auto ShaderItr = m_Shaders.begin( );

		while( ShaderItr != m_Shaders.end( ) )
		{
			if( ShaderItr->first == ShaderHash )
			{
				break;
			}

			++ShaderItr;
		}

		if( ShaderItr == m_Shaders.end( ) )
		{
			std::cout << "[Killer::MaterialManager::Apply] <ERROR> "
				"Failed to find shader with the hash: " << ShaderHash <<
				std::endl;

			return KIL_FAIL;
		}

		if( MaterialItr->second->GetTextureCount( ) )
		{
			std::vector< KIL_UINT32 > TextureArray;
			MaterialItr->second->GetTextureHashes( TextureArray );

			for( KIL_MEMSIZE i = 0; i < TextureArray.size( ); ++i )
			{
				auto TextureItr = m_Textures.begin( );

				while( TextureItr != m_Textures.end( ) )
				{
					if( TextureItr->first == TextureArray[ i ] )
					{
						TextureItr->second->Activate( );
						break;
					}
					++TextureItr;
				}

				if( TextureItr == m_Textures.end( ) )
				{
					std::cout << "[Killer::MaterialManager::Apply] <ERROR> "
						"Could not find texture with the hash: " <<
						TextureArray[ i ] << std::endl;

					return KIL_FAIL;
				}
			}
		}

		ShaderItr->second->Activate( );

		return KIL_OK;
	}

	KIL_UINT32 MaterialManager::CreateShader(
		const MATERIAL_SHADER &p_ShaderInfo, KIL_UINT32 &p_Hash )
	{
		Shader *pNewShader = new Shader( );

		if( p_ShaderInfo.VertexSource.size( ) != 0 )
		{
			if( pNewShader->AddShaderSource( SHADER_TYPE_VERTEX,
				p_ShaderInfo.VertexSource.c_str( ) ) != KIL_OK )
			{
				std::cout << "[Killer::MaterialManager::CreateShader] <ERROR> "
					"Failed to create vertex shader" << std::endl;

				return KIL_FAIL;
			}
		}

		if( p_ShaderInfo.FragmentSource.size( ) != 0 )
		{
			if( pNewShader->AddShaderSource( SHADER_TYPE_FRAGMENT,
				p_ShaderInfo.FragmentSource.c_str( ) ) != KIL_OK )
			{
				std::cout << "[Killer::MaterialManager::CreateShader] <ERROR> "
					"Failed to create fragment shader" << std::endl;

				return KIL_FAIL;
			}
		}

		p_Hash = pNewShader->GetHash( );

		std::pair< std::map< KIL_UINT32, Shader * >::iterator, bool >
			InsertResult;

		InsertResult = m_Shaders.insert( std::pair< KIL_UINT32, Shader * >(
			p_Hash, pNewShader ) );


		if( InsertResult.second == false )
		{
			std::cout << "[Killer::MaterialManager::CreateShader] <ERROR "
				"Shader already exists" << std::endl;

			SafeDelete< Shader >( pNewShader );

			return KIL_FAIL;
		}

		return KIL_OK;
	}

	KIL_UINT32 MaterialManager::SetShaderConstant( const KIL_UINT32 p_Hash,
		const char *p_pConstant, void *p_pData )
	{
		auto MaterialItr = m_Materials.begin( );

		while( MaterialItr != m_Materials.end( ) )
		{
			if( MaterialItr->first == p_Hash )
			{
				break;
			}

			++MaterialItr;
		}

		if( MaterialItr == m_Materials.end( ) )
		{
			std::cout << "[Killer::MaterialManager::SetShaderConstant] "
				"<ERROR> Failed to find material with the hash: " << p_Hash <<
				std::endl;

			return KIL_FAIL;
		}

		KIL_UINT32 ShaderHash = MaterialItr->second->GetShaderHash( );

		auto ShaderItr = m_Shaders.begin( );

		while( ShaderItr != m_Shaders.end( ) )
		{
			if( ShaderItr->first == ShaderHash )
			{
				break;
			}

			++ShaderItr;
		}

		if( ShaderItr == m_Shaders.end( ) )
		{
			std::cout << "[Killer::MaterialManager::SetShaderConstant] "
				"<ERROR> Failed to find the shader with hash: " <<
				ShaderHash << std::endl;

			return KIL_FAIL;
		}

		return ShaderItr->second->SetConstantData( p_pConstant, p_pData );
	}

	KIL_UINT32 MaterialManager::LoadTexture( const std::string &p_FileName,
		KIL_UINT32 &p_Hash )
	{
		Texture *pNewTexture = new Texture( );

		if( pNewTexture->Load( p_FileName ) != KIL_OK )
		{
			std::cout << "[Killer::MaterialManager::LoadTexture] <ERROR> "
				"Failed to load texture: \"" << p_FileName << "\"" <<
				std::endl;

			return KIL_FAIL;
		}

		p_Hash = pNewTexture->GetHash( );

		std::pair< std::map< KIL_UINT32, Texture * >::iterator, bool >
			InsertResult;

		InsertResult = m_Textures.insert(
			std::pair< KIL_UINT32, Texture * >( p_Hash, pNewTexture ) );
		
		if( InsertResult.second == false )
		{
			std::cout << "[Killer::MaterialManager::LoadTexture] <ERROR> "
				"Texture hash " << p_Hash << " already exists" << std::endl;

			return KIL_FAIL;
		}

		return KIL_OK;
	}
}

