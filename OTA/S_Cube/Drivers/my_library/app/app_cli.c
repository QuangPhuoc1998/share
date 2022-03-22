#include "app_cli.h"

void app_cli_task(void * pv_params);

static uint8_t app_cli_get_temperature(uint8_t argc, const char *argv[], char *out_buffer, uint16_t out_max);

static uint8_t app_cli_get_humidity(uint8_t argc, const char *argv[], char *out_buffer, uint16_t out_max);

static uint8_t app_cli_get_veloc(uint8_t argc, const char *argv[], char *out_buffer, uint16_t out_max);

static uint8_t app_cli_led_control(uint8_t argc, const char *argv[], char *out_buffer, uint16_t out_max);

CLI_Command_t temperature_definition =
    {
        .CLI_Command = "get_temp",
        .CLI_Command_Description = "Get temperature value",
        .CLI_Callback = app_cli_get_temperature,
};
		
CLI_Command_t humidity_definition =
    {
        .CLI_Command = "get_hum",
        .CLI_Command_Description = "Get humidity value",
        .CLI_Callback = app_cli_get_humidity,
};
		
CLI_Command_t veloc_definition =
    {
        .CLI_Command = "get_veloc",
        .CLI_Command_Description = "Get veloc value",
        .CLI_Callback = app_cli_get_veloc,
};
		
CLI_Command_t led_control_definition =
    {
        .CLI_Command = "led",
        .CLI_Command_Description = "Control led",
        .CLI_Callback = app_cli_led_control,
};

void app_cli_init(void)
{
	ftr_cli_add_command(&temperature_definition);
	ftr_cli_add_command(&humidity_definition);
	ftr_cli_add_command(&veloc_definition);
	ftr_cli_add_command(&led_control_definition);
}

void app_cli_task(void * pv_params)
{
	
}

static uint8_t app_cli_get_temperature(uint8_t argc, const char *argv[], char *out_buffer, uint16_t out_max)
{
	uint8_t temp = 34;
	snprintf(out_buffer, out_max, "=> Temp: %d oC\n", temp);
	return 0;
}

static uint8_t app_cli_get_humidity(uint8_t argc, const char *argv[], char *out_buffer, uint16_t out_max)
{
	uint8_t hum = 77;
	snprintf(out_buffer, out_max, "=> Hum: %d %%\n", hum);
	return 0;
}

static uint8_t app_cli_get_veloc(uint8_t argc, const char *argv[], char *out_buffer, uint16_t out_max)
{
	uint8_t temp = 34;
	snprintf(out_buffer, out_max, "=> Veloc: %d m/s\n", temp);
	return 0;
}

static uint8_t app_cli_led_control(uint8_t argc, const char *argv[], char *out_buffer, uint16_t out_max)
{
	if(strstr(argv[1], "green"))
	{ 
		if(strstr(argv[2], "on"))
		{
			BSP_LED_On(LED_GREEN);
			snprintf(out_buffer, out_max, "=> Led green on\n");
		}
		else if(strstr(argv[2], "off"))
		{
			BSP_LED_Off(LED_GREEN);
			snprintf(out_buffer, out_max, "=> Led green off\n");
		}
		else
		{
			snprintf(out_buffer, out_max, "=> Wrong parameter\n");
		}
	}	
	else if(strstr(argv[1], "red"))
	{
		if(strstr(argv[2], "on"))
		{
			BSP_LED_On(LED_RED);
			snprintf(out_buffer, out_max, "=> Led red on\n");
		}
		else if(strstr(argv[2], "off"))
		{
			BSP_LED_Off(LED_RED);
			snprintf(out_buffer, out_max, "=> Led red off\n");
		}
		else
		{
			snprintf(out_buffer, out_max, "=> Wrong parameter\n");
		}
	}
	else
	{
		snprintf(out_buffer, out_max, "=> Wrong parameter\n");
	}
	return 0;
}
