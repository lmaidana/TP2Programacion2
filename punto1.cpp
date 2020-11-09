// Este ejercicio lo hice con argc y argv en el main pero al menos en visual studio code tuve que ejecutar por terminal y no sabía si entregarlo así, por lo que decidí hacer el ejercicio para matematicas.dat unicamente //
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define FORMATO_LEGAJO "Legajo: %d\n"
#define FECHA_NOTA "\tFecha:%hhd/%hhd/%d\tNota: %.2f \n"

const int MAX_RUTA = 100;
const int MAX_CARACTERES = 31;
const int MAX_REGISTRO = 200;

typedef struct Alumno
{
  int legajo;
  char carrera;
  char nombre[MAX_CARACTERES];
  char apellido[MAX_CARACTERES];
  char email[MAX_CARACTERES];
  char telefono[11];
} STR_ALUMNO;

typedef struct Carrera
{
  char codigo;
  char nombre[MAX_CARACTERES];
  char descripcion[MAX_CARACTERES];
} STR_CARRERA;

typedef struct Materia
{
  int legajo;
  int fecha;
  float nota;
} STR_MATERIA;

typedef struct Promedio
{
  int legajo;
  float promedio;
} STR_PROMEDIO;

typedef struct Fecha
{
  unsigned char dia;
  unsigned char mes;
  unsigned short year;
} STR_FECHA;

typedef struct Dato
{
  int legajo;
  int pos;
} STR_DATO;

typedef struct Nodo
{
  STR_DATO dato;
  Nodo *siguiente;
} STR_NODO;

FILE *abrir(const char *fileName, const char *modo);
void cerrar(FILE *file);
size_t leer(STR_MATERIA *registro, FILE *file);
size_t escribir(STR_MATERIA registro, FILE *file);
size_t readAt(FILE *file, STR_MATERIA *registro, int posicion);
STR_FECHA obtenerFecha(int formatoFecha);
void tokenNull(const char *token, FILE *texto, FILE *binario);
void textoBinario(const char *rutaTexto, const char *rutaBinaria, const char *separadores);
void binarioTexto(const char *rutaTexto, const char *rutaBinaria);
void create(STR_NODO **lista);
bool isEmpty(STR_NODO *lista);
STR_NODO *insertOrdered(STR_DATO valor, STR_NODO **lista);
void print(STR_NODO *lista);
void printDato(STR_DATO dato);
void clearList(STR_NODO **lista);
STR_DATO deleteFirst(STR_NODO **lista);
int count(STR_NODO *listaAux);

int main()
{
  // textoBinario("matematica.txt", "matematica.dat", ";\n");
  // binarioTexto("promediosMatematicaTraducido.txt", "matematica.dat");
  FILE *materia = abrir("matematica.dat", "rb");
  FILE *promedios = abrir("promediosMatematica.dat", "wb");
  STR_MATERIA unRegistro, unAlumno;
  STR_FECHA fecha;
  STR_PROMEDIO alumno;
  STR_DATO dato;
  STR_NODO *lista;
  create(&lista);
  int posicion = 0;
  int cantNodos = 0;
  int i = 0;

  leer(&unRegistro, materia);
  while (!feof(materia))
  {
    dato.legajo = unRegistro.legajo;
    dato.pos = posicion;
    posicion++;
    insertOrdered(dato, &lista);
    leer(&unRegistro, materia);
  }
  cantNodos = count(lista);

  if (!isEmpty(lista))
  {
    dato = deleteFirst(&lista);
    readAt(materia, &unRegistro, dato.pos);
    while (i < cantNodos)
    {
      alumno.promedio = 0;
      unAlumno.legajo = unRegistro.legajo;
      printf(FORMATO_LEGAJO, unAlumno.legajo);
      while (i < cantNodos && unAlumno.legajo == dato.legajo)
      {
        fecha = obtenerFecha(unRegistro.fecha);
        printf(FECHA_NOTA, fecha.dia, fecha.mes, fecha.year, unRegistro.nota);
        alumno.promedio += unRegistro.nota;
        alumno.legajo = unRegistro.legajo;
        if (!isEmpty(lista))
        {
          dato = deleteFirst(&lista);
          readAt(materia, &unRegistro, dato.pos);
        }
        i++;
      }
      alumno.promedio = alumno.promedio / 2;
      fwrite(&alumno, sizeof(STR_PROMEDIO), 1, promedios);
    }
  }

  cerrar(materia);
  cerrar(promedios);
  clearList(&lista);
  return 0;
}

void create(STR_NODO **lista)
{
  *lista = NULL;
  return;
}

bool isEmpty(STR_NODO *lista)
{
  return lista == NULL;
}

STR_NODO *insertOrdered(STR_DATO valor, STR_NODO **lista)
{
  STR_NODO *nodo = (STR_NODO *)malloc(sizeof(STR_NODO));
  if (nodo)
  {
    nodo->dato = valor;
    nodo->siguiente = NULL;

    STR_NODO *listaAux = *lista;
    STR_NODO *nodoAnt = NULL;
    while (listaAux != NULL && listaAux->dato.legajo < valor.legajo)
    {
      nodoAnt = listaAux;
      listaAux = listaAux->siguiente;
    }

    if (nodoAnt == NULL)
    {
      *lista = nodo;
    }
    else
    {
      nodoAnt->siguiente = nodo;
    }

    nodo->siguiente = listaAux;
  }

  return nodo;
}

void print(STR_NODO *lista)
{
  STR_NODO *listaAux;
  listaAux = lista;
  printf("POSICION\t\tLEGAJO\n");
  while (listaAux != NULL)
  {
    printf("%d\t\t%d\n", listaAux->dato.pos, listaAux->dato.legajo);
    listaAux = listaAux->siguiente;
  }
}

void clearList(STR_NODO **lista)
{
  STR_NODO *aux = NULL;
  while (*lista != NULL)
  {
    aux = *lista;
    *lista = (*lista)->siguiente;
    free(aux);
  }
}

STR_DATO deleteFirst(STR_NODO **lista)
{
  STR_DATO dato = (*lista)->dato;
  STR_NODO *aux = *lista;
  *lista = (*lista)->siguiente;
  free(aux);
  return dato;
}

int count(STR_NODO *listaAux)
{
  int cant = 0;
  while (listaAux != NULL)
  {
    listaAux = listaAux->siguiente;
    cant++;
  }

  return cant;
}

FILE *abrir(const char *fileName, const char *modo)
{
  FILE *file = fopen(fileName, modo);
  if (file == NULL)
  {
    fprintf(stderr, "No se pudo abrir el archivo: %s", fileName);
    exit(EXIT_FAILURE);
  }

  return file;
}

void cerrar(FILE *file)
{
  fclose(file);
  file = NULL;
}

size_t leer(STR_MATERIA *registro, FILE *file)
{
  return fread(registro, sizeof(STR_MATERIA), 1, file);
}
size_t escribir(STR_MATERIA registro, FILE *file)
{
  return fwrite(&registro, sizeof(STR_MATERIA), 1, file);
}

size_t readAt(FILE *file, STR_MATERIA *registro, int posicion)
{
  fseek(file, sizeof(STR_MATERIA) * posicion, SEEK_SET);
  return fread(registro, sizeof(STR_MATERIA), 1, file);
}

STR_FECHA obtenerFecha(int formatoFecha)
{
  STR_FECHA fecha;
  fecha.dia = (unsigned char)((formatoFecha % 10000) % 100);
  fecha.mes = (unsigned char)((formatoFecha % 10000) / 100);
  fecha.year = (unsigned short)(formatoFecha / 10000);
  return fecha;
}

void tokenNull(const char *token, FILE *texto, FILE *binario)
{

  if (token == NULL)
  {
    printf("Fallo parseo.\n");
    cerrar(texto);
    cerrar(binario);
    exit(EXIT_FAILURE);
  }
  return;
}

//TXT A BIN:

void textoBinario(const char *rutaTexto, const char *rutaBinaria, const char *separadores)
{

  FILE *texto = fopen(rutaTexto, "r");
  if (!texto)
  {
    printf("No se pudo abrir el archivo de texto \n");
    return;
  }
  FILE *binario = fopen(rutaBinaria, "wb");
  if (!binario)
  {
    fclose(texto);
    printf("No se pudo crear el archivo binario \n");
    return;
  }
  STR_MATERIA unRegistro;

  char linea[MAX_REGISTRO];
  char *token = NULL;

  while (fgets(linea, MAX_REGISTRO - 1, texto) != NULL)
  {
    token = strtok(linea, separadores);
    tokenNull(token, texto, binario);
    unRegistro.legajo = atoi(token);

    token = strtok(NULL, separadores);
    tokenNull(token, texto, binario);
    unRegistro.fecha = atoi(token);

    token = strtok(NULL, separadores);
    tokenNull(token, texto, binario);
    unRegistro.nota = (float)atof(token);

    fwrite(&unRegistro, sizeof(STR_MATERIA), 1, binario);
  }

  fclose(texto);
  fclose(binario);
  texto = NULL;
  binario = NULL;
  if (token != NULL)
  {
    token = NULL;
  }
  return;
}

//BIN A TXT:

////al igual con la anterior debo modificar el struct cada vez que quiera reutilizarla, y el formato global
void binarioTexto(const char *rutaTexto, const char *rutaBinaria)
{

  FILE *texto = fopen(rutaTexto, "w");
  if (!texto)
  {
    printf("No se pudo crear el archivo de texto \n");
    return;
  }
  FILE *binario = fopen(rutaBinaria, "rb");
  if (!binario)
  {
    fclose(texto);
    printf("No se pudo abrir el archivo binario \n");
    return;
  }

  STR_PROMEDIO unRegistro; //aca modificar
  fread(&unRegistro, sizeof(STR_PROMEDIO), 1, binario);
  while (!feof(binario))
  {
    fprintf(texto, " \t%d\t%f", unRegistro.legajo, unRegistro.promedio);
    fread(&unRegistro, sizeof(STR_PROMEDIO), 1, binario);
  }
  fclose(texto);
  fclose(binario);
  texto = NULL;
  binario = NULL;
  return;
}
