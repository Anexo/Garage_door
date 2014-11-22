//	Puerta de Garaje
//	Tomás López-Fragoso Rumeu
//	22/05/2013	

//////////////////////////////////////////////////////////////////////////

//////////////////
//  PORTD		//
//			D0	// Receptor mando
//			D1	// Final de carrera alto
//			D2	// Final de carrera bajo
//			D3	// Sensor de cruce (activo a baja)
//			D4	// Motor subida
//			D5	// Motor bajada
//				//
//////////////////

//////////////////////////////////////////////////////////////////////////

//Librerías
#include <avr/io.h>
#include <util/delay.h>

//Variables:
int subiendo;
int bajando;

//Función principal
int main(void)			
{
//Puertos:
	DDRD = 0xF0;		//Parte alta como salida, parte baja como entrada.
		
//Variables:
	subiendo = 0;
	bajando = 0;		
		
	while (1)
	{
		
//Si pulsamos el mando y la puerta esta abajo.
		if ((PIND &(1<<0)) && PIND &(1<<2) )
		{
			PORTD |= 1 << PIND4;	//Activa el motor de subida.
			subiendo = 1;
		}			

//Si activa el final de carrera alto (Puerta llega arriba)
		if((PIND &(1<<1)) && subiendo == 1)
		{
			PORTD &=0 << PIND4;	//Para el motor.
			subiendo = 0;
		}				

 //Si ponemos el PinD0 a alta y la puerta esta arriba.		
		if ((PIND &(1<<0)) && PIND &(1<<1) )
		{
			PORTD |= 1 << PIND5;	//Activa el motor de bajada.
			bajando = 1;
		}
		
//Si activa el final de carrera bajo. (Puerta llega abajo)
		if((PIND &(1<<2)) && bajando == 1)
		{
			PORTD &=0 << PIND5;	//Para el motor de bajada.
			bajando = 0;
		}
		
//Si pulsamos el mando y la puerta esta subiendo: para dos segundos y baja:
		if ((PIND &(1<<0)) && subiendo == 1)
		{
			PORTD &=0 << PIND4;	//Para el motor subida
			_delay_ms(2000);
			subiendo = 0;
			bajando = 1;
			PORTD |=1 << PIND5;	//Activa el motor bajada.
			//PORTD &= ~(1 << PIND0);
		}

//Si pulsamos el mando y la puerta esta bajando: para dos segundos y sube:
		if ((PIND &(1<<0)) && bajando == 1)
		{
			PORTD &=0 << PIND5;	//Para el motor bajada
			_delay_ms(2000);
			subiendo = 1;
			bajando = 0;
			PORTD |=1 << PIND4;	//Activa el motor subida.
		}

//Sensor cruce (activo a baja) cuando la puerta baja
		if (((bit_is_clear(PIND, 3)) && bajando == 1))
		{
			PORTD &=0 << PIND5;	//Para el motor bajada
			_delay_ms(2000);
			bajando = 0;
			subiendo = 1;		
			PORTD |=1 << PIND4;	//Activa el motor subida.
		}
	
	}
}
