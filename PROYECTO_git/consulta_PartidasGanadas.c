/* En MySQL quedaría de la forma:
SELECT j.usuario, COUNT(jp.ID_p) AS partidas_jugadas,
       SUM(CASE WHEN p.ID_ganador = j.ID_j THEN 1 ELSE 0 END) AS partidas_ganadas
FROM jugadores j
LEFT JOIN jugadores_partida jp ON j.ID_j = jp.ID_j
LEFT JOIN partida p ON jp.ID_p = p.ID_p
GROUP BY j.ID_j; */
______________________________________

// Esta consulta devuelve el print: "El jugador (usuario del jugador) ha jugado (nº de partidas jugadas) y ha ganado (nº de partidas ganadas)
// Código en C de la consulta:

#include <stdio.h>
#include <mysql.h>
#include "DatosConexion.h"  // Este archivo debe definir HOST, USERNAME, PASSWORD, DATABASE, PORT

int conectar(MYSQL **conn);
void ejecutar_consulta(MYSQL *conn, char *consulta);

int main(int argc, char *argv[]) {
    int error;
    char *consulta;
    MYSQL *conn;

    error = conectar(&conn);
    if (!error) {
        // Consulta que agrupa por jugador, contando las partidas jugadas y sumando las ganadas.
        consulta = "SELECT j.usuario, COUNT(jp.ID_p) AS partidas_jugadas, "
                   "SUM(CASE WHEN p.ID_ganador = j.ID_j THEN 1 ELSE 0 END) AS partidas_ganadas "
                   "FROM jugadores j "
                   "LEFT JOIN jugadores_partida jp ON j.ID_j = jp.ID_j "
                   "LEFT JOIN partida p ON jp.ID_p = p.ID_p "
                   "GROUP BY j.ID_j;";
        ejecutar_consulta(conn, consulta); // Ejecuta la consulta
        mysql_close(conn); // Cierra la conexión con la BBDD
    }
    return 0;
}

int conectar(MYSQL **conn){ 
    int error; // Variable para controlar si hay error en la conexión
    *conn = mysql_init(NULL);
    
    if (mysql_real_connect(*conn, HOST, USERNAME, PASSWORD, DATABASE, PORT, NULL, 0) != NULL){
        printf("Se estableció la conexión con la base de datos\n");
        error = 0;
    }
    else{
        printf("Error al conectarse con la base de datos: %s\n", mysql_error(*conn));
        error = 1; 
    }
    return error;
}

void ejecutar_consulta(MYSQL *conn, char *consulta) {
    int error;
    MYSQL_RES *res_ptr; // Puntero al conjunto de resultados
    MYSQL_ROW res_fila;

    error = mysql_query(conn, consulta);
    if (!error) {
        res_ptr = mysql_store_result(conn); // Obtiene el resultado de la consulta
        if (res_ptr) {
            // Recorre cada fila del resultado
            while ((res_fila = mysql_fetch_row(res_ptr)) != NULL) {
                // res_fila[0]: usuario, res_fila[1]: partidas_jugadas, res_fila[2]: partidas_ganadas
                printf("El usuario %s ha jugado %s partidas y ha ganado %s partidas.\n",
                       res_fila[0] ? res_fila[0] : "NULL",
                       res_fila[1] ? res_fila[1] : "0",
                       res_fila[2] ? res_fila[2] : "0");
            }
            mysql_free_result(res_ptr);
        }
        else {
            printf("Error al obtener el resultado: %u %s\n", mysql_errno(conn), mysql_error(conn));
        }
    }
    else { 
        printf("Error al ejecutar la consulta: %u %s\n", mysql_errno(conn), mysql_error(conn));
    }
}
