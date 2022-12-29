#pragma config(Sensor, S1, c1, sensorEV3_Color)
#pragma config(Sensor, S2, c2, sensorEV3_Color)
#pragma config(Sensor, S3, c3, sensorEV3_Color)
#pragma config(Motor, motorB, lm, tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor, motorC, rm, tmotorEV3_Large, PIDControl, encoder)

#define DIFF 10

int nMotorSpeedSetting = 20, vertex = 0, count = 0, row = 0, r = 0, c = 0, score = 0, val;
int S[4][4], dt[4][4], OX[4][4];

void go()
{
   val = 5;

   if(getColorName(c2) == 4) 			// 4 : yellow, Tracing 1 sensor line through sensor c2.
   {
      setMotorSpeed(lm, nMotorSpeedSetting - val);
      setMotorSpeed(rm, nMotorSpeedSetting + val);
   }
   else
   {
      setMotorSpeed(lm, nMotorSpeedSetting + val);
      setMotorSpeed(rm, nMotorSpeedSetting - val);
 	 }

   if(getColorName(c3) == 4 && count != 4) {    // yellow
       vertex++;
       if ( vertex == 1 ) count++;      // When the edge is recognized, count is increased.

     	 setMotorSpeed(lm, 10);
    	 setMotorSpeed(rm, 10);
    	 sleep(210);
    	 setMotorSpeed(lm, 20);
    	 setMotorSpeed(rm, -20);
    	 sleep(110);
    	 setMotorSpeed(lm, 0);
    	 setMotorSpeed(rm, 0);
       sleep(100);

    	if(getColorName(c2) == 5)         // 5 : red
   		{
      		if(row % 2 == 0) S[row][count-1] = 1;
      		else S[row][4-count] = 1;
      		playTone(440, 20); sleep(100);
   		}
   		else if(getColorName(c2) == 3)      // 3 : green
   		{
      		if (row % 2 == 0) S[row][count-1] = -1;
      		else S[row][4-count] = -1;
      		playTone(400,20); sleep(100);
   		}

    	setMotorSpeed(lm, -15);
    	setMotorSpeed(rm, 15);
    	sleep(150);
    	setMotorSpeed(lm, 20);
    	setMotorSpeed(rm, 20);
    	sleep(200);

    } else vertex = 0;
}

void go_r()
{
   val = 5;

   if(getColorName(c2) == 4) 			// 4 : yellow, Tracing 1 sensor line through sensor c2.
   {
      setMotorSpeed(lm, nMotorSpeedSetting - val);
      setMotorSpeed(rm, nMotorSpeedSetting + val);
   }
   else
   {
      setMotorSpeed(lm, nMotorSpeedSetting + val);
      setMotorSpeed(rm, nMotorSpeedSetting - val);
 	 }

   if(getColorName(c1) == 4 && count != 4) {    // yellow
       vertex++;
       if ( vertex == 1 ) count++;      // When the edge is recognized, count is increased.

     	 setMotorSpeed(lm, 10);
    	 setMotorSpeed(rm, 10);
    	 sleep(210);
    	 setMotorSpeed(lm, 20);
    	 setMotorSpeed(rm, -20);
    	 sleep(110);
    	 setMotorSpeed(lm, 0);
    	 setMotorSpeed(rm, 0);
       sleep(100);

    	if(getColorName(c2) == 5)         // 5 : red
   		{
      		if(row % 2 == 0) S[row][count-1] = 1;
      		else S[row][4-count] = 1;
      		playTone(440, 20); sleep(100);
   		}
   		else if(getColorName(c2) == 3)      // 3 : green
   		{
      		if (row % 2 == 0) S[row][count-1] = -1;
      		else S[row][4-count] = -1;
      		playTone(400,20); sleep(100);
   		}

    	setMotorSpeed(lm, -15);
    	setMotorSpeed(rm, 15);
    	sleep(150);
    	setMotorSpeed(lm, 20);
    	setMotorSpeed(rm, 20);
    	sleep(200);

    } else vertex = 0;
}

void turnLeft()
{
   setMotorSpeed(lm, 30);
   setMotorSpeed(rm, 30);
   sleep(150);
   while(getColorName(c1) > 4)
   {
      setMotorSpeed(lm, -nMotorSpeedSetting * 6/10);
      setMotorSpeed(rm, nMotorSpeedSetting * 6/10);
      sleep(10);
   }

   while(getColorName(c2) > 4)
   {
      setMotorSpeed(lm, -nMotorSpeedSetting * 6/10);
      setMotorSpeed(rm, nMotorSpeedSetting * 6/10);
      sleep(10);
   }
   sleep(150);
   setMotorSpeed(lm, 0);
   setMotorSpeed(rm, 0);
   sleep(100);
}

void turnRight()
{
   setMotorSpeed(lm, 20);
   setMotorSpeed(rm, 20);
   sleep(100);
   while(getColorName(c3) > 4)
   {
      setMotorSpeed(lm, nMotorSpeedSetting * 6/10);
      setMotorSpeed(rm, -nMotorSpeedSetting * 6/10);
      sleep(10);
   }

   while(getColorName(c2) > 4)
   {
      setMotorSpeed(lm, nMotorSpeedSetting * 6/10);
      setMotorSpeed(rm, -nMotorSpeedSetting * 6/10);
      sleep(10);
   }
   sleep(150);
   setMotorSpeed(lm, 0);
   setMotorSpeed(rm, 0);
   sleep(100);
}

void stopMotor()
{
   setMotorSpeed(lm, 0);
   setMotorSpeed(rm, 0);
}

void Search()
{
   while(true)
   {
      go();

      if(count == 4)      // When EV3 is done with a line,
      {
         if(row ==3) break;         // When the current row number is 3, that is, the destination point
         if(row % 2 == 0)
         {
            setMotorSpeed(lm, 35);
            setMotorSpeed(rm, 30);
            //sleep(400);
            for(int i=0; i<3; i++)
            {
               if(getColorName(c2) == 5)        // red
               {
                  if(row % 2 == 0) S[row][count-1] = 1;
                  else S[row][4-count] = 1;
                  playTone(440, 20); sleep(80);
               }
               else if(getColorName(c2) == 3)         // green
               {
                   if(row % 2 == 0) S[row][count-1] = -1;
                   else S[row][4-count] = -1;
                   playTone(400, 20); sleep(80);
               }
               else sleep(90);
            }
            turnRight();      // When the current row number is 0, 2, a right turn must be made after reaching the end of the row.
         }
         else
         {
           	setMotorSpeed(lm, 30);
            setMotorSpeed(rm, 35);
            //sleep(300);
            for(int i=0; i<3; i++)
            {
               if(getColorName(c2) == 5)			// red
               {
                  if(row % 2 ==0) S[row][count-1] = 1;
                  else S[row][4-count] = 1;
                  playTone(440, 20);
                  sleep(80);
               }
               else if(getColorName(c2) == 3)		// green
               {
                  if(row % 2 == 0) S[row][count-1] = -1;
                  else S[row][4-count] = -1;
                  playTone(400, 20); sleep(80);
               }
               else sleep(90);
            }
            turnLeft();      // When the current row number is 1, 3, a left turn must be made after reaching the end of the row.
         }

         if(row % 2 == 0)      // when the current row number is 0, 2,
         {
            while(getColorName(c3) == 6) go(); // 6 : white

            setMotorSpeed(lm, 35);
            setMotorSpeed(rm, 30);
            sleep(400);
            turnRight();
            setMotorSpeed(lm, -30);
            setMotorSpeed(rm, -30);
            sleep(800);
            if(getColorName(c2) == 4)   // 4 : yellow
               setMotorSpeed(lm, 20);
               setMotorSpeed(rm, 20);
               sleep(10);
         }
         else
         {
            while(getColorName(c1) == 6) go();

            setMotorSpeed(lm, 30);
            setMotorSpeed(rm, 35);
            sleep(400);
            turnLeft();
            setMotorSpeed(lm, -30);
            setMotorSpeed(rm, -30);
            sleep(800);
            if(getColorName(c2) == 4)
               setMotorSpeed(lm, 20);
               setMotorSpeed(rm, 20);
               sleep(10);
         }
         row++;
         count = 0;
      }
   }
   stopMotor();
   sleep(100);
}

void MoveToCheckPoint()
{
   setMotorSpeed(lm, nMotorSpeedSetting);
   setMotorSpeed(rm, nMotorSpeedSetting);
   sleep(1000);
   setMotorSpeed(lm, nMotorSpeedSetting);
   setMotorSpeed(rm, -nMotorSpeedSetting);
   sleep(1650);

   int a_count = 0, val = 5;

   while(True) {

	   if(getColorName(c2) == 4)	// 4 : yellow
  	 {
    	 setMotorSpeed(lm, nMotorSpeedSetting - val);
     	 setMotorSpeed(rm, nMotorSpeedSetting + val);
   	 }
   	 else
   	 {
     	 setMotorSpeed(lm, nMotorSpeedSetting + val);
       setMotorSpeed(rm, nMotorSpeedSetting - val);
   	 }

   	 if(getColorName(c1) == 4 && a_count != 3) {
   	 		vertex++;
   	 		if (vertex == 1) {
   	 			a_count++;
   	 		  setMotorSpeed(lm, nMotorSpeedSetting);
       	  setMotorSpeed(rm, nMotorSpeedSetting);
       	  sleep(200);
		 	 }
	   }
		 else vertex = 0;

		 if(a_count == 3)  break;

 	 }

 	 setMotorSpeed(lm, nMotorSpeedSetting);
   setMotorSpeed(rm, nMotorSpeedSetting);
   sleep(1000);
   setMotorSpeed(lm, nMotorSpeedSetting);
   setMotorSpeed(rm, -nMotorSpeedSetting);
   sleep(1650);

   stopMotor();
   sleep(100);
}

void patch_print()
{
    for(int i = 0; i<4; i++)
    {
      for(int j = 0; j<4; j++)
      {
        if(S[i][j] == 1) OX[i][j] = 'O';
        else if(S[i][j] == 0) OX[i][j] = '+';
        else if(S[i][j] == -1) OX[i][j] = 'X';
        else OX[i][j] = 'F';
      }
    }

    for(int i = 0; i<4; i++)
       for(int j = 0; j<4; j++)
          if(OX[i][j] != 'F')
             displayBigStringAt((j+1)*20, 130-(i+1)*20, "%c ", OX[i][j]);
    sleep(6000);		// 6 seconds
    eraseDisplay();
}

int max(int a, int b)
{
	return a > b ? a : b;
}

void goUp()
{
   r--; row++;
   turnRight();
   count = 0;
   while(true)
   {
     go();
     if (count == 1)
     {
       sleep(300);
    	 turnLeft();
    	 break;
     }
  }
}

void goLeft()
{
  c--;
  count = 0;
  while(true)
	{
		go();
		if(r == 0)
			go_r();
		if(count == 1)
		{
			setMotorSpeed(lm, 30);
			setMotorSpeed(rm, 30);
			sleep(400);
			break;
		}
	}
}

void calculation() {
  for(int i=0; i < 4; i++)
    for(int j=0; j < 4; j++)
    {
      if(i == 0 && j == 0) dt[i][j] = S[i][j];
      else if(i == 0) dt[i][j] = dt[i][j-1] + S[i][j];
      else if(j == 0) dt[i][j] = dt[i-1][j] + S[i][j];
      else dt[i][j] = max(dt[i-1][j], dt[i][j-1]) + S[i][j];
    }
}

task main()
{
   Search();
   MoveToCheckPoint();
   patch_print();

   count = row = 0;

   calculation();					// calculate shortest path through dynamic programming.

   row = 0; r = c = 3;			// return from end point to start point.

   while(r != 0 || c != 0)
   {
     if(r == 0) goLeft();
     else if(c == 0) goUp();
     else if(dt[r-1][c] > dt[r][c-1]) goUp();
     else goLeft();
     score += S[r][c];
     eraseDisplay();
     displayBigTextLine(1, "%d %d(%d)", r, c, row);
   }

   if(r == 0 && c == 0)
   {
     playTone(240, 20); sleep(200);
     stopMotor();
     displayBigTextLine(3, "Total score : %d", score);
     sleep(7000);		// 7 seconds
   }
}
