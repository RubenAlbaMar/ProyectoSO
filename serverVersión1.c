#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <mysql.h>
#include <stdio.h>

/*char username[20];*/
/*char name[20];*/
/*char surname[20];*/
/*char email[20];*/
/*char password[20];*/

void ADD_INFO_PLAYER(char username[], char name[], char surname[], char email[], char password[], MYSQL *conn) // A\ufff1ADE UN JUGADOR A LA TABLA JUGADORES DE LA BASE DE DATOS
{
	/*	char username[20];*/
	/*	char name[20];*/
	/*	char surname[20];*/
	/*	char email[20];*/
	/*	char password[20];*/
	
	char consulta[200];
	strcpy (consulta,"INSERT INTO Player VALUES ('");
	strcat (consulta, username);
	strcat (consulta,"','");
	strcat (consulta, name);
	strcat (consulta,"','");
	strcat (consulta, surname);
	strcat (consulta,"','");
	strcat (consulta, email);
	strcat (consulta,"','");
	strcat (consulta, password);
	strcat (consulta,"',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);");
	int err;
	err=mysql_query (conn, consulta);
	if (err!=0) 
	{
		printf ("Error al introducir datos en la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
}


int SEARCH_FOR_USER( char username[], char password[],MYSQL *conn) // BUSCA A UN JUGADOR DE LA BASE DE DATOS PARA VER SI ES UN USUARIO EXISTENTE
{
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	int exists=0;
	/*	char username[20];*/
	/*	char password[20];*/
	char mypassword[20];
	char consulta[80];
	strcpy (consulta,"SELECT Player.pass FROM Player WHERE Player.username = '");
	strcat (consulta, username);
	strcat (consulta,"';");
	int err;
	err=mysql_query (conn, consulta);
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	resultado = mysql_store_result (conn);
	
	row = mysql_fetch_row (resultado);
	
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	
	/*	else*/
	/*	{*/
	/*		strcpy (password, row[0]);*/
	/*	}*/
	/*	printf ("exists es igual a %s\n", row[0]);*/
	if (strcmp(password,row[0])==0)
	{
		exists =1;	
	}
	/*	printf ("exists es igual a %i\n", exists);*/
	return exists;
	
}


void PORCENTAJE_PREGUNTAS_PARTIDAS(int idGame, MYSQL *conn, int sock_conn) // A PARTIR DE EL NUMERO DE PARTIDA, OBTENEMOS EL PORCENTAJE DE PREGUNTAS DE CADA TEMA
{
	printf ("8a prueba\n");
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int err;
	//Declaro las variables que necesitare
	int numPreguntaPartidaIX;
	int numPreguntaPartidaAERO;
	int numPreguntaPartidaMET;
	int numPreguntaPartidaSO;
	int numPreguntaPartidaCA1;
	int numPreguntaPartidaERM;
	int totalPreguntas;
	
	int PercentageIX;
	int PercentageAERO;
	int PercentageMET;
	int PercentageSO;
	int PercentageCA1;
	int PercentageERM;
	printf ("9a prueba\n");
	char answer[512];
	/*answer = malloc(sizeof(char*)*5000);*/
	char answer2[512];
	/*answer2 = malloc(sizeof(char)*100);*/
	char idgame[20];
	
	printf ("10a prueba\n");
	sprintf(idgame, "%d", idGame);
	// Pregunto el identificador de partida
	/*strcpy (idgame, sidGame);*/ 
	printf ("11a prueba\n");
	char consulta [80];
	strcpy (consulta,"SELECT Game.numGameQuestIX, Game.numGameQuestAERO, Game.numGameQuestMET, Game.numGameQuestSO, Game.numGameQuestCA1, Game.numGameQuestERM  FROM Game WHERE Game.id = '");
	strcat (consulta, idgame);
	strcat (consulta,"';");
	printf ("12a prueba\n");
	err=mysql_query (conn, consulta);
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	printf ("13a prueba\n");
	resultado = mysql_store_result (conn);
	
	row = mysql_fetch_row (resultado);
	
	printf ("14a prueba\n");
	if (row != NULL)
	{
		numPreguntaPartidaIX= atoi (row[0]);
		numPreguntaPartidaAERO= atoi (row[1]);
		numPreguntaPartidaMET= atoi (row[2]);
		numPreguntaPartidaSO= atoi (row[3]);
		numPreguntaPartidaCA1= atoi (row[4]);
		numPreguntaPartidaERM= atoi (row[5]);
		
		totalPreguntas = numPreguntaPartidaIX + numPreguntaPartidaAERO + numPreguntaPartidaMET +numPreguntaPartidaSO + numPreguntaPartidaCA1 + numPreguntaPartidaERM;
		
		PercentageIX = ((numPreguntaPartidaIX*100)/totalPreguntas);
		PercentageAERO = ((numPreguntaPartidaAERO*100)/totalPreguntas);
		PercentageMET = ((numPreguntaPartidaMET*100)/totalPreguntas);
		PercentageSO = ((numPreguntaPartidaSO*100)/totalPreguntas);
		PercentageCA1 = ((numPreguntaPartidaCA1*100)/totalPreguntas);
		PercentageERM = ((numPreguntaPartidaERM*100)/totalPreguntas);
		printf ("15a prueba\n");
		
		// ESTO EN VEZ DE SALIR EN PANTALLA LO TENEMOS QUE ENVIAR A L C# !!!!!!!!!!!!!!!!!
		printf("Percentage of IX questions:  %d %  \n",PercentageIX);
		printf("Percentage of AERO questions: %d % \n",PercentageAERO);
		printf("Percentage of MET questions : %d % \n",PercentageMET);		
		printf("Percentage of SO questions : %d % \n",PercentageSO);
		printf("Percentage of CA1 questions : %d % \n",PercentageCA1);
		printf("Percentage of ERM questions : %d % \n",PercentageERM);
		
		sprintf(answer, "Percentage of IX questions: %d \n Percentage of AERO questions: %d \n Percentage of MET questions : %d \n Percentage of SO questions : %d \n Percentage of CA1 questions : %d \n Percentage of ERM questions : %d \n ",PercentageIX, PercentageAERO, PercentageMET, PercentageSO, PercentageCA1 , PercentageERM);
		sprintf(answer2, "%d/%d/%d/%d/%d/%d",PercentageIX, PercentageAERO, PercentageMET, PercentageSO, PercentageCA1 , PercentageERM);
	}
	
	else if (row == NULL)
	{
		printf ("No se han obtenido datos en la consulta\n");
		sprintf(answer, "No se han obtenido datos en la consulta\n");
	}
	/*write (sock_conn,answer,strlen(answer));*/
	printf ("16a prueba\n");
	printf ("Answer: %s\n", answer);
	printf ("Answer2: %s\n", answer2);
	write (sock_conn,answer,strlen(answer));
	/*return "16/16/16/16/16/16";*/
	/*return "hola";*/
	/*	return answer2;*/
	/*printf ("17a prueba\n");*/
	
	
}
void PERCENTAGE_CORRECT_ANSWERS_PER_TOPIC( char username[],MYSQL *conn,int sock_conn)
{
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int err;
	char answer[512];
	char consulta [512];
	// consulta SQL para obtener una tabla con todos los datos
	// de la base de datos
	err=mysql_query (conn, "SELECT * FROM Player");
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//recogemos el resultado de la consulta. El resultado de la
	//consulta se devuelve en una variable del tipo puntero a
	//MYSQL_RES tal y como hemos declarado anteriormente.
	//Se trata de una tabla virtual en memoria que es la copia
	//de la tabla real en disco.
	resultado = mysql_store_result (conn);
	// El resultado es una estructura matricial en memoria
	// en la que cada fila contiene los datos de una persona.
	
	// Ahora obtenemos la primera fila que se almacena en una
	// variable de tipo MYSQL_ROW
	row = mysql_fetch_row (resultado);
	// En una fila hay tantas columnas como datos tiene una
	// persona. En nuestro caso hay tres columnas: nombre(row[0]),
	// nombre(row[1]) y edad (row[2]).
	
	//Ahora vamos a consultar la posicion que tiene un jugador,
	//cuyo nombre es dado por el usuario
	char id [20];
	strcpy(id, username);
	char answer2[512];
	printf ("10a prueba\n");
	strcpy (consulta,"SELECT numQuestionsIX, numQuestionsAERO, numQuestionsERM, numQuestionsCA1, numQuestionsSO, numQuestionsMET, numCorrectQuestionsIX, numCorrectQuestionsAERO, numCorrectQuestionsERM, numCorrectQuestionsCA1, numCorrectQuestionsSO, numCorrectQuestionsMET FROM Player WHERE username = '"); 
	strcat (consulta, id);
	strcat (consulta,"'");
	printf ("11a prueba\n");
	err=mysql_query (conn, consulta); 
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//recogemos el resultado de la consulta 
	resultado = mysql_store_result (conn); 
	row = mysql_fetch_row (resultado);
	printf ("12a prueba\n");
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
	{
		int PIX = atoi (row[0]);
		int AIX = atoi (row[6]);
		
		int PAERO = atoi (row[1]);
		int AAERO = atoi (row[7]);
		
		int PERM = atoi (row[2]);
		int AERM = atoi (row[8]);
		
		int PCA1 = atoi (row[3]);
		int ACA1 = atoi (row[9]);
		
		int PSO = atoi (row[4]);
		int ASO = atoi (row[10]);
		
		int PMET = atoi (row[5]);
		int AMET = atoi (row[11]);
		int Percent_IX_Player =(AIX*100)/PIX;
		int Percent_AERO_Player= (AAERO*100)/PAERO;
		int Percent_ERM_Player = (AERM*100)/PERM;
		int Percent_CA1_Player = (ACA1*100)/PCA1;
		int Percent_SO_Player = (ASO*100)/PSO;
		int Percent_MET_Player = (AMET*100)/PMET;

		printf ("13a prueba\n");
		sprintf(answer2, "Percentage of correct IX questions: %d \n Percentage of correct AERO questions: %d \n Percentage of correct MET questions : %d \n Percentage of correct SO questions : %d \n Percentage of correct CA1 questions : %d \n Percentage of correct ERM questions : %d \n ",Percent_IX_Player, Percent_AERO_Player, Percent_MET_Player, Percent_SO_Player, Percent_CA1_Player , Percent_ERM_Player);
		printf ("El porcentaje de aciertos de IX es %d\n", (AIX*100)/PIX);
		printf ("El porcentaje de aciertos de AERO es %d\n", (AAERO*100)/PAERO);
		printf ("El porcentaje de aciertos de ERM es %d\n", (AERM*100)/PERM);
		printf ("El porcentaje de aciertos de CA1 es %d\n", (ACA1*100)/PCA1);
		printf ("El porcentaje de aciertos de SO es %d\n", (ASO*100)/PSO);
		printf ("El porcentaje de aciertos de MET es %d\n", (AMET*100)/PMET);/*(AIX*100)/PIX,(AAERO*100)/PAERO),(AERM*100)/PERM),(ACA1*100)/PCA1),(ASO*100)/PSO),(AMET*100)/PMET)*/
		//sprintf("El porcentaje de aciertos de IX es %d\n El porcentaje de aciertos de AERO es %d\n El porcentaje de aciertos de ERM es %d\n El porcentaje de aciertos de CA1 es %d\n El porcentaje de aciertos de SO es %d\n El porcentaje de aciertos de MET es %d\n",
	}
	printf ("14a prueba\n");
	write (sock_conn,answer2,strlen(answer2));
}
void TELL_ME_THE_RANKING(char idGame[20] ,MYSQL *conn, int sock_conn)
{
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int err;

	char id [20];
	char consulta [200];
	strcpy(id,idGame);

	strcpy(consulta,"SELECT winner, 2ndplace, 3rdplace FROM Game WHERE id= '");
	strcat (consulta, id);
	strcat (consulta,"';");
	char answer3[512];
	err=mysql_query (conn, consulta); 
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}

	resultado = mysql_store_result (conn); 
	row = mysql_fetch_row (resultado);
	if (row == NULL)
	{
		printf ("No se han obtenido datos en la consulta\n");
		sprintf(answer3, "No se han obtenido datos en la consulta\n");
	}

	else
	{
		printf ("Primer puesto: %s\n Segundo Puesto: %s\n Tercer Puesto: %s\n", row[0], row [1], row [2]);
		
		sprintf(answer3, "Primer puesto: %s\n Segundo Puesto: %s\n Tercer Puesto: %s\n", row[0], row [1], row [2]);
	}
	write (sock_conn,answer3,strlen(answer3));

}
/*void TELL_ME_THE_RANKING(char idGame[],MYSQL *conn)*/
/*{*/
/*	MYSQL_RES *resultado;*/
/*	MYSQL_ROW row;*/
/*	int err;*/
	
/*	char id [20];*/
/*	char consulta [200];*/
/*	strcpy(id,idGame);*/
	
/*	strcpy(consulta,"SELECT winner, 2ndplace, 3rdplace FROM Game WHERE id= '");*/
/*	strcat (consulta, id);*/
/*	strcat (consulta,"'");*/
	
/*	err=mysql_query (conn, consulta); */
/*	if (err!=0) {*/
/*		printf ("Error al consultar datos de la base %u %s\n",*/
/*				mysql_errno(conn), mysql_error(conn));*/
/*		exit (1);*/
/*	}*/
	
	//recogemos el resultado de la consulta 
/*	resultado = mysql_store_result (conn); */
/*	row = mysql_fetch_row (resultado);*/
/*	if (row == NULL)*/
/*		printf ("No se han obtenido datos en la consulta\n");*/
/*	else*/
		
/*		printf (" Primer puesto: %s\n Segundo Puesto: %s\n Tercer Puesto: %s\n", row[0], row [1], row [2]);*/
	// cerrar la conexion con el servidor MYSQL 
/*}*/


int main(int argc, char *argv[])
{
	char username[20];
	char name[20];
	char surname[20];
	char email[20];
	char password[20];
	
	
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "BBDDquiz",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	char peticion[512];
	char respuesta[512];
	// INICIALITZACIONS
	// Obrim el socket
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error creant socket");
	// Fem el bind al port
	
	
	memset(&serv_adr, 0, sizeof(serv_adr));// inicialitza a zero serv_addr
	serv_adr.sin_family = AF_INET;
	
	// asocia el socket a cualquiera de las IP de la maquina. 
	//htonl formatea el numero que recibe al formato necesario
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	// establecemos el puerto de escucha
	serv_adr.sin_port = htons(9200);
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind");
	
	if (listen(sock_listen, 3) < 0)
		printf("Error en el Listen");
	
	int i;
	// Bucle infinito
	char *p;
	int codigo;
	for (;;)
	{
		printf ("Listening\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("I recieved connection\n");
		//sock_conn es el socket que usaremos para este cliente
		
		int terminar =0;
		// Entramos en un bucle para atender todas las peticiones de este cliente
		//hasta que se desconecte
		
		while (terminar ==0)
		{
			// Ahora recibimos la peticion
			ret=read(sock_conn,peticion, sizeof(peticion));
			printf ("Recibido\n");
			
			// Tenemos que anadirle la marca de fin de string 
			// para que no escriba lo que hay despues en el buffer
			peticion[ret]='\0';
			
			
			printf ("Peticion: %s\n",peticion);
			printf ("1a prueba\n");
			// vamos a ver que quieren
			p = strtok( peticion, "/");
			printf ("2a prueba\n");
			/*printf("el p: %d",p);*/
			codigo =  atoi (p);
			printf ("3a prueba\n");
			printf ("cod: %d\n",codigo);
			// Ya tenemos el codigo de la peticion
			printf ("4a prueba\n");
			
			
			if (codigo == 1) // PARA EL SIGN IN
			{
				char username[20];
				char name[20];
				char surname[20];
				char email[20];
				char password[20];
				
				p = strtok( NULL, "/");
				strcpy (username, p);
				p = strtok( NULL, "/");
				strcpy (name, p);
				p = strtok( NULL, "/");
				strcpy (surname, p);
				p = strtok( NULL, "/");
				strcpy (email, p);
				p = strtok( NULL, "/");
				strcpy (password, p);
				
				printf ("Codigo: %d\n Usename: %s\n Name: %s\n Surname: %s\n Email: %s\n Password: %s\n",codigo, username, name, surname, email, password);
				
				ADD_INFO_PLAYER(username, name, surname, email, password, conn);
				
				
				/*				printf ("hey");*/
			}
			else if (codigo == 2) // PARA EL LOG IN
			{
				
				char username[20];
				char password[20];
				
				p = strtok( NULL, "/");
				strcpy (username, p);
				p = strtok( NULL, "/");
				strcpy (password, p);
				
				int a = SEARCH_FOR_USER(username, password, conn );
				if (a==1)
				{
					printf ("Codigo: %d\n Usename: %s\n Password: %s\n",codigo, username, password);
					sprintf(respuesta,"%d",a);
					write (sock_conn,respuesta,strlen(respuesta));
					/*memset(peticion,0,sizeof(peticion));*/
					
				}
				else if (a==0)
				{
					printf ("No se ha podido encontrar al usuario");
				}
				
			}
			
			else if (codigo == 3 ) // PARA CONSULTA 1
			{	
				printf ("5a prueba\n");
				
				char idGame[20];
				p = strtok( NULL, "/");
				strcpy (idGame, p);
				printf ("6a prueba\n");
				int iidGame = atoi(idGame);
				printf ("%d\n",iidGame);
				
				char * consulta1;
				printf ("7a prueba\n");
				/*consulta1 = PORCENTAJE_PREGUNTAS_PARTIDAS(iidGame, conn);*/
				printf ("18a prueba\n");
				PORCENTAJE_PREGUNTAS_PARTIDAS(iidGame, conn,sock_conn);
/*				printf ("Resultado Consulta1 %s\n",PORCENTAJE_PREGUNTAS_PARTIDAS(iidGame, conn));*/
/*				write (sock_conn,PORCENTAJE_PREGUNTAS_PARTIDAS(iidGame, conn),strlen(PORCENTAJE_PREGUNTAS_PARTIDAS(iidGame, conn)));*/
				printf ("19a prueba\n");
				/*PORCENTAJE_PREGUNTAS_PARTIDAS(int idGame, MYSQL *conn, int sock_conn)*/
				
				
			}
			else if (codigo == 4) // PARA CONSULTA 2
			{
				char username[20];
				p = strtok(NULL,"/");
				strcpy (username,p);
				PERCENTAGE_CORRECT_ANSWERS_PER_TOPIC(username, conn, sock_conn);
			}
			else if (codigo == 5) // PARA CONSULTA 3
			{
				p = strtok(NULL,"/");
				strcpy (username,p);
				char idGame[20];
				
				TELL_ME_THE_RANKING(idGame, conn, sock_conn);
			}
			else if (codigo ==0) //peticion de desconexion
				terminar=1;
		}
		
		
		
		
		
		//TODO ESTO PA FUERA QUE ESTABA EN EL CODIGO DE ANTES Y NO SABEMOS PARA QUE USARLO, ES DE REFERENCIA
		// else if (codigo ==1) //piden la longitd del nombre
		// 	sprintf (respuesta,"%d",strlen (nombre));
		// else if (codigo ==2)
		// 	// quieren saber si el nombre es bonito
		// 	if((nombre[0]=='M') || (nombre[0]=='S'))
		// 	strcpy (respuesta,"SI");
		// 	else
		// 		strcpy (respuesta,"NO");
		// else //quiere saber si es alto
		// {
		// 	p = strtok( NULL, "/");
		// 	float altura =  atof (p);
		// 	if (altura > 1.70)
		// 		sprintf (respuesta, "%s: eres alto",nombre);
		// 	else
		// 		sprintf (respuesta, "%s: eresbajo",nombre);
		// }
		
		// if (codigo !=0)
		// {
		
		// 	printf ("Respuesta: %s\n", respuesta);
		// 	// Enviamos respuesta
		// 	write (sock_conn,respuesta, strlen(respuesta));
		// }
		//}
		// Se acabo el servicio para este cliente
		close(sock_conn); 
	}
}
