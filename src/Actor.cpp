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

#include "Actor.h"
#include "Juego.h"
#include "Nivel.h"
#include "Animacion.h"
#include "Imagen.h"

/*!
 * \brief Constructor
 * \author Hugo Ruscitti
 */
Actor :: Actor (class Juego *juego, int x, int y, int flip)
{
	this->juego = juego;
	this->flip = 1;
	this->x = x;
	this->y = y;
	velocidad_salto = 0.0;
}

/*!
 * \brief Constructor
 * \author Hugo Ruscitti
 */
Actor :: ~Actor ()
{
	printf("Actor :: ~Actor\n");
}


/*!
 * \brief intenta avanzar sobre el eje x siempre que no exista una pared
 * \author Hugo Ruscitti
 */
void Actor :: mover_sobre_x (int incremento)
{
	if (incremento > 0)
	{
		if (x < 640*2 - 30)
			x += incremento;
	}
	else
	{
		if (x > 30)
			x += incremento;
	}
}


/*!
 * \brief determina la cantidad de pixeles hasta el suelo.
 * \author Hugo Ruscitti
 */
int Actor :: distancia_al_suelo (int rango)
{
	return juego->nivel->get_distancia_al_suelo (x, y, rango);
}


/*!
 * \brief Informa si está sobre una plataforma.
 * \author Hugo Ruscitti
 */
bool Actor :: pisa_el_suelo (void)
{
	if (distancia_al_suelo(1) == 0)
		return true;
	else
		return false;
}

/*!
 * \brief Informa si una coordenada será un piso para el Actor.
 * \author Hugo Ruscitti
 */
bool Actor :: pisa_el_suelo (int _x, int _y)
{
	if (juego->nivel->get_distancia_al_suelo (_x, _y, 1) == 0)
		return true;
	else
		return false;
}

/*!
 * \brief Actualización gráfica para los Actores dentro del scroll de Nivel
 * \author Hugo Ruscitti
 */
void Actor :: imprimir (SDL_Surface *screen)
{
	ima->imprimir(screen, animaciones[estado]->get_cuadro(), \
			x - juego->nivel->camara->get_x(),\
			y - juego->nivel->camara->get_y(), flip);
}


