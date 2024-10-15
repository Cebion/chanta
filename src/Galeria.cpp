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


#include <stdio.h>
#include "Galeria.h"
#include "Imagen.h"
#include "Fuente.h"

/*!
 * \brief Constructor
 * \author Hugo Ruscitti
 */
Galeria :: Galeria ()
{
	printf("Galeria :: Galeria\n");
	
	imagenes[CHANTA] = new Imagen ("chanta.png", 4, 6, 45, 90, false);
	imagenes[TILES] = new Imagen ("tiles.png", 10, 6);
	imagenes[ENEMIGO1] = new Imagen ("enemigo1.png", 2, 2, 45, 72, false);
	imagenes[MENU] = new Imagen ("menu.png", 2, 1);
	imagenes[TITULO_CHANTA] = new Imagen ("titulo_chanta.png", 1, 1);
	imagenes[TITULO_CLAUS] = new Imagen ("titulo_claus.png", 3, 1);
	imagenes[LOGO] = new Imagen ("logo.png", 1, 1);
	imagenes[IMA_ITEM] = new Imagen ("item.png", 1, 6, 15, 30);
	
	fuentes[CHICA] = new Fuente ("chica.png", true);
}

/*!
 * \brief Destructor
 * \author Hugo Ruscitti
 */
Galeria :: ~Galeria ()
{
	delete imagenes[CHANTA];
	delete imagenes[TILES];
	delete imagenes[ENEMIGO1];
	delete imagenes[MENU];
	delete imagenes[TITULO_CHANTA];
	delete imagenes[TITULO_CLAUS];
	delete imagenes[LOGO];
	delete imagenes[IMA_ITEM];
	
	delete fuentes[CHICA];
	printf("Galeria :: ~Galeria\n");
}


/*!
 * \brief retorna la referencia a una Imagen
 * \return referencia al objeto buscado
 */
class Imagen * Galeria :: get_imagen (enum codigo_imagen codigo_imagen)
{
	return imagenes[codigo_imagen];
}

/*!
 * \brief retorna la referencia a una Fuente
 * \author Hugo Ruscitti
 */
class Fuente * Galeria :: get_fuente (enum codigo_fuente indice)
{
	return fuentes[indice];
}
