/*
 * Calculato.c
 *
 * Created: 23/02/2023 07:40:24 م
 *  Author: Menna Eid
 */ 
#include "../MCAL/DIO/StdTypes.h"
#include "../MCAL/DIO/Registers1.h"
#include "../MCAL/DIO/DIO_priv.h"
#include "../MCAL/DIO/errorstate.h"
#include "../MCAL/DIO/DI0_interface.h"
#include "../ECUAL/LCD/LCD_Interface.h"
#include "../ECUAL/KeyPad/KETPAD_INTERFACE.h"
#include "Calculator.h"

ES_t enCalculator()
{
	ES_t LocalErrorState= ES_OK;
	static s32  _result;
    s32 num1=0;
    s32 num2=0;
	uint8_t Localu8Iter=0;
	static uint8_t arrNum[7];
     uint8_t _keyvalue;
    uint8_t volatile _operation;
    uint8_t _sizeArr=0;
	uint8_t Localu8Flag;
	// take input from keypad
	while(1)
	{
		_keyvalue = KeyPad_u8KeyPressedVal(&Localu8Flag);
		if(Localu8Flag==HIGH)
		{
			if(_keyvalue=='=')
			{
				LCD_enDisplayChar(_keyvalue);
				break;
			}
			else if(_keyvalue=='c')
			{
				continue;
			}
			else
			{
				LCD_enDisplayChar(_keyvalue);
				arrNum[Localu8Iter]=_keyvalue;
				switch(arrNum[Localu8Iter])
				{
					case '+':
					_operation=Localu8Iter;
					break;
					case '-':
					_operation=Localu8Iter;
					break;
					case '/':
					_operation=Localu8Iter;
					break;
					case 'x':
					_operation=Localu8Iter;
					break;
					
				}
				_sizeArr++;
				Localu8Flag=LOW;
				Localu8Iter++;
			}
		}
	}
	
	// calc num1
	for(Localu8Iter=0;Localu8Iter<_operation;Localu8Iter++)
	{
		num1 = num1*10 + (arrNum[Localu8Iter]-'0');
	}
	// calc num2
	for(Localu8Iter=_operation+1;Localu8Iter<_sizeArr;Localu8Iter++)
	{
		num2 = num2*10 + (arrNum[Localu8Iter]-'0');
	}
	// calc result
	switch(arrNum[_operation])
	{
		case '+':
			_result= num1+num2;
			break;
		case '-':
			_result= num1-num2;
			break;
		case 'x':
			_result= num1*num2;
			break;
		case '/':
		_result= num1/num2;
		break;
		
	   
	} 
	LCD_enDisplayNum(_result);
	
	return LocalErrorState;
	
}