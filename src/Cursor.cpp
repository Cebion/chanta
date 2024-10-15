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

#include "Cursor.h"
#include "Nivel.h"
#include "Imagen.h"
#include "Editor.h"
#include "Mundo.h"

/*!
 * \brief Constructor
 * \author Hugo Ruscitti
 */
Cursor :: Cursor (class Editor * editor)
{
	this->editor = editor;

	x = 0;
	y = 0;
	bloque_actual = 0;
}


/*!
 * \brief muestra el puntero del mouse en la pantalla
 * \author Hugo Ruscitti
 */
void Cursor :: imprimir (SDL_Surface *screen)
{
	editor->ima->imprimir(screen, 53, x, y, 1);
}

/*!
 * \brief Actualización lógica
 * \author Hugo Ruscitti
 */
void Cursor :: actualizar (void)
{
	static bool pulsado = false; // el botón del mouse se mantiene pulsado
	
	botones = SDL_GetMouseState(&x, &y);

	// está sobre la grilla y se pulsa algún boton
	if (x < 544)
		pulsa_sobre_grilla(botones);
	else
	{
		if (botones == SDL_BUTTON(1))
		{
			if (! pulsado)
			{
				pulsa_sobre_barra(botones);
				pulsado = true;
			}
		}
		else
			pulsado = false;
	}
}


/*!
 * \brief Acciones a realizar cuando se realiza un 'click' sobre el mapa
 * \author Hugo Ruscitti
 */
void Cursor :: pulsa_sobre_grilla (int botones)
{
	if (botones == SDL_BUTTON(3))
		editor->nivel->editar_bloque(-1, x, y);

	if (botones == SDL_BUTTON(1))
		editor->nivel->editar_bloque(bloque_actual, x, y);
}


void Cursor :: pulsa_sobre_barra (int botones)
{
	int fila = y / 32;
	int columna = (x / 32) - 17;

	if (fila == 0)
	{
		editor->nivel->guardar();
		
		switch (columna)
		{
			case 0:
				editor->nivel->anterior();
				break;

			case 2:
				editor->nivel->siguiente();
				break;
		}
	}

	if (fila == 1)
	{
		switch (columna)
		{
			case 0:	
				editor->nivel->cargar();
				break;

			case 1:
				editor->nivel->guardar();
				editor->mundo->cambiar_escena(ESCENA_MENU);
				break;

			case 2:
				editor->nivel->limpiar();
				break;
		}
	}
	
	if (fila == 3 && columna == 1)
	{
		editor->mover_barra_scroll(-1);
		return;
	}

	if (fila == 14 && columna == 1)
	{
		editor->mover_barra_scroll(+1);
		return;
	}

	if (fila > 3 && fila < 14)
		bloque_actual = (fila - 4) * 3 + \
				editor->get_barra_scroll() * 3\
				+ columna;
	

}
