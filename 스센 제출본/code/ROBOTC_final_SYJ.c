#pragma config(Sensor, S1, ts, sensorEV3_Touch)
#pragma config(Sensor, S2, gs, sensorEV3_Gyro)
#pragma config(Sensor, S3, cs, sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S4, ss, sensorEV3_Ultrasonic)
#pragma config(Motor, motorB, lm, tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor, motorC, rm, tmotorEV3_Large, PIDControl, encoder)


#define Black 1
#define Blue 2
#define Green 3
#define Yellow 4
#define Red 5
#define White 6
#define Brown 7



int color, speed =10, start_val = 0;
int blue_num= 0;
int black_num = 0;
float dist;
int enc_degree;
int finish_line;
int first_color;
int play_num = 0;






int convert(float dist){
	return (int)(360.0*dist / 17.58);
}



void encoder(int dist){
	enc_degree = convert(dist);
	resetMotorEncoder(lm);

	while(getMotorEncoder(lm) < enc_degree){

		setMotorSpeed(lm,speed*0.5);
		setMotorSpeed(rm,speed*0.5);


	}
	setMotorSpeed(lm,0);
	setMotorSpeed(rm,0);


}



void go(int s){

	setMotorSpeed(lm,s);
	setMotorSpeed(rm,s);
}




void point_turn_cw(int s){

	int initval_cw = getGyroDegrees(gs);
	int gyro_cw = getGyroDegrees(gs);
	while(gyro_cw - initval_cw < 85)
	{
		gyro_cw = getGyroDegrees(gs);
		setMotorSpeed(lm, speed*0.5);
		setMotorSpeed(rm, -1*speed*0.5);
		displayBigTextLine(9, "differ_cw = %d",gyro_cw - initval_cw);

	}
	go(0);
	sleep(500);

}


void point_turn_ccw(int s){

	int initval_ccw = getGyroDegrees(gs);
	int gyro_ccw = getGyroDegrees(gs);
	displayBigTextLine(7, "f_differ = %d",gyro_ccw - initval_ccw);


	while(gyro_ccw - initval_ccw  > ( -85))
	{
		gyro_ccw = getGyroDegrees(gs);
		setMotorSpeed(lm, (-1*speed*0.5));
		setMotorSpeed(rm, (speed*0.5));
		displayBigTextLine(9, "differ_ccw =%d",gyro_ccw - initval_ccw);

	}
	go(0);
	sleep(500);

}



void detect(){

	int obs_dist = getUSDistance(ss);

	if( obs_dist < 30 ){

		if(play_num == 0){

			playSound(soundBeepBeep);
			play_num++;
		}

		go(speed*0.5);

		if( obs_dist < 10){

			enc_degree = convert(20);
			resetMotorEncoder(lm);

			while(getMotorEncoder(lm) > (-1) *enc_degree){

				go(-speed*0.5);
			}

			go(0);
			sleep(500);

			point_turn_cw(speed);

			dist = 10 * black_num;
			encoder(dist);


			point_turn_cw(speed);
			go(speed);

		}




	}
}



int checkColor(){
	int arr[] = {0,0,0,0,0,0,0,0};


	while(1){
		int tmpColor = getColorName(cs);

		if(tmpColor == White) break;


		arr[tmpColor]++;

	}
	int max = 0;


	for(int i = 0; i< 8; i++){

		if(arr[i] > arr[max]) max = i;
	}
	return max;


}





task main()
{
	while(getTouchValue(ts) == 0) {}
	while(getTouchValue(ts) == 1) {}
	float t;
	



	while(1)
	{

		go(speed);


		first_color = getColorName(cs);
		color = checkColor();
		detect();

		if( (first_color != White)&& start_val== 0 )
		{
			go(0);
			sleep(500);
			finish_line = first_color;
			
         	clearTimer(T1);

			setLEDColor(ledGreen);
			sleep(700);

			displayBigTextLine(5,"first_color= %d",first_color);
			start_val++;


			color = getColorName(cs);
		}



		if((color == finish_line && start_val != 0)|| black_num == 10 ){
			go(0);
			sleep(1000);
			displayBigTextLine(3, "black_num = %d", black_num);
			displayBigTextLine(7, "finish_line = %d", finish_line);
			sleep(500);
			break;

		}



		if( color == Black){
			black_num++;
		}



		if(color == Blue)
		{
			if(blue_num == 0){

				playSound(soundBeepBeep);
				blue_num++;
			}
			else{

				for(int i =1; i <= black_num; i++){
					playSound(soundBeepBeep);
					sleep(100);
				}

			}

		}

		if(color == Red){

			while(1)
			{

				go(0);
				sleep(500);
				point_turn_ccw(speed);


				dist = 10 * black_num;
				encoder(dist);

				point_turn_ccw(speed);

				go(0);
				sleep(500);

				break;

			}

		}




	}
	t= time1[T1];
	displayBigTextLine(1, "record = %.2f sec", t/1000);
	sleep(5000);
}
