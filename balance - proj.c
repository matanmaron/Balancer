#pragma config(Sensor, S2,     Gyro,           sensorEV3_Gyro, modeEV3Gyro_Angle)
#pragma config(Motor,  motorA,          rightMotor,    tmotorEV3_Large, openLoop, driveRight, encoder)
#pragma config(Motor,  motorD,          leftMotor,     tmotorEV3_Large, openLoop, driveLeft, encoder)
//the P
float error=0;
float offset=0;
float kp=1; //slope - power to add to engine
//the I
float integral=0; //=integral+error
float ki=0.2; //proporsional error
//the D
float lasterror=0; //same
float derivative=0; //future error predict
float kd=0.2;
//global var
float gero=0;
float speed=0;


float fix()
{
	error = getGyroDegrees(Gyro)-offset;
	integral=integral+error;
	derivative=error-lasterror;
	speed = (kp*error) + (ki*integral) + (kd*derivative);
	lasterror=error;
	if (error>lasterror)
		offset=abs(error/lasterror);
	if (error<lasterror)
		offset=abs(lasterror/error);
	return(speed);
}

void outofbound()
{
	 if (gero>25 || gero<(-25))
                  	 {
                     playSound( soundBeepBeep );
                     setMotorSpeed(leftMotor, 0);
                     setMotorSpeed(rightMotor, 0);
                     sleep(99999);
                     }
}


task main()
{
	resetGyro(Gyro);

	//drawBmpfile(0, 127, "Mouth 2 open");
	while (true)
{
		resetMotorEncoder( rightMotor );
		resetMotorEncoder( leftMotor );
		sleep( 100 );
		playSound( soundBeepBeep );
		resetGyro( Gyro );
		// This sleep is very important!
   // If not used, the gyro readings will be way off afterwards
   sleep( 4000 );
   playSound( soundDownwardTones );



				eraseDisplay();
   			displayCenteredBigTextLine( 2, "Balancing" );
				resetGyro(Gyro);
						while (true)
									{
										gero=getGyroDegrees(Gyro);
										integral=0;
											while (gero < 0)
													{
												  setMotorSpeed(leftMotor, fix());
                          setMotorSpeed(rightMotor, fix());
													sleep(1);
													gero=getGyroDegrees(Gyro);
													outofbound();
													}

											while (gero > 0)
												{
													setMotorSpeed(leftMotor, fix());
                          setMotorSpeed(rightMotor, fix());
													sleep(1);
													gero=getGyroDegrees(Gyro);
													outofbound();
												}
											while (gero == 0)
												{
													setMotorSpeed(leftMotor, 0);
                          setMotorSpeed(rightMotor, 0);
                          sleep(1);
                          gero=getGyroDegrees(Gyro);
                          outofbound();
                         }

									}
				}
			sleep(1);

}
