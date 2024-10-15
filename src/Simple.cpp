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
#include "Simple.h"
#include "Imagen.h"


/*!
 * \brief Constructor
 * \author Hugo Ruscitti
 */
Simple :: Simple(class Imagen *ima, int indice, int x, int y)
{
	printf("\tSimple :: Simple ()\n");
	
	this->ima = ima;
	this->x = x;
	this->y = y;
	x_destino = x;
	y_destino = y;
	this->indice = indice;
}


/*!
 * \brief Actualización lógica
 * \author Hugo Ruscitti
 */
void Simple :: actualizar (void)
{
	int dx = x_destino - x;
	int dy = y_destino - y;
	
	if (dx != 0)
	{
		if (abs(dx) >= 4)
			x += dx / 4;
		else
			x += dx / abs(dx);
	}

	if (dy != 0)
	{
		if (abs(dy) >= 4)
			y += dy / 4;
		else
			y += dy / abs(dy);
	}
}


/*!
 * \brief Actualización gráfica
 * \author Hugo Ruscitti
 */
void Simple :: imprimir (SDL_Surface *screen)
{
	ima->imprimir(screen, indice, x, y, 1);
}


/*!
 * \brief Posiciona el objeto en una nueva coordenada de manera incremental
 * \author Hugo Ruscitti
 */
void Simple :: mover (int x, int y)
{
	x_destino = x;
	y_destino = y;
}

/*!
 * \brief posiciona el objeto en otra posición inmediatamente (sin incrementos)
 * \author Hugo Ruscitti
 */
void Simple :: mover_inmediatamente (int x, int y)
{
	mover(x,y);
	this->x = x;
	this->y = y;
}
