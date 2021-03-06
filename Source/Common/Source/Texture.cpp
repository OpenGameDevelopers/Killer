#include <Texture.hpp>
#include <iostream>
#include <cstring>
#include <GLES2/gl2ext.h>
#include <FNV.hpp>

namespace Killer
{
	Texture::Texture( ) :
		m_Width( 0 ),
		m_Height( 0 ),
		m_TextureID( 0 ),
		m_TextureUnit( 0 ),
		m_Hash( FNV32_OFFSET )
	{
	}

	Texture::~Texture( )
	{
	}

	KIL_UINT32 Texture::Load( const std::string &p_FileName )
	{
		if( p_FileName.size( ) == 0 )
		{
			return KIL_FAIL;
		}

		FILE *pFile = fopen( p_FileName.c_str( ), "rb" );

		if( pFile == KIL_NULL )
		{
			std::cout << "[Killer::Texture::Load] <ERROR> "
				"Failed to open texture: \"" << p_FileName << "\"" <<
				std::endl;

			return KIL_FAIL;
		}

		struct TARGA_HEADER TargaHeader;

		fread( &TargaHeader, sizeof( TargaHeader ), 1, pFile );

		fseek( pFile, TargaHeader.IDLength, SEEK_SET );

		KIL_MEMSIZE ExpectedImageSize = TargaHeader.Width *
			TargaHeader.Height * ( TargaHeader.BitsPerPixel / 8 );

		KIL_BYTE *pImageData = new KIL_BYTE[ ExpectedImageSize ];

		fread( pImageData, 1, ExpectedImageSize, pFile );

		fclose( pFile );
		pFile = KIL_NULL;

		GLenum Format, Type;

		switch( TargaHeader.BitsPerPixel )
		{
			case 16:
			{
				Format = GL_RGBA;
				Type = GL_UNSIGNED_SHORT_5_5_5_1;
				break;
			}
			case 24:
			{
				Format = GL_RGB;
				Type = GL_UNSIGNED_BYTE;
				break;
			}
			case 32:
			{
				Format = GL_RGBA;
				Type = GL_UNSIGNED_BYTE;
				for( KIL_MEMSIZE i = 0;
					i < ( TargaHeader.Width * TargaHeader.Height ); ++i )
				{
					char ColourBuffer[ 4 ];
					memcpy( ColourBuffer, &pImageData[ i * 4 ], 4 );
					// R
					pImageData[ i * 4 ] = ColourBuffer[ 2 ];
					// G
					pImageData[ ( i * 4 ) + 1 ] = ColourBuffer[ 3 ];
					// B
					pImageData[ ( i * 4 ) + 2 ] = ColourBuffer[ 0 ];
					// A
					pImageData[ ( i * 4 ) + 3 ] = ColourBuffer[ 1 ];
				}
				break;
			}
			default:
			{
				std::cout << "[Killer::Texture::Load] <ERROR> "
					"Failed to get the correct bits per pixel, got: " <<
					TargaHeader.BitsPerPixel << std::endl;
				delete [ ] pImageData;
				return KIL_FAIL;
			}
		}

		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

		glGenTextures( 1, &m_TextureID );
		GLenum Error;
		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, m_TextureID );

		glTexImage2D( GL_TEXTURE_2D, 0, Format, TargaHeader.Width,
			TargaHeader.Height, 0, Format, Type, pImageData );

		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		delete [ ] pImageData;

		m_Hash = HashStringFNV1a( p_FileName.c_str( ) );

		return KIL_OK;
	}

	KIL_UINT32 Texture::Activate( )
	{
		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, m_TextureID );

		return KIL_OK;
	}

	KIL_UINT32 Texture::GetWidth( ) const
	{
		return m_Width;
	}

	KIL_UINT32 Texture::GetHeight( ) const
	{
		return m_Height;
	}

	KIL_UINT32 Texture::GetHash( ) const
	{
		return m_Hash;
	}
}

