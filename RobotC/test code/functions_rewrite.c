void turn(int power, int deg, int time = 6000) {

	/*// 90 Degree Modifier
	if (abs(deg) == 90) {
		int modifier = deg * 8/9;
		deg = modifier;
	}
	// 45 Degree Modifier
	else if (abs(deg) == 45) {
		int modifier = deg * 7/9;
		deg = modifier;
	}*/

	heading = 0;
	wait1Msec(250);
	clearTimer(T1);

	if (deg > 0) {
		while (time1[T1] < time && abs(heading) < abs(deg)) {
			heading += HTGYROreadRot(SENSOR_GYRO) * (float)(20 / 1000.0);
			setMotors(power, -power);
			wait1Msec(20);
		}
	}

	if (deg < 0) {
		while (time1[T1] < time && abs(heading) < abs(deg)) {
		heading += HTGYROreadRot(SENSOR_GYRO) * (float)(20 / 1000.0);
			setMotors(-power, power);
			wait1Msec(20);
		}
	}

	stopMotors();
}

void arcTurn(int power, int deg, int time = 7000) {

	// 90 Degree Modifier
	if (abs(deg) == 90) {
		int modifier = deg * 8/9;
		deg = modifier;
	}

	// 45 Degree Modifier
	else if (abs(deg) == 45) {
		int modifier = deg * 7/9;
		deg = modifier;
	}

	heading = 0;
	wait1Msec(250);
	clearTimer(T1);
	// Forward arcTurn
	if (power > 0) {
		if (deg > 0) {
			while (time1[T1] < time && abs(heading) < abs(deg)) {
				heading += HTGYROreadRot(SENSOR_GYRO) * (float)(20 / 1000.0);
				setMotors(power, 0);
				wait1Msec(20);
			}
		}

		else {
			while (time1[T1] < time && abs(heading) < abs(deg)) {
				heading += HTGYROreadRot(SENSOR_GYRO) * (float)(20 / 1000.0);
				setMotors(0, power);
				wait1Msec(20);
			}
		}
	}

	// Backward arcTurn (flips inequalities)
	else {
		if (deg > 0) {
			while (time1[T1] < time && abs(heading) < abs(deg)) {
				heading += HTGYROreadRot(SENSOR_GYRO) * (float)(20 / 1000.0);
				setMotors(power, 0);
				wait1Msec(20);
			}
		}

		else {
			while (time1[T1] < time && abs(heading) < abs(deg)) {
				heading += HTGYROreadRot(SENSOR_GYRO) * (float)(20 / 1000.0);
				setMotors(0, power);
				wait1Msec(20);
			}
		}
	}
	stopMotors();
}

void drift(int power, int deg, int angle, int time = 8000) {
	heading = 0;
	nMotorEncoder[motorFL] = 0;
	nMotorEncoder[motorFR] = 0;
	wait1Msec(250);
	clearTimer(T1);
	if (power > 0) {
		while (time1[T1] < time && getEncoderAverage(nMotorEncoder[motorFL], nMotorEncoder[motorFR]) < deg) {
			heading += HTGYROreadRot(SENSOR_GYRO) * (float)(20 / 1000.0);
			if (angle > 0) {
				while (heading < angle) {
					setMotors(power, power - (power / 10));
				}
			}
			else {
				while (heading > angle) {
					setMotors(power - (power / 10), power);
				}
			}
		}
	}
	if (power < 0) {
		while (time1[T1] < time && getEncoderAverage(nMotorEncoder[motorFL], nMotorEncoder[motorFR]) < deg) {
			heading += HTGYROreadRot(SENSOR_GYRO) * (float)(20 / 1000.0);
			if (angle > 0) {
				while (heading < angle) {
					setMotors(power, power - 10);
				}
			}
			else {
				while (heading > angle) {
					setMotors(power - 10, power);
				}
			}
		}
	}
	stopMotors();
}