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


#ifndef Juego_h
#define Juego_h

#include <SDL/SDL.h>
#include "Escena.h"

/*!
 * \brief Durante la partida de juego
 * \author Hugo Ruscitti
 */
class Juego : public Escena
{
	public:
		Juego(class Mundo *mundo);
		~Juego();

		void reiniciar (void);
		void actualizar (void);
		void imprimir (void);

		class Procesos *procesos;
		class Nivel *nivel;
};

#endif
