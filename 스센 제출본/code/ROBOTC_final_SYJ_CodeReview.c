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
//사용할 색상 값들을 문자 값으로 정의한다.



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

// 이동할 거리를 실수형 변수 dist로 받아서 필요한 엔코더 값을 정수 형태로 변환하여 리턴한다.



void encoder(int dist){
   enc_degree = convert(dist);
   //covert 함수가 리턴한 값을 변수 enc_degree에 저장한다.


   resetMotorEncoder(lm);
   //왼쪽 모터의 엔코더 값을 0으로 초기화 한다.

   while(getMotorEncoder(lm) < enc_degree){
    //왼쪽 모터의 엔코더 값이 변수 enc_degree의 값보다 작은 동안 직진한다.

      setMotorSpeed(lm,speed*0.5);
      setMotorSpeed(rm,speed*0.5);
    // 양쪽 모터 speed에 0.5를 곱해 정상 속도의 ½으로 줄인다. 
      
   }
      setMotorSpeed(lm,0);
      setMotorSpeed(rm,0);
    //왼쪽 모터의 엔코더 값이 변수 enc_degree의 값과 같아지면 정지한다.
  
}
//엔코더 값을 이용해 이동 속도 및 대기 시간 상관없이 일정한 거리를 이동할 수 있다





void go(int s){

   setMotorSpeed(lm,s);
   setMotorSpeed(rm,s);
}
// 지정한 모터 값으로 직진하기 위한 함수를 정의한다.



void point_turn_cw(int s){

    int initval_cw = getGyroDegrees(gs);
    //변수 initval_cw에 초기 상태의 자이로 센서의 값을 저장한다.

    int gyro_cw = getGyroDegrees(gs);
    //변수 gyro_cw에 처음 상태의 자이로 센서의 값을 저장한다.
    // == initval_cw와 같은 값을 가진다.


    while(gyro_cw - initval_cw < 85)
      {
        //gyro_cw - initval_cw 현재 시점의 자이로 센서의 값과 초기 시점의 자이로 센서의 값 차를 통해 회전한 각도를 알수있다.
        //땅의 표면이 매끈하지 않다는 점을 고려했을때 , 대략 85도 정도가 적합하였기에 회전 각도가 85도 미만일때 시계방향으로 포인트 턴 하도록 설정하였다. 
        
         gyro_cw = getGyroDegrees(gs);
         // 조건문을 만족했을 경우, gyro_cw 변수에 시간에 현재 시점의 자이로 값을 저장한다.
         // 현재 로봇의 자이로 센서의 값 정보 업데이트가 가능하다.
    
         
         setMotorSpeed(lm, speed*0.5);
         setMotorSpeed(rm, -1*speed*0.5);
        // 속도에 0.5를 곱해 주행 속도를 ½으로 줄였다.
        // 왼쪽 바퀴는 앞으로 전진, 오른쪽 바퀴는 후진해 시계 방향으로 포인트 턴 한다.
         displayBigTextLine(9, "differ_cw = %d",gyro_cw - initval_cw);
         //조건과 일치하는지 파악하기 위해, 회전각도를 display에 출력했다. 

       }
       //각도 85도보다 커지게 되면 포인트 턴을 멈춘다.

       go(0);
       sleep(500);
       //0.5초동안 정지한다.
       

}


void point_turn_ccw(int s){

    int initval_ccw = getGyroDegrees(gs);
    //변수 initval_ccw에 초기 상태의 자이로 센서의 값을 저장한다.

    int gyro_ccw = getGyroDegrees(gs);
    //변수 gyro_ccw에 처음 상태의 자이로 센서의 값을 저장한다.
    // == initval_ccw와 같은 값을 가진다.

    displayBigTextLine(7, "f_differ = %d",gyro_ccw - initval_ccw);
    //differ_cw 값이 0부터 -85도까지 점점 감소해야하는데, 빨간 줄을 인식했을때 처음부터 gyro_ccw - initval_ccw 값이 -2825도로 인식하는 에러가 발생했다.
    //버그 원인을 두 가지 예측했다.
    //1. while문에 sleep() 함수를 걸지 않아 너무 빠르게 반복돼 발생한 오류 
    //- 이에 대한 첫번째 디버깅 시도는 아래 while문에 sleep(100)을 설정했다. 하지만 똑같은 오류가 발생했다.
    //- 두번째 시도로 포인트턴이 일어나지 않은 초기값의 차, gyro_ccw - initval_ccw값을 display에 출력했다. 0이 찍히지 않는다면 센서의 문제이기 때문이다.
    //2. 자이로 센서의 문제

    //시행 결과 , f_differ 값 역시 258도와 같은 잘못된 각도가 나왔다. 
    //센서 체크를 해보니 로봇이 아무런 동작을 하지 않았을때도 자이로 센서의 값이 실시간으로 변하는 문제가 있었다.
    //자이로 센서를 재연결한 후 시행했더니 해결되었다. 


        while(gyro_ccw - initval_ccw  > ( -85))
        {
            
            //gyro_ccw - initval_ccw 현재 시점의 자이로 센서의 값과 초기 시점의 자이로 센서의 값 차를 통해 회전한 각도를 알수있다.
            //마찬가지로 땅의 표면이 매끈하지 않다는 점을 고려해, 회전 각도가 -85도 이상일때 반시계방향으로 포인트 턴 하도록 설정하였다. 
           
            gyro_ccw = getGyroDegrees(gs);

            //gyro_ccw 변수에 현재의 로봇의 자이로 값 정보를 업데이트 한다.

            setMotorSpeed(lm, (-1*speed*0.5));
            setMotorSpeed(rm, (speed*0.5));

            //반시계 방향의 포인트 턴이기 때문에 왼쪽 바퀴는 후진 오른쪽 바퀴는 전진한다.


            displayBigTextLine(9, "differ_ccw =%d",gyro_ccw - initval_ccw);
            //회전 각도의 오류가 발생해 디버깅을 위해 실시간 로봇 회전 각도를 display에 출력했다. 


         }
        go(0);
        sleep(500);
        //0.5초동안 정지한다.


}




 void detect(){

    //초음파 센서를 이용한 장애물 감지 함수이다.

    int obs_dist = getUSDistance(ss);
    //초음파 센서값을 obs_dist에 저장한다.

    if( obs_dist < 30 ){
    //변수의 값이 30cm 미만이면 soundBeepBeep 소리를 출력한다.
    //과제에 있는 5번 조건을 50cm 미만일 때 소리를 한번만 출력하는 것을 이해했다.
    //본 코드에서는 30cm 미만으로 조건을 설정하였다.

		if(play_num == 0){
        //27번째 줄에 전역변수 int play_num 변수를 0으로 설정했었다.

       	playSound(soundBeepBeep);
        //soundBeepBeep 소리를 출력한다.

       	play_num++;
        //play_num 변수를 1만큼 증가시켜, play_num == 0 조건문을 만족하지 못하게 한다.
        //소리 출력을 한번만 하기 위함이다.
   		}
   

       go(speed*0.5);
       //소리 출력 후 속도를 정상의 ½만큼 전진한다.

       if( obs_dist < 10){
        //초음파 값, 즉 장애물과의 거리가 10cm미만 일때 속도를 정상의 ½로 줄인 상태에서 20cm 후진해야한다.

        enc_degree = convert(20);
        //20cm 이동하기 위해 회전해야하는 엔코더의 값을 변수 enc_degree에 저장한다.
        
        
        resetMotorEncoder(lm);
        //왼쪽 모터의 엔코더 값을 0으로 초기화 한다.


         while(getMotorEncoder(lm) > (-1) * enc_degree){
            // 20cm만큼 후진이기에, 변수 enc_degree에도 (-1)을 곱해야 한다
            // 바퀴가 후진할 때, 바퀴의 회전 각도는 음수이기 때문이다.            

            go(-speed*0.5);
            //정상의 ½로 줄인 상태에서 후진한다.

            //후진하기 때문에 getMotorEncoder(lm), 즉 왼쪽 모터의 엔코더 값이 점점 작아진다.
    
         }

         go(0);
         sleep(500);
         //왼쪽 모터의 엔코더 값이 (-1) * enc_degree의 값과 같아지면 0.5초동안 정지한다.

         point_turn_cw(speed);
         //시계 방향으로 포인트 턴한다.

    
         dist = 10 * black_num;
         //변수 black_num은 지금까지 지나친 검정색 구간의 개수이다.
         //변수 dist에 (지금까지 지나친 검정색 구간의 개수 * 10cm)을 저장한다.


         encoder(dist);
        //변수 dist 거리만큼 전진한다.

        point_turn_cw(speed);
        //다시 시계 방향으로 포인트 턴한다.

         go(speed);
        // 포인트 턴 후 직진한다.

      }

       }
           }


// color = getColorName(cs)를 선언해 컬러 센서에서 읽은 값을 변수 color에 저장했었다. 
// main 함수에서 조건문을 선언해 특정색에서 작업을 수행할 수 있게 코드를 작성했으나,
// 하얀색에서 다른 색라인을 넘어가는 지점에서 , 두 색을 동시에 인식해 오류가 발생했다.
// ex) 초록색 라인을 파란색 라인으로 인식해 소리 출력
// 이를 해결하기 위해 checkColor() 함수를 설정해 색을 명확히 인식하게 했다.         



int checkColor(){
   int arr[] = {0,0,0,0,0,0,0,0};
   //비교를 위해 크기가 8인 배열을 선언한다.
   // 1~7인 컬러값을 각각의 인덱스로 설정할것이기 때문이다.
   // 예) 파란색 인식했을 경우, arr[2]의 값을 1만큼 증가시킨다. (Blue의 컬러 센서 값은 2)


   while(1){
      int tmpColor = getColorName(cs);
      // 색깔의 값을 변수 tmpColor에 저장한다.

      if(tmpColor == White) break;
      //만약 white라면 반복문을 벗어난다.
      // white를 인식했을때 다른 색 라인을 벗어났음을 혹은, 새로운 색 라인에 진입하지 않았음을 의미하기 때문이다.

      arr[tmpColor]++;
      // 배열 tmpColor번째에 값을 1씩 증가시킨다.
      //예를 들어, 파란색을 인식했을 경우, 변수 tmpColor에는 2가 저장되고 arr[2]의 값이 1 증가한다.

   }

   int max = 0;
   /// max라는 변수에 0을 저장한다.


   for(int i = 0; i< 8; i++){

      if(arr[i] > arr[max]) max = i;
      //반복문을 통해 8개의 배열을 비교해 최댓값, 즉 가장 많이 인식한 색을 찾는다.
      //변수 max에 최댓값의 인덱스를 저장한다.

   }
   return max;
   //변수 max를 리턴한다.

   //이를 통해 하얀색과 다른색을 동시에 인식해 섞인 색을 인식해도,
   // 섞여진 색을 인식한 횟수보다 섞이지 않은 원래의 색을 인식한 횟수가 더 크고, 또한 그 값을 리턴하기 때문에 혼동하는 오류가 발생하지 않는다.
   


}







task main()
{
   while(getTouchValue(ts) == 0) {}
   while(getTouchValue(ts) == 1) {}

   //터치센서가 눌렀다 떼질때까지 대기한다.



   float t;
   //주행 시간을 저장하기 위한 변수 t를 실수형으로 저장한다.



   while(1)
   {

      go(speed);
      //직진한다.


      first_color = getColorName(cs);
      //변수 first color에 컬러센서값을 저장한다.

      color = checkColor();
      //마찬가지로 변수 color에 컬러센서 값을 저장한다.


      detect();
      //장애물 감지 시 작업을 수행할 수 있게 detect 함수를 넣었다.

      if( (first_color != White)&& start_val== 0 )
      {
         go(0);
         sleep(500);

         //직진 중 white가 아닌 첫 색을 인지하는 순간, 0.5초 정지한다.

         finish_line = first_color;
         //인지한 first_color의 값을 변수 finish_line에 저장한다.
         //첫 라인 색과 끝나는 라인 색을 같게 해 멈추기 위함이다.

         clearTimer(T1);
         // 시작 지점 인식 후 시간을 초기화 해준다.

         setLEDColor(ledGreen);
         sleep(700);
         //시작 지점을 인식하면 브릭의 LED를 0.7초동안 초록으로 표시한다

         displayBigTextLine(5,"first_color= %d",first_color);
         //제대로 색을 인식했는가를 보기 위해 first_color를 display에 출력했다. 

         start_val++;
         //start_val을 1 증가시켜, 직진 중 white가 아닌 첫 색을 인지하는에만 작업이 수행되도록 한다.

         color = getColorName(cs);
         //해당 작업 수행 후, 변수 color의 값을 업데이트 시킨다.
      }

    

      if((color == finish_line && start_val != 0)|| black_num == 10 ){

         go(0);
         sleep(1000);

         // 변수 color 값이 finish_line과 같으면서 start_val이 0이 아닐때,
         //그리고 검정색 라인을 10번 지나쳤을 때, 1초 정지한다.

         displayBigTextLine(3, "black_num = %d", black_num);
         displayBigTextLine(7, "finish_line = %d", finish_line);
         sleep(500);
         
         //변수 black_num 은 지나친 검정색 라인의 개수를, finish_line은 마지막 지점의 색 값이 저장돼있다.
         //올바르게 인식했는지 확인하기 위해 0.5초동안 display에 출력했다. 

         break;
         //마지막 지점 도착하거나, 검정색 라인을 10번 지나쳤을 때 반복문을 벗어난다.

      }



      if( color == Black){
         black_num++;
         //검정색 라인을 인식했을때 black_num 변수를 1씩 증가시켜 지나친 검정색 라인의 개수를 저장한다.
      }



      if(color == Blue)          
      {

         if(blue_num == 0){

            playSound(soundBeepBeep);
            //첫번째 파란색 지시색을 인식했을때 소리를 한번 출력한다.
      
            blue_num++;
            //이후 변수 blue_num을 1 증가시켜, 위 작업을 이후에 두번째 파란색 지시색 인식 이후 수행할 수 없게 한다.
         }
         else{
         
            for(int i =1; i <= black_num; i++){

               playSound(soundBeepBeep);

               //이후 지나친 검정색 라인의 개수만큼 소리를 출력한다.
            }

         }

      }



      if(color == Red){

         while(1)
         {
			   go(0);
			   sleep(500);
            //빨간색을 인식했을때 0.5초 정지한다.


            point_turn_ccw(speed);
            //시계 반대 방향으로 포인트 턴한다.


            dist = 10 * black_num;
            //변수 black_num은 지금까지 지나친 검정색 구간의 개수이다.
            //변수 dist에 (지금까지 지나친 검정색 구간의 개수 * 10cm)을 저장한다.

            encoder(dist);
            //변수 dist 거리만큼 전진한다.

            point_turn_ccw(speed);
            //다시 시계 반대 방향으로 포인트 턴한다.
            
            go(0);
            sleep(500);
            //0.5초동안 정지한다.

            break;
            //반복문을 벗어난다.

         }

      }

   }

   t= time1[T1];
   //타이머 값은 time1[]을 이용하여 1/1000초 단위로 측정할 수 있다.
   //변수 t에 타이머 값을 저장한다.


   displayBigTextLine(1, "record = %.2f sec", t/1000);
   sleep(5000);
   // 측정된 주행시간을 5초동안 display에 출력했다.

}
