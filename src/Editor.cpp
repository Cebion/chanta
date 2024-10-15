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

#include "Editor.h"
#include "Mundo.h"
#include "Nivel.h"
#include "Galeria.h"
#include "Imagen.h"
#include "Controles.h"
#include "Cursor.h"
#include "Fuente.h" // temporal


/*!
 * \brief Constructor
 * \author Hugo Ruscitti
 */
Editor :: Editor (class Mundo *mundo) : Escena (mundo)
{
	printf("\tEditor :: Editor ()\n");
	nivel = new class Nivel (mundo, 15, 17);
	controles = &(mundo->controles);
	cursor = new class Cursor (this);
	barra_scroll = 0;
	x = 0;
	y = 0;
	
	ima = mundo->galeria->get_imagen(TILES);
}

/*!
 * \brief Destructor
 * \author Hugo Ruscitti
 */
Editor :: ~Editor ()
{
	delete nivel;
	delete cursor;
	printf("\tEditor :: ~Editor\n");
}


/*!
 * \brief inicia los componentes del editor de niveles
 * \author Hugo Ruscitti
 */
void Editor :: reiniciar (void)
{
}

/*!
 * \brief Actualización lógica
 * \author Hugo Ruscitti
 */
void Editor :: actualizar (void)
{
	mover_camara();
	nivel->actualizar();

	cursor->actualizar();

	if (controles->pulso(TECLA_SALIR))
		mundo->cambiar_escena(ESCENA_MENU);
}


/*!
 * \brief Permite manejar la cámara del Scroll con los direccionales
 * \author Hugo Ruscitti
 */
void Editor :: mover_camara (void)
{
	int x_ant = x;
	int y_ant = y;
	
	if (controles->pulso(TECLA_IZQUIERDA))
		x -= 20;
	
	if (controles->pulso(TECLA_DERECHA))
		x += 20;

	if (controles->pulso(TECLA_BAJAR))
		y += 20;

	if (controles->pulso(TECLA_SUBIR))
		y -= 20;

	
	if (x != x_ant || y != y_ant)
	{
		nivel->camara->set_pos(x, y);

		// captura los límites del scroll
		nivel->camara->get_pos_final(&x, &y);
	}
}


/*!
 * \brief Actualización gráfica
 * \author Hugo Ruscitti
 */
void Editor :: imprimir (void)
{
	nivel->imprimir(mundo->screen);
	nivel->imprimir_actores(mundo->screen);
	imprimir_menu();
	cursor->imprimir(mundo->screen);
	imprimir_numero_nivel();
	SDL_Flip(mundo->screen);
}


/*!
 * \brief imprime el menu de tiles y opciones
 * \author Hugo Ruscitti
 */
void Editor :: imprimir_menu (void)
{
	int i;
	int j;
	
	mundo->imprimir_rect(544, 0, 96, 480, \
			SDL_MapRGB(mundo->screen->format, 150, 150, 150));

	ima->imprimir(mundo->screen, 48, 544, 0);
	ima->imprimir(mundo->screen, 49, 576, 0);
	ima->imprimir(mundo->screen, 50, 608, 0);

	ima->imprimir(mundo->screen, 54, 544, 32);
	ima->imprimir(mundo->screen, 55, 576, 32);
	ima->imprimir(mundo->screen, 56, 608, 32);

	// flechas del scroll
	ima->imprimir(mundo->screen, 51, 576, 92);
	ima->imprimir(mundo->screen, 52, 576, 448);

	for (i = 0; i < 10; i ++)
	{
		for (j = 0; j < 3 ; j ++)
		{
			ima->imprimir(mundo->screen, (i + barra_scroll)*3 + j,\
					544 + j * 32, 96 + 32 + i * 32);
		}
	}
}


/*!
 * \brief Imprime el número de nivel actual
 * \author Hugo Ruscitti
 */
void Editor :: imprimir_numero_nivel (void)
{
	char numero_aux[200];
	class Fuente *fuente = mundo->galeria->get_fuente(CHICA);

	sprintf(numero_aux, "Nivel : %d", nivel->get_indice());

	fuente->imprimir(mundo->screen, numero_aux, 10, 10);
}


/*!
 * \brief Modifica el desplazamiento de la barra con tiles y objetos
 * \author Hugo Ruscitti
 */
void Editor :: mover_barra_scroll (int incremento)
{
	barra_scroll += incremento;
	
	if (barra_scroll < 0)
		barra_scroll = 0;

	if (barra_scroll > 5)
		barra_scroll = 5;
}
