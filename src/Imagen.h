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


#ifndef Imagen_h
#define Imagen_h

#include <SDL/SDL.h>

/*!
 * \brief Almacena una plantilla de gr�ficos
 * \author Hugo Ruscitti
 */
class Imagen
{
	public:
		Imagen (char *ruta, int fil, int col, int x0 = 0, int y0 = 0, bool alpha = false);
		~Imagen ();
		void imprimir (SDL_Surface *dst, int i, int x, int y, int flip = 1);
		
	private:
		SDL_Surface *ima;
		SDL_Surface *ima_flip;
		int col;
		int fil;
		int bloque_ancho;
		int bloque_alto;
		/// punto de control horizontal
		int x0;
		/// punto de control vertical
		int y0;

		SDL_Surface * invertir_imagen (SDL_Surface *imagen);
};

#endif
