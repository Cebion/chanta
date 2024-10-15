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


#include "Protagonista.h"
#include "Juego.h"
#include "Controles.h"
#include "Galeria.h"
#include "Mundo.h"
#include "Nivel.h"
#include "Imagen.h"
#include "Animacion.h"

/*!
 * \brief inicializa el protagonista del juego
 * \author Hugo Ruscitti
 */
Protagonista :: Protagonista (class Juego *juego, int x, int y, int flip) : Actor (juego, x, y, flip)
{
	this->juego = juego;
	this->controles = &(juego->mundo->controles);
	
	printf("\t\tProtagonista :: Protagonista\n");
	
	ima = juego->mundo->galeria->get_imagen(CHANTA);

	animaciones[PARADO] = new Animacion("0", 5);
	animaciones[CAMINAR] = new Animacion("2,3,4,5,6,7,8,9,10,11,12,13", 5);
	animaciones[SALTAR] = new Animacion("18,19", 0);
	animaciones[DISPARAR] = new Animacion("14, 15, 16", 10);
	animaciones[MORIR] = new Animacion("21, 22", 10);

	x_inicial = x;
	y_inicial = y;
	
	reiniciar ();
}


/*!
 * \brief Destructor 
 * \author Hugo Ruscitti
 */
Protagonista :: ~Protagonista ()
{
	delete animaciones[PARADO];
	delete animaciones[CAMINAR];
	delete animaciones[SALTAR];
	delete animaciones[DISPARAR];
	delete animaciones[MORIR];
	
	printf("\t\tProtagonista :: ~Protagonista\n");
}


/*!
 * \brief Actualización Lógica
 * \author Hugo Ruscitti
 */
void Protagonista :: actualizar (void)
{
	juego->nivel->camara->set_pos(x - 320, y - 240);
	
	if (estado != estado_anterior)
	{
		animaciones[estado]->reiniciar();
		estado_anterior = estado;
	}

	switch (estado)
	{
		case PARADO:
			estado_parado();
			break;

		case CAMINAR:
			estado_caminar();
			break;

		case DISPARAR:
			estado_disparar();
			break;

		case SALTAR:
			estado_saltar();
			break;

		case MORIR:
			estado_morir();
			break;
			
		default:
			printf("Error, estado no contemplado\n");
			break;
	}

}



/*!
 * \brief gestiona el estado PARADO
 * \author Hugo Ruscitti
 */
void Protagonista :: estado_parado (void)
{
	if (controles->pulso(TECLA_IZQUIERDA))
	{
		flip = -1;
		estado = CAMINAR;
	}

	if (controles->pulso(TECLA_DERECHA))
	{
		flip = 1;
		estado = CAMINAR;
	}

	if (controles->pulso(TECLA_DISPARAR))
		estado = DISPARAR;

	if (controles->pulso(TECLA_SALTAR))
	{
		velocidad_salto = -5;
		estado = SALTAR;
	}
}


/*!
 * \brief gestiona el estado CAMINAR
 * \author Hugo Ruscitti
 */
void Protagonista :: estado_caminar (void)
{
	animaciones[estado]->avanzar();

	mover_sobre_x(flip*2);
	
	if (flip == 1 && ! controles->pulso(TECLA_DERECHA))
		estado = PARADO;

	if (flip == -1 && ! controles->pulso(TECLA_IZQUIERDA))
		estado = PARADO;

	if (controles->pulso(TECLA_DISPARAR))
		estado = DISPARAR;

	if (controles->pulso(TECLA_SALTAR))
	{
		velocidad_salto = -5;
		estado = SALTAR;
	}

	if (! pisa_el_suelo())
	{
		velocidad_salto = 0;
		estado = SALTAR;
	}
}


/*!
 * \brief gestiona el estado DISPARAR
 * \author Hugo Ruscitti
 */
void Protagonista :: estado_disparar (void)
{
	if (animaciones[estado]->avanzar())
		estado = PARADO;
}


/*!
 * \brief gestiona el estado SALTAR
 * \author Hugo Ruscitti
 */
void Protagonista :: estado_saltar (void)
{
	velocidad_salto += 0.1;
	
	if (controles->pulso(TECLA_IZQUIERDA))
	{
		flip = -1;
		mover_sobre_x(flip*2);
	}

	if (controles->pulso(TECLA_DERECHA))
	{
		flip = 1;
		mover_sobre_x(flip*2);
	}

	if (velocidad_salto > 0.0)
	{
		y += distancia_al_suelo ((int) velocidad_salto);

		// cambia el cuadro de animación solo cuando cae
		if (animaciones[estado]->es_primer_cuadro())
			animaciones[estado]->avanzar();
		
		if (velocidad_salto >= 1.0 && pisa_el_suelo())
			estado = PARADO;

		if (y > 480*2)
		{
			estado = MORIR;
			velocidad_salto = -5;
		}
	}
	else
	{
		y += (int) velocidad_salto;
	}
}


/*!
 * \brief gestiona el estado MORIR
 * \author Hugo Ruscitti
 */
void Protagonista :: estado_morir (void)
{
	velocidad_salto += 0.1;
	y += (int) velocidad_salto;
	
	mover_sobre_x(flip*2*-1);
	
	animaciones[estado]->avanzar();
	
	if (y > 480*2 + 200)
		reiniciar();
}


/*!
 * \brief Le informan que colisiona con un actor (siempre enemigo en este caso)
 * \author Hugo Ruscitti
 */
void Protagonista :: colisiona_con (class Actor *otro)
{
	if (estado != MORIR)
	{
		estado = MORIR;
		velocidad_salto = -5;
	}
}


/*!
 * \brief Retoma su estado y posicion inicial
 * \author Hugo Ruscitti
 */
void Protagonista :: reiniciar (void)
{
	x = x_inicial;
	y = y_inicial;
	flip = 1;

	estado = PARADO;
	velocidad_salto = 0;
	estado_anterior = estado;
}
