#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_RUTA = 100;
const int MAX_CARACTERES = 31;
const int MAX_TEL = 100;
const int MAX_LINEA = 200;

typedef struct Alumno
{
  int legajo;
  char carrera;
  char nombre[MAX_CARACTERES];
  char apellido[MAX_CARACTERES];
  char email[MAX_CARACTERES];
  char telefono[MAX_CARACTERES];
} STR_ALUMNO;

typedef struct Carrera
{
  int codigo_carrera;
  char nombre[MAX_CARACTERES];
  char descripcion_carrera[MAX_CARACTERES];
} STR_CARRERA;

typedef struct Materia
{
  int legajo;
  int fecha; //AAAAMMDD
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
  int pos; //en archivo fseek
} STR_DATO;

typedef struct Nodo
{
  STR_DATO dato;
  Nodo *siguiente;
} STR_NODO;

//Funciones de archivos
FILE *abrir(const char *fileName, const char *modo);
void cerrar(FILE *file);
size_t leer(STR_MATERIA *registro, FILE *file);
size_t escribir(STR_MATERIA registro, FILE *file);

//Otras funciones
STR_FECHA obtenerFecha(int formatoFecha);
void binarioTexto(const char *rutaTexto, const char *rutaBinaria);

// Funcriones de lista
void create(STR_NODO **lista);
bool isEmpty(STR_NODO *lista);
STR_NODO *insertInFront(STR_DATO valor, STR_NODO **lista);
STR_NODO *insertAtEnd(STR_DATO valor, STR_NODO **lista);
STR_NODO *insertOrdered(STR_DATO valor, STR_NODO **lista);
void print(STR_NODO *lista);
void clearList(STR_NODO **lista);
STR_NODO *search(STR_NODO *lista, STR_DATO valor);
STR_DATO deleteFirst(STR_NODO **lista);
void sort(STR_NODO **lista);
int count(STR_NODO *listaAux);
size_t readAt(FILE *file, STR_MATERIA *registro, int posicion);

//Otras funciones
void tokenNull(const char *token, FILE *texto, FILE *binario);
void textoBinario(const char *rutaTexto, const char *rutaBinaria, const char *separadores);

// int main() //int argc, char *argv[]
// {
//   // if (argc < 7)
//   // {
//   //   printf("No ingresaste la ruta del archivo <materia>.dat");
//   //   exit(EXIT_FAILURE);
//   // }
//   char rutaPromedio[MAX_RUTA] = "promedios";
//   strcat(rutaPromedio, "fisica.dat");

//   FILE *materia = abrir("fisica.dat", "rb");
//   FILE *promedios = abrir(rutaPromedio, "wb");
//   STR_MATERIA unaMateria, alumnoActual;
//   STR_FECHA fecha;
//   STR_PROMEDIO alumno;
//   STR_DATO dato;
//   STR_NODO *lista;
//   create(&lista);
//   int pos = 0;

//   leer(&unaMateria, materia);
//   while (!feof(materia))
//   {
//     dato.legajo = unaMateria.legajo;
//     dato.pos = pos;
//     pos++;
//     insertOrdered(dato, &lista);
//     leer(&unaMateria, materia);
//   }
//   if (!isEmpty(lista))
//   {
//     dato = deleteFirst(&lista);
//     readAt(materia, &unaMateria, dato.pos);
//     while (lista != NULL)
//     {
//       alumno.promedio = 0;
//       alumnoActual.legajo = unaMateria.legajo;
//       printf("\tLegajo: %d\n", alumnoActual.legajo);
//       while (lista != NULL && alumnoActual.legajo == dato.legajo)
//       {
//         fecha = obtenerFecha(unaMateria.fecha);
//         printf("\t\t\tFecha:%hhd/%hhd/%d\tNota: %.2f  \n", fecha.dia, fecha.mes, fecha.year, unaMateria.nota);
//         alumno.promedio += unaMateria.nota;
//         alumno.legajo = unaMateria.legajo;
//         if (!isEmpty(lista))
//         {
//           dato = deleteFirst(&lista);
//           readAt(materia, &unaMateria, dato.pos);
//         }
//       }
//       alumno.promedio = alumno.promedio / 2;
//       fwrite(&alumno, sizeof(STR_PROMEDIO), 1, promedios);
//     }
//   }

//   cerrar(materia);
//   cerrar(promedios);
//   //   clearList(&lista);
//   return 0;
// }

int main()
{
  binarioTexto("fisicaTraducida.txt", "fisica.dat");
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

STR_NODO *insertInFront(STR_DATO valor, STR_NODO **lista)
{
  STR_NODO *nodo = (STR_NODO *)malloc(sizeof(STR_NODO));
  nodo->dato = valor;
  nodo->siguiente = *lista;

  *lista = nodo;
  return nodo;
}

STR_NODO *insertAtEnd(STR_DATO valor, STR_NODO **lista)
{
  STR_NODO *nodo = (STR_NODO *)malloc(sizeof(STR_NODO));
  nodo->dato = valor;
  nodo->siguiente = NULL;

  if (isEmpty(*lista))
  {
    *lista = nodo;
  }
  else
  {
    STR_NODO *listaAux = *lista;
    while (listaAux->siguiente != NULL)
    {
      listaAux = listaAux->siguiente;
    }
    listaAux->siguiente = nodo;
  }

  return nodo;
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

STR_NODO *search(STR_NODO *lista, STR_DATO valor)
{
  STR_NODO *listaAux = lista;
  while (listaAux != NULL && listaAux->dato.legajo != valor.legajo)
  {
    listaAux = listaAux->siguiente;
  }
  return listaAux;
}

STR_DATO deleteFirst(STR_NODO **lista)
{
  STR_DATO dato = (*lista)->dato;
  STR_NODO *aux = *lista;
  *lista = (*lista)->siguiente;
  free(aux);
  return dato;
}

void sort(STR_NODO **lista)
{
  STR_NODO *listaAux;
  create(&listaAux);
  STR_DATO dato;
  while (*lista != NULL)
  {
    dato = deleteFirst(lista);
    insertOrdered(dato, &listaAux);
  }

  *lista = listaAux;
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
  fseek(file, sizeof(STR_ALUMNO) * posicion, SEEK_SET);
  return fread(registro, sizeof(STR_ALUMNO), 1, file);
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
  STR_MATERIA unaMateria;

  char linea[MAX_LINEA];
  char *token = NULL;

  while (fgets(linea, MAX_LINEA - 1, texto) != NULL)
  {
    token = strtok(linea, separadores);
    tokenNull(token, texto, binario);
    unaMateria.legajo = atoi(token);

    token = strtok(NULL, separadores);
    tokenNull(token, texto, binario);
    unaMateria.fecha = atoi(token);

    token = strtok(NULL, separadores);
    tokenNull(token, texto, binario);
    unaMateria.nota = (float)atof(token);

    fwrite(&unaMateria, sizeof(STR_MATERIA), 1, binario);
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

  STR_MATERIA unaMateria; //aca modificar
  fread(&unaMateria, sizeof(STR_MATERIA), 1, binario);
  while (!feof(binario))
  {
    fprintf(texto, "%d\t%d\t%f", unaMateria.legajo, unaMateria.fecha, unaMateria.nota);
    fread(&unaMateria, sizeof(STR_MATERIA), 1, binario);
  }
  fclose(texto);
  fclose(binario);
  texto = NULL;
  binario = NULL;
  return;
}