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

#include "Menu.h"
#include "Mundo.h"
#include "Galeria.h"
#include "Imagen.h"
#include "Controles.h"
#include "Simple.h"
#include "Fuente.h" // temporal
#include "Cadena.h"

/*!
 * \brief Constructor
 * \author Hugo Ruscitti
 */
Menu :: Menu (class Mundo *mundo) : Escena (mundo)
{
	printf("\tMenu :: Menu ()\n");
	controles = &(mundo->controles);
	ima = mundo->galeria->get_imagen(MENU);
	x = 0;
	y = 0;
	opcion = 0;

	logo = new Simple (mundo->galeria->get_imagen(LOGO), 0, 440, 420);
	cursor = new Simple(mundo->galeria->get_imagen(TILES), 50, 100, 300);

	crear_titulos();
	crear_cadenas();
	
	reiniciar();
}

/*!
 * \brief Destructor
 * \author Hugo Ruscitti
 */
Menu :: ~Menu ()
{
	printf("\tMenu :: ~Menu\n");

	delete cursor;
	delete titulo_claus;
	delete titulo_chanta;
	delete logo;

	for (int i = 0; i < 3; i ++)
		delete cadena_opciones[i];
}


/*!
 * \brief inicia los componentes del menu
 * \author Hugo Ruscitti
 */
void Menu :: reiniciar (void)
{
	titulo_chanta->mover_inmediatamente(100, -250);
	titulo_chanta->mover(100,10);

	titulo_claus->mover_inmediatamente(640, 200);
	titulo_claus->mover(400, 200);
}

/*!
 * \brief Actualización lógica
 * \author Hugo Ruscitti
 */
void Menu :: actualizar (void)
{
	static int delay = 0;
	
	cursor->actualizar();

	titulo_chanta->actualizar();
	titulo_claus->actualizar();
	
	if (controles->pulso(TECLA_BAJAR) && opcion < 2 && delay == 0)
	{
		delay = 30;
		opcion ++;
		cursor->mover(100, 300 + 50 * opcion);
	}

	if (controles->pulso(TECLA_SUBIR) && opcion > 0 && delay == 0)
	{
		delay = 30;
		opcion --;
		cursor->mover(100, 300 + 50 * opcion);
	}

	if (delay)
		delay --;
	
	if (controles->pulso(TECLA_ACEPTAR))
	{
		switch (opcion)
		{
			case 0:
				mundo->cambiar_escena(ESCENA_JUEGO);
				break;

			case 1:
				mundo->cambiar_escena(ESCENA_EDITOR);
				break;

			case 2:
				mundo->terminar();
				break;
		}
	}
}


/*!
 * \brief Actualización gráfica
 * \author Hugo Ruscitti
 */
void Menu :: imprimir (void)
{
	SDL_FillRect(mundo->screen, NULL, \
			SDL_MapRGB(mundo->screen->format, 56, 68, 112));

	cursor->imprimir(mundo->screen);

	titulo_chanta->imprimir(mundo->screen);
	titulo_claus->imprimir(mundo->screen);
	logo->imprimir(mundo->screen);
	
	for (int i = 0; i < 3; i ++)
		cadena_opciones[i]->imprimir (mundo->screen);
	
	SDL_Flip(mundo->screen);
}


/*!
 * \brief Genera las cadenas de texto de las opciones 
 * \author Hugo Ruscitti
 */
void Menu :: crear_cadenas (void)
{
	char textos[][60] = {\
		{"Nueva partida"},\
		{"Editor de niveles"},\
		{"Salir"}\
	};
	
	class Fuente * fuente = mundo->galeria->get_fuente(CHICA);

	for (int i = 0; i < 3; i ++)
	{
		cadena_opciones[i] = new Cadena (fuente, 150, 300 + i * 50, \
				textos[i]);
	}
}


/*!
 * \brief Genera el titulo principal "Chanta Claus"
 * \author Hugo Ruscitti
 */
void Menu :: crear_titulos (void)
{
	titulo_chanta = new Simple(mundo->galeria->get_imagen(TITULO_CHANTA),\
			0, 300, 200);

	titulo_claus = new Simple(mundo->galeria->get_imagen(TITULO_CLAUS), \
			0, 300, 400);
}
