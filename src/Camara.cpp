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
#include "Camara.h"

/*!
 * \brief Constructor
 * \author Hugo Ruscitti
 */
Camara :: Camara (int filas, int columnas)
{
	x = 0;
	y = 0;
	x_final = 0;
	y_final = 0;

	limite_x = 1280 - columnas * 32;
	limite_y = 960 - filas * 32;
}


/*!
 * \brief actualiza su posición
 * \author Hugo Ruscitti
 */
void Camara :: actualizar (void)
{
	int dx = x_final - x;
	int dy = y_final - y;

	if (dx != 0)
	{
		if (abs(dx) >= 10)
			x += dx / 10;
		else
			x += dx / abs(dx);
	}

	if (dy != 0)
	{
		if (abs(dy) >= 10)
			y += dy / 10;
		else
			y += dy / abs(dy);
	}
}


/*!
 * \brief Define la nueva posición
 * \author Hugo Ruscitti
 */
void Camara :: set_pos (int x, int y)
{
	this->x_final = x;
	this->y_final = y;

	limitar_scroll();
}


/*!
 * \brief retorna la posición destino de la Camara
 * \author Hugo Ruscitti
 */
void Camara :: get_pos_final (int *x, int *y)
{
	*x = x_final;
	*y = y_final;
}


/*!
 * \brief retorna la posición actual de la Camara
 * \author Hugo Ruscitti
 */
void Camara :: get_pos (int *x, int *y)
{
	*x = this->x;
	*y = this->y;
}


/*!
 * \brief Evita que la cámara apunte fuera del escenario
 * \author Hugo Ruscitti
 */
void Camara :: limitar_scroll (void)
{
	if (x_final < 0)
		x_final = 0;

	if (y_final < 0)
		y_final = 0;
	
	if (x_final > limite_x)
		x_final = limite_x;

	if (y_final > limite_y)
		y_final = limite_y;
}

