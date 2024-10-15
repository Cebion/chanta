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


#include "Enemigo.h"
#include "Juego.h"
#include "Mundo.h"
#include "Galeria.h"
#include "Imagen.h"
#include "Animacion.h"
#include "Nivel.h"

/*!
 * \brief Constructor
 * \author Hugo Ruscitti
 */
Enemigo :: Enemigo (class Juego *juego, int x, int y, int flip) : Actor (juego, x, y, flip)
{
	animaciones[PARADO] = new class Animacion("0", 5);
	animaciones[CAMINAR] = new class Animacion("2,3", 5);
	animaciones[MORIR] = new class Animacion("1", 5);
	
	ima = juego->mundo->galeria->get_imagen(ENEMIGO1);
	estado = CAMINAR;
}


/*!
 * \brief Destructor
 * \author Hugo Ruscitti
 */
Enemigo :: ~Enemigo ()
{
	delete animaciones[PARADO];
	delete animaciones[CAMINAR];
	delete animaciones[MORIR];

	printf("Enemigo :: ~Enemigo\n");
}


/*!
 * \brief Actualización lógica
 * \author Hugo Ruscitti
 */
void Enemigo :: actualizar (void)
{

	animaciones[estado]->avanzar();
	
	velocidad_salto += 0.1;
	y += distancia_al_suelo((int) velocidad_salto);

	if (pisa_el_suelo())
	{
		if (! pisa_el_suelo ( x + flip, y))
			flip *= -1;
		
		x += flip;
	}

}

/*!
 * \brief Le informan que existe una colision con otro Actor
 * \author Hugo Ruscitti
 */
void Enemigo :: colisiona_con (class Actor *otro)
{
}
