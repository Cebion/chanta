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


#ifndef Nivel_h
#define Nivel_h

#include <SDL/SDL.h>
#include "Camara.h"


/*!
 * \brief Almacena todos los bloques de un nivel
 * \author Hugo Ruscitti
 */
class Nivel
{
	public:
		Nivel (class Mundo *mundo, int filas = 15, int columnas = 20);
		~Nivel ();
		void imprimir (SDL_Surface *dst);
		void actualizar (void);
		
		void imprimir_actores (SDL_Surface *dst);
		
		int get_distancia_al_suelo (int x, int y, int rango);
		bool es_solido (char codigo);
		
		void siguiente (void);
		void anterior (void);
		
		void editar_bloque (int i, int x, int y);
		void guardar (void);
		int cargar (void);
		void limpiar (void);

		int get_indice (void) {return indice_nivel;};
		void generar_actores (class Procesos * procesos);
		class Camara * camara;

	private:
		int indice_nivel;
		int filas;
		int columnas;
		/// indica si este nivel ha sido editado
		bool modificado;
		char mapa[30][40];
		FILE *archivo;
		
		class Imagen *tiles;
		class Mundo *mundo;

		void abrir_archivo (void);
		void cerrar_archivo (void);
		FILE * crear_archivo (void);
		void ruta_base (char * destino);
		void copiar_archivo (FILE * tmp);
};

#endif
