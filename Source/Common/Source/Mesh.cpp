#include <Mesh.hpp>
#include <MaterialManager.hpp>
#include <Matrix4x4.hpp>

namespace Killer
{
	Mesh::Mesh( MaterialManager *p_pMaterialManager ) :
		m_pMaterialManager( p_pMaterialManager )
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
		KIL_FLOAT32 IdentityMatrix[ 16 ] = 
		{	1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f };

		Matrix4x4 Translation, RotationX, RotationY, RotationZ, Scale;

		//m_pMaterialManager->Apply( m_MaterialHash );

		for( KIL_MEMSIZE Primitive = 0; Primitive < m_Primitives.size( );
			++Primitive )
		{
			m_Primitives[ Primitive ]->Render( );
		}

		return KIL_OK;
	}

	KIL_UINT32 Mesh::SetMaterial( const KIL_UINT32 p_MaterialHash )
	{
		m_MaterialHash = p_MaterialHash;

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

	void Mesh::ToggleWireframe( )
	{
		for( KIL_MEMSIZE Primitive = 0; Primitive < m_Primitives.size( );
			++Primitive )
		{
			m_Primitives[ Primitive ]->ToggleWireframe( );
		}
	}
}

