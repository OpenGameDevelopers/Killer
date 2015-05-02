#include <Mesh.hpp>

namespace Killer
{
	Mesh::Mesh( )
	{
	}

	Mesh::~Mesh( )
	{
	}

	KIL_UINT32 Mesh::AddPrimitive( RendererPrimitive *p_pPrimitive )
	{
		m_Primitives.push_back( p_pPrimitive );

		return KIL_OK;
	}

	KIL_UINT32 Mesh::Render( )
	{
		m_pShader->Activate( );

		KIL_FLOAT32 IdentityMatrix[ 16 ] = 
		{	1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f };

		m_pShader->SetConstantData( "WorldMatrix", IdentityMatrix );

		for( KIL_MEMSIZE Primitive = 0; Primitive < m_Primitives.size( );
			++Primitive )
		{
			m_Primitives[ Primitive ]->Render( );
		}

		return KIL_OK;
	}

	KIL_UINT32 Mesh::SetShader( Shader *p_pShader )
	{
		m_pShader = p_pShader;

		return KIL_OK;
	}

	KIL_UINT32 Mesh::SetPosition( const Vector3 &p_Position )
	{
		m_Position = p_Position;

		return KIL_OK;
	}

	KIL_UINT32 Mesh::SetOrientation( const Vector3 &p_Orientation )
	{
		m_Orientation = p_Orientation;

		return KIL_OK;
	}

	KIL_UINT32 Mesh::SetScale( const Vector3 &p_Scale )
	{
		m_Scale = p_Scale;

		return KIL_OK;
	}
}

