#include "brains.hpp"






void calculateAverages(){       
    // TODO store last 3 data readings for all important variables (eg accelZ)
    // and create an average for those last 3, called accelZ_avg.
    // We will use that data to figure out what state we're in
    // NOTE: Dont create averages for ALL the data readings (for example,
    // we don't need a smoothed average for temperature readings)
    
    // create lists for last 3 readings of each important variable
    static float accelX_list[3] = {0.0f, 0.0f, 0.0f};
    static float accelY_list[3] = {0.0f, 0.0f, 0.0f};
    static float accelZ_list[3] = {0.0f, 0.0f, 0.0f};
    static float gyroX_list[3] = {0.0f, 0.0f, 0.0f};
    static float gyroY_list[3] = {0.0f, 0.0f, 0.0f};
    static float gyroZ_list[3] = {0.0f, 0.0f, 0.0f};
    static float magX_list[3] = {0.0f, 0.0f, 0.0f};
    static float magY_list[3] = {0.0f, 0.0f, 0.0f};
    static float magZ_list[3] = {0.0f, 0.0f, 0.0f};
    static float quatReal_list[3] = {0.0f, 0.0f, 0.0f};
    static float quatI_list[3] = {0.0f, 0.0f, 0.0f};
    static float quatJ_list[3] = {0.0f, 0.0f, 0.0f};
    static float quatK_list[3] = {0.0f, 0.0f, 0.0f};
    static float temperature_C_list[3] = {0.0f, 0.0f, 0.0f};
    static float pressure_hPa_list[3] = {0.0f, 0.0f, 0.0f};
    
    // create index variables to keep track of where to insert new readings
    static int accel_index = 0;
    static int gyro_index = 0;
    static int mag_index = 0;
    static int quat_index = 0;
    static int temperature_index = 0;
    static int pressure_index = 0;

    // create a divisor variable to divide the sum of the last 3 readings by 3 to get the average
    static int accel_divisor = 0;
    static int gyro_divisor = 0;
    static int mag_divisor = 0;
    static int quat_divisor = 0;
    static int temperature_divisor = 0;
    static int pressure_divisor = 0;

    // shift readings over and add new reading to the end of the list
    if(sensorValue.sensorId == SH2_ACCELEROMETER){
   
    //assign new readings to the lists
    accelX_list[accel_index] = accelX;
    accelY_list[accel_index] = accelY;
    accelZ_list[accel_index] = accelZ;

    //Calculate averages for the acceleration readings
    //update divisor for new reading, stop at 3
    if(accel_divisor < 3) {
        accel_divisor++;
    }
    accelX_avg = (accelX_list[0] + accelX_list[1] + accelX_list[2]) / accel_divisor;
    accelY_avg = (accelY_list[0] + accelY_list[1] + accelY_list[2]) / accel_divisor;
    accelZ_avg = (accelZ_list[0] + accelZ_list[1] + accelZ_list[2]) / accel_divisor;

    //update index for new reading, wrap around if it reaches 3
    accel_index = (accel_index + 1) % 3;

}   else if(sensorValue.sensorId == SH2_GYROSCOPE_CALIBRATED){
    
    //assign new readings to the lists
    gyroX_list[gyro_index] = gyroX;
    gyroY_list[gyro_index] = gyroY;
    gyroZ_list[gyro_index] = gyroZ;

    //Calculate the averages for the gyro readings
    //update divisor for new reading, stop at 3
    if(gyro_divisor < 3) {
        gyro_divisor++;
    }
    gyroX_avg = (gyroX_list[0] + gyroX_list[1] + gyroX_list[2]) / gyro_divisor;
    gyroY_avg = (gyroY_list[0] + gyroY_list[1] + gyroY_list[2]) / gyro_divisor;
    gyroZ_avg = (gyroZ_list[0] + gyroZ_list[1] + gyroZ_list[2]) / gyro_divisor;

    //update index for new reading, wrap around if it reaches 3
    gyro_index = (gyro_index + 1) % 3;


}   else if(sensorValue.sensorId == SH2_MAGNETIC_FIELD_CALIBRATED){
    
    //assign new readings to the lists
    magX_list[mag_index] = magX;
    magY_list[mag_index] = magY;
    magZ_list[mag_index] = magZ;

    //Calculate the averages for the mag readings
    //update divisor for new reading, stop at 3
    if(mag_divisor < 3) {
        mag_divisor++;
    }
    magX_avg = (magX_list[0] + magX_list[1] + magX_list[2]) / mag_divisor;
    magY_avg = (magY_list[0] + magY_list[1] + magY_list[2]) / mag_divisor;
    magZ_avg = (magZ_list[0] + magZ_list[1] + magZ_list[2]) / mag_divisor;

    //update index for new reading, wrap around if it reaches 3
    mag_index = (mag_index + 1) % 3;

}   else if(sensorValue.sensorId == SH2_ROTATION_VECTOR){
   
    //assign new readings to the lists
    quatReal_list[quat_index] = quatReal;
    quatI_list[quat_index] = quatI;
    quatJ_list[quat_index] = quatJ;
    quatK_list[quat_index] = quatK;


    //Calculate the averages for the quat readings
    //update divisor for new reading, stop at 3
    if(quat_divisor < 3) {
        quat_divisor++;
    }
    quatReal_avg = (quatReal_list[0] + quatReal_list[1] + quatReal_list[2]) / quat_divisor;
    quatI_avg = (quatI_list[0] + quatI_list[1] + quatI_list[2]) / quat_divisor;
    quatJ_avg = (quatJ_list[0] + quatJ_list[1] + quatJ_list[2]) / quat_divisor;
    quatK_avg = (quatK_list[0] + quatK_list[1] + quatK_list[2]) / quat_divisor;

    //update index for new reading, wrap around if it reaches 3
    quat_index = (quat_index + 1) % 3;

}   else if(temperature_C != temperature_C_list[2]) { // Check if temperature and pressure readings are valid
   
    
    //store new temp reading
    temperature_C_list[temperature_index] = temperature_C;

    //Calculate the average temp readings
    //update divisor for new reading, stop at 3
    if(temperature_divisor < 3) {
        temperature_divisor++;
    }
    temperature_C_avg = (temperature_C_list[0] + temperature_C_list[1] + temperature_C_list[2]) / temperature_divisor;

    //update index for new reading, wrap around if it reaches 3
    temperature_index = (temperature_index + 1) % 3;

}   else if(pressure_hPa != pressure_hPa_list[2]) { // Check if temperature and pressure readings are valid
    //store new pressure reading
    pressure_hPa_list[pressure_index] = pressure_hPa;

    //Calculate the average pressure readings
    //update divisor for new reading, stop at 3
    if(pressure_divisor < 3) {
        pressure_divisor++;
    }
    pressure_hPa_avg = (pressure_hPa_list[0] + pressure_hPa_list[1] + pressure_hPa_list[2]) / pressure_divisor;

    //update index for new reading, wrap around if it reaches 3
    pressure_index = (pressure_index + 1) % 3;

}
}

void figureOutState(){
    // TODO: figure out state from the data given. THese down here are just silly examples!
    if(accelZ_avg && state == STATE_STANDBY){
        state = STATE_STANDBY; // this would be fully useless!
        // please remember not to waste compute power, here its very limited
    }
    else if(accelZ_avg == 123456789.123 && state == STATE_STANDBY){
        state = STATE_BURN;
    }

}
