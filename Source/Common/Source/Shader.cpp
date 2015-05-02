#include <Shader.hpp>
#include <iostream>
#include <cstring>

namespace Killer
{
	Shader::Shader( ) :
		m_Program( 0 ),
		m_VertexShader( 0 ),
		m_FragmentShader( 0 ),
		m_Linked( KIL_FALSE )
	{
	}

	Shader::~Shader( )
	{
	}

	KIL_UINT32 Shader::AddShaderSource( const SHADER_TYPE p_Type,
		const char *p_pSource )
	{
		std::string ShaderTypeName;
		GLenum ShaderTypeGL;
		GLuint *pShader;

		switch( p_Type )
		{
			case SHADER_TYPE_VERTEX:
			{
				ShaderTypeName = "vertex";
				ShaderTypeGL = GL_VERTEX_SHADER;
				pShader = &m_VertexShader;

				break;
			}
			case SHADER_TYPE_FRAGMENT:
			{
				ShaderTypeName = "fragment";
				ShaderTypeGL = GL_FRAGMENT_SHADER;
				pShader = &m_FragmentShader;

				break;
			}
		}

		( *pShader ) = glCreateShader( ShaderTypeGL );

		glShaderSource( ( *pShader ), 1, &p_pSource, KIL_NULL );

		glCompileShader( ( *pShader ) );

		GLint Compile;
		glGetShaderiv( ( *pShader ), GL_COMPILE_STATUS, &Compile );

		if( Compile == GL_FALSE )
		{
			GLint LogLength;
			glGetShaderiv( ( *pShader ), GL_INFO_LOG_LENGTH, &LogLength );

			if( LogLength > 1 )
			{
				char *pLog = new char[ LogLength ];
				glGetShaderInfoLog( ( *pShader ), LogLength, KIL_NULL, pLog );
				std::cout << "[Killer::Shader::AddShaderSource] <ERROR> "
					"Failed to compile " << ShaderTypeName << " shader:" <<
					std::endl << pLog << std::endl;
				delete [ ] pLog;
			}

			glDeleteShader( ( *pShader ) );

			return KIL_FAIL;
		}

		// Some more processing is required to extract the attributes and
		// manually set their locations in the shader
		if( p_Type == SHADER_TYPE_VERTEX )
		{
			this->ExtractAttributesFromSource( p_pSource );
		}

		return KIL_OK;
	}

	KIL_UINT32 Shader::SetConstantData( const KIL_MEMSIZE p_Index,
		void *p_pData )
	{
		if( m_Linked == KIL_FALSE )
		{
			this->Activate( );
		}
		
		if( p_Index > m_ShaderConstants.size( ) ) 
		{
			return KIL_FAIL;
		}

		SHADER_CONSTANT Constant = m_ShaderConstants[ p_Index ];

		switch( Constant.Type )
		{
			case CONSTANT_TYPE_FLOAT1:
			{
				glUniform1fv( Constant.Location, Constant.ArraySize,
					static_cast< const GLfloat * >( p_pData ) );
				break;
			}
			case CONSTANT_TYPE_FLOAT2:
			{
				glUniform2fv( Constant.Location, Constant.ArraySize,
					static_cast< const GLfloat * >( p_pData ) );
				break;
			}
			case CONSTANT_TYPE_FLOAT3:
			{
				glUniform3fv( Constant.Location, Constant.ArraySize,
					static_cast< const GLfloat * >( p_pData ) );
				break;
			}
			case CONSTANT_TYPE_FLOAT4:
			{
				glUniform4fv( Constant.Location, Constant.ArraySize,
					static_cast< const GLfloat * >( p_pData ) );
				break;
			}
			case CONSTANT_TYPE_INT1:
			case CONSTANT_TYPE_BOOL1:
			{
				glUniform1iv( Constant.Location, Constant.ArraySize,
					static_cast< const GLint * >( p_pData ) );
				break;
			}
			case CONSTANT_TYPE_INT2:
			case CONSTANT_TYPE_BOOL2:
			{
				glUniform2iv( Constant.Location, Constant.ArraySize,
					static_cast< const GLint * >( p_pData ) );
				break;
			}
			case CONSTANT_TYPE_INT3:
			case CONSTANT_TYPE_BOOL3:
			{
				glUniform3iv( Constant.Location, Constant.ArraySize,
					static_cast< const GLint * >( p_pData ) );
				break;
			}
			case CONSTANT_TYPE_INT4:
			case CONSTANT_TYPE_BOOL4:
			{
				glUniform4iv( Constant.Location, Constant.ArraySize,
					static_cast< const GLint * >( p_pData ) );
				break;
			}
			case CONSTANT_TYPE_MAT2X2:
			{
				glUniformMatrix2fv( Constant.Location, Constant.ArraySize,
					GL_FALSE, static_cast< GLfloat * >( p_pData ) );
				break;
			}
			case CONSTANT_TYPE_MAT3X3:
			{
				glUniformMatrix3fv( Constant.Location, Constant.ArraySize,
					GL_FALSE, static_cast< GLfloat * >( p_pData ) );
				break;
			}
			case CONSTANT_TYPE_MAT4X4:
			{
				glUniformMatrix4fv( Constant.Location, Constant.ArraySize,
					GL_FALSE, static_cast< GLfloat * >( p_pData ) );
				break;
			}
		}

		return KIL_OK;
	}

	KIL_UINT32 Shader::SetConstantData( const char *p_pName, void *p_pData )
	{
		if( m_Linked == KIL_FALSE )
		{
			this->Activate( );
		}

		auto Constant = m_ShaderConstants.begin( );
		KIL_MEMSIZE StringLength = strlen( p_pName );

		while( Constant != m_ShaderConstants.end( ) )
		{
			if( ( *Constant ).Name.compare( 0, StringLength, p_pName ) == 0 )
			{
				break;
			}
			++Constant;
		}

		switch( ( *Constant ).Type )
		{
			case CONSTANT_TYPE_FLOAT1:
			{
				glUniform1fv( ( *Constant ).Location, ( *Constant ).ArraySize,
					static_cast< const GLfloat * >( p_pData ) );
				break;
			}
			case CONSTANT_TYPE_FLOAT2:
			{
				glUniform2fv( ( *Constant ).Location, ( *Constant ).ArraySize,
					static_cast< const GLfloat * >( p_pData ) );
				break;
			}
			case CONSTANT_TYPE_FLOAT3:
			{
				glUniform3fv( ( *Constant ).Location, ( *Constant ).ArraySize,
					static_cast< const GLfloat * >( p_pData ) );
				break;
			}
			case CONSTANT_TYPE_FLOAT4:
			{
				glUniform4fv( ( *Constant ).Location, ( *Constant ).ArraySize,
					static_cast< const GLfloat * >( p_pData ) );
				break;
			}
			case CONSTANT_TYPE_INT1:
			case CONSTANT_TYPE_BOOL1:
			{
				glUniform1iv( ( *Constant ).Location, ( *Constant ).ArraySize,
					static_cast< const GLint * >( p_pData ) );
				break;
			}
			case CONSTANT_TYPE_INT2:
			case CONSTANT_TYPE_BOOL2:
			{
				glUniform2iv( ( *Constant ).Location, ( *Constant ).ArraySize,
					static_cast< const GLint * >( p_pData ) );
				break;
			}
			case CONSTANT_TYPE_INT3:
			case CONSTANT_TYPE_BOOL3:
			{
				glUniform3iv( ( *Constant ).Location, ( *Constant ).ArraySize,
					static_cast< const GLint * >( p_pData ) );
				break;
			}
			case CONSTANT_TYPE_INT4:
			case CONSTANT_TYPE_BOOL4:
			{
				glUniform4iv( ( *Constant ).Location, ( *Constant ).ArraySize,
					static_cast< const GLint * >( p_pData ) );
				break;
			}
			case CONSTANT_TYPE_MAT2X2:
			{
				glUniformMatrix2fv( ( *Constant ).Location,
					( *Constant ).ArraySize, GL_FALSE,
					static_cast< GLfloat * >( p_pData ) );
				break;
			}
			case CONSTANT_TYPE_MAT3X3:
			{
				glUniformMatrix3fv( ( *Constant ).Location,
					( *Constant ).ArraySize, GL_FALSE,
					static_cast< GLfloat * >( p_pData ) );
				break;
			}
			case CONSTANT_TYPE_MAT4X4:
			{
				glUniformMatrix4fv( ( *Constant ).Location,
					( *Constant ).ArraySize, GL_FALSE,
					static_cast< GLfloat * >( p_pData ) );
				break;
			}
		}

		return KIL_OK;
	}

	KIL_UINT32 Shader::GetConstantIndex( const char *p_pName,
		KIL_MEMSIZE &p_Index ) 
	{
		if( m_Linked == KIL_FALSE )
		{
			this->Activate( );
		}

		auto Constant = m_ShaderConstants.begin( );
		KIL_MEMSIZE StringLength = strlen( p_pName );

		while( Constant != m_ShaderConstants.end( ) )
		{
			if( ( *Constant ).Name.compare( 0, StringLength, p_pName ) == 0 )
			{
				break;
			}
			++Constant;
		}

		p_Index = ( *Constant ).Location;

		return KIL_OK;
	}

	KIL_MEMSIZE Shader::GetConstantCount( ) const
	{
		return m_ShaderConstants.size( );
	}

	KIL_UINT32 Shader::GetConstant( const KIL_MEMSIZE p_Index,
		SHADER_CONSTANT *p_pConstant )
	{
		if( p_Index > m_ShaderConstants.size( ) )
		{
			return KIL_FAIL;
		}

		( *p_pConstant ) = m_ShaderConstants[ p_Index ];

		return KIL_OK;
	}

	KIL_UINT32 Shader::Activate( )
	{
		if( m_Linked == KIL_FALSE )
		{
			if( this->Link( ) != KIL_OK )
			{
				return KIL_FAIL;
			}

			if( this->GetAttributes( ) != KIL_OK )
			{
				return KIL_FAIL;
			}

			if( this->GetConstants( ) != KIL_OK )
			{
				return KIL_FAIL;
			}

			m_Linked = KIL_TRUE;
		}

		glUseProgram( m_Program );

		return KIL_OK;
	}

	KIL_UINT32 Shader::Link( )
	{
		if( glIsProgram( m_Program ) )
		{
			glDeleteProgram( m_Program );
		}

		m_Program = glCreateProgram( );

		glAttachShader( m_Program, m_VertexShader );
		glAttachShader( m_Program, m_FragmentShader );

		// Link

		glLinkProgram( m_Program );

		for( KIL_MEMSIZE Attribute = 0;
			Attribute < m_ShaderAttributesExplicit.size( ); ++Attribute )
		{
			glBindAttribLocation( m_Program,
				m_ShaderAttributesExplicit[ Attribute ].Location,
				m_ShaderAttributesExplicit[ Attribute ].Name.c_str( ) );
		}

		// Re-link to apply the changes from glBindAttribLocation in
		// GetAttributes
		glLinkProgram( m_Program );

		GLint Linked;
		glGetProgramiv( m_Program, GL_LINK_STATUS, &Linked );

		if( Linked == GL_FALSE )
		{
			GLint LogLength;

			glGetProgramiv( m_Program, GL_INFO_LOG_LENGTH, &LogLength );

			if( LogLength > 1 )
			{
				char *pLog = new char[ LogLength ];

				glGetProgramInfoLog( m_Program, LogLength, KIL_NULL,
					pLog );
				std::cout << "[Killer::Shader::Link] <ERROR> "
					"Failed to link shader:" << std::endl << pLog <<
					std::endl;
					
				delete [ ] pLog;
			}

			glDeleteProgram( m_Program );

			return KIL_FAIL;

		}

		// Validate

		glValidateProgram( m_Program );

		GLint Validated;
		glGetProgramiv( m_Program, GL_VALIDATE_STATUS, &Validated );

		if( Validated == GL_FALSE )
		{
			GLint LogLength;

			glGetProgramiv( m_Program, GL_INFO_LOG_LENGTH, &LogLength );

			if( LogLength > 1 )
			{
				char *pLog = new char[ LogLength ];

				glGetProgramInfoLog( m_Program, LogLength, KIL_NULL,
					pLog );
				std::cout << "[Killer::Shader::Link] <ERROR> "
					"Shader did not pass validation:" << std::endl <<
					pLog << std::endl;

				delete [ ] pLog;
			}
		}

		return KIL_OK;
	}

	KIL_UINT32 Shader::GetConstants( )
	{
		GLint Constants, ConstantLength;
		glGetProgramiv( m_Program, GL_ACTIVE_UNIFORMS, &Constants );
		glGetProgramiv( m_Program, GL_ACTIVE_UNIFORM_MAX_LENGTH,
			&ConstantLength );

		m_ShaderConstants.clear( );

		for( GLint Constant = 0; Constant < Constants; ++Constant )
		{
			SHADER_CONSTANT ShaderConstant;
			GLenum ConstantType;
			char *pConstantName = new char[ ConstantLength ];

			glGetActiveUniform( m_Program, Constant, ConstantLength,
				KIL_NULL, &ShaderConstant.ArraySize, &ConstantType,
				pConstantName );

			ShaderConstant.Name = pConstantName;

			delete [ ] pConstantName;

			switch( ConstantType )
			{
				case GL_FLOAT:
				{
					ShaderConstant.Type = CONSTANT_TYPE_FLOAT1;
					break;
				}
				case GL_FLOAT_VEC2:
				{
					ShaderConstant.Type = CONSTANT_TYPE_FLOAT2;
					break;
				}
				case GL_FLOAT_VEC3:
				{
					ShaderConstant.Type = CONSTANT_TYPE_FLOAT3;
					break;
				}
				case GL_FLOAT_VEC4:
				{
					ShaderConstant.Type = CONSTANT_TYPE_FLOAT4;
					break;
				}
				case GL_INT:
				{
					ShaderConstant.Type = CONSTANT_TYPE_INT1;
					break;
				}
				case GL_INT_VEC2:
				{
					ShaderConstant.Type = CONSTANT_TYPE_INT2;
					break;
				}
				case GL_INT_VEC3:
				{
					ShaderConstant.Type = CONSTANT_TYPE_INT3;
					break;
				}
				case GL_INT_VEC4:
				{
					ShaderConstant.Type = CONSTANT_TYPE_INT4;
					break;
				}
				case GL_BOOL:
				{
					ShaderConstant.Type = CONSTANT_TYPE_BOOL1;
					break;
				}
				case GL_BOOL_VEC2:
				{
					ShaderConstant.Type = CONSTANT_TYPE_BOOL2;
					break;
				}
				case GL_BOOL_VEC3:
				{
					ShaderConstant.Type = CONSTANT_TYPE_BOOL3;
					break;
				}
				case GL_BOOL_VEC4:
				{
					ShaderConstant.Type = CONSTANT_TYPE_BOOL4;
					break;
				}
				case GL_FLOAT_MAT2:
				{
					ShaderConstant.Type = CONSTANT_TYPE_MAT2X2;
					break;
				}
				case GL_FLOAT_MAT3:
				{
					ShaderConstant.Type = CONSTANT_TYPE_MAT3X3;
					break;
				}
				case GL_FLOAT_MAT4:
				{
					ShaderConstant.Type = CONSTANT_TYPE_MAT4X4;
					break;
				}
				case GL_SAMPLER_2D:
				{
					ShaderConstant.Type = CONSTANT_TYPE_SAMPLER_2D;
					break;
				}
				case GL_SAMPLER_CUBE:
				{
					ShaderConstant.Type = CONSTANT_TYPE_SAMPLER_CUBE;
					break;
				}
			}

			ShaderConstant.Location = glGetUniformLocation( m_Program,
				ShaderConstant.Name.c_str( ) );

			m_ShaderConstants.push_back( ShaderConstant );
		}

		return KIL_OK;
	}

	KIL_UINT32 Shader::GetAttributes( )
	{
		GLint Attributes, AttributeLength;

		glGetProgramiv( m_Program, GL_ACTIVE_ATTRIBUTES, &Attributes );
		glGetProgramiv( m_Program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
			&AttributeLength );

		m_ShaderAttributes.clear( );

		for( GLint Attribute = 0; Attribute < Attributes; ++Attribute )
		{
			SHADER_ATTRIBUTE ShaderAttribute;
			GLenum AttributeType;
			char *pAttributeName = new char [ AttributeLength ];

			glGetActiveAttrib( m_Program, Attribute, AttributeLength,
				KIL_NULL, &ShaderAttribute.ArraySize, &AttributeType,
				pAttributeName );

			ShaderAttribute.Name = pAttributeName;

			ShaderAttribute.Location = glGetAttribLocation( m_Program,
				pAttributeName );

			delete [ ] pAttributeName;

			switch( AttributeType )
			{
				case GL_FLOAT:
				{
					ShaderAttribute.Type = VERTEXATTRIBUTE_TYPE_FLOAT1;
					break;
				}
				case GL_FLOAT_VEC2:
				{
					ShaderAttribute.Type = VERTEXATTRIBUTE_TYPE_FLOAT2;
					break;
				}
				case GL_FLOAT_VEC3:
				{
					ShaderAttribute.Type = VERTEXATTRIBUTE_TYPE_FLOAT3;
					break;
				}
				case GL_FLOAT_VEC4:
				{
					ShaderAttribute.Type = VERTEXATTRIBUTE_TYPE_FLOAT4;
					break;
				}
				case GL_FLOAT_MAT2:
				{
					ShaderAttribute.Type = VERTEXATTRIBUTE_TYPE_MAT2X2;
					break;
				}
				case GL_FLOAT_MAT3:
				{
					ShaderAttribute.Type = VERTEXATTRIBUTE_TYPE_MAT3X3;
					break;
				}
				case GL_FLOAT_MAT4:
				{
					ShaderAttribute.Type = VERTEXATTRIBUTE_TYPE_MAT4X4;
					break;
				}
			}

			m_ShaderAttributes.push_back( ShaderAttribute );
		}

		return KIL_OK;
	}

	KIL_UINT32 Shader::ExtractAttributesFromSource(
		const std::string &p_Shader )
	{
		KIL_MEMSIZE AttributePosition = p_Shader.find( "attribute" );

		GLint AttributeLocation = 0;

		m_ShaderAttributesExplicit.clear( );

		while( AttributePosition != std::string::npos )
		{
			KIL_MEMSIZE DelimiterPosition = p_Shader.find_first_of( ",;",
				AttributePosition );

			if( DelimiterPosition == std::string::npos )
			{
				std::cout << "[Killer::Shader::ExtractAttributesFromsource] "
					"<ERROR> Could not find a delimiter following the "
					"attribute" << std::endl;

				return KIL_FAIL;
			}

			// Skip over the type
			KIL_MEMSIZE NameStart = p_Shader.find_first_of( " \t",
				AttributePosition );
			NameStart = p_Shader.find_first_not_of( " \t", NameStart );
			NameStart = p_Shader.find_first_of( " \t", NameStart );
			NameStart = p_Shader.find_first_not_of( " \t", NameStart );

			KIL_MEMSIZE NameEnd = p_Shader.find_first_of( " ,[;\t",
				NameStart );

			KIL_MEMSIZE EndOfLine = p_Shader.find_first_of( ';',
				NameStart );

			KIL_BOOL DoneProcessing = KIL_FALSE;

			do
			{
				std::string AttributeName = p_Shader.substr( NameStart,
					NameEnd - NameStart );
				
				SHADER_ATTRIBUTE Attribute;
				Attribute.Name = AttributeName;
				Attribute.Location = AttributeLocation;

				std::cout << "Setting attribute \"" << AttributeName << "\" "
					"to location " << AttributeLocation << std::endl;

				m_ShaderAttributesExplicit.push_back( Attribute );

				DoneProcessing = KIL_TRUE;
				++AttributeLocation;
			}while( DoneProcessing = KIL_FALSE );

			AttributePosition = p_Shader.find( "attribute",
				DelimiterPosition );
		}

		return KIL_OK;
	}
}

