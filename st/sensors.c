/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <hardware/sensors.h>

#include "nusensors.h"

/*****************************************************************************/

/*
 * The SENSORS Module
 */

/*
 * the AK8973 has a 8-bit ADC but the firmware seems to average 16 samples,
 * or at least makes its calibration on 12-bits values. This increases the
 * resolution by 4 bits.
 */

static const struct sensor_t sSensorList[] = {
        { "Gravity sensor",    
            	"Freescale Semiconductor",
                1, SENSORS_HANDLE_BASE+ID_A,
                SENSOR_TYPE_ACCELEROMETER, 4.0f*9.81f, (4.0f*9.81f)/256.0f, 0.2f, 0, { } },
        { "Compass Magnetic field sensor",
                "Asahi Kasei",
                1, SENSORS_HANDLE_BASE+ID_M,
                SENSOR_TYPE_MAGNETIC_FIELD, 2000.0f, 1.0f/16.0f, 6.8f, 0, { } },
        { "Compass Orientation sensor",
                "Asahi Kasei",
                1, SENSORS_HANDLE_BASE+ID_O,
                SENSOR_TYPE_ORIENTATION, 360.0f, 1.0f, 7.0f, 0, { } }, 

	{ "Gyroscope sensor",
          "STMicroelectronics",
          1, SENSORS_HANDLE_BASE+ID_GY,
          SENSOR_TYPE_GYROSCOPE, RANGE_GYRO, CONVERT_GYRO, 6.1f, 1190, { } },
			
	{ "Proximity sensor",
		"Dyna Image Corporation",
		1, SENSORS_HANDLE_BASE+ID_P,
		SENSOR_TYPE_PROXIMITY,
		PROXIMITY_THRESHOLD_CM, PROXIMITY_THRESHOLD_CM,
		0.5f, 0, { } },
		
        { "Light sensor",
                "Dyna Image Corporation",
                1, SENSORS_HANDLE_BASE+ID_L,
                SENSOR_TYPE_LIGHT, 10240.0f, 1.0f, 0.5f, 0, { } },

	{ "Pressure sensor",
                "ms5607",
                1, SENSORS_HANDLE_BASE+ID_PR,
                SENSOR_TYPE_PRESSURE, 110000.0f, 1.0f, 1.0f, 30000, { } },

	{ "Temperature sensor",
                "ms5607",
                1, SENSORS_HANDLE_BASE+ID_TMP,
                SENSOR_TYPE_AMBIENT_TEMPERATURE, 110000.0f, 1.0f, 1.0f, 30000, { } },
	
       /* { "CM3602 Proximity sensor",
                "Capella Microsystems",
                1, SENSORS_HANDLE_BASE+ID_P,
                SENSOR_TYPE_PROXIMITY,
                PROXIMITY_THRESHOLD_CM, PROXIMITY_THRESHOLD_CM,
                0.5f, 0, { } },
        { "CM3602 Light sensor",
                "Capella Microsystems",
                1, SENSORS_HANDLE_BASE+ID_L,
                SENSOR_TYPE_LIGHT, 10240.0f, 1.0f, 0.5f, 0, { } },
		*/
};

static int open_sensors(const struct hw_module_t* module, const char* name,
        struct hw_device_t** device);

static int sensors__get_sensors_list(struct sensors_module_t* module,
        struct sensor_t const** list)
{
    *list = sSensorList;
    return ARRAY_SIZE(sSensorList);
}

static struct hw_module_methods_t sensors_module_methods = {
    .open = open_sensors
};

 struct sensors_module_t HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .version_major = 1,
        .version_minor = 0,
        .id = SENSORS_HARDWARE_MODULE_ID,
        .name = "MMA8451Q & AK8973A & gyro Sensors Module",
        .author = "The RKdroid Project",
        .methods = &sensors_module_methods,
    },
    .get_sensors_list = sensors__get_sensors_list
};

/*****************************************************************************/

static int open_sensors(const struct hw_module_t* module, const char* name,
        struct hw_device_t** device)
{
    return init_nusensors(module, device);
}
