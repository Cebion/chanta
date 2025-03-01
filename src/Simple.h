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

#ifndef Simple_h
#define Simple_h

#include <SDL/SDL.h>

/*!
 * \brief Muestra un gr�fico y se puede mover desde afuera
 * \author Hugo Ruscitti
 */
class Simple
{
	public:
		Simple(class Imagen *ima, int indice = 0, int x = 0, int y = 0);
		void actualizar (void);
		void imprimir (SDL_Surface *screen);
		void mover (int x, int y);
		void mover_inmediatamente (int x, int y);
		
	private:
		int x;
		int y;
		int x_destino;
		int y_destino;
		int indice;
		class Imagen *ima;
};

#endif
