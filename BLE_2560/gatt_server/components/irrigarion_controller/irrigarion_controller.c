#include "irrigation_controller.h"
#include "nvs_flash.h"
#include "nvs.h"
// #include "nvs.hpp"


// Global data for storing all the program information:
Irrigation_program irrigation_program[4];

void irrig_controller_init_data()
{
    esp_err_t ret;
    // Initialize NVS:
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Open
    printf("\n");
    printf("Opening Non-Volatile Storage (NVS): ");
    nvs_handle_t my_handle;
    ret = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (ret != ESP_OK)
    {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(ret));
    }
    else
    {
        printf("Done\n");
        // Read
        printf("Reading restart counter from NVS ... ");
        //int32_t restart_counter = 0; // value will default to 0, if not set yet in NVS
        irrigation_program[0].water_percentage = 12;
        nvs_handle_t my_handle;
        // ret = nvs_get_i8(my_handle, "a_water_percentage", &irrigation_program[0].water_percentage);
        // printf((ret != ESP_OK) ? "Failed!\n" : "Done Getting a_water_percentage\n");
        // printf("%i", irrigation_program[0].water_percentage);
/*
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");

        ret = nvs_set_i8(my_handle, "a_start_hour_0", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_start_hour_1", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_start_hour_2", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_start_hour_3", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");

        ret = nvs_set_i8(my_handle, "a_start_min_0", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_start_min_1", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_start_min_2", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_start_min_3", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");

        ret = nvs_set_i8(my_handle, "a_time_hour_v0", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_hour_v1", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_hour_v2", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_hour_v3", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_hour_v4", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_hour_v5", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_hour_v6", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_hour_v7", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");

        ret = nvs_set_i8(my_handle, "a_time_min_v0", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_min_v1", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_min_v2", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_min_v3", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_min_v4", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_min_v5", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_min_v6", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_min_v7", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
*/
        //Get the data:
        // for (uint8_t index_program = 0; index_program < MAX_NUMBER_PROGRAM; index_program++)
        // {
        //     nvs_get_i8(my_handle, "prog_A_", &restart_counter);
        //     uint8_t water_percentage;               //0 - 10 -20 -  400%
        //     uint8_t start_hour[MAX_NUMBER_PROGRAM]; //0-24 h
        //     uint8_t start_min[MAX_NUMBER_PROGRAM];  //0-59 min
        //     uint8_t time_hour[MAX_NUMBER_VALVES];   //0 min a 12 min
        //     uint8_t time_min[MAX_NUMBER_VALVES];    //0 min a 60 min
        // }
        // switch (ret)
        // {
        // case ESP_OK:
        //     printf("Done\n");
        //     printf("Restart counter = %d\n", restart_counter);
        //     break;
        // case ESP_ERR_NVS_NOT_FOUND:
        //     printf("The value is not initialized yet!\n");
        //     break;
        // default:
        //     printf("Error (%s) reading!\n", esp_err_to_name(ret));
        // }

        // Write
        /*
        printf("Writing program data from nvs memmory: ");

        ret = nvs_set_i8(my_handle, "a_water_percentage", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");

        ret = nvs_set_i8(my_handle, "a_start_hour_0", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_start_hour_1", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_start_hour_2", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_start_hour_3", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");

        ret = nvs_set_i8(my_handle, "a_start_min_0", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_start_min_1", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_start_min_2", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_start_min_3", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");

        ret = nvs_set_i8(my_handle, "a_time_hour_v0", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_hour_v1", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_hour_v2", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_hour_v3", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_hour_v4", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_hour_v5", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_hour_v6", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_hour_v7", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");

        ret = nvs_set_i8(my_handle, "a_time_min_v0", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_min_v1", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_min_v2", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_min_v3", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_min_v4", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_min_v5", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_min_v6", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        ret = nvs_set_i8(my_handle, "a_time_min_v7", 0);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
        // Commit written value.
        // After setting any values, nvs_commit() must be called to ensure changes are written
        // to flash storage. Implementations may write to storage at other times,
        // but this is not guaranteed.
        printf("Committing updates in NVS ... ");
        ret = nvs_commit(my_handle);
        printf((ret != ESP_OK) ? "Failed!\n" : "Done\n");
*/
        // Close
        nvs_close(my_handle);
    }
}

void irrig_controller_save_data()
{
    for (uint8_t index_program = 0; index_program < MAX_NUMBER_PROGRAM; index_program++)
    {
        printf("%i", irrigation_program[index_program].water_percentage);
    }
}
