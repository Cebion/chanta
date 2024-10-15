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


#ifndef Actor_h
#define Actor_h

#include <stdio.h>
#include <SDL/SDL.h>

/// tipos de actores
enum tipo_actor
{
	TIPO_PROTAGONISTA,
	TIPO_ENEMIGO1
};


/// estados o animaciones generales de un Actor
enum estados
{
	PARADO,
	CAMINAR,
	SALTAR,
	DISPARAR,
	MORIR,
	_QUITAR
};


/*!
 * \brief Base de los personajes del Juego
 * \author Hugo Ruscitti
 */
class Actor
{
	public:
		Actor (class Juego *juego, int x, int y, int flip = 1);
		virtual ~Actor();
		/// obtiene el valor de x
		int get_x (void) {return x;};
		/// obtiene el valor de y
		int get_y (void) {return y;};
		/// actualización lógica		
		virtual void actualizar (void) = 0;
		void imprimir (SDL_Surface *screen);
		/// le informan que a colisionado con otro Actor
		virtual void colisiona_con (class Actor *otro) = 0;

		enum estados get_estado (void) {return estado;};

	protected:
		void mover_sobre_x (int incremento);
		bool pisa_el_suelo (void);
		bool pisa_el_suelo (int _x, int _y);
		int distancia_al_suelo (int rango);
		
		class Imagen *ima;
		class Juego *juego;
		int x;
		int y;
		int flip;
		float velocidad_salto;

		enum estados estado;
		enum estados estado_anterior;

		class Animacion *animaciones[10];
};

#endif
