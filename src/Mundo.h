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


#ifndef Mundo_h
#define Mundo_h

#include <SDL/SDL.h>
#include "Controles.h"
#include "Escena.h"


/*!
 * \brief Continene todo el proyecto
 * \author Hugo Ruscitti
 */
class Mundo
{
	public:
		Mundo();
		~Mundo();
		void bucle_principal (void);
		SDL_Surface *screen;

		void cambiar_escena (enum escenas nueva);
		void imprimir_rect(int x, int y, int w, int h, Uint32 color=0);
		void terminar (void);

		class Controles controles;
		class Galeria *galeria;

	private:
		class Escena *actual;
		class Juego *juego;
		class Editor *editor;
		class Menu *menu;

		bool salir;
		
		void iniciar_ventana (bool reducido, bool fullscreen);
		void pantalla_completa (void);
		int procesar_eventos (void);
		int sincronizar_fps (void);
};

#endif
