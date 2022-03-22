/*
 * app_cli.c
 *
 * Created: 10/29/2021 3:19:53 PM
 *  Author: phuoc
 */ 
#include "app_cli.h"

#define MAX_DATA_ROW 3
#define MAX_DATA_COL 3

rtc_t my_rtc;

static uint8_t app_cli_slip_time_data(uint8_t * data_in, rtc_t * rtc);

static uint8_t app_cli_slip_date_data(uint8_t * data_in, rtc_t * rtc);

static uint8_t app_cli_set_time(uint8_t argc, const char *argv[], char *out_buffer, uint16_t out_max);

static uint8_t app_cli_set_date(uint8_t argc, const char *argv[], char *out_buffer, uint16_t out_max);

static uint8_t app_cli_sensor(uint8_t argc, const char *argv[], char *out_buffer, uint16_t out_max);

static uint8_t app_cli_led(uint8_t argc, const char *argv[], char *out_buffer, uint16_t out_max);

CLI_Command_t time_definition =
{
	.CLI_Command = "AT+TIME",
	.CLI_Command_Description = "Set time",
	.CLI_Callback = app_cli_set_time,
};

CLI_Command_t date_definition =
{
	.CLI_Command = "AT+DATE",
	.CLI_Command_Description = "Set date",
	.CLI_Callback = app_cli_set_date,
};

CLI_Command_t sensor_definition =
{
	.CLI_Command = "AT+SENSOR",
	.CLI_Command_Description = "Get sensor",
	.CLI_Callback = app_cli_sensor,
};

CLI_Command_t led_definition =
{
	.CLI_Command = "AT+LED",
	.CLI_Command_Description = "Control led",
	.CLI_Callback = app_cli_led,
};

void app_cli_init(void)
{
	ftr_cli_add_command(&time_definition);
	ftr_cli_add_command(&date_definition);
	ftr_cli_add_command(&sensor_definition);
	ftr_cli_add_command(&led_definition);
}

static uint8_t app_cli_set_time(uint8_t argc, const char *argv[], char *out_buffer, uint16_t out_max)
{
	switch (argv[0][time_definition.CLI_Command_Length])
	{
		case 0x0A:
			sprintf(out_buffer, "=> Nothing to execution\n");
			break;
		case '=':
			if(argv[0][time_definition.CLI_Command_Length+1] == '?')
			{
				sprintf(out_buffer, "=> AT+TIME=hour,minute,second\n");
			}
			else
			{	
				ds1307_get_time(&my_rtc);
				app_cli_slip_time_data((uint8_t * )argv[0], &my_rtc);
				ds1307_set_time(&my_rtc);
				sprintf(out_buffer, "=> OK\n");
			}
			break;
		case '?':
			ds1307_get_time(&my_rtc);
			sprintf(out_buffer,"=> %d:%d:%d\n", my_rtc.hour,my_rtc.min,my_rtc.sec);
			break;
		default:
			sprintf(out_buffer, "=> Error format\n");
			break;
	}
	return 0;
}
static uint8_t app_cli_set_date(uint8_t argc, const char *argv[], char *out_buffer, uint16_t out_max)
{
	switch (argv[0][date_definition.CLI_Command_Length])
	{
		case 0x0A:
		sprintf(out_buffer, "=> Nothing to execution\n");
		break;
		case '=':
		if(argv[0][time_definition.CLI_Command_Length+1] == '?')
		{
			sprintf(out_buffer, "=> AT+DATE=date,month,year\n");
		}
		else
		{
			ds1307_get_time(&my_rtc);
			app_cli_slip_date_data((uint8_t * )argv[0], &my_rtc);
			ds1307_set_time(&my_rtc);
			sprintf(out_buffer, "=> OK\n");
		}
		break;
		case '?':
		ds1307_get_time(&my_rtc);
		sprintf(out_buffer,"=> %d/%d/%d\n", my_rtc.date,my_rtc.month,my_rtc.year);
		break;
		default:
		sprintf(out_buffer,"=> Error format\n");
		break;
	}
	return 0;
}

static uint8_t app_cli_sensor(uint8_t argc, const char *argv[], char *out_buffer, uint16_t out_max)
{
	switch (argv[0][sensor_definition.CLI_Command_Length])
	{
		case 0x0A:
			sprintf(out_buffer, "=> Nothing to execution\n");
			break;
		case '=':
			if(argv[0][sensor_definition.CLI_Command_Length+1] == '?')
			{
				sprintf(out_buffer, "=> AT+SENSOR=sensor name\n");
			}
			else
			{
				if(strstr(argv[0], "temp"))
				{
					sprintf(out_buffer, "=> temp = %d oC\n", ftr_sensor_get_temperature());
				}
				else
				{
					sprintf(out_buffer, "=> Wrong parameter\n");
				}
			}
			break;
		case '?':
			sprintf(out_buffer, "=> AT+SENSOR=sensor_name\n");
			break;
		default:
			sprintf(out_buffer,"=> Error format\n");
			break;
	}
	return 0;
}

static uint8_t app_cli_led(uint8_t argc, const char *argv[], char *out_buffer, uint16_t out_max)
{
	switch (argv[0][led_definition.CLI_Command_Length])
	{
		case 0x0A:
		sprintf(out_buffer, "=> Nothing to execution\n");
		break;
		case '=':
		if(argv[0][led_definition.CLI_Command_Length+1] == '?')
		{
			sprintf(out_buffer, "=> AT+LED=led name,status\n");
		}
		else
		{
			if(strstr(argv[0], "led1") && strstr(argv[0], "on"))
			{
				cbi(PORTB, 0);
				sprintf(out_buffer, "=> OK\n");
			}
			else if(strstr(argv[0], "led1") && strstr(argv[0], "off"))
			{
				sbi(PORTB, 0);
				sprintf(out_buffer, "=> OK\n");
			}
			else if(strstr(argv[0], "led2") && strstr(argv[0], "on"))
			{
				cbi(PORTB, 1);
				sprintf(out_buffer, "=> OK\n");
			}
			else if(strstr(argv[0], "led2") && strstr(argv[0], "off"))
			{
				sbi(PORTB, 1);
				sprintf(out_buffer, "=> OK\n");
			}
			else
			{
				sprintf(out_buffer, "=> Wrong parameter\n");
			}
		}
		break;
		case '?':
			sprintf(out_buffer, "=> AT+LED=led name,status\n");
			break;
		default:
			sprintf(out_buffer,"=> Error format\n");
		break;
	}
	return 0;
}

static uint8_t app_cli_slip_time_data(uint8_t * data_in, rtc_t * rtc)
{
	uint8_t i;
	char ** p_data;
	char* p_token;
	/*--- memory allocation ---*/
	p_data = (char **)malloc(MAX_DATA_ROW * sizeof(char *));
	for (i = 0; i < MAX_DATA_ROW; i++)
	{
		p_data[i] = (char *)malloc(MAX_DATA_COL * sizeof(char));
	}
	/*--------Splip data--------*/
	i = 0;
	p_token = strtok(strstr((char *)data_in, "="), ",");
	p_token++;
	while (i < MAX_DATA_ROW && p_token != NULL)
	{
		strcpy(p_data[i], p_token);
		p_token = strtok(NULL, ",");
		i++;
	}
	/*--- Printf ---*/
	if(i != MAX_DATA_ROW)
	{
		for (i = 0; i < MAX_DATA_ROW; i++)
		{
			free(p_data[i]);
		}
		free(p_data);
		return 1;
	}
	/*--- Assign value ---*/
	rtc->hour = atoi(p_data[0]);
	rtc->min = atoi(p_data[1]);
	rtc->sec = atoi(p_data[2]);
	/*--- Free memory ---*/
	for (i = 0; i < MAX_DATA_ROW; i++)
	{
		free(p_data[i]);
	}
	free(p_data);
	return 0;
}

static uint8_t app_cli_slip_date_data(uint8_t * data_in, rtc_t * rtc)
{
	uint8_t i;
	char ** p_data;
	char* p_token;
	/*--- memory allocation ---*/
	p_data = (char **)malloc(MAX_DATA_ROW * sizeof(char *));
	for (i = 0; i < MAX_DATA_ROW; i++)
	{
		p_data[i] = (char *)malloc(MAX_DATA_COL * sizeof(char));
	}
	/*--------Splip data--------*/
	i = 0;
	p_token = strtok(strstr((char *)data_in, "="), ",");
	p_token++;
	while (i < MAX_DATA_ROW && p_token != NULL)
	{
		strcpy(p_data[i], p_token);
		p_token = strtok(NULL, ",");
		i++;
	}
	/*--- Printf ---*/
	if(i != MAX_DATA_ROW)
	{
		for (i = 0; i < MAX_DATA_ROW; i++)
		{
			free(p_data[i]);
		}
		free(p_data);
		return 1;
	}
	/*--- Assign value ---*/
	rtc->date = atoi(p_data[0]);
	rtc->month = atoi(p_data[1]);
	rtc->year = atoi(p_data[2]);
	/*--- Free memory ---*/
	for (i = 0; i < MAX_DATA_ROW; i++)
	{
		free(p_data[i]);
	}
	free(p_data);
	return 0;
}