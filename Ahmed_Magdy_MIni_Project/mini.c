
/*
 ============================================================================
 Name        : sdf.c
 Author      : Ahmed Magdy
 Version     :
 Copyright   : Your copyright notice
 Description : Mini Project
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>


#define ON 1
#define OFF 0


struct v1 {

	char AC;
	char Engine_Temp_Controller;
	char Engine_state;
	int v_speed;
	int room_temp;
	int engine_temp;

};


char main_menu(void){

	char chose;

	printf("\t\t<<- Choose your requirement from ->> (a:b:c)\n\n");
	printf("a:Turn on the vehicle engine\n");
	printf("b:Turn off the vehicle engine\n");
	printf("c:Quit the system\n");
	fflush(stdout);

	scanf(" %c",&chose);

	while(chose!='a'&& chose!='A'&& chose!='b' && chose!='B' && chose!='c' && chose!='C'){
		printf("\n\t\t<<- Please choose from ->> (a:b:c)\n");
		fflush(stdout);
		scanf(" %c",&chose);
	}



	return chose;

}

char sensor_menu(void){

	char chose;

	printf("\t\t<<- turn off the engine or enter sensors reads ->> (a:b:c:d)\n\n");
	printf("a:Turn of the engine\n");
	printf("b:Set the traffic light color\n");
	printf("c:Set the room temperature (Temperature sensor)\n");
	printf("d:Set the engine temperature (Engine Temperature sensor)\n");

	fflush(stdout);

	scanf(" %c",&chose);

	while(chose!='a' && chose!='A' && chose!='b' && chose!='B' && chose!='c' && chose!='C' && chose!='d' && chose!='D'){
		printf("\t\t<<- Please choose from ->> (a:b:c:d)\n");
		fflush(stdout);
		scanf(" %c",&chose);
	}



	return chose;

}

void traffic_light_color_speed(struct v1 *ptr){

	char traffic_light;

	printf("\t Please enter the color of traffic light->> (G:O:R)\n");
	fflush(stdout);


	scanf(" %c",&traffic_light);

	while (traffic_light!='g'&& traffic_light!='G' && traffic_light!='r' && traffic_light!='R' && traffic_light!='o' && traffic_light!='O'){
		printf("\t\t<<- Please choose from ->> (g:o:r)\n");
		fflush(stdout);
		scanf(" %c",&traffic_light);

	}

	switch(traffic_light){
	case 'g':
	case 'G':

		ptr->v_speed=100;

		break;
	case 'o':
	case 'O':

		ptr->v_speed=30;

		break;
	case 'r':
	case 'R':

		ptr->v_speed=0;

		break;

	default :
		break;
	}

}

void room_temperature(struct v1 *ptr){

	int room_t=0;

	printf("#Please enter room temperature sensor read ->> \n");
	fflush(stdout);

	scanf("%d",&room_t);

	if((room_t<10) || (room_t>30)){
		ptr->AC = ON;
		ptr->room_temp = 20;
	}else{
		ptr->AC=OFF;
		ptr->room_temp = room_t;
	}

	if((ptr->v_speed)==30){

		if(ptr->AC == OFF)ptr->AC= ON;

		ptr->room_temp = ptr->room_temp * ((float)5/4)+1;

	}

}

void engine_temperature(struct v1 *ptr){

	int engine_t=0;

	printf("#Please enter engine temperature sensor read ->> \n");
	fflush(stdout);

	scanf("%d",&engine_t);

	if((engine_t<100) || (engine_t>150)){
		ptr->Engine_Temp_Controller=ON;
		ptr->engine_temp=125;
	}else{
		ptr->Engine_Temp_Controller=OFF;
		ptr->engine_temp=engine_t;

	}

	if((ptr->v_speed)==30){

		if(ptr->Engine_Temp_Controller == OFF) ptr->Engine_Temp_Controller = ON;

		ptr->engine_temp = ptr->engine_temp * ((float)5/4)+1;
	}

}



void Display_the_current_vehicle_state(struct v1 *ptr){

	printf("\n____________________________________________________________________________\n");
	printf("\t\t***Display the current vehicle state***\n");
	printf("____________________________________________________________________________\n\n");

	(ptr->Engine_state==ON)? printf("Engine state: ON\n") : printf("Engine state: OFF\n");
	(ptr->AC==ON)? printf("AC: ON\n") : printf("AC: OFF\n");
	printf("Vehicle Speed: %d km/hr\n",ptr->v_speed);
	printf("Room Temperature: %d \n",ptr->room_temp);
	(ptr->Engine_Temp_Controller==ON)? printf("Engine Temperature Controller State: ON\n") : printf("Engine Temperature Controller State: OFF\n");
	printf("Engine Temperature: %d\n",ptr->engine_temp);
	fflush(stdout);


}



int main(){

	struct v1 Vehicle;
	char main_ch,sensor_menu_select;
	char flag=1;
	char  data_flag[3]={0};   //to check if data entered
	char  display_flag=0;


	printf("_________________________________________________________\n");
	printf("\t\t***Vehicle Control System***\n");
	printf("________________________________________________________\n");
	fflush(stdout);

	main_ch = main_menu();

	while(flag){

		switch(main_ch){
		case 'a':
		case 'A':

			printf("\n________________________________________________________\n");
			printf("\t\t<<- vehicle engine is turned ON ->>\n");
			printf("________________________________________________________\n\n");

			fflush(stdout);

			Vehicle.Engine_state = ON;

			{
				sensor_menu_select = sensor_menu();

				switch(sensor_menu_select){
				case 'a':
				case 'A':
					printf("\n________________________________________________________\n");
					printf("\t\t<<- vehicle engine is turned OFF ->>\n");
					printf("________________________________________________________\n\n");
					fflush(stdout);

					main_ch = main_menu();

					break;
				case 'b':
				case 'B':

					traffic_light_color_speed(&Vehicle);
					data_flag[0]=1;

					break;
				case 'c':
				case 'C':

					room_temperature(&Vehicle);

					data_flag[1]=1;

					break;
				case 'd':
				case 'D':

					engine_temperature(&Vehicle);
					data_flag[2]=1;

					break;
				default :
					break;

				}

			}

			display_flag = (data_flag[0]) & (data_flag[1]) & ( data_flag[2]);//to check if all data entered

			if(display_flag){

				Display_the_current_vehicle_state(&Vehicle);
			}

			break;
		case 'b':
		case 'B':

			printf("\n________________________________________________________\n");
			printf("\t\t<<- vehicle engine is turned OFF ->>\n");
			printf("________________________________________________________\n\n");
			fflush(stdout);

			Vehicle.Engine_state=OFF;

			main_ch = main_menu();

			break;
		case 'c':
		case 'C':

			printf("\t\t<<- Quit the system ->>\n");
			fflush(stdout);

			flag=0;

			break;

		default :
			break;

		}


	}


	return 0;

}
