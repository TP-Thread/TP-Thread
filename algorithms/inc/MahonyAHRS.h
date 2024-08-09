#ifndef MahonyAHRS_h
#define MahonyAHRS_h

extern volatile float q0, q1, q2, q3;	// quaternion of sensor frame relative to auxiliary frame


void MahonyAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
void MahonyAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);

float invSqrt(float x);

#endif
