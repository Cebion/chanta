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


#ifndef Galeria_h
#define Galeria_h


/// Imagenes dentro de la Galeria
enum codigo_imagen
{
	TILES,
	CHANTA,
	ENEMIGO1,
	MENU,
	TITULO_CHANTA,
	TITULO_CLAUS,
	LOGO,
	IMA_ITEM
};

/// Fuentes dentro de la Galeria
enum codigo_fuente
{
	CHICA
};


/*!
 * \brief mantiene un conjunto de objetos Imagen y Fuente
 * \author Hugo Ruscitti
 */
class Galeria
{
	public:
		Galeria ();
		~Galeria ();
		class Imagen * imagenes [10];
		class Fuente * fuentes [1];
		
		class Imagen * get_imagen (enum codigo_imagen imagen);
		class Fuente * get_fuente (enum codigo_fuente indice);
};

#endif
