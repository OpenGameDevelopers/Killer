#ifndef __KILLER_MESH_HPP__
#define __KILLER_MESH_HPP__

#include <DataTypes.hpp>
#include <vector>
#include <RendererPrimitive.hpp>
#include <Vector3.hpp>
#include <Matrix4x4.hpp>

namespace Killer
{
	class MaterialManager;
	class Camera;

	class Mesh
	{
	public:
		Mesh( MaterialManager *p_pMaterialManager );
		~Mesh( );

		KIL_UINT32 AddPrimitive( RendererPrimitive *p_pPrimitive );

		KIL_UINT32 SetMaterial( const KIL_UINT32 p_MaterialID );

		KIL_UINT32 Render( Camera &p_Camera);

		KIL_UINT32 SetPosition( const Vector3 &p_Position );
		KIL_UINT32 SetOrientation( const Vector3 &p_Position );
		KIL_UINT32 SetScale( const Vector3 &p_Scale );

		void ToggleWireframe( );

		void ShowNormals( );
		void HideNormals( );

	private:
		Mesh( const Mesh &p_Other );
		Mesh &operator=( const Mesh &p_Other );

		std::vector< RendererPrimitive * >	m_Primitives;

		Vector3	m_Position;
		Vector3	m_Orientation;
		Vector3	m_Scale;

		KIL_UINT32	m_MaterialHash;
		KIL_BOOL	m_DrawNormals;
		KIL_BOOL	m_DrawWireframe;

		MaterialManager	*m_pMaterialManager;

		KIL_UINT32	m_PositionSolidColourMaterial;

		Matrix4x4	m_ScaleMatrix;
		Matrix4x4	m_RotationX;
		Matrix4x4	m_RotationY;
		Matrix4x4	m_RotationZ;
		Matrix4x4	m_Translation;

		// Need to add a bounding volume
	};
}

#endif // __KILLER_MESH_HPP__

