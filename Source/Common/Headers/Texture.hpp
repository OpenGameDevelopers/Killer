#ifndef __KILLER_TEXTURE_HPP__
#define __KILLER_TEXTURE_HPP__

#include <DataTypes.hpp>
#include <GLES2/gl2.h>
#include <string>

namespace Killer
{
#pragma pack( 1 )
	struct TARGA_HEADER
	{
		KIL_BYTE	IDLength;
		KIL_BYTE	ColourmapType;
		KIL_BYTE	ImageType;
		KIL_BYTE	ColourmapSpecifiaction[ 5 ];
		KIL_UINT16	X;
		KIL_UINT16	Y;
		KIL_UINT16	Width;
		KIL_UINT16	Height;
		KIL_BYTE	BitsPerPixel;
		KIL_BYTE	ImageDescription;
	};
#pragma pack( )

	class Texture
	{
	public:
		Texture( );
		~Texture( );

		KIL_UINT32 Load( const std::string &p_FileName );

		KIL_UINT32 Activate( );

		KIL_UINT32 SetTextureUnit( const KIL_UINT32 p_TextureUnit );

		KIL_UINT32 GetWidth( ) const;
		KIL_UINT32 GetHeight( ) const;

		KIL_UINT32 GetHash( ) const;

	private:
		Texture( const Texture &p_Other );
		Texture &operator=( const Texture &p_Other );

		KIL_UINT32	m_Width;
		KIL_UINT32	m_Height;
		GLuint		m_TextureID;
		GLenum		m_TextureUnit;
		GLenum		m_TextureType;

		KIL_UINT32	m_Hash;
	};
}

#endif // __KILLER_TEXTURE_HPP__

