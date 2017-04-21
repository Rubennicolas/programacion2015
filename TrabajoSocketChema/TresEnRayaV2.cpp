#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <pthread.h>

#define TAM 3

int _tablero[TAM][TAM];
int _numJugador;
const char *socket_para_conectar;
const char *socket_nombre;

void InitTablero()
{
  for (int f = 0; f < TAM; f++)
  {
    for (int c = 0; c < TAM; c++)
      _tablero[f][c] = 0;
  }
}

void DibujarTablero()
{
  //Primero borrar la pantalla
  system("clear");

  //Dibujar el tablero

  //printf("  1  2  3\n");

  for (int f = 0; f < TAM; f++)
  {
    for (int c = 0; c < TAM; c++)
    {
      if(_tablero[f][c] == 0)
        printf(" · ");
      else
      {
        if(_tablero[f][c] == 1)
            printf(" x ");
        else
        {            
          if(_tablero[f][c] == 2)
            printf(" o ");   
        }
      }
    }

    //printf("%d  ", f);
    printf("\n\n");
  }
}

int ArrayToPos(int posicion[2])
{
  int swap = 0;

  swap += posicion[0];
  swap *= 10;
  swap += posicion[1];

  return swap;
}

void PosToArray(int posicion, int *_posi)
{
  //Guardamos la fila primero.
  //int fila = posicion / 10;
  int fila, columna;
  fila = posicion / 10;
  _posi[0] = fila;
  //Ahora la columna.
  columna = posicion % 10;
  _posi[1] = columna;
}

void RellenarTablero(int *_posicion)
{
  int fil, col;
  fil = _posicion[0];
  col = _posicion[1];

  _tablero[fil][col] = 1;
}

void RellenarTableroRecibido(int *_posicion)
{
  int fil, col;
  fil = _posicion[0];
  col = _posicion[1];

  _tablero[fil][col] = 2; //Imprimira un 0
}

int Ganador(int pos_uno, int pos_dos, int pos_tres)
{
    if(pos_uno == 1 && pos_dos == 1 && pos_tres == 1)
    {
        system("clear");
        printf("¡¡¡HAS GANADO!!! \n");
        
        return 1; // Has ganado
    } 
    else 
    {
        system("clear");
        printf("Has perdido :( \n");
        
        return 2; // Has perdido
    }
        
}

int Empate()
{
    int contador = 0;
    
    for (int f = 0; f < TAM; f++)
    {
    for (int c = 0; c < TAM; c++)
      if(_tablero[f][c] != 0)
        contador++;
    }
    
    if(contador == TAM * TAM)
    {
        system("clear");
        printf("EMPATE!");
        
        return 1; //Si hay empate retorna 1
    }
    
    return 0; //Si no hay empate retorna 0
}

int ComprobarGanador()
{
  int bandera = 0;
    
  //Causuisticas ganadoras desde la fila 0
  if(_tablero[0][0] != 0 && _tablero[0][1] != 0 && _tablero[0][2] != 0)
    bandera = Ganador(_tablero[0][0], _tablero[0][1], _tablero[0][2]);

  if(_tablero[0][0] != 0 && _tablero[1][1] != 0 && _tablero[2][2] != 0)
    bandera = Ganador(_tablero[0][0], _tablero[1][1], _tablero[2][2]);

  if(_tablero[0][0] != 0 && _tablero[1][0] != 0 && _tablero[2][0] != 0)
    bandera = Ganador(_tablero[0][0], _tablero[1][0], _tablero[2][0]);


  //Desde la fila 1
  if(_tablero[1][0] != 0 && _tablero[1][1] != 0 && _tablero[1][2] != 0)
    bandera = Ganador(_tablero[1][0], _tablero[1][1], _tablero[1][2]);

  //Desde la fila 2
  if(_tablero[2][0] != 0 && _tablero[1][1] != 0 && _tablero[0][2] != 0)
    bandera = Ganador(_tablero[2][0], _tablero[1][1], _tablero[0][2]);

  if(_tablero[2][0] != 0 && _tablero[2][1] != 0 && _tablero[2][2] != 0)
    bandera = Ganador(_tablero[2][0], _tablero[2][1], _tablero[2][2]);

  //Desde la columna 1
  if(_tablero[0][1] != 0 && _tablero[1][1] != 0 && _tablero[2][1] != 0)
    bandera = Ganador(_tablero[0][0], _tablero[0][1], _tablero[0][2]);

  //Desde la columna 2
  if(_tablero[0][2] != 0 && _tablero[1][2] != 0 && _tablero[2][2] != 0)
    bandera = Ganador(_tablero[0][2], _tablero[1][2], _tablero[2][2]);
    
    return bandera;
}

void ComprobarPartida()
{
    if(ComprobarGanador() != 0 || Empate() != 0)
    {
        //Terminar la partida.
        printf("Partida terminada. Pulse cualquier tecla...");
        scanf(" ");
        InitTablero();
    }
}

int LeerPosicionPorTurnos(int client_socket)
{
  while(1)
  {
    int lenght;
    int _pos;
    int _posicion[2];
    char *recibo;

    // si no lee nada devuelve 0
    if (read (client_socket, &lenght, sizeof(lenght)) == 0)
      return 0;

    // reservar el tamaño del mensaje
    //_pos = (int *)malloc(lenght);
    recibo = (char *)malloc(lenght);
    

    // lee el mensaje y lo imprime
    read(client_socket, recibo, lenght);

    //prueba-----
    //printf("%s\n", recibo);
    
    //Pasar la cadena a int
    sscanf(recibo, "%d", &_pos);
    
    PosToArray(_pos, _posicion);
    RellenarTableroRecibido(_posicion);
    DibujarTablero();
    
    //Comprobar si hay ganador o empate
    ComprobarPartida();
    
    // liberar el malloc
    free(recibo);
  }
  return 1;
}

void EscribirPosicionPorTurnos(int socket)
{
  while(1)
  {
    int posicion[2];
    int pos;

    printf("Fila: \n");
    scanf("%d", &posicion[0]);

    printf("Columna: \n");
    scanf("%d", &posicion[1]);

    pos = ArrayToPos(posicion);
    
    //Ahora hay que convertir pos (entero de dos digitos) a un char* (cadena de texto)
    char envio[2];
    sprintf(envio, "%d", pos);

    int lenght = strlen(envio) + 1;
    write(socket, &lenght, sizeof(lenght));
    write(socket, envio, lenght);
    
    RellenarTablero(posicion);
    DibujarTablero();
    
    //Comprobar si hay ganador o empate
    ComprobarPartida();
  }
}

// Esta funcion sirve para establecer la conexion para enviar
void *ConectarAlOtro(void *)
{
  int socket_fd;
  struct sockaddr_un socket_datos;

  socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
  socket_datos.sun_family = AF_LOCAL;
  strcpy(socket_datos.sun_path, socket_para_conectar);
  connect(socket_fd, (struct sockaddr *)&socket_datos, SUN_LEN(&socket_datos));
  
  EscribirPosicionPorTurnos(socket_fd);
  
  close(socket_fd);
}


int main(int argc, char const *argv[]) {

  // usar el argumento 1 para dar nombre al socket_name
  socket_nombre = argv[1];
  socket_para_conectar = argv[2];

  //Iniciamos el tablero
  InitTablero();
  //Dibujamos el tablero
  DibujarTablero();

  //Numero para rellenar las celdas. Siempre que no sea un 0. Si es un 0 ponemos un 1.
  if (*argv[3] == '0')
  {
    _numJugador = 1;
  }
  else
  {
    char *swap;
    //_numJugador = (int)argv[3];
    swap = (char *)argv[3];
    //Pasar a int para guardar el numero de jugador del argumento 4
    sscanf(swap, "%d", &_numJugador);
  }


  // declarar la variable del socket
  int socket_fd;
  // declaramos una estructura para almacenar datos del socket
  struct sockaddr_un socket_datos;
  // declarar una variable que guarde el mensaje de salida del cliente.
  int salida_cliente;

  // iniciar el socket con los valores.
  socket_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
  // en el campo sun_family de sockaddr_un socket_datos poner local.
  socket_datos.sun_family = AF_LOCAL;
  // copiar lo que hay en socket_name en el campo sun_path de socket_datos.
  strcpy(socket_datos.sun_path, socket_nombre);
  // une el socket con el struct.
  bind(socket_fd, (struct sockaddr *) &socket_datos, SUN_LEN(&socket_datos));
  // usar la funcion listen() para escuchar conexiones, el socket y el numero
  //de conexiones.
  listen(socket_fd, 5);
  

  //Usar hilo para conectar y escribir con el socket server del otro usuario
  pthread_t idHilo_uno, idHilo_dos;
  pthread_create(&idHilo_uno, NULL, ConectarAlOtro, NULL);
  
  //pthread_join(idHilo_uno, NULL);
  
  do 
  {
    // declarar estructura para almacenar datos del socket del cliente.
    struct sockaddr_un cliente_datos;
    // declarar variable tipo socklen_t para almacenar el tamaño del cliente.
    socklen_t cliente_datos_len = SUN_LEN(&cliente_datos);
    // declarar la variable del socket del cliente.
    int cliente_socket_fd;

    // hacer la conexion guardando en la variable del socket cliente para
    // aceptar las conexiones.
    cliente_socket_fd = accept(socket_fd, (struct sockaddr *) &cliente_datos,
                              &cliente_datos_len);
    // guardamos en la variable salida_cliente lo que devuelva
    //la funcion server
    salida_cliente = LeerPosicionPorTurnos(cliente_socket_fd);
    // cerramos el socket del cliente
    //close(cliente_socket_fd);

    // ahora elegimos la posición que queremos poner la ficha con dos numeros (1º fila 2º columna)
    //LeerPosicionPorTurnos(cliente_socket_fd);

  } 
  while(!salida_cliente);


  close(socket_fd);
  unlink(socket_nombre);

  return EXIT_SUCCESS;
}