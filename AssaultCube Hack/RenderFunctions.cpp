#include "RenderFunctions.h"

namespace RenderFunctions
{
	void DrawRect( int x, int y, int x2, int y2, Color32 color, bool bFilled )
	{
		glDepthMask( GL_FALSE );
		glDisable( GL_TEXTURE_2D );

		glColor4f( color.r, color.g, color.b, color.a );

		glBegin( bFilled ? GL_QUADS : GL_LINE_LOOP );

		glVertex2f( x, y );
		glVertex2f( x2, y );
		glVertex2f( x2, y2 );
		glVertex2f( x, y2 );

		glEnd( );

		glEnable( GL_TEXTURE_2D );
		glDepthMask( GL_TRUE );
	}

	void DrawLine( int x, int y, int x2, int y2, float width, Color32 color )
	{
		glDepthMask( GL_FALSE );
		glDisable( GL_TEXTURE_2D );

		glLineWidth( width );
		glColor4f( color.r, color.g, color.b, color.a );

		glBegin( GL_LINES );

		glVertex2f( x, y );
		glVertex2f( x2, y2 );

		glEnd( );

		glEnable( GL_TEXTURE_2D );
		glDepthMask( GL_TRUE );
	}

	void DrawHealthBar( int x, int y, int w, int h, float health, Color32 color )
	{
		//Outline
		DrawRect( x, y, x + w, y + h, Color32( 0.0F, 0.0F, 0.0F, 1.0F ) );

		//Content
		DrawRect( x + 1, y + 1, x + ( w * health ) - 1, y + h - 1, color );
	}
}

