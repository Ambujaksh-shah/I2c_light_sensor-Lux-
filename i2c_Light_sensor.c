#include<avr/io.h>
#include<util/delay.h>


void i2c_write(unsigned char data)
{

TWDR=data;
TWCR=(1<<TWINT)|(1<<TWEN);
while((TWCR&(1<<TWINT))==0);

}

void i2c_start(void)
{
TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
while((TWCR&(1<<TWINT))==0);
}
void i2c_stop()
{
TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}
unsigned char i2c_read(unsigned char last)
{
if(last==0)
TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);

else
TWCR=(1<<TWINT)|(1<<TWEN);

while((TWCR&(1<<TWINT))==0);
return TWDR;
} 
void i2c_init(void)
{
TWSR=0x00;
TWBR=0x68;
//TWCR=0x04;
}
unsigned char i2c_readAck(unsigned char val)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (val<<TWEA);
	while(!(TWCR & (1<<TWINT)));    

    return TWDR;

}
unsigned char i2c_readNak(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	
    return TWDR;

}
uint16_t getlux() {
	uint16_t ret = 0;

	ret = i2c_readAck();
	ret <<= 8;
	ret |= i2c_readNak();
	i2c_stop();

	ret = ret/1.2;
	return ret;
}

void main()
{
i2c_init();
i2c_start();
i2c_write(0x23);
i2c_write(0x10);
i2c_stop();
unsigned long long lux;
while(1)
{
lux=i2c_read(a); 

}
}
