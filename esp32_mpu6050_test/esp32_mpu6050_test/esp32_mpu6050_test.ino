#include "mpu6050.h"

const float accelerationThreshold = 2.5; // threshold of significant in G's
const int numSamples = 119;

int samplesRead = numSamples;

void setup() {
  Serial.begin(115200);
  Init_mpu6050();

  // print the header
  Serial.println("aX,aY,aZ,gX,gY,gZ");
}

void loop() {
  // wait for significant motion
  while (samplesRead == numSamples) {
      ReadMPU6050();

      // sum up the absolutes
      float aSum = fabs(mpu6050_data.Acc_X) + fabs(mpu6050_data.Acc_Y) + fabs(mpu6050_data.Acc_Z);

      // check if it's above the threshold
      if (aSum >= accelerationThreshold) {
        // reset the sample read count
        samplesRead = 0;
        break;
      }
  }

  // check if the all the required samples have been read since
  // the last time the significant motion was detected
  while (samplesRead < numSamples) {
      float aX, aY, aZ, gX, gY, gZ;
      ReadMPU6050();
      aX = mpu6050_data.Acc_X;
      aY = mpu6050_data.Acc_Y;
      aZ = mpu6050_data.Acc_Z;
      gX = mpu6050_data.Angle_Velocity_R;
      gY = mpu6050_data.Angle_Velocity_P;
      gZ = mpu6050_data.Angle_Velocity_Y;
      samplesRead++;

      // print the data in CSV format
      Serial.print(aX, 3);
      Serial.print(',');
      Serial.print(aY, 3);
      Serial.print(',');
      Serial.print(aZ, 3);
      Serial.print(',');
      Serial.print(gX, 3);
      Serial.print(',');
      Serial.print(gY, 3);
      Serial.print(',');
      Serial.print(gZ, 3);
      Serial.println();

      if (samplesRead == numSamples) {
        // add an empty line if it's the last sample
        Serial.println();
      }
  }

  // ReadMPU6050();
  // // 串口绘图仪 可视化线加速度曲线
  // Serial.print("Acc_x:");
  // Serial.print(mpu6050_data.Acc_X);
  // Serial.print(",");
  // Serial.print("Acc_Y:");
  // Serial.print(mpu6050_data.Acc_Y);
  // Serial.print(",");
  // Serial.print("Acc_Z:");
  // Serial.println(mpu6050_data.Acc_Z);

  // // 串口绘图仪 可视化角速度曲线
  // Serial.print("Angle_velocity_R:");
  // Serial.println(mpu6050_data.Angle_Velocity_R);
  // Serial.print(",");
  // Serial.print("Angle_velocity_P:");
  // Serial.print(mpu6050_data.Angle_Velocity_P);
  // Serial.print(",");
  // Serial.print("Angle_velocity_Y:");
  // Serial.println(mpu6050_data.Angle_Velocity_Y);

  // delay(50);

}