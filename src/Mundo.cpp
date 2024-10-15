/*
 * Chanta Claus - Free 2D jump 'n run video game
 * Codename: chanta
 * 
 * Copyright (c) 2004, 2005 Hugo Ruscitti
 * web site: http://www.losersjuegos.com.ar
 * 
 * Chanta Claus is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Chanta Claus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <stdlib.h>
#include "Mundo.h"
#include "Juego.h"
#include "Editor.h"
#include "Menu.h"
#include "Galeria.h"


/*!
 * \brief Constructor
 * \author Hugo Ruscitti
 */
Mundo :: Mundo ()
{
	printf("Mundo :: Mundo ()\n");
	
	iniciar_ventana(false, false);

	galeria = new class Galeria;
	
	juego = new class Juego (this);
	editor = new class Editor (this);
	menu = new class Menu (this);

	salir = false;
	
	actual = juego;
	cambiar_escena(ESCENA_MENU);
}

/*!
 * \brief Destructor
 * \author Hugo Ruscitti
 */
Mundo :: ~Mundo ()
{
	delete juego;
	delete galeria;
	delete editor;
	delete menu;
	printf("Graciar por Jugar\n");
}


/*!
 * \brief Mantiene el juego a velocidad constante.
 * \author Hugo Ruscitti
 */
void Mundo :: bucle_principal (void)
{
	int i;
	int rep;
	
	while (! salir && procesar_eventos())
	{
		controles.actualizar();

		rep = sincronizar_fps();
		
		for (i = 0; i < rep; i ++)
		{
			actual->actualizar();
		}

		SDL_FillRect(screen, NULL, \
				SDL_MapRGB(screen->format, 200, 200, 200));

		actual->imprimir();
	}
}

/*!
 * \brief Crea la ventana principal
 * \author Hugo Ruscitti
 */
void Mundo :: iniciar_ventana (bool reducido, bool fullscreen)
{
	int flags = 0;
	
	if (SDL_Init(0) == -1)
	{
		printf("Error: %s\n", SDL_GetError());
		exit (1);
	}

	atexit(SDL_Quit);
	
	if (fullscreen)
		flags |= SDL_FULLSCREEN;

#ifdef WIN32
	flags |= SDL_SWSURFACE;
#else
	flags |= SDL_HWSURFACE | SDL_DOUBLEBUF;
#endif

	if (reducido)
		screen = SDL_SetVideoMode(320, 240, 16, flags);
	else
		screen = SDL_SetVideoMode(640, 480, 16, flags);


	if (screen == NULL)
	{
		printf("Error: %s\n", SDL_GetError());
		exit (1);
	}

	SDL_WM_SetCaption ("Chanta Claus (version: " VERSION ")", NULL);
	SDL_ShowCursor(SDL_DISABLE);
}


/*!
 * \brief Gestiona los eventos de la ventana
 * \author Hugo Ruscitti
 * \return 1 si debe terminar, 0 en otro caso.
 */
int Mundo :: procesar_eventos (void)
{
	static SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				return 0;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_q)
					return 0;

				if (event.key.keysym.sym == SDLK_f)
					pantalla_completa();

				break;

			default:
				break;
				
		}
	}

	return 1;
}

/*!
 * \brief Alterna entre 'Ventana' y 'Pantalla completa'
 * \author Hugo Ruscitti
 */
void Mundo :: pantalla_completa (void)
{
	SDL_WM_ToggleFullScreen(screen);
}


/*!
 * \brief Mantiene la velocidad constante del programa, puede deterlo.
 *
 * \author Hugo Ruscitti
 * \return > 0 cantidad de repeticiones lógicas que se deben ejecutar
 */
int Mundo :: sincronizar_fps (void)
{
	static int t;
	static int tl = SDL_GetTicks ();
	static int frecuencia = 1000 / 100;
	static int tmp;
#ifdef DEBUG
	static int fps = 0;
	static int t_fps = 0;
#endif
	
	t = SDL_GetTicks ();

#ifdef DEBUG
	if ((t - t_fps) >= 1000)
	{
		printf("FPS = %d\n", fps);
		fps = 0;
		t_fps += 1000 + 1;
	}

	fps ++
#endif
	
	if ((t - tl) >= frecuencia)
	{
		tmp = (t - tl) / frecuencia;
		tl += tmp * frecuencia;
		return tmp;
	}
	else
	{
		SDL_Delay (frecuencia - (t - tl));
		tl += frecuencia;
		return 1;
	}
}

/*!
 * \brief Elije la Escena a ejectar
 * \author Hugo Ruscitti
 */
void Mundo :: cambiar_escena (enum escenas nueva)
{
	class Escena * anterior = actual;
	
	switch (nueva)
	{
		case ESCENA_MENU:
			actual = menu;
			break;

		case ESCENA_JUEGO:
			actual = juego;
			break;

		case ESCENA_EDITOR:
			actual = editor;
			break;
	}

	if (anterior == actual)
	{
		printf("ERROR, se intentó cambiar a la misma escena");
	}

	actual->reiniciar ();
}


/*!
 * \brief Imprime un rectángulo en la pantalla
 * \author Hugo Ruscitti
 */
void Mundo :: imprimir_rect(int x, int y, int w, int h, Uint32 color)
{
	SDL_Rect rect = {x, y, w, h};

	SDL_FillRect(screen, &rect, color);
}


/*!
 * \brief termina el programa inmediatamente
 * \author Hugo Ruscitti
 */
void Mundo :: terminar (void)
{
	salir = true;
}
