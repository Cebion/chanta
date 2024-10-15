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
#include "Mundo.h"
#include "Nivel.h"
#include "Procesos.h"
#include "Galeria.h"
#include "Imagen.h"


/*!
 * \brief Constructor
 * \author Hugo Ruscitti
 */
Juego :: Juego (class Mundo *mundo) : Escena (mundo)
{
	printf("\tJuego :: Juego ()\n");
	nivel = NULL;
	procesos = NULL;

	reiniciar();
}

/*!
 * \brief Destructor
 * \author Hugo Ruscitti
 */
Juego :: ~Juego ()
{
	delete procesos;
	delete nivel;
	printf("\tJuego :: ~Juego\n");
}

/*!
 * \brief Inicia los componentes de la escena
 * \author Hugo Ruscitti
 */
void Juego :: reiniciar (void)
{
	if (procesos != NULL)
		delete procesos;

	if (nivel != NULL)
		delete nivel;

	procesos = new class Procesos (this);
	nivel = new class Nivel (mundo);
	nivel->generar_actores(procesos);

	printf("Reiniciando el juego\n");
}


/*!
 * \brief Actualización lógica
 * \author Hugo Ruscitti
 */
void Juego :: actualizar (void)
{
	if (mundo->controles.pulso(TECLA_SALIR))
		mundo->cambiar_escena(ESCENA_MENU);
			
	nivel->actualizar();
	procesos->actualizar();
}


/*!
 * \brief Actualización gráfica
 * \author Hugo Ruscitti
 */
void Juego :: imprimir (void)
{
	nivel->imprimir(mundo->screen);
	procesos->imprimir(mundo->screen);
	SDL_Flip(mundo->screen);
}
