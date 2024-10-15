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

#include "Cadena.h"
#include <string.h>

/*!
 * \brief Constructor
 * \author Hugo Ruscitti
 */
Cadena :: Cadena (class Fuente * fuente, int x, int y, char * cadena)
{
	this->fuente = fuente;
	this->x = x;
	this->y = y;

	strcpy (this->cadena, cadena);
}


/*!
 * \brief imprime la cadena sobre screen
 * \author Hugo Ruscitti
 */
void Cadena :: imprimir (SDL_Surface *screen)
{
	fuente->imprimir(screen, cadena, x, y);
}


/*!
 * \brief actualiza su posición
 * \author Hugo Ruscitti
 */
void Cadena :: actualizar (void)
{
}
