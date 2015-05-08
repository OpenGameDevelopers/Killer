#include <Material.hpp>
#include <FNV.hpp>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace Killer
{
	Material::Material( ) :
		m_Hash( FNV32_OFFSET ),
		m_ShaderHash( FNV32_OFFSET )
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

		char *pSource = new char[ FileSize ];

		fread( pSource, 1, FileSize, pFile );

		fclose( pFile );
		pFile = KIL_NULL;

		rapidjson::Document MaterialFile;
		MaterialFile.Parse( pSource );

		delete [ ] pSource;
		pSource = KIL_NULL;

		if( MaterialFile.HasMember( "shader" ) )
		{
			std::cout << "[Killer::Material::CreateFromFile] <INFO> "
				"Found a material shader" << std::endl;

			rapidjson::Value &ShaderRoot = MaterialFile[ "shader" ];

			if( ShaderRoot.HasMember( "source" ) )
			{
				std::cout << "[Killer::Material::CreateFromFile] <INFO> "
					"Found shader source in shader" << std::endl;

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
					if( ShaderSourceRoot[ i ].HasMember( "type" ) )
					{
						std::string ShaderType =
							ShaderSourceRoot[ i ][ "type" ].GetString( );

						if( ShaderType.compare( "vertex" ) == 0 )
						{
							std::cout << "[Killer::Material::CreateFromFile] "
								"<INFO> Found a vertex shader" << std::endl;
						}
						else if( ShaderType.compare( "fragment" ) == 0 )
						{
							std::cout << "[Killer::Material::CreateFromFile] "
								"<INFO> Found a fragment shader" << std::endl;
						}
						else
						{
							std::cout << "[Killer::Material::CreateFromFile] "
								"<ERROR> Unrecognised shader type" <<
								std::endl;

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
					}
					else if( ShaderSourceRoot[ i ].HasMember( "code" ) )
					{
						std::cout << "[Killer::Material::CreateFromFile] "
							"<INFO> Shader is in code form" << std::endl;
					}
					else
					{
						std::cout << "[Killer::Material::CreateFromFile] "
							"<ERROR> Failed to find either a \"path\" or "
							"\"code\" member" << std::endl;

						return KIL_FAIL;
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
								"<INFO> Albedo texture found" << std::endl;
						}
						else
						{
							std::cout << "[Killer::Material::CreateFromFile] "
								"<WARN> Unknown texture" << std::endl;
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

		std::cout << "[Killer::Material::CreateFromFile] <INFO> "
			"Loaded material" << std::endl;

		m_Hash = HashStringFNV1a( p_FileName.c_str( ) );

		return KIL_OK;
	}

	KIL_UINT32 Material::GetHash( ) const
	{
		return m_Hash;
	}
}

