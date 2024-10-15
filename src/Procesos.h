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

#ifndef Procesos_h
#define Procesos_h

#include <SDL/SDL.h>
#include "Actor.h"

/*!
 * \brief Nodo de las listas de Procesos
 */
struct nodo
{
	class Actor *obj;
	struct nodo *siguiente;
};



/*!
 * \brief mantiene una lista de todos los objetos Actor
 * \author Hugo Ruscitti
 */
class Procesos
{
	public:
		Procesos (class Juego * juego);
		~Procesos ();
	
		void actualizar (void);
		void imprimir (SDL_Surface *screen);
		
		class Juego * juego;
		
		void crear_enemigo (int indice, int x, int y, int flip);
		void crear_protagonista (int x, int y, int flip);
		void crear_item (int x, int y, int flip);

		
	private:
		void avisar_colisiones (void);

		void borrar_lista (struct nodo * lista);
		void borrar_nodo (struct nodo * nodo);
		void eliminar_antiguos (struct nodo ** lista);

		class Protagonista *protagonista;
		struct nodo * lista_enemigos;
		struct nodo * lista_items;

		bool hay_colision (int x0, int y0, int x1, int y1, int radio);
};

#endif
