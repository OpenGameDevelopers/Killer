#ifndef __KILLER_MESH_HPP__
#define __KILLER_MESH_HPP__

#include <DataTypes.hpp>
#include <vector>
#include <RendererPrimitive.hpp>
#include <Vector3.hpp>
#include <Shader.hpp>

namespace Killer
{
	class Mesh
	{
	public:
		Mesh( );
		~Mesh( );

		KIL_UINT32 AddPrimitive( RendererPrimitive *p_pPrimitive );

		KIL_UINT32 Render( );

		KIL_UINT32 SetShader( Shader *p_pShader );

		KIL_UINT32 SetPosition( const Vector3 &p_Position );
		KIL_UINT32 SetOrientation( const Vector3 &p_Position );
		KIL_UINT32 SetScale( const Vector3 &p_Scale );

	private:
		Mesh( const Mesh &p_Other );
		Mesh &operator=( const Mesh &p_Other );

		std::vector< RendererPrimitive * >	m_Primitives;

		Shader	*m_pShader;

		Vector3	m_Position;
		Vector3	m_Orientation;
		Vector3	m_Scale;

		// Need to add a bounding volume
	};
}

#endif // __KILLER_MESH_HPP__

