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
#include "Mundo.h"

/*!
 * \mainpage Chanta Claus
 *
 * \section intro Introducción
 *
 * 	Chanta Claus es un videojuego navideño de plataformas muy simple.
 * 
 * 	Inicialmente fué desarrollado para sistemas DOS utilizando Div Games 
 * 	Studio.
 *
 * 	En esta versión buscamos reahacer el videojuego para otros sistemas 
 * 	operativos como GNU/Linux. En lugar de utilizar el antiguo código 
 * 	fuente lo creamos nuevamente, desde cero, utilizando otras 
 * 	herramientas de trabajo como:
 * 
 * 		\li \c GNU/Linux
 *	 	\li \c C++
 * 		\li \c SDL
 *
 * \section author Copyright
 * 
 * 	Copyright (c) 2004, 2005 Hugo Ruscitti <hugoruscitti@yahoo.com.ar>
 *
 * 	web : http://www.losersjuegos.com.ar
 *
 * 	Para más detalles lea el archivo README, AUTHORS y COPYING.
 * 
 * \section license License
 *
 * 	Chanta Claus is free software; you can redistribute it and/or modify
 * 	it under the terms of the gnu general public license as published by
 * 	the free software foundation; either version 2 of the license, or
 * 	(at your option) any later version.
 *
 *	Chanta Claus is distributed in the hope that it will be useful,
 *	but without any warranty; without even the implied warranty of
 *	merchantability or fitness for a particular purpose.  see the
 *	gnu general public license for more details.
 *	   
 *	You should have received a copy of the gnu general public license
 *	along with this program; if not, write to the free software
 *	foundation, inc., 59 temple place, suite 330, boston, ma 02111-1307 
 *	usa
 */


/*!
 * \brief Función principal
 * \author Hugo Ruscitti
 */
int main (void)
{
	class Mundo mundo;
	
	mundo.bucle_principal();
	return 0;
}
