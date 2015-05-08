#ifndef __KILLER_SHADER_HPP__
#define __KILLER_SHADER_HPP__

#include <DataTypes.hpp>
#include <VertexAttributes.hpp>
#include <GLES2/gl2.h>
#include <vector>
#include <string>

namespace Killer
{
	typedef enum
	{
		SHADER_TYPE_VERTEX = 1,
		SHADER_TYPE_FRAGMENT,
		SHADER_TYPE_UNKNOWN
	}SHADER_TYPE;

	typedef enum
	{
		CONSTANT_TYPE_FLOAT1,
		CONSTANT_TYPE_FLOAT2,
		CONSTANT_TYPE_FLOAT3,
		CONSTANT_TYPE_FLOAT4,
		CONSTANT_TYPE_INT1,
		CONSTANT_TYPE_INT2,
		CONSTANT_TYPE_INT3,
		CONSTANT_TYPE_INT4,
		CONSTANT_TYPE_BOOL1,
		CONSTANT_TYPE_BOOL2,
		CONSTANT_TYPE_BOOL3,
		CONSTANT_TYPE_BOOL4,
		CONSTANT_TYPE_MAT2X2,
		CONSTANT_TYPE_MAT3X3,
		CONSTANT_TYPE_MAT4X4,
		CONSTANT_TYPE_SAMPLER_2D,
		CONSTANT_TYPE_SAMPLER_CUBE
	}CONSTANT_TYPE;

	typedef struct __tagSHADER_CONSTANT
	{
		std::string		Name;
		CONSTANT_TYPE	Type;
		GLint			ArraySize;
		GLint			Location;
	}SHADER_CONSTANT;

	typedef struct __tagSHADER_ATTRIBUTE
	{
		std::string				Name;
		VERTEXATTRIBUTE_TYPE	Type;
		GLint					ArraySize;
		GLint					Location;
	}SHADER_ATTRIBUTE;

	class Shader
	{
	public:
		Shader( );
		~Shader( );

		KIL_UINT32 AddShaderSource( const SHADER_TYPE p_Type,
			const char *p_pSource );

		KIL_UINT32 SetConstantData( const KIL_MEMSIZE p_Index, void *p_pData );
		KIL_UINT32 SetConstantData( const char *p_pName, void *p_pData );

		KIL_UINT32 GetConstantIndex( const char *p_pName,
			KIL_MEMSIZE &p_Index );

		KIL_MEMSIZE GetConstantCount( ) const;
		KIL_UINT32 GetConstant( const KIL_MEMSIZE p_Index,
			SHADER_CONSTANT *p_pConstant );

		KIL_UINT32 Activate( );

		KIL_UINT32 GetHash( ) const;

	private:
		KIL_UINT32 Link( );
		KIL_UINT32 GetConstants( );
		KIL_UINT32 GetAttributes( );
		KIL_UINT32 ExtractAttributesFromSource( const std::string &p_Shader );

		GLuint							m_Program;
		GLuint							m_VertexShader;
		GLuint							m_FragmentShader;
		std::vector< SHADER_CONSTANT >	m_ShaderConstants;
		std::vector< SHADER_ATTRIBUTE >	m_ShaderAttributes;
		std::vector< SHADER_ATTRIBUTE >	m_ShaderAttributesExplicit;
		KIL_BOOL						m_Linked;

		KIL_UINT32						m_Hash;
	};
}

#endif // __KILLER_SHADER_HPP__

