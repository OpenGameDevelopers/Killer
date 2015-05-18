#include <Material.hpp>
#include <MaterialManager.hpp>
#include <Shader.hpp>
#include <Memory.hpp>
#include <FNV.hpp>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace Killer
{
	Material::Material( MaterialManager *p_pMaterialManager ) :
		m_pMaterialManager( p_pMaterialManager ),
		m_Hash( FNV32_OFFSET ),
		m_ShaderHash( FNV32_OFFSET ),
		m_TextureCount( 0 )
	{
	}

	Material::~Material( )
	{
	}

	KIL_UINT32 Material::CreateFromFile( const std::string &p_FileName )
	{
		if( p_FileName.size( ) == 0 )
		{
			std::cout << "[Killer::Material::CreateFromFile] <ERROR> "
				"File path is of length zero" << std::endl;

			return KIL_FAIL;
		}

		std::cout << "[Killer::Material::CreateFromFile] <INFO> "
			"Loading: \"" << p_FileName << "\"" << std::endl;

		FILE *pFile = fopen( p_FileName.c_str( ), "rb" );

		if( pFile == KIL_NULL )
		{
			std::cout << "[Killer::Material::CreateFromFile] <ERROR> "
				"Failed to open file \"" << p_FileName << "\"" << std::endl;

			return KIL_FAIL;
		}

		fseek( pFile, 0L, SEEK_END );
		KIL_MEMSIZE FileSize = ftell( pFile );
		rewind( pFile );

		char *pSource = new char[ FileSize + 1 ];

		fread( pSource, 1, FileSize, pFile );

		pSource[ FileSize ] = '\0';

		fclose( pFile );
		pFile = KIL_NULL;

		rapidjson::Document MaterialFile;
		MaterialFile.Parse( pSource );

		SafeDeleteArray< char >( pSource );

		struct MATERIAL_SHADER MaterialShader;

		if( MaterialFile.HasMember( "shader" ) )
		{
			rapidjson::Value &ShaderRoot = MaterialFile[ "shader" ];

			if( ShaderRoot.HasMember( "source" ) )
			{
				if( ShaderRoot[ "source" ].IsArray( ) == false )
				{
					std::cout << "[Killer::Material::CreateFromFile] <ERROR> "
						"Failed to load shader source, it is not recognised "
						"as being an array of values" << std::endl;

					return KIL_FAIL;
				}

				rapidjson::Value &ShaderSourceRoot = ShaderRoot[ "source" ];

				std::cout << "[Killer::material::CreateFromFile] <INFO> "
					"Processing " << ShaderSourceRoot.Size()  << " shaders" <<
					std::endl;

				for( rapidjson::SizeType i = 0; i < ShaderSourceRoot.Size( );
					++i )
				{
					std::string ShaderSource;
					SHADER_TYPE ShaderType = SHADER_TYPE_UNKNOWN;

					if( ShaderSourceRoot[ i ].HasMember( "type" ) )
					{
						std::string ShaderTypeString =
							ShaderSourceRoot[ i ][ "type" ].GetString( );

						if( ShaderTypeString.compare( "vertex" ) == 0 )
						{
							std::cout << "[Killer::Material::CreateFromFile] "
								"<INFO> Found a vertex shader" << std::endl;
							ShaderType = SHADER_TYPE_VERTEX;
						}
						else if( ShaderTypeString.compare( "fragment" ) == 0 )
						{
							std::cout << "[Killer::Material::CreateFromFile] "
								"<INFO> Found a fragment shader" << std::endl;
							ShaderType = SHADER_TYPE_FRAGMENT;
						}
						else
						{
							std::cout << "[Killer::Material::CreateFromFile] "
								"<ERROR> Unrecognised shader type \"" <<
								ShaderSourceRoot[ i ][ "type" ].GetString( ) <<
								"\"" << std::endl;

							return KIL_FAIL;
						}
					}
					else
					{
						std::cout << "[Killer::Material::CreateFromFile] "
							"<ERROR> Could not find a \"type\" member" <<
							std::endl;

						return KIL_FAIL;
					}

					if( ShaderSourceRoot[ i ].HasMember( "path" ) )
					{
						std::cout << "[Killer::Material::CreateFromFile] "
							"<INFO> Shader is in a file" << std::endl;

						FILE *pShaderFile = fopen(
							ShaderSourceRoot[ i ][ "path" ].GetString( ),
							"rb" );

						if( pShaderFile == KIL_NULL )
						{
							std::cout << "[Killer::Material::CreateFromFile] "
								"<ERROR> Failed to open shader for reading" <<
								std::endl;

							return KIL_FAIL;
						}

						fseek( pShaderFile, 0L, SEEK_END );
						KIL_MEMSIZE ShaderLength = ftell( pShaderFile );
						rewind( pShaderFile );

						char *pShaderSource = new char[ ShaderLength + 1 ];
						pShaderSource[ ShaderLength ] = '\0';

						fread( pShaderSource, 1, ShaderLength, pShaderFile );

						fclose( pShaderFile );

						ShaderSource.assign( pShaderSource );

						SafeDeleteArray< char >( pShaderSource );
					}
					else if( ShaderSourceRoot[ i ].HasMember( "code" ) )
					{
						std::cout << "[Killer::Material::CreateFromFile] "
							"<INFO> Shader is in code form" << std::endl;

						ShaderSource =
							ShaderSourceRoot[ i ][ "code" ].GetString( );
					}
					else
					{
						std::cout << "[Killer::Material::CreateFromFile] "
							"<ERROR> Failed to find either a \"path\" or "
							"\"code\" member" << std::endl;

						return KIL_FAIL;
					}

					switch( ShaderType )
					{
						case SHADER_TYPE_VERTEX:
						{
							MaterialShader.VertexSource = ShaderSource;
							break;
						}
						case SHADER_TYPE_FRAGMENT:
						{
							MaterialShader.FragmentSource = ShaderSource;
							break;
						}
						default:
						{
							std::cout << "[Killer::Material::CreateFromFile] "
								"<ERROR> Unknown shader type" << std::endl;
							return KIL_FAIL;
						}
					}
				}
			}
			else
			{
				std::cout << "[Killer::Material::CreateFromFile] <ERROR> "
					"Failed to find a \"source\" member for the shader" <<
					std::endl;

				return KIL_FAIL;
			}
		}
		else
		{
			std::cout << "[Killer::Material::CreateFromFile] <ERROR> "
				"Could not find a shader" << std::endl;

			return KIL_FAIL;
		}

		if( MaterialFile.HasMember( "texture" ) )
		{
			rapidjson::Value &TextureRoot = MaterialFile[ "texture" ];

			if( TextureRoot.IsArray( ) )
			{
				for( rapidjson::SizeType i = 0; i < TextureRoot.Size( ); ++i )
				{
					std::string TextureFile;
					if( TextureRoot[ i ].HasMember( "type" ) )
					{
						std::string TypeString =
							TextureRoot[ i ][ "type" ].GetString( );

						if( TypeString.compare( "albedo" ) == 0 )
						{
							std::cout << "[Killer::Material::CreateFromFile] "
								"<INFO> Albedo texture found: \"";
						}
						else
						{
							std::cout << "[Killer::Material::CreateFromFile] "
								"<WARN> Unknown texture: \"" << std::endl;
						}
					}
					else
					{
						std::cout << "[Killer::Material::CreateFromFile] "
							"<ERROR> No \"type\" member found for texture" <<
							std::endl;

						return KIL_FAIL;
					}

					if( TextureRoot[ i ].HasMember( "path" ) )
					{
						TextureFile = TextureRoot[ i ][ "path" ].GetString( );
					}
					else
					{
						std::cout << "[Killer::Material::CreateFromFile] "
							"<ERROR> No path to texture" << std::endl;

						return KIL_FAIL;
					}

					std::cout << TextureFile << "\"" << std::endl;

					KIL_UINT32 TextureHash;
					if( m_pMaterialManager->LoadTexture( TextureFile,
						TextureHash ) != KIL_OK )
					{
						std::cout << "[Killer::Material::CreateFromFile] "
							"<ERROR> Could not load texture: \"" <<
							TextureFile << "\"" << std::endl;

						return KIL_FAIL;
					}

					m_TextureHashes.push_back( TextureHash );
					++m_TextureCount;
				}
			}
			else
			{
				std::cout << "[Killer::Material::CreateFromFile] <ERROR> "
					"Textures are not in an array, aborting" << std::endl;

				return KIL_FAIL;
			}
		}
		else
		{
			std::cout << "[Killer::Material::CreateFromFile] <INFO> "
				"No textures found" << std::endl;
		}

		m_pMaterialManager->CreateShader( MaterialShader, m_ShaderHash );

		m_Hash = HashStringFNV1a( p_FileName.c_str( ) );

		return KIL_OK;
	}

	KIL_UINT32 Material::GetHash( ) const
	{
		return m_Hash;
	}

	KIL_UINT32 Material::GetShaderHash( ) const
	{
		return m_ShaderHash;
	}

	KIL_UINT32 Material::GetTextureHashes(
		std::vector< KIL_UINT32 > &p_Hashes ) const
	{
		if( m_TextureHashes.size( ) == 0 )
		{
			std::cout << "[Killer::Material::GetTextureHashes] <WARN> "
				"No textures present in material" << std::endl;

			return KIL_FAIL;
		}

		for( KIL_MEMSIZE TextureIndex = 0;
			TextureIndex < m_TextureHashes.size( ); ++TextureIndex )
		{
			p_Hashes.push_back( m_TextureHashes[ TextureIndex ] );
		}

		return KIL_OK;
	}

	KIL_MEMSIZE Material::GetTextureCount( ) const
	{
		return m_TextureCount;
	}
}

