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


#ifndef Camara_h
#define Camara_h

#include <SDL/SDL.h>

/*!
 * \brief Cámara utilizada para el desplazamiento del Nivel
 * \author Hugo Ruscitti
 */
class Camara
{
	public:
		Camara (int filas, int columnas);
		void actualizar (void);
		void set_pos (int x, int y);
		void get_pos (int * x, int * y);
		void get_pos_final (int * x, int * y);

		int get_x (void) {return x;};
		int get_y (void) {return y;};
		
	private:
		int x;
		int y;

		int x_final;
		int y_final;

		int limite_x;
		int limite_y;

		void limitar_scroll (void);
};

#endif
