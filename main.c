#include <msp430.h> 
#include <signal.h>

#define kPeriod  3000      // 12000/6000 = 2Hz

void initializeMCU(void){
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //Setup Clock
    BCSCTL3 |= LFXT1S_2;    //Select VLO for ACLK
    //Setup Port1
    P1SEL &= ~(BIT0 + BIT6);
    P1DIR |= (BIT0 + BIT6);

    //Setup Timer_A
    TACTL = TASSEL_1 + ID_0 + MC_1;
    TACCR0 = kPeriod;                   // é¸ä˙ê›íË
    TACCTL0 |= CCIE;                    // enable interrupt
}

//TimeräÑÇËçûÇ›ÉCÉxÉìÉgä÷êî
#pragma vector = TIMER0_A0_VECTOR
__interrupt void interruputPort1Test(void)
{
    P1OUT ^= (BIT0 + BIT6);
    //TACTL = TASSEL_1 + ID_0 + MC_0;     //Timerí‚é~
}

/**
 * main.c
 */
void main(void)
{
	initializeMCU();
	_BIS_SR(GIE);
	_BIS_SR(SCG0 | SCG0 | CPUOFF);  //goes in LPM3
	for(;;);

}
