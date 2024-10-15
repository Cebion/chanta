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
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include "Nivel.h"
#include "Procesos.h"
#include "Mundo.h"
#include "Protagonista.h"
#include "Juego.h"
#include "Imagen.h"
#include "Galeria.h"


/*!
 * \brief Constructor
 * \author Hugo Ruscitti
 * 
 * \param filas limite de filas del scroll
 * \param columnas limite de columnas para el scroll
 */
Nivel :: Nivel (class Mundo *mundo, int filas, int columnas)
{
	printf("\t\tNivel :: Nivel ()\n");
	this->mundo = mundo;
	this->tiles = mundo->galeria->get_imagen(TILES);
	this->filas = filas;
	this->columnas = columnas;
	
	indice_nivel = 0;
	archivo = NULL;
	modificado = false;
	camara = new Camara (filas, columnas);

	abrir_archivo ();
	cargar();
}

/*!
 * \brief Destructor
 * \author Hugo Ruscitti
 */
Nivel :: ~Nivel (void)
{
	printf("\t\tNivel :: ~Nivel ()\n");
	delete camara;
	cerrar_archivo ();
}


/*!
 * \brief imprimie todos los bloques del nivel
 * \author Hugo Ruscitti
 */
void Nivel :: imprimir (SDL_Surface *dst)
{
	int lx; // columna que se lee desde mapa
	int ly; // fila que se lee desde mapa
	int margen_x; // zona que se pierde al imprimir el primer tile
	int margen_y; // zona que se pierde al imprimir el primer tile
	int cant_x; // bloques a imprimir sobre x
	int cant_y; // bloques a imprimir sobre y
	char bloque;

	ly = camara->get_y() / 32;
	lx = camara->get_x() / 32;
	margen_y = camara->get_y() % 32;
	margen_x = camara->get_x() % 32;

	(margen_x == 0)? cant_x = columnas: cant_x = columnas + 1;
	(margen_y == 0)? cant_y = filas: cant_y = filas + 1;

	for (int col = 0; col < cant_x; col ++)
	{
		for (int fil = 0; fil < cant_y; fil ++)
		{
			bloque = mapa[fil + ly][col + lx];

			if (bloque != -1 && bloque < 36)
			{
				tiles->imprimir(dst, bloque,\
						col * 32 - margen_x,\
						fil * 32 - margen_y, 1);
			}
		}
	}
}


/*!
 * \brief Imprime los objetos Actor completos, en lugar de un bloque de 32x32px
 * \author Hugo Ruscitti
 */
void Nivel :: imprimir_actores (SDL_Surface *dst)
{
	int lx; // columna que se lee desde mapa
	int ly; // fila que se lee desde mapa
	int margen_x; // zona que se pierde al imprimir el primer tile
	int margen_y; // zona que se pierde al imprimir el primer tile
	int cant_x; // bloques a imprimir sobre x
	int cant_y; // bloques a imprimir sobre y
	char bloque;
	class Imagen *ima_tmp;
	enum codigo_imagen tmp;
	int x0, y0;

	ly = camara->get_y() / 32;
	lx = camara->get_x() / 32;
	margen_y = camara->get_y() % 32;
	margen_x = camara->get_x() % 32;

	(margen_x == 0)? cant_x = columnas: cant_x = columnas + 1;
	(margen_y == 0)? cant_y = filas: cant_y = filas + 1;

	for (int col = 0; col < cant_x; col ++)
	{
		for (int fil = 0; fil < cant_y; fil ++)
		{
			bloque = mapa[fil + ly][col + lx];

			if (bloque > 35 && bloque < 45)
			{
				switch (bloque)
				{
					case 36:
						x0 = 16;
						y0 = 32;
						tmp = ENEMIGO1;
						break;

					case 42:
						x0 = 0;
						y0 = 0;
						tmp = IMA_ITEM;
						break;
						
					case 44:
						x0 = 16;
						y0 = 32;
						tmp = CHANTA;
						break;

					default:
						tmp = TILES; // temporal
						break;
				}

				if (tmp != TILES) // temporal
				{
					ima_tmp = mundo->galeria->get_imagen(tmp);
					ima_tmp->imprimir(dst, 0,\
						col * 32 - margen_x + x0,\
						fil * 32 - margen_y + y0, 1);
				}
			}
		}
	}

}


/*!
 * \brief actualiza la posicion de la cámara
 * \author Hugo Ruscitti
 */
void Nivel :: actualizar (void)
{
	camara->actualizar();
}



/*!
 * \brief Informa la distancia (en pixeles) hasta el suelo
 * \author Hugo Ruscitti
 * \return (< rango) la distancia al suelo, (= rango) no encontró el suelo
 */
int Nivel :: get_distancia_al_suelo (int x, int y, int rango)
{
	int delta;
	int fila;
	int columna;

	if (x < 0 || x >= 640*2 || y < 0 || y >= 480*2)
		return rango;

	for (delta = 0; delta < rango; delta ++)
	{
		columna = x / 32;
		fila = (y + delta) / 32;
		
		if ((y + delta) %32 == 0 && es_solido(mapa[fila][columna]))
			return delta;
	}

	return rango;
}

/*!
 * \brief informa si un bloque del mapa es sólido
 * \author Hugo Ruscitti
 */
bool Nivel :: es_solido (char codigo)
{
	if (codigo >= 0 && codigo <= 5 || codigo >= 30 && codigo <= 35)
		return true;
	else
		return false;
}


/*!
 * \brief Altera un bloque del nivel
 * \author Hugo Ruscitti
 * 
 * \param i nuevo bloque, asigne -1 para borrar el bloque.
 * \param x posición horizontal relativa a la ventana (no tiene scroll).
 * \param y posición vertical relativa a la ventana (no tiene scroll).
 */
void Nivel :: editar_bloque (int i, int x, int y)
{
	int fila_destino = (y + camara->get_y()) / 32;
	int columna_destino = (x + camara->get_x()) / 32;

	mapa[fila_destino][columna_destino] = i;

	modificado = true;
}


/*!
 * \brief Guarda los cambios del Nivel desde el archivo de niveles
 * \author Hugo Ruscitti
 */
void Nivel :: guardar (void)
{
	char nombre [1024] = "";
	FILE * salida;

	if (! modificado)
	{
		printf("El nivel no fué modificado, cancelando la grabación\n");
		return;
	}

	ruta_base (nombre);

	salida = fopen (nombre, "rb+");

	if (salida == NULL)
	{
		salida = crear_archivo ();

		if (salida == NULL)
		{
			printf("No se pueden guardar los cambios del nivel.\n");
			return;
		}
		
	}

	if (fseek(salida, 30 * 40 * indice_nivel, SEEK_SET))
	{
		printf ("Error en el archivo %s\n", nombre);
		fclose (salida);
		return;
	}
	else
	{
		if (fwrite(&mapa, sizeof(char), 30 * 40, salida) < 30 * 40)
		{
			printf("Falló la grabación del archivo %s\n", nombre);
			fclose (salida);
			return;
		}
	}

	modificado = false;

	printf("Guardando los cambios del nivel en %s\n", nombre);
	printf("Intercambiando los archivos personalizado y original\n");

	fclose(archivo);

	fflush(salida);
	archivo = salida;
}



/*!
 * \brief Recupera los bloques desde el archivo de niveles
 * \author Hugo Ruscitti
 * \return 0 en caso de éxito y 1 si no existe ese numero de nivel
 */
int Nivel :: cargar (void)
{
	if (fseek(archivo, 30 * 40 * indice_nivel, SEEK_SET))
	{
		printf("No se puede acceder al nivel %d\n", indice_nivel);
		return 1;
	}
	else
	{
		if (fread(&mapa, sizeof(char), 30 * 40, archivo) < 30 * 40)
		{
			printf("No se puede cargar el nivel %d\n", indice_nivel);
			return 1;
		}
	}

	return 0;
}


/*!
 * \brief Borra el contenido de todo el nivel
 * \author Hugo Ruscitti
 */
void Nivel :: limpiar (void)
{
	memset(mapa, -1, 30 * 40);
}



/*!
 * \brief Selecciona el siguiente nivel
 * \author Hugo Ruscitti
 */
void Nivel :: siguiente (void)
{
	indice_nivel ++;

	if (cargar())
		indice_nivel --;
}


/*!
 * \brief Selecciona un nivel anterior
 * \author Hugo Ruscitti
 */
void Nivel :: anterior (void)
{
	if (indice_nivel > 0)
	{
		indice_nivel --;
		cargar();
	}
}

/*!
 * \brief Genera los actores en base a la información del Nivel
 * \author Hugo Ruscitti
 */
void Nivel :: generar_actores (class Procesos * procesos)
{
	int bloque;
	int x;
	int y;
	
	for (int col = 0; col < 40; col ++)
	{
		for (int fil = 0; fil < 30; fil ++)
		{
			bloque = mapa[fil][col];
			
			x = (col * 32) + 16;
			y = (fil * 32) + 32;
			
			switch (bloque)
			{
				case 36:
					procesos->crear_enemigo(1, x, y, 1);
					break;

				case 42:
					procesos->crear_item(x, y, 1);
					break;

				case 44:
					procesos->crear_protagonista(x, y, 1);
					break;
					
				default:
					break;
			}
		}
	}

}


/*!
 * \brief Abre el archivo de niveles personalizados, o bien, los predefinidos
 * \author Hugo Ruscitti
 */
void Nivel :: abrir_archivo (void)
{
	char nombre [1024] = "";

	ruta_base (nombre);

	archivo = fopen (nombre, "rb");

	if (archivo == NULL)
		archivo = fopen (DATADIR "data/niveles.dat", "rb");
	else
		printf("Abriendo niveles personalizados: %s\n", nombre);
}


/*!
 * \brief cierra el archivo de niveles
 * \author Hugo Ruscitti
 */
void Nivel :: cerrar_archivo (void)
{
	if (archivo)
	{
		fclose (archivo);
		archivo = NULL;
	}
	else
	{
		printf("Error en %s, el archivo ya estaba cerrado\n", "Nivel");
	}

	printf("Cerrando el archivo\n");
}

/*!
 * \brief Genera el archivo de niveles personalizado por el usuario
 * \author Hugo Ruscitti
 */
FILE * Nivel :: crear_archivo (void)
{
	char nombre [1024] = "";
	FILE * tmp;

#ifndef WIN32
	char * base = getenv("HOME");
	
	strcpy(nombre, base);
	strcat(nombre, "/.chanta/");

	if (mkdir(nombre, 0777) == -1 && errno != EEXIST)
	{
		printf("No se puede guardar el nivel en: %s\n", nombre);
		exit(-1);
	}

	ruta_base(nombre);
#else
	strcpy(nombre, DATADIR "data/niveles.dat");
#endif

	tmp = fopen (nombre, "wb+");

	if (tmp == NULL)
		printf("Falló la creación del archivo de niveles %s\n", nombre);
	else
	{
		copiar_archivo (tmp);
		printf("Creando el archivo de niveles %s\n", nombre);
	}

	return tmp;
}


/*!
 * \brief informa la ruta hacia el archivo personalizado de niveles
 * \author Hugo Ruscitti
 */
void Nivel :: ruta_base (char * destino)
{
#ifndef WIN32
	char * base = getenv("HOME");

	strcpy(destino, base);
	strcat(destino, "/.chanta/niveles.dat");
#else
	strcpy(destino, DATADIR "data/niveles.dat");
#endif
}


/*!
 * \brief Copia el archivo por defecto sobre el nivel personalizado
 * \author Hugo Ruscitti
 */
void Nivel :: copiar_archivo (FILE * tmp)
{
	char mapa_tmp[30][40];
	int size = 30 * 40;
	int i;
	
	for (i = 0; i < 40; i ++)
	{
		fseek (archivo, i * size, SEEK_SET);
		fseek (tmp, i * size, SEEK_SET);
		
		fread (mapa_tmp, size, 1, archivo);
		fwrite (mapa_tmp, size, 1, tmp);
	}

	printf("Copiando el archivo por defecto al nivel personalizado\n");
}
