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


#include <SDL/SDL_image.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Imagen.h"

/*!
 * \brief Carga una grilla con cuadros de animación
 * \author Hugo Ruscitti
 */
Imagen :: Imagen (char *ruta, int fil, int col, int x0, int y0, bool alpha)
{
	Uint32 colorkey;
	char tmp_ruta[1024] = DATADIR "ima/";

	this->fil = fil;
	this->col = col;
	
	strcat(tmp_ruta, ruta);
	printf("+ Cargando: %s\n", ruta);

	ima = IMG_Load(tmp_ruta);

	if (ima == NULL)
	{
		printf("Error: %s\n", SDL_GetError());
		exit(1);
	}

	if (!alpha)
	{
		SDL_Surface *tmp = ima;
		
		ima = SDL_DisplayFormat(tmp);
		SDL_FreeSurface(tmp);

		if (ima == NULL)
		{
			printf("Error: %s\n", SDL_GetError());
			exit(1);
		}

		colorkey = SDL_MapRGB(ima->format, 255, 0, 255);
		SDL_SetColorKey(ima, SDL_SRCCOLORKEY, colorkey);
	}

	ima_flip = invertir_imagen(ima);

	if (ima_flip == NULL)
	{
		printf("Error: no se puede copiar la superficie\n");
		exit(1);
	}
	
	bloque_ancho = ima->w / col;
	bloque_alto = ima->h / fil;

	this->x0 = x0;
	this->y0 = y0;
}

/*!
 * \brief Destructor del objeto
 * \author Hugo Ruscitti
 */
Imagen :: ~Imagen ()
{
	SDL_FreeSurface(ima);
	SDL_FreeSurface(ima_flip);
	printf("- Descargando imagen.\n");
}

/*!
 * \brief Imprime un grafico sobre dst
 * \author Hugo Ruscitti
 */
void Imagen :: imprimir (SDL_Surface *dst, int i, int x, int y, int flip)
{
	SDL_Rect srcrect;
	SDL_Rect dstrect = {x - x0, y - y0, 0, 0};

	if (i > (fil * col) || i < 0)
	{
		printf("Imagen::imprimir = no existe el cuadro %d\n", i);
		return;
	}
	
	srcrect.w = bloque_ancho - 2;
	srcrect.h = bloque_alto - 2;

	switch (flip)
	{
		case 1:
			srcrect.x = ((i % col) * bloque_ancho) + 2;
			srcrect.y = ((i / col) * bloque_alto) + 2;
			
			SDL_BlitSurface(ima, &srcrect, dst, &dstrect);
			break;

		case -1:
			srcrect.x = ((col-1) - (i%col)) * bloque_ancho + 1;
			srcrect.y = (i / col) * bloque_alto + 2;

			SDL_BlitSurface(ima_flip, &srcrect, dst, &dstrect);
			break;

		default:
			printf("flip = %d no es válido \n", flip);
			break;
	}
}

/*!
 * \brief Genera una imágen invertida horizontalmente
 *
 * \author Hugo Ruscitti
 */
SDL_Surface * Imagen :: invertir_imagen (SDL_Surface *imagen)
{
	SDL_Rect srcrect = {0, 0, 1, imagen->h};
	SDL_Rect dstrect = {imagen->w, 0, 1, imagen->h};
	SDL_Surface *ret;

	ret = SDL_DisplayFormat (imagen);

	if (ret == NULL)
	{
		printf("I can't copy surface in 'invertir_imagen'\n");
		return NULL;
	}

	SDL_FillRect(ret, NULL, SDL_MapRGB(ret->format, 255, 0, 255));

	for (int delta = 0; delta < imagen->w; delta ++)
	{
		SDL_BlitSurface(imagen, &srcrect, ret, &dstrect);
		srcrect.x ++;
		dstrect.x --;
	}

	return ret;
}
