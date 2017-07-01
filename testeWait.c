#include <time.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

#define CLOUD 0
#define SECURITY 1
#define ENTERTAINMENT 2
#define CONFORT 3
#define UPDATE 4
#define INTERVAL_SECURITY 50
#define INTERVAL_ENTERTAINMENT 20
#define INTERVAL_CONFORT 200
#define INTERVAL_UPDATE 1000

/* estrutura que guarda o ultimo horario de certa acao e seu numero */
typedef struct time_register {
	time_t last_entertainment;
	time_t last_confort;
	time_t last_security;
	time_t last_update;
	int numEntertainment;
	int numConfort;
	int numSecurity;
} time_register;

/* retorna o tempo atual em ms */
long get_time () {
	struct timespec time;
	long time_sec;
	long time_ms;

	if (clock_gettime(CLOCK_REALTIME, &time))
		return 0;
	time_sec = time.tv_sec;
	time_ms = (long) (time.tv_nsec / 1.0e6);
	time_ms += (long) time_sec * (1000);

	return time_ms;
}

/* Constroi um registrador de horarios */
void buildTimeRegister(time_register *tr, long currentTime) {
	tr->last_entertainment = currentTime;
	tr->last_confort = currentTime;
	tr->last_security = currentTime;
	tr->last_update = currentTime;
	tr->numEntertainment = 0;
	tr->numConfort = 0;
	tr->numSecurity = 0;
}

/* Determina se esta no horario de algo de acordo com um intervalo */
int isTime (int mode, long currentTime, time_register *tr) {
	if (mode == ENTERTAINMENT &&
		currentTime - tr->last_entertainment > INTERVAL_ENTERTAINMENT) {
	    tr->last_entertainment = currentTime;
		return 1;
	} else if (mode == CONFORT &&
			   currentTime - tr->last_confort > INTERVAL_CONFORT) {
		tr->last_confort = currentTime;
		return 1;
	} else if (mode == UPDATE &&
			   currentTime - tr->last_update > INTERVAL_UPDATE) {
		tr->last_update = currentTime;
		return 1;
	}
	
	return 0;
}

/* Envia mensagens se estiver dentro do intervalo especificado */
void sendMessages (long currentTime, time_register *tr) {
	if (isTime(ENTERTAINMENT, currentTime, tr))
		//printf("Are you entertained?\n");
		tr->numEntertainment += 1;
	
	if (isTime(CONFORT, currentTime, tr))
	    //printf("You have a new notification on Facebook\n");
		tr->numConfort += 1;
}

void displayActivities(long currentTime, time_register *tr) {
	if (isTime(UPDATE, currentTime, tr)) {
		printf("UPDATE:\n%d entertainment messages sent\n",
			   tr->numEntertainment);
		printf("%d confort messages sent\n%d security messages sent\n",
			   tr->numConfort, tr->numSecurity);
		tr->numEntertainment = 0;
		tr->numConfort = 0;
		tr->numSecurity = 0;
	}
}

int main() {
	long time, initial_time;
	int i;
	time_register tr;
	
	// horario inicial
	time = get_time();
	if (!time) {
		printf("ERROR: can't retrive time\n");
	}

	// inicia variaveis
	initial_time = time;
	buildTimeRegister(&tr, time);
	time++; // somente para entrar no loop, nao muda a execucao

	// imprime atividades realizadas a cada certo intervalo
	while(time - initial_time < 5000) {
		
		time = get_time();
		if (!time) {
			printf("ERROR: can't retrive time\n");
		}

		sendMessages(time, &tr);
		displayActivities(time, &tr);
	}

	return 0;
}
	
