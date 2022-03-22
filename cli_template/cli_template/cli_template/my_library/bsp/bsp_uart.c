#include "main.h"
#include "bsp_uart.h"

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

bsp_uart_function_handle_t bsp_uart_callback;

void bsp_uart_init(long USART_BAUDRATE)
{
	// set baudrate in UBRR
	UBRR0L = (uint8_t)(BAUD_PRESCALE & 0xFF);
	UBRR0H = (uint8_t)(BAUD_PRESCALE >> 8);

	// enable the transmitter and receiver
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);;
		
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);/* Use 8-bit character sizes */
}

unsigned char bsp_uart_read_char()
{
	while ((UCSR0A & (1 << RXC0)) == 0);/* Wait till data is received */
	return(UDR0);			/* Return the byte*/
}

void bsp_uart_read_string(char *Output, unsigned int length)
{
	for(int i=0;i<length;i++)
	Output[i] = bsp_uart_read_char();
}

void bsp_uart_write_char(char ch)
{
	while (! (UCSR0A & (1<<UDRE0)));	/* Wait for empty transmit buffer*/
	UDR0 = ch ;
}

void bsp_uart_send_string(char *str)
{
	unsigned char j=0;
	
	while (str[j]!=0)		/* Send string till null */
	{
		bsp_uart_write_char(str[j]);
		j++;
	}
}
void bsp_uart_set_function_handle(bsp_uart_function_handle_t pfun)
{
	bsp_uart_callback = pfun;
}

ISR (USART_RX_vect)
{
	(*bsp_uart_callback)((uint8_t)bsp_uart_read_char());
}
