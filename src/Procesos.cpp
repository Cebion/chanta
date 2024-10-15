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
#include "Procesos.h"
#include "Juego.h"
#include "Item.h"
#include "Protagonista.h"
#include "Enemigo.h"
#include "Mundo.h"


/*!
 * \brief constructor
 * \author Hugo Ruscitti
 */
Procesos :: Procesos (class Juego * juego)
{
	printf("\t\tProcesos :: Procesos ()\n");
	this->juego = juego;
	protagonista = NULL;
	lista_enemigos = NULL;
	lista_items = NULL;
}


/*!
 * \brief destructor
 * \author Hugo Ruscitti
 */
Procesos :: ~Procesos ()
{
	delete protagonista;
	borrar_lista(lista_enemigos);
	borrar_lista(lista_items);
	printf("\t\tProcesos :: ~Procesos ()\n");
}


/*!
 * \brief actualiza la posición y estado de todos los Procesos
 * \author Hugo Ruscitti
 */
void Procesos :: actualizar (void)
{
	struct nodo * tmp;

	if (protagonista)
		protagonista->actualizar();

	for (tmp = lista_enemigos; tmp; tmp = tmp->siguiente)
		tmp->obj->actualizar();

	for (tmp = lista_items; tmp; tmp = tmp->siguiente)
		tmp->obj->actualizar();

	eliminar_antiguos(&lista_enemigos);
	eliminar_antiguos(&lista_items);

	if (protagonista)
		avisar_colisiones();
}


/*!
 * \brief imprime a los objetos en las pantalla
 * \author Hugo Ruscitti
 */
void Procesos :: imprimir (SDL_Surface *screen)
{
	struct nodo *tmp;

	for (tmp = lista_enemigos; tmp; tmp = tmp->siguiente)
		tmp->obj->imprimir(juego->mundo->screen);

	if (protagonista)
		protagonista->imprimir(juego->mundo->screen);
	
	for (tmp = lista_items; tmp; tmp = tmp->siguiente)
		tmp->obj->imprimir(juego->mundo->screen);

}


/*!
 * \brief Informa las colisiones entre Actores
 * \author Hugo Ruscitti
 */
void Procesos :: avisar_colisiones (void)
{
	static int radio = 30;
	int x0, y0;
	int x1, y1;
	struct nodo * tmp;
	
	x0 = protagonista->get_x ();
	y0 = protagonista->get_y ();

	// verifica colisiones con los enemigos
	for (tmp = lista_enemigos; tmp; tmp = tmp->siguiente)
	{
		x1 = tmp->obj->get_x ();
		y1 = tmp->obj->get_y ();

		if (hay_colision(x0, y0, x1, y1, radio))
		{
			protagonista->colisiona_con (tmp->obj);
		}
	}


	// verifica colisiones con los Item
	for (tmp = lista_items; tmp; tmp = tmp->siguiente)
	{
		x1 = tmp->obj->get_x ();
		y1 = tmp->obj->get_y ();

		if (hay_colision(x0, y0, x1, y1, 10))
		{
			tmp->obj->colisiona_con (protagonista);
			return;
		}
	}
}


/*!
 * \brief Genera un nuevo Enemigo
 * \author Hugo Ruscitti
 */
void Procesos :: crear_enemigo (int indice, int x, int y, int flip)
{
	struct nodo * tmp;

	tmp = (struct nodo *) malloc (sizeof(struct nodo));
	
	printf("Creando un enemigo tipo %d en (%d, %d)\n", indice, x, y);

	switch (indice)
	{
		case 1:
			tmp->obj = new class Enemigo (juego, x, y, flip);
			break;
			
		default:
			printf("El indice %d, como tipo de %s es desconocido",\
					indice, "Enemigo");
			free(tmp);
			return;
			break;
	}

	tmp->siguiente = lista_enemigos;
	lista_enemigos = tmp;
}


/*!
 * \brief Genera el Protagonista del nivel
 * \author Hugo Ruscitti
 */
void Procesos :: crear_protagonista (int x, int y, int flip)
{
	if (protagonista)
		printf("Error, ya existe un protagonista en el nivel\n");
	else
		protagonista = new Protagonista (juego, x, y, flip);
}


/*!
 * \brief Genera un nuevo Item del nivel
 * \author Hugo Ruscitti
 */
void Procesos :: crear_item (int x, int y, int flip)
{
	struct nodo * tmp;

	tmp = (struct nodo *) malloc (sizeof(struct nodo));
	tmp->obj = new class Item (juego, x, y, flip);
	
	printf("Creando un Item en (%d, %d)\n", x, y);

	tmp->siguiente = lista_items;
	lista_items = tmp;
}


/*!
 * \brief Elimina todos los nodos de la lista
 * \author Hugo Ruscitti
 */
void Procesos :: borrar_lista (struct nodo * lista)
{
	struct nodo *borrar;

	while (lista)
	{
		borrar = lista;
		lista = lista->siguiente;

		borrar_nodo(borrar);
	}
}


/*!
 * \brief Elimina un nodo de la lista de Procesos
 * \author Hugo Ruscitti
 */
void Procesos :: borrar_nodo (struct nodo * nodo)
{
	delete nodo->obj;
	free(nodo);

	printf("borrando nodo\n");
}



/*!
 * \brief Verifica si 2 objetos colisionan
 * \author Hugo Ruscitti
 */
bool Procesos :: hay_colision (int x0, int y0, int x1, int y1, int radio)
{
	if ((abs(x0 - x1) <  (radio * 2)) && (abs(y0 - y1) < (radio *2)))
		return true;
	else
		return false;
}


/*!
 * \brief Elimina de la lista a objeto Actor con estado _QUITAR
 * \author Hugo Ruscitti
 */
void Procesos :: eliminar_antiguos (struct nodo ** lista)
{
	struct nodo * anterior = NULL;
	struct nodo * leer;
	struct nodo * borrar;

	leer = *lista;

	while (leer)
	{
		if (leer->obj->get_estado() == _QUITAR)
		{
			if (anterior != NULL)
				anterior->siguiente = leer->siguiente;
			else
				*lista = leer->siguiente;

			borrar = leer;
			leer = leer->siguiente;
			borrar_nodo(borrar);
		}
		else
		{
			anterior = leer;
			leer = leer->siguiente;
		}
	}
}
