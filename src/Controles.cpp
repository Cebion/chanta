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


#include "Controles.h"

/*!
 * \brief constructor
 * \author Hugo Ruscitti
 */
Controles :: Controles ()
{
	teclas_configuradas[TECLA_SALIR] = SDLK_ESCAPE;
	teclas_configuradas[TECLA_SUBIR] = SDLK_UP;
	teclas_configuradas[TECLA_BAJAR] = SDLK_DOWN;
	teclas_configuradas[TECLA_ACEPTAR] = SDLK_RETURN;
	teclas_configuradas[TECLA_DISPARAR] = SDLK_SPACE;
	teclas_configuradas[TECLA_IZQUIERDA] = SDLK_LEFT;
	teclas_configuradas[TECLA_DERECHA] = SDLK_RIGHT;
	teclas_configuradas[TECLA_SALTAR] = SDLK_UP;
	teclas_configuradas[TECLA_GUARDAR] = SDLK_s;
}


/*!
 * \brief captura el estado de las teclas.
 *
 * \author Hugo Ruscitti
 */
void Controles :: actualizar (void)
{
	keys = SDL_GetKeyState(NULL);
}


/*!
 * \brief informa si una tecla fu� pulsada (con repetici�n)
 * 
 * \author Hugo Ruscitti
 */
bool Controles :: pulso (enum teclas i)
{
	if (keys[teclas_configuradas[i]])
		return true;
	else
		return false;
}
