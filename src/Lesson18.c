/*
 *		This Code Was Created By Jeff Molofee and GB Schmick 2000
 *		A HUGE Thanks To Fredric Echols For Cleaning Up
 *		And Optimizing The Base Code, Making It More Flexible!
 *		If You've Found This Code Useful, Please Let Me Know.
 *		Visit Our Sites At www.tiptup.com and nehe.gamedev.net
 *      Modified for LCCWin32 compiler by Robert Wishlaw 2002/11/24
 */

 /***************************************************************
 *  Project : $(project)
 *  Function : Main program
 ***************************************************************
 *  $Author : Jeff Molofee and GB Schmick 2000
 *  $Name :  $
 ***************************************************************
 *
 *  Copyright NeHe Production
 *
 ***************************************************************/

/**         Comments manageable by Doxygen
*
*  Modified smoothly by Thierry DECHAIZE
*
*  Paradigm : obtain one source (only one !) compatible for multiple free C Compilers
*    and provide for all users an development environment on Windows (64 bits compatible),
*    the great Code::Blocks manager (version 20.03), and don't use glaux.lib or glaux.dll.
*
*	a) Mingw 32 bits, version officielle gcc 9.2.0 (old !) : downloadable on http://sourceforge.net/projects/mingw/ (official)
*	b) Mingw 64 bits included in new IDE Red Panda Dev-Cpp, version gcc 10.3.0 : donwloadable on http://sourceforge.net/projects/dev-cpp-2020/
*	c) Mingw 64 bits included in package Code::Blocks (version 20.03), version gcc 8.1.0 (very old !) : downloadable on http://sourceforge.net/projects/codeblocks/files/Binaries/20.03/Windows/
*	d) Mingw 32 and 64 bits packag�s, version gcc 11.2.0 : downloadable on  https://winlibs.com/ (and CLANG included in, 32 and 64 bits), two kits :
*			- winlibs-i686-posix-dwarf-gcc-12.2.0-llvm-14.0.6-mingw-w64ucrt-10.0.0-r2.7z (32 bits)
*			- winlibs-x86_64-posix-seh-gcc-12.2.0-llvm-14.0.6-mingw-w64ucrt-10.0.0-r2.7z (64 bits)
*	e) Cygwin64, 32 et 64 bits, version gcc 11.3.0 : downloadable on http://www.cygwin.com/install.html (tool for install : setup-x86_64.exe)
*	f) TDM GCC, 32 et 64 bits, version 10.3.0 : downloadable on http://sourceforge.net/projects/TDM-GCC
*	g) MSYS2 environnement MINGW32 and MINGW64, 32 et 64 bits, version de 2022 (msys2-x86_64-20220603.exe), version gcc 12.2.0 : downloadable on https://repo.msys2.org/distrib/x86_64/msys2-x86_64-20220603.exe
*	h) Visual Studio 2022, 32 et 64 bits, community edition for free : downloadable on https://visualstudio.microsoft.com/fr/thank-you-downloading-visual-studio/?sku=Community&rel=17
*	i) Borland C/C++ 32 bits, version 5.5 : downloadable on https://developerinsider.co/download-and-install-borland-c-compiler-on-windows-10/
*	j) Digital Mars Compiler C/C++ 32 bits version 8.57 : downloadable on http://www.digitalmars.com (the more old compiler, the more bugged, dead branch !)
*	k) OpenWatcom C/C++ 32 et 64 bits, version 2.0 : downloadable on http://openwatcom.mirror.fr/ (only 32 bits version run correctly !)
*	l) Lcc and Lcc64, 32 et 64 bits: downloadable http://www.cs.virginia.edu/~lcc-win32/
*	m) PELLES C (only C) , 32 et 64 bits, version 11.0 : downloadable on http://www.smorgasbordet.com/pellesc/
*	o) CLANG, adoss� aux environnements MINGW64 et MINGW32, version 14.0.6 (version gcc 12.0.0) : downloadable on https://winlibs.com/
*	p) CLANG, adoss� aux environnements Visual Studio 2022 (+ kits Microsoft), version 15.0.0 : downloadable on https://releases.llvm.org/download.html
*	q) CLANG de la version MSYS2, adoss� aux environnements MINGW64 et MINGW32, version 15.0.0 (version gcc 12.2.0) : downloadable on https://repo.msys2.org/distrib/x86_64/msys2-x86_64-20220118.exe
*	r) CLANG de la version CYGWIN, adoss� aux environnements MINGW64 et MINGW32, version 8.0.0 (very old !) (version gcc 11.3.0) : downloadable http://www.cygwin.com/install.html (tool for install or update : setup-x86_64.exe)
*
*   TDE -> Add resource file and resource header for restitute version + icon OpenGL.ico for fun
*			because versionning is important, same for freeware :-) !
*
*  Date : 2022/02/15
*
* \file            Lesson18.c
* \author          Jeff Molofee ( NeHe ) & GB Schmick 2000 originely, Modified for LCCWin32 compiler by Robert Wishlaw 2002/11/24
* \author          After adapted by Thierry Dechaize to verify paradigm : one source for multiple C Compilers
* \version         2.0.1.0
* \date            15 f�vrier 2022
* \brief           Ouvre une simple fen�tre Windows et dessine des textes g�n�r�s en 2D Font, ainsi qu'une forme en rotation en forme de losange avec OpenGL.
* \details         Ce programme ne g�re que deux �v�nements : le clic sur le bouton "Ferm�" de la fen�tre, la sortie par la touche ESC.
*
*
*/

#if defined __CYGWIN__ || defined __LCC__
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>		// Header File For Windows
#if defined(__LCC__)
#ifndef WINGDIAPI
#   define WINGDIAPI __stdcall
#endif
#endif

#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glext.h>		// Header File For The GLext Library
/* #include <gl\glaux.h>		// Header File For The Glaux Library   (NEW) */

#if defined __GNUC__ || defined __LCC__ || defined _MSC_VER || defined __TURBOC__
#include <stdbool.h>
#endif

#ifdef __DMC__
typedef BOOL         bool;
#endif

// A user defined ``bool'' type for compilers that don't yet support one.
//
#if defined(__BORLANDC__) && (__BORLANDC__ < 0x500) || defined(__WATCOMC__)
  #define DONT_HAVE_BOOL_TYPE
#endif

// A ``bool'' type for compilers that don't yet support one.
#if defined(DONT_HAVE_BOOL_TYPE)
  typedef char bool;

  #ifdef true
    #warning Better check include file ``mytypes.h''.
    #undef true
  #endif
  #define true 1

  #ifdef false
    #warning Better check include file ``mytypes.h''.
    #undef false
  #endif
  #define false 0
#endif

HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

BOOL	keys[256];			// Array Used For The Keyboard Routine
BOOL	active=TRUE;		// Window Active Flag Set To TRUE By Default
BOOL	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default
BOOL	light;				// Lighting ON/OFF
BOOL	lp;					// L Pressed?
BOOL	fp;					// F Pressed?
BOOL    sp;                 // Spacebar Pressed? ( NEW )

int		part1;				// Start Of Disc ( NEW )
int		part2;				// End Of Disc ( NEW )
int		p1=0;				// Increase 1 ( NEW )
int		p2=1;				// Increase 2 ( NEW )

GLfloat	xrot;				// X Rotation
GLfloat	yrot;				// Y Rotation
GLfloat xspeed;				// X Rotation Speed
GLfloat yspeed;				// Y Rotation Speed
GLfloat	z=-5.0f;			// Depth Into The Screen

GLUquadricObj *quadratic;	// Storage For Our Quadratic Objects ( NEW )

GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]=	{ 0.0f, 0.0f, 2.0f, 1.0f };

GLuint	filter;				// Which Filter To Use
GLuint	texture[3];			// Storage For 3 Textures
GLuint  object=0;			// Which Object To Draw (NEW)

static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		0,  										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
    };

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

/**	            This Code Creates Texture From a Bitmap File.
*
* \brief      Fonction NeHeLoadBitmap3 : charge un fichier BMP en m�moire pour generer un tableau de trois textures
* \details    En entr�e le nom du fichier Bitmap et en sortie le tableau des trois textures utilisables avec OpenGL
* \param	  szFileName			nom du fichier BMP				                *
* \param	  *texid			    un pointeur sur lae tableau des trois textures g�n�r�es			    *
* \return     bool                  un booleen, le tableau des trois textures cr�� ou non.
*
*/

bool NeHeLoadBitmap3(LPTSTR szFileName, GLuint *texid)					// Creates Texture From A Bitmap File
{
	HBITMAP hBMP;														// Handle Of The Bitmap
	BITMAP	BMP;														// Bitmap Structure

    glGenTextures(3, &texid[0]);					                    // Create Three Textures

	hBMP=(HBITMAP)LoadImage(GetModuleHandle(NULL), szFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );

	if (!hBMP)															// Does The Bitmap Exist?
		return FALSE;													// If Not Return False

	GetObject(hBMP, sizeof(BMP), &BMP);									// Get The Object
																		// hBMP:        Handle To Graphics Object
																		// sizeof(BMP): Size Of Buffer For Object Information
																		// &BMP:        Buffer For Object Information
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);								// Pixel Storage Mode (Word Alignment / 4 Bytes)

    // Create Nearest Filtered Texture
    glBindTexture(GL_TEXTURE_2D, texid[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

    // Create Linear Filtered Texture
    glBindTexture(GL_TEXTURE_2D, texid[1]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

    // Create MipMapped Texture
    glBindTexture(GL_TEXTURE_2D, texid[2]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, BMP.bmWidth, BMP.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);


	DeleteObject(hBMP);													// Delete The Object

	return TRUE;														// Loading Was Successful
}

int LoadGLTextures()									// Load Bitmaps And Convert To Textures
{
	// Start Of User Initialization
	if (!NeHeLoadBitmap3("../../Data/Wall2.bmp", texture))		// Load The Bitmap
		return FALSE;


/*	if (TextureImage[0])									// If Texture Exists
	{
		if (TextureImage[0]->data)							// If Texture Image Exists
		{
			free(TextureImage[0]->data);					// Free The Texture Image Memory
		}

		free(TextureImage[0]);								// Free The Image Structure
	}
*/
	return TRUE;										    // Return The Status
}

/**	            This Code Resize the main window.
*
* \brief      Fonction ReSizeGLScene : redimensionnement de la fen�tre Windows g�rant OpenGL
* \details    En entr�e les deux nouvelles dimensions de la fen�tre
* \param	  width			Width of the GL Window Or Fullscreen Mode				*
* \param	  height		Height of the GL Window Or Fullscreen Mode			    *
* \return     GLvoid        un void OpenGL.
*
*/

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

/**	            This Code finish the initialization OpenGL of the main window.
*
* \brief      Fonction InitGL : Fin de l'initialisation de la fen�tre Windows g�rant OpenGL
* \details    Rien
* \param	  GLvoid		un void OpenGL.
* \return     int        	un entier (booleen)
*
*/

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	if (!LoadGLTextures())								// Jump To Texture Loading Routine
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}

	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
	glEnable(GL_LIGHT1);								// Enable Light One

	quadratic=gluNewQuadric();							// Create A Pointer To The Quadric Object (Return 0 If No Memory) (NEW)
	gluQuadricNormals(quadratic, GLU_SMOOTH);			// Create Smooth Normals (NEW)
	gluQuadricTexture(quadratic, GL_TRUE);				// Create Texture Coords (NEW)

	return TRUE;										// Initialization Went OK
}

/**	            This Code draw all the cubes.
*
* \brief      Fonction glDrawCube : Dessin de tous les cubes
* \details    Rien
* \return     GLvoid        	un void OpenGL
*
*/
GLvoid glDrawCube()
{
		glBegin(GL_QUADS);
		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glNormal3f( 0.0f, 0.0f,-1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right Face
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
}

/**	            This Code draw the scene OpenGL in the main window.
*
* \brief      Fonction DrawGLScene : Dessin sous OpenGL dans la fen�tre Windows.
* \details    Rien
* \param	  GLvoid		un void OpenGL.
* \return     int        	un entier (booleen)
*
*/

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The View
	glTranslatef(0.0f,0.0f,z);

	glRotatef(xrot,1.0f,0.0f,0.0f);
	glRotatef(yrot,0.0f,1.0f,0.0f);

	glBindTexture(GL_TEXTURE_2D, texture[filter]);

	switch(object)
	{
	case 0:
		glDrawCube();
		break;
	case 1:
		glTranslatef(0.0f,0.0f,-1.5f);					// Center The Cylinder
		gluCylinder(quadratic,1.0f,1.0f,3.0f,32,32);	// A Cylinder With A Radius Of 0.5 And A Height Of 2
		break;
	case 2:
		gluDisk(quadratic,0.5f,1.5f,32,32);				// Draw A Disc (CD Shape) With An Inner Radius Of 0.5, And An Outer Radius Of 2.  Plus A Lot Of Segments ;)
		break;
	case 3:
		gluSphere(quadratic,1.3f,32,32);				// Draw A Sphere With A Radius Of 1 And 16 Longitude And 16 Latitude Segments
		break;
	case 4:
		glTranslatef(0.0f,0.0f,-1.5f);					// Center The Cone
		gluCylinder(quadratic,1.0f,0.0f,3.0f,32,32);	// A Cone With A Bottom Radius Of .5 And A Height Of 2
		break;
	case 5:
		part1+=p1;
		part2+=p2;

		if(part1>359)									// 360 Degrees
		{
			p1=0;
			part1=0;
			p2=1;
			part2=0;
		}
		if(part2>359)									// 360 Degrees
		{
			p1=1;
			p2=0;
		}
		gluPartialDisk(quadratic,0.5f,1.5f,32,32,part1,part2-part1);	// A Disk Like The One Before
		break;
	};

	xrot+=xspeed;
	yrot+=yspeed;
	return TRUE;										// Keep Going
}

/**	            This Code destroy all resources of this program.
*
* \brief      Fonction KillGLWindow : Destruction de toutes les ressources du programme.
* \details    Rien
* \param	  GLvoid			un void OpenGL.
* \return     GLvoid        	un void OpenGL.
*
*/

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	gluDeleteQuadric(quadratic);						// Delete The Quadratic To Free System Resources

	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/**	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *  \brief          Creation of our OpenGL Window
 *  \param 			title			- Title To Appear At The Top Of The Window				*
 *	\param 			width			- Width Of The GL Window Or Fullscreen Mode				*
 *	\param 			height			- Height Of The GL Window Or Fullscreen Mode			*
 *	\param          bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	\param          fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*
 *  \return         BOOL            - un entier booleen (OK ou non).
 */

BOOL CreateGLWindow(char* title, int width, int height, int bits, BOOL fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

    pfd.cColorBits = bits;

    if (!(hDC=GetDC(hWnd)))                         // Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

/**         Comments manageable by Doxygen
*
* \brief      Fonction CALLBACK de traitement des messages Windows
* \details    Traitement de la boucle infinie des messages Windows
* \param      hWnd         L'header de la fen�tre principale.
* \param      uMsg         Un entier non sign�.
* \param      wParam       Les param�tres en entr�e.
* \param      lParam       Autres param�tres en entr�e.
* \return     LRESULT 	   Un LRESULT donnant le status du traitement du message.
*
*/

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
			}
			else
			{
				active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

/**	This Code is mandatory to create windows application (function WinMain)					*
 *  \brief          Creation of our application on Windows System (not console application) *
 *  \param 			hInstance		- Header de l'instance Windows				            *
 *	\param 			hPrevInstance	- Header de l'instance pr�c�dente de Windows 			*
 *	\param 			lpCmdLine		- Un pointeur sur la ligne de commande 			        *
 *	\param          nCmdShow		- Un indicateur d'�tat			                        *
 *  \return         int             - un entier booleen (OK ou non).                        *
 *	                                                                                        *
 */

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// BOOL Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("NeHe & TipTup's Quadratics Tutorial",640,480,16,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
			{
				done=TRUE;							// ESC or DrawGLScene Signalled A Quit
			}
			else									// Not Time To Quit, Update Screen
			{
				SwapBuffers(hDC);					// Swap Buffers (Double Buffering)
				if (keys['L'] && !lp)
				{
					lp=TRUE;
					light=!light;
					if (!light)
					{
						glDisable(GL_LIGHTING);
					}
					else
					{
						glEnable(GL_LIGHTING);
					}
				}
				if (!keys['L'])
				{
					lp=FALSE;
				}
				if (keys['F'] && !fp)
				{
					fp=TRUE;
					filter+=1;
					if (filter>2)
					{
						filter=0;
					}
				}
				if (!keys['F'])
				{
					fp=FALSE;
				}
				if (keys[' '] && !sp)
				{
					sp=TRUE;
					object++;
					if(object>5)
						object=0;
				}
				if (!keys[' '])
				{
					sp=FALSE;
				}
				if (keys[VK_PRIOR])
				{
					z-=0.02f;
				}
				if (keys[VK_NEXT])
				{
					z+=0.02f;
				}
				if (keys[VK_UP])
				{
					xspeed-=0.01f;
				}
				if (keys[VK_DOWN])
				{
					xspeed+=0.01f;
				}
				if (keys[VK_RIGHT])
				{
					yspeed+=0.01f;
				}
				if (keys[VK_LEFT])
				{
					yspeed-=0.01f;
				}

				if (keys[VK_F1])						// Is F1 Being Pressed?
				{
					keys[VK_F1]=FALSE;					// If So Make Key FALSE
					KillGLWindow();						// Kill Our Current Window
					fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
					// Recreate Our OpenGL Window
					if (!CreateGLWindow("NeHe & TipTup's Quadratics Tutorial",640,480,16,fullscreen))
					{
						return 0;						// Quit If Window Was Not Created
					}
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}
