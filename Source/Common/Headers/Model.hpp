#ifndef __KILLER_MODEL_HPP__
#define __KILLER_MODEL_HPP__

#include <DataTypes.hpp>
#include <Vector3.hpp>
#include <string>
#include <vector>

namespace Killer
{
#pragma pack( 1 )
	struct MODEL_HEADER
	{
		KIL_SCHAR	ID[ 4 ];
		KIL_SCHAR	Name[ 32 ];
	};

	struct MODEL_MESH
	{
		KIL_UINT32	Flags;
		KIL_UINT32	VertexCount;
		KIL_UINT32	MaterialHash;
		KIL_UINT16	TriangleListCount;
		KIL_UINT16	TriangleStripCount;
		KIL_UINT16	TriangleFanCount;
	};
#pragma pack( )

	const KIL_UINT16 CHUNK_MESH				= 0x0001;
	const KIL_UINT16 CHUNK_MATERIAL			= 0x0002;
	const KIL_UINT16 CHUNK_JOINT			= 0x0004;
	const KIL_UINT16 CHUNK_TRIANGLE_LIST	= 0x0008;
	const KIL_UINT16 CHUNK_TRIANGLE_STRIP	= 0x0010;
	const KIL_UINT16 CHUNK_TRIANGLE_FAN		= 0x0020;

	const KIL_UINT32 MESH_NORMAL_TANGENT	= 0x00000001;
	const KIL_UINT32 MESH_NORMAL_LOCAL		= 0x00000002;

	class Mesh;
	class MaterialManager;

	class Model
	{
	public:
		Model( MaterialManager *p_pMaterialManager );
		~Model( );

		KIL_UINT32 Load( const std::string &p_FileName );
		KIL_UINT32 Render( );

		KIL_UINT32 SetPosition( const Vector3 &p_Position );
		KIL_UINT32 SetScale( const Vector3 &p_Scale );
		KIL_UINT32 SetOrientation( const Vector3 &p_Orientation );

		void ToggleWireframe( );

	private:
		Model( const Model &p_Other );
		Model &operator=( const Model &p_Other );

		KIL_UINT32 ReadMeshData( FILE *p_pFile );

		Vector3	m_Position;
		Vector3	m_Scale;
		Vector3	m_Orientation;

		std::vector< Mesh * >	m_Meshes;

		MaterialManager	*m_pMaterialManager;

		std::string	m_Name;
	};
}

#endif // __KILLER_MODEL_HPP__

