#ifndef List_h
#define List_h
#define MAX 50

//Estas son las structs de el codigo

//Aqui se crea el libro con todas las informaciones correspondientes.
typedef struct {
    char tituloLibro[MAX];
    char autorLibro[MAX];
    char generoLibro[MAX];
    int isbnLibro;
    char ubicacionLibro[MAX];
    char estadoLibro[MAX];
    char reservasLibro[MAX][MAX];
    int numeroReservasLibros;
} Libro;

// Aqui se crea un nodo, cada libro funciona como nodo y cada nodo tiene todos los datos de ese libro
typedef struct NodoLibro {
    Libro libro;
    struct NodoLibro *siguiente;
} NodoLibro;


// Acá colocamos el prototipo de las funciones que utilizamos en nuestro código.
void registrarLibro(NodoLibro **listaLibros);
void mostrarDatosLibro(NodoLibro *listaLibros, char titulo[], char autor[]);
void mostrarTodosLosLibros(NodoLibro *listaLibros);
void reservarLibro(NodoLibro *listaLibros, char titulo[], char autor[], char nombreEstudiante[]);
void cancelarReservaLibro(NodoLibro *listaLibros, char titulo[], char autor[], char nombreEstudiante[]);
void retirarLibro(NodoLibro **listaLibros, char titulo[], char autor[], char nombreEstudiante[]);
void devolverLibro(NodoLibro *listaLibros, char titulo[], char autor[]);
void mostrarLibrosPrestados(NodoLibro *listaLibros);
void importarLibrosDesdeCSV(NodoLibro **listaLibros, char nombreArchivo[]);
void exportarLibrosACSV(NodoLibro *listaLibros, char nombreArchivo[]);

#endif  