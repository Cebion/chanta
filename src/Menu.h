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

#ifndef Menu_h
#define Menu_h

#include <SDL/SDL.h>
#include "Escena.h"

/*!
 * \brief Menu de opciones
 * \author Hugo Ruscitti
 */
class Menu : public Escena
{
	public:
		Menu(class Mundo *mundo);
		~Menu();

		void reiniciar (void);
		void actualizar (void);
		void imprimir (void);
		
		class Controles *controles;
		
		class Simple *cursor;
		class Simple *titulo_chanta;
		class Simple *titulo_claus;
		class Simple *logo;

		class Cadena * cadena_opciones[3];

	private:
		int x;
		int y;
		int opcion;
		class Imagen *ima;

		void crear_cadenas (void);
		void crear_titulos (void);
};

#endif
