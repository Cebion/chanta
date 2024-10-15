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
#include <stdio.h>
#include <string.h>
#include "Animacion.h"

/*!
 * \brief constructor
 * 
 * \author Hugo Ruscitti
 */
Animacion :: Animacion (char *_cuadros, int delay)
{
	int i = 0;
	char tmp[1024];
	char *proximo;

	
	strcpy(tmp, _cuadros);

	for (proximo = strtok(tmp, ","); proximo; i++)
	{
		this->cuadros[i] = atoi(proximo);
		proximo = strtok(NULL, ",\0");
	}
	
	this->cuadros[i] = -1;
	this->paso = 0;
	this->cont_delay = 0;
	this->delay = delay;
	
	printf("\t\t\tAnimacion :: Animacion () \n");
}

/*!
 * \brief destructor
 * \author Hugo Ruscitti
 */
Animacion :: ~Animacion ()
{
	printf("\t\t\tAnimacion :: ~Animacion () \n");
}


/**
 * \brief avanza un cuadro de animación
 *
 * \author Hugo Ruscitti
 * \return 1 si la animación llegó al último cuadro (se reinicia aqui)
 */
int Animacion :: avanzar (void)
{	
	if ((++ cont_delay) >= delay)
	{
		cont_delay = 0;
		
		if (cuadros[++paso] == -1)
		{
			paso = 0;
			return 1;
		}
	}

	return 0;
}

/*!
 * \brief Reinicia la Animacion al primer cuadro
 * \author Hugo Ruscitti
 */
void Animacion :: reiniciar (void)
{
	paso = 0;
	cont_delay = 0;
}

/*!
 * \brief informa si la Animación recién comienza
 * \author Hugo Ruscitti
 */
bool Animacion :: es_primer_cuadro (void)
{
	return (paso == 0);
}
