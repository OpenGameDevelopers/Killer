#include <Model.hpp>
#include <Chunk.hpp>
#include <FNV.hpp>
#include <MaterialManager.hpp>
#include <Memory.hpp>
#include <Mesh.hpp>
#include <RendererPrimitive.hpp>
#include <VertexAttributes.hpp>
#include <Camera.hpp>
#include <iostream>
#include <iomanip>

namespace Killer
{
	Model::Model( MaterialManager *p_pMaterialManager ) :
		m_pMaterialManager( p_pMaterialManager )
	{
	}

	Model::~Model( )
	{
	}

	KIL_UINT32 Model::Load( const std::string &p_FileName )
	{
		FILE *pFile = fopen( p_FileName.c_str( ), "rb" );

		if( pFile == KIL_NULL )
		{
			std::cout << "[Killer::Model::Load] <ERROR> "
				"Could not open \"" << p_FileName << "\"" << std::endl;

			return KIL_FAIL;
		}

		struct MODEL_HEADER ModelHeader;

		if( fread( &ModelHeader, sizeof( ModelHeader ), 1, pFile ) != 1 )
		{
			std::cout << "[Killer::Model::Load] <ERROR> "
				"Failed to read model header" << std::endl;

			return KIL_FAIL;
		}

		struct CHUNK Chunk;
		
		do
		{
			if( ReadChunk( Chunk, pFile ) != KIL_OK )
			{
				std::cout << "[Killer::Model::Load] <ERROR> "
					"Could not load chunk" << std::endl;

				return KIL_FAIL;
			}
			
			switch( Chunk.Type )
			{
				case CHUNK_MESH:
				{
					if( this->ReadMeshData( pFile ) != KIL_OK )
					{
						std::cout << "[Killer::Model::Load] <ERROR> "
							"Failed to load mesh data" << std::endl;

						return KIL_FAIL;
					}
					break;
				}
				case CHUNK_END:
				{
					break;
				}
				default:
				{
					std::cout << "[Killer::Model::Load] <WARN> "
						"Unknown chunk type, reading past it" << std::endl;

					std::cout << "Chunk type: " << std::hex << Chunk.Type <<
						std::dec << std::endl;
					std::cout << "Chunk size: " << Chunk.Size << std::endl;

					fseek( pFile, Chunk.Size, SEEK_CUR );

					if( ReadChunk( Chunk, pFile ) != KIL_OK )
					{
						std::cout << "[Killer::Model::Load] <ERROR> "
							"Could not load chunk" << std::endl;

						return KIL_FAIL;
					}

					if( ( Chunk.Type != CHUNK_END ) && ( Chunk.Size != 0 ) )
					{
						std::cout << "[Killer::Model::Load] <ERROR> "
							"Unexpected chunk, was expecting end chunk" <<
							std::endl;

						return KIL_FAIL;
					}
				}
			}
		} while( Chunk.Type != CHUNK_END );


		fclose( pFile );

		return KIL_OK;
	}

	KIL_UINT32 Model::Render( Camera &p_Camera )
	{
		for( KIL_MEMSIZE Mesh = 0; Mesh < m_Meshes.size( ); ++Mesh )
		{
			m_Meshes[ Mesh ]->Render( p_Camera );
		}

		return KIL_OK;
	}

	KIL_UINT32 Model::SetPosition( const Vector3 &p_Position )
	{
		for( KIL_MEMSIZE Mesh = 0; Mesh < m_Meshes.size( ); ++Mesh )
		{
			m_Meshes[ Mesh ]->SetPosition( p_Position );
		}

		return KIL_OK;
	}

	KIL_UINT32 Model::SetScale( const Vector3 &p_Scale )
	{
		for( KIL_MEMSIZE Mesh = 0; Mesh < m_Meshes.size( ); ++Mesh )
		{
			m_Meshes[ Mesh ]->SetScale( p_Scale );
		}

		return KIL_OK;
	}

	KIL_UINT32 Model::SetOrientation( const Vector3 &p_Orientation )
	{
		for( KIL_MEMSIZE Mesh = 0; Mesh < m_Meshes.size( ); ++Mesh )
		{
			m_Meshes[ Mesh ]->SetOrientation( p_Orientation );
		}

		return KIL_OK;
	}

	void Model::ToggleWireframe( )
	{
		for( KIL_MEMSIZE Mesh = 0; Mesh < m_Meshes.size( ); ++Mesh )
		{
			m_Meshes[ Mesh ]->ToggleWireframe( );
		}
	}

	void Model::ShowNormals( )
	{
		for( KIL_MEMSIZE Mesh = 0; Mesh < m_Meshes.size( ); ++Mesh )
		{
			m_Meshes[ Mesh ]->ShowNormals( );
		}
	}

	void Model::HideNormals( )
	{
		for( KIL_MEMSIZE Mesh = 0; Mesh < m_Meshes.size( ); ++Mesh )
		{
			m_Meshes[ Mesh ]->HideNormals( );
		}
	}

	KIL_UINT32 Model::ReadMeshData( FILE *p_pFile )
	{
		struct MODEL_MESH ModelMesh;

		fread( &ModelMesh, sizeof( ModelMesh ), 1, p_pFile );

		KIL_BYTE *pVertices = new KIL_BYTE[ 32 * ModelMesh.VertexCount ];

		VertexAttributes VertexAttribs( 8 );

		VertexAttribs.AddVertexAttribute( VERTEXATTRIBUTE_TYPE_FLOAT3,
			VERTEXATTRIBUTE_INTENT_POSITION );
		VertexAttribs.AddVertexAttribute( VERTEXATTRIBUTE_TYPE_FLOAT3,
			VERTEXATTRIBUTE_INTENT_NORMAL );
		VertexAttribs.AddVertexAttribute( VERTEXATTRIBUTE_TYPE_FLOAT2,
			VERTEXATTRIBUTE_INTENT_TEXTURE );

		fread( pVertices, VertexAttribs.GetStride( ), ModelMesh.VertexCount,
			p_pFile );

		KIL_UINT16 *pListIndices = new KIL_UINT16[
			ModelMesh.TriangleListCount * 3 ];
		
		fread( pListIndices, sizeof( KIL_UINT16 ), ModelMesh.TriangleListCount,
			p_pFile );

		Mesh *pNewMesh = new Mesh( m_pMaterialManager );

		RendererPrimitive *pListPrimitives = new RendererPrimitive( );

		pListPrimitives->Create( pVertices, pListIndices,
			ModelMesh.VertexCount, ModelMesh.TriangleListCount,
			VertexAttribs, PRIMITIVE_TYPE_TRIANGLE_LIST );

		pNewMesh->AddPrimitive( pListPrimitives );

		KIL_UINT32 MaterialHash = HashStringFNV1a(
			"Test/Materials/Test.material" );
		pNewMesh->SetMaterial( MaterialHash );

		m_Meshes.push_back( pNewMesh );

		SafeDeleteArray< KIL_UINT16 >( pListIndices );
		SafeDeleteArray< KIL_BYTE >( pVertices );

		struct CHUNK EndChunk;

		if( ReadChunk( EndChunk, p_pFile ) != KIL_OK )
		{
			std::cout << "[Killer::Model::ReadMeshData] <ERROR> "
				"Did not find chunk after the mesh data" << std::endl;

			return KIL_FAIL;
		}

		if( ( EndChunk.Type != CHUNK_END ) && ( EndChunk.Size != 0 ) )
		{
			std::cout << "[Killer::Model::ReadMeshData] <ERROR> "
				"Unexpected chunk at end of mesh data" << std::endl;

			return KIL_FAIL;
		}

		return KIL_OK;
	}
}

