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


#ifndef Fuente_h
#define Fuente_h

#include <SDL/SDL.h>

/*!
 * \brief Almacena una plantilla de fuentes
 * \author Hugo Ruscitti
 */
class Fuente
{
	public:
		Fuente (char *ruta, bool alpha = false);
		~Fuente ();
		void imprimir (SDL_Surface *dst, char *cadena, int x, int y);
		
	private:
		SDL_Surface *ima;
		int separacion;
		/// define el órden de las letras en la grilla
		char cadena[113 + 1];
		/// mantiene la posición de cada letra en la grilla
		SDL_Rect rect_letras[113];

		void buscar_posiciones (void);
		int imprimir (SDL_Surface *dst, char letra, int x, int y);
		Uint32 get_pixel(SDL_Surface *surface, int x, int y);
};

#endif
