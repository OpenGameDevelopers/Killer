#include <Mesh.hpp>
#include <MaterialManager.hpp>
#include <Matrix4x4.hpp>
#include <FNV.hpp>
#include <Camera.hpp>
#include <iostream>

namespace Killer
{
	Mesh::Mesh( MaterialManager *p_pMaterialManager ) :
		m_DrawNormals( KIL_FALSE ),
		m_DrawWireframe( KIL_FALSE ),
		m_pMaterialManager( p_pMaterialManager )
	{
		m_PositionSolidColourMaterial =
			HashStringFNV1a( "Test/Materials/PositionSolidColour.material" );

		m_MaterialHash =
			HashStringFNV1a( "Test/Materials/Test.material" );
	}

	Mesh::~Mesh( )
	{
	}

	KIL_UINT32 Mesh::AddPrimitive( RendererPrimitive *p_pPrimitive )
	{
		m_Primitives.push_back( p_pPrimitive );

		return KIL_OK;
	}

	KIL_UINT32 Mesh::Render( Camera &p_Camera )
	{
		KIL_FLOAT32 WorldRaw[ 16 ];
		KIL_FLOAT32 ViewRaw[ 16 ];
		KIL_FLOAT32 ProjectionRaw[ 16 ];

		Matrix4x4 World, View, Projection;

		p_Camera.GetViewMatrix( View );
		p_Camera.GetProjectionMatrix( Projection );

		World = m_ScaleMatrix * ( m_RotationZ * m_RotationY * m_RotationX ) *
			m_Translation;

		World.AsFloat( WorldRaw );
		View.AsFloat( ViewRaw );
		Projection.AsFloat( ProjectionRaw );

		if( m_DrawWireframe )
		{
			KIL_FLOAT32 WireframeColour [ 4 ] = { 0.0f, 1.0f, 0.0f, 1.0f };

			m_pMaterialManager->Apply( m_PositionSolidColourMaterial );

			m_pMaterialManager->SetShaderConstant(
				m_PositionSolidColourMaterial, "Colour", WireframeColour );

			m_pMaterialManager->SetShaderConstant(
				m_PositionSolidColourMaterial, "World", WorldRaw );
			m_pMaterialManager->SetShaderConstant(
				m_PositionSolidColourMaterial, "View", ViewRaw );
			m_pMaterialManager->SetShaderConstant(
				m_PositionSolidColourMaterial, "Projection", ProjectionRaw );

			for( KIL_MEMSIZE Primitive = 0; Primitive < m_Primitives.size( );
				++Primitive )
			{
				m_Primitives[ Primitive ]->RenderWireframe( );
			}
		}
		else
		{
			KIL_FLOAT32 EyePositionRaw[ 3 ] = { 0.0f, 0.0f, 100.0f };
			KIL_SINT32 Zero = 0;
			KIL_FLOAT32 One = 1.0f;

			m_pMaterialManager->Apply( m_MaterialHash );

			m_pMaterialManager->SetShaderConstant( m_MaterialHash, "World",
				WorldRaw );
			m_pMaterialManager->SetShaderConstant( m_MaterialHash, "View",
				ViewRaw );
			m_pMaterialManager->SetShaderConstant( m_MaterialHash,
				"Projection", ProjectionRaw );

			m_pMaterialManager->SetShaderConstant( m_MaterialHash,
				"EyePosition", EyePositionRaw );

			m_pMaterialManager->SetShaderConstant( m_MaterialHash, "Texture",
				&Zero );
			m_pMaterialManager->SetShaderConstant( m_MaterialHash, "Shininess",
				&One );

			for( KIL_MEMSIZE Primitive = 0; Primitive < m_Primitives.size( );
				++Primitive )
			{
				m_Primitives[ Primitive ]->Render( );
			}
		}

		if( m_DrawNormals )
		{
			m_pMaterialManager->Apply( m_PositionSolidColourMaterial );

			KIL_FLOAT32 NormalsColour [ 4 ] = { 1.0f, 1.0f, 0.0f, 1.0f };

			m_pMaterialManager->SetShaderConstant(
				m_PositionSolidColourMaterial, "Colour", NormalsColour );

			m_pMaterialManager->SetShaderConstant(
				m_PositionSolidColourMaterial, "World", WorldRaw );
			m_pMaterialManager->SetShaderConstant(
				m_PositionSolidColourMaterial, "View", ViewRaw );
			m_pMaterialManager->SetShaderConstant(
				m_PositionSolidColourMaterial, "Projection", ProjectionRaw );

			for( KIL_MEMSIZE Primitive = 0; Primitive < m_Primitives.size( );
				++Primitive )
			{
				m_Primitives[ Primitive ]->RenderNormals( );
			}
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

		m_Translation.Translate( p_Position );

		return KIL_OK;
	}

	KIL_UINT32 Mesh::SetOrientation( const Vector3 &p_Orientation )
	{
		m_Orientation = p_Orientation;

		m_RotationX.RotateX( p_Orientation.GetX( ) );
		m_RotationY.RotateY( p_Orientation.GetY( ) );
		//m_RotationZ.RotateZ( p_Orientation.GetZ( ) );

		return KIL_OK;
	}

	KIL_UINT32 Mesh::SetScale( const Vector3 &p_Scale )
	{
		m_Scale = p_Scale;

		//m_ScaleMatrix.Scale( p_Scale );

		return KIL_OK;
	}

	void Mesh::ToggleWireframe( )
	{
		m_DrawWireframe = !m_DrawWireframe;
	}

	void Mesh::ShowNormals( )
	{
		m_DrawNormals = KIL_TRUE;
	}

	void Mesh::HideNormals( )
	{
		m_DrawNormals = KIL_FALSE;
	}
}

