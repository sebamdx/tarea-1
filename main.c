#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#define MAX 50

void registrarLibro(NodoLibro **listaLibros){//esta funcion registra cada libro en el nodo correspondiente
    NodoLibro *nuevoNodo = (NodoLibro *)malloc(sizeof(NodoLibro));
    if (nuevoNodo == NULL) {
        printf("No se logró asignar memoria\n");
        return;
    }

    printf("Ingrese el titulo del libro: ");
    scanf(" %[^\n]", nuevoNodo->libro.tituloLibro); //toma el titulo del libro 
    printf("Ingrese el autor del libro: ");
    scanf(" %[^\n]", nuevoNodo->libro.autorLibro); //toma el autor del libro 
    printf("Ingrese el género del libro: ");
    scanf(" %[^\n]", nuevoNodo->libro.generoLibro);//toma el genero del libro
    printf("Ingrese el código del libro: ");
    scanf("%d", &nuevoNodo->libro.isbnLibro);//toma el codigo del libro
    printf("Ingrese la ubicación del libro: ");
    scanf(" %[^\n]", nuevoNodo->libro.ubicacionLibro);//toma la ubicacion del libro
    strcpy(nuevoNodo->libro.estadoLibro, "Disponible");
    nuevoNodo->libro.numeroReservasLibros = 0;
    nuevoNodo->siguiente=NULL;
    if (*listaLibros==NULL) { // pone el nodo si en la lista el espacio esta vacio
        *listaLibros=nuevoNodo;
    } else {
        NodoLibro *actual=*listaLibros;// si no esta vacio pasa al siguiente y lo pone ahi
        while (actual->siguiente!=NULL) {
            actual=actual->siguiente;
        }
        actual->siguiente=nuevoNodo;
    }
    printf("Libro registrado.\n");
}


void mostrarDatosLibro(NodoLibro *listaLibros, char tituloLibro[], char autorLibro[]) {
    int encontrado = 0;
    NodoLibro *actual = listaLibros;
    while (actual != NULL) {
        if (strcmp(actual->libro.tituloLibro, tituloLibro) == 0 && strcmp(actual->libro.autorLibro, autorLibro) == 0) {
            printf("Titulo del libro: %s\n", actual->libro.tituloLibro);
            printf("Autor del libro: %s\n", actual->libro.autorLibro);
            printf("Genero del libro: %s\n", actual->libro.generoLibro);
            printf("Codigo del libro: %d\n", actual->libro.isbnLibro);
            printf("Ubicacion del libro: %s\n", actual->libro.ubicacionLibro);
            printf("Estado del libro: %s\n", actual->libro.estadoLibro);

            if (actual->libro.numeroReservasLibros > 0) {
                printf("Reservas:\n");
                for (int i = 0; i < actual->libro.numeroReservasLibros; i++) {
                    printf("%s\n", actual->libro.reservasLibro[i]);
                }
            }
            encontrado = 1;
            break;
        }
        actual = actual->siguiente;
    }
    if (!encontrado) {
        printf("El libro no se ha podido encontrar, intente nuevamente.\n");
    }
}
// Función para mostrar todos los libros registrados
void mostrarTodosLosLibros(NodoLibro *listaLibros) {
    if (listaLibros == NULL) {
        printf("No hay libros registrados.\n");
    } else {
        printf("Listado de libros:\n");
        NodoLibro *actual = listaLibros;
        while (actual != NULL) {
            printf("Título: %s, Autor: %s\n", actual->libro.tituloLibro, actual->libro.autorLibro);
            actual = actual->siguiente;
        }
    }
}
// Función para reservar un libro por título, autorLibro y nombre del estudiante
void reservarLibro(NodoLibro *listaLibros, char tituloLibro[], char autorLibro[], char nombreEstudiante[]) {
    int encontrado = 0;
    NodoLibro *actual = listaLibros;

    while (actual != NULL) {
        if (strcmp(actual->libro.tituloLibro, tituloLibro) == 0 && strcmp(actual->libro.autorLibro, autorLibro) == 0) {
            if (strcmp(actual->libro.estadoLibro, "Disponible") == 0) {
                // El libro está disponible, se puede reservar
                if (actual->libro.numeroReservasLibros < MAX) {
                    strcpy(actual->libro.estadoLibro, "Reservado");
                    strcpy(actual->libro.reservasLibro[actual->libro.numeroReservasLibros], nombreEstudiante);
                    actual->libro.numeroReservasLibros++;
                    printf("Libro reservado con éxito por %s.\n", nombreEstudiante);
                } else {
                    printf("No se pueden hacer más reservasLibro para este libro.\n");
                }
            } else {
                printf("El libro no está disponible para reservar en este momento.\n");
            }
            encontrado = 1;
            break;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        printf("Libro no encontrado.\n");
    }
}

// Función para cancelar la reserva de un libro por título, autorLibro y nombre del estudiante
void cancelarReservaLibro(NodoLibro *listaLibros, char tituloLibro[], char autorLibro[], char nombreEstudiante[]) {
    int encontrado = 0;
    NodoLibro *actual = listaLibros;

    while (actual != NULL) {
        if (strcmp(actual->libro.tituloLibro, tituloLibro) == 0 && strcmp(actual->libro.autorLibro, autorLibro) == 0) {
            if (strcmp(actual->libro.estadoLibro, "Reservado") == 0) {
                // El libro está reservado, se puede cancelar la reserva
                int j;
                for (j = 0; j < actual->libro.numeroReservasLibros; j++) {
                    if (strcmp(actual->libro.reservasLibro[j], nombreEstudiante) == 0) {
                        // Encontrado el estudiante en la cola de reservasLibro, eliminar la reserva
                        for (int k = j; k < actual->libro.numeroReservasLibros - 1; k++) {
                            strcpy(actual->libro.reservasLibro[k], actual->libro.reservasLibro[k + 1]);
                        }
                        actual->libro.numeroReservasLibros--;
                        printf("Reserva de %s cancelada.\n", nombreEstudiante);

                        if (actual->libro.numeroReservasLibros == 0) {
                            // Si no hay más reservasLibro, cambiar el estadoLibro a Disponible
                            strcpy(actual->libro.estadoLibro, "Disponible");
                        }
                        encontrado = 1;
                        break;
                    }
                }

                if (!encontrado) {
                    printf("No se encontró la reserva de %s.\n", nombreEstudiante);
                }
            } else {
                printf("El libro no está reservado.\n");
            }
            break;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        printf("Libro no encontrado.\n");
    }
}

// Esta función hace que se retire el libro.
void retirarLibro(NodoLibro **listaLibros, char tituloLibro[], char autorLibro[], char nombreEstudiante[]) {
    int encontrado = 0;
    NodoLibro *actual = *listaLibros;

    while (actual != NULL) {
        if (strcmp(actual->libro.tituloLibro, tituloLibro) == 0 && strcmp(actual->libro.autorLibro, autorLibro) == 0) {
            if (strcmp(actual->libro.estadoLibro, "Disponible") == 0 ||
                (strcmp(actual->libro.estadoLibro, "Reservado") == 0 && strcmp(actual->libro.reservasLibro[0], nombreEstudiante) == 0)) {
                // El libro está disponible o el estudiante tiene prioridad para retirarlo
                strcpy(actual->libro.estadoLibro, "Prestado");
                printf("Libro retirado por %s.\n", nombreEstudiante);
                encontrado = 1;
            } else if (strcmp(actual->libro.estadoLibro, "Prestado") == 0) {
                printf("El libro se encuenta en estado prestado.\n");
            } else {
                printf("El libro no está disponible para ser retirado.\n");
            }
            break;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        printf("Libro no encontrado.\n");
    }
}

// Esta función devuelve los Libros y cambia el estado del libro.
void devolverLibro(NodoLibro *listaLibros, char tituloLibro[], char autorLibro[]) {
    int encontrado = 0;
    NodoLibro *actual = listaLibros;

    while (actual != NULL) {
        if (strcmp(actual->libro.tituloLibro, tituloLibro) == 0 && strcmp(actual->libro.autorLibro, autorLibro) == 0) {
            if (strcmp(actual->libro.estadoLibro, "Prestado") == 0) {
                strcpy(actual->libro.estadoLibro, "Reservado");
                printf("Libro devuelto.\n");
                encontrado = 1;
            } else {
                printf("El libro no está prestado.\n");
            }
            break;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        printf("Libro no encontrado.\n");
    }
}
// Esta funcion recorre toda la lista y muestra los que esteén en estado prestados.
void mostrarLibrosPrestados(NodoLibro *listaLibros) {
    int prestadosEncontrados = 0;
    NodoLibro *actual = listaLibros;

    while (actual != NULL) {
        if (strcmp(actual->libro.estadoLibro, "Prestado") == 0) {
            printf("Título: %s, Autor: %s, Prestado a: %s\n", actual->libro.tituloLibro, actual->libro.autorLibro, actual->libro.reservasLibro[0]);
            prestadosEncontrados = 1;
        }
        actual = actual->siguiente;
    }

    if (!prestadosEncontrados) {
        printf("No hay libros prestados.\n");
    }
}
// Esta función importa los libros desde un CSV
void importarLibrosDesdeCSV(NodoLibro **listaLibros, char nombreArchivo[]) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error en la lectura del archivo.\n");
        return;
    }

    char linea[256];  // Se supone que una línea no tendrá más de 256 caracteres
    while (fgets(linea, sizeof(linea), archivo)) {
        char *token;
        token = strtok(linea, ",");
        
        Libro nuevoLibro;
        strcpy(nuevoLibro.tituloLibro, token);
        
        token = strtok(NULL, ",");
        strcpy(nuevoLibro.autorLibro, token);
        
        token = strtok(NULL, ",");
        strcpy(nuevoLibro.generoLibro, token);
        
        token = strtok(NULL, ",");
        nuevoLibro.isbnLibro = atoi(token);
        
        token = strtok(NULL, ",");
        strcpy(nuevoLibro.ubicacionLibro, token);
        
        token = strtok(NULL, ",");
        strcpy(nuevoLibro.estadoLibro, token);

        NodoLibro *nuevoNodo = (NodoLibro *)malloc(sizeof(NodoLibro));
        nuevoNodo->libro = nuevoLibro;
        nuevoNodo->siguiente = NULL;

        if (*listaLibros == NULL) {
            *listaLibros = nuevoNodo;
        } else {
            NodoLibro *actual = *listaLibros;
            while (actual->siguiente != NULL) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo;
        }
    }

    fclose(archivo);
    printf("Libros importados con éxito desde %s.\n", nombreArchivo);
}

// Esta funcion exporta los libros a CSV
void exportarLibrosACSV(NodoLibro *listaLibros, char nombreArchivo[]) {
    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }

    fprintf(archivo, "Titulo,Autor,Genero,Codigo,Ubicacion,Estado\n");
    NodoLibro *actual = listaLibros;
    while (actual != NULL) {
        fprintf(archivo, "%s,%s,%s,%d,%s,%s\n", actual->libro.tituloLibro, actual->libro.autorLibro, actual->libro.generoLibro,
                actual->libro.isbnLibro, actual->libro.ubicacionLibro, actual->libro.estadoLibro);
        actual = actual->siguiente;
    }

    fclose(archivo);
    printf("Libros exportados con éxito a %s.\n", nombreArchivo);
}



int main() {
    // La lista de los libros empieza vacia.
    NodoLibro *listaLibros = NULL;

    int opcion;
    char tituloLibro[MAX];
    char autorLibro[MAX];
    char nombreEstudiante[MAX];
    char nombreArchivo[MAX];
    // Aquí se crea el menú principal de la aplicación.
    do {
        printf("Que operación desea hacer?\n");
        printf("1. Registrar Libro\n");
        printf("2. Mostrar Datos de Libro\n");
        printf("3. Mostrar Todos los Libros\n");
        printf("4. Reservar Libro\n");
        printf("5. Cancelar Reserva de Libro\n");
        printf("6. Retirar Libro\n");
        printf("7. Devolver Libro\n");
        printf("8. Mostrar Libros Prestados\n");
        printf("9. Importar Libros desde CSV\n");
        printf("10. Exportar Libros a CSV\n");
        printf("0. Salir del programa\n");

        printf("Opción ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                registrarLibro(&listaLibros);
                break;
            case 2:
                printf("Ingrese el título del libro: ");
                scanf(" %[^\n]", tituloLibro);
                printf("Ingrese el autorLibro del libro: ");
                scanf(" %[^\n]", autorLibro);
                mostrarDatosLibro(listaLibros, tituloLibro, autorLibro);
                break;
            case 3:
                mostrarTodosLosLibros(listaLibros);
                break;
            case 4:
                printf("Ingrese el título del libro: ");
                scanf(" %[^\n]", tituloLibro);
                printf("Ingrese el autorLibro del libro: ");
                scanf(" %[^\n]", autorLibro);
                printf("Ingrese el nombre del estudiante: ");
                scanf(" %[^\n]", nombreEstudiante);
                reservarLibro(listaLibros, tituloLibro, autorLibro, nombreEstudiante);
                break;
            case 5:
                printf("Ingrese el título del libro: ");
                scanf(" %[^\n]", tituloLibro);
                printf("Ingrese el autorLibro del libro: ");
                scanf(" %[^\n]", autorLibro);
                printf("Ingrese el nombre del estudiante: ");
                scanf(" %[^\n]", nombreEstudiante);
                cancelarReservaLibro(listaLibros, tituloLibro, autorLibro, nombreEstudiante);
                break;
            case 6:
                printf("Ingrese el título del libro: ");
                scanf(" %[^\n]", tituloLibro);
                printf("Ingrese el autorLibro del libro: ");
                scanf(" %[^\n]", autorLibro);
                printf("Ingrese el nombre del estudiante: ");
                scanf(" %[^\n]", nombreEstudiante);
                retirarLibro(&listaLibros, tituloLibro, autorLibro, nombreEstudiante);
                break;
            case 7:
                printf("Ingrese el título del libro: ");
                scanf(" %[^\n]", tituloLibro);
                printf("Ingrese el autorLibro del libro: ");
                scanf(" %[^\n]", autorLibro);
                devolverLibro(listaLibros, tituloLibro, autorLibro);
                break;
            case 8:
                mostrarLibrosPrestados(listaLibros);
                break;
            case 9:
                printf("Ingrese el nombre del archivo CSV para importar: ");
                scanf(" %[^\n]", nombreArchivo);
                importarLibrosDesdeCSV(&listaLibros, nombreArchivo);
                break;
            case 10:
                printf("Ingrese el nombre del archivo CSV para exportar: ");
                scanf(" %[^\n]", nombreArchivo);
                exportarLibrosACSV(listaLibros, nombreArchivo);
                break;
            case 0:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción invalida.\n");
                break;
        }
    } while (opcion != 0);
  
    while (listaLibros != NULL) {
        NodoLibro *temporal = listaLibros;
        listaLibros = listaLibros->siguiente;
        free(temporal);
    }

    return 0;
}
