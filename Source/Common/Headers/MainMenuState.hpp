#ifndef __KILLER_MAINMENUSTATE_HPP__
#define __KILLER_MAINMENUSTATE_HPP__

#include <System/DataTypes.hpp>
#include <Game/GameState.hpp>
#include <Renderer/OGL/GLPrimitive.hpp>
#include <Renderer/OGL/GLShader.hpp>

namespace Killer
{
	class MainMenuState : public ZED::Game::GameState
	{
	public:
		MainMenuState( );
		virtual ~MainMenuState( );

		virtual ZED_UINT32 Enter( );
		virtual void Update( const ZED_UINT64 p_DeltaTime );
		virtual void Render( );
		virtual ZED_UINT32 Exit( );

		virtual ZED_CHAR8 *GetName( ) const;

	private:
		ZED::Renderer::GLPrimitive	m_TestTriangle;
		ZED::Renderer::GLShader		m_OpenGLShader;
	};
}


#endif // ___MAINMENUSTATE_HPP__

