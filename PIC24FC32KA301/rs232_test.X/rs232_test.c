/* 
 * File:   rs232_test.c
 * Author: erik
 *
 * Created on November 5, 2014, 9:55 PM
 */

#include <xc.h>

// FBS
#pragma config BWRP = OFF               // Boot Segment Write Protect (Disabled)
#pragma config BSS = OFF                // Boot segment Protect (No boot program flash segment)

// FGS
#pragma config GWRP = OFF               // General Segment Write Protect (General segment may be written)
#pragma config GSS0 = OFF               // General Segment Code Protect (No Protection)

// FOSCSEL
#pragma config FNOSC = FRCDIV           // Oscillator Select (8MHz FRC oscillator With Postscaler (FRCDIV))
#pragma config SOSCSRC = DIG            // SOSC Source Type (Digital Mode for use with external source)
#pragma config LPRCSEL = HP             // LPRC Oscillator Power and Accuracy (High Power, High Accuracy Mode)
#pragma config IESO = ON                // Internal External Switch Over bit (Internal External Switchover mode enabled (Two-speed Start-up enabled))

// FOSC
#pragma config POSCMOD = NONE           // Primary Oscillator Configuration bits (Primary oscillator disabled)
#pragma config OSCIOFNC = ON            // CLKO Enable Configuration bit (CLKO output signal is active on the OSCO pin)
#pragma config POSCFREQ = HS            // Primary Oscillator Frequency Range Configuration bits (Primary oscillator/external clock input frequency greater than 8MHz)
#pragma config SOSCSEL = SOSCHP         // SOSC Power Selection Configuration bits (Secondary Oscillator configured for high-power operation)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Both Clock Switching and Fail-safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPS = PS32768          // Watchdog Timer Postscale Select bits (1:32768)
#pragma config FWPSA = PR128            // WDT Prescaler bit (WDT prescaler ratio of 1:128)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bits (WDT disabled in hardware; SWDTEN bit disabled)
#pragma config WINDIS = OFF             // Windowed Watchdog Timer Disable bit (Standard WDT selected(windowed WDT disabled))

// FPOR
#pragma config BOREN = BOR0             // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware, SBOREN bit disabled)
#pragma config LVRCFG = OFF             //  (Low Voltage regulator is not available)
#pragma config PWRTEN = ON              // Power-up Timer Enable bit (PWRT enabled)
#pragma config I2C1SEL = PRI            // Alternate I2C1 Pin Mapping bit (Use Default SCL1/SDA1 Pins For I2C1)
#pragma config BORV = V20               // Brown-out Reset Voltage bits (Brown-out Reset set to lowest voltage (2.0V))
#pragma config MCLRE = ON               // MCLR Pin Enable bit (RA5 input pin disabled,MCLR pin enabled)

// FICD
#pragma config ICS = PGx1               // ICD Pin Placement Select bits (EMUC/EMUD share PGC1/PGD1)

// FDS
#pragma config DSWDTPS = DSWDTPSF       // Deep Sleep Watchdog Timer Postscale Select bits (1:2,147,483,648 (25.7 Days))
#pragma config DSWDTOSC = LPRC          // DSWDT Reference Clock Select bit (DSWDT uses Low Power RC Oscillator (LPRC))
#pragma config DSBOREN = ON             // Deep Sleep Zero-Power BOR Enable bit (Deep Sleep BOR enabled in Deep Sleep)
#pragma config DSWDTEN = ON             // Deep Sleep Watchdog Timer Enable bit (DSWDT enabled)



/*
 * 
 */
int main()
{
//    ANSA = 0x00;
//    ANSB = 0x00;
//    ANSBbits.ANSB14 = 0b0;
//    ANSBbits.ANSB13 = 0b0;
//    TRISA = 0x00;
//    TRISB = 0x00;
//    TRISAbits.TRISA3 = 0b0;
    ANSBbits.ANSB4 = 0;
    TRISBbits.TRISB7 = 0;
    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB9 = 0;

    U1MODEbits.BRGH = 1;
    U1BRG = 8;
    U1MODEbits.UARTEN = 0b1;
    U1STAbits.UTXEN = 1;
    int i = 0, j = 0, k = 0;
    while(1)
    {
        if (U1STAbits.TRMT == 1)
        {
            //LATBbits.LATB8 = i;
            i += 1;
            if (i == 5)
            {
                U1TXREG = 0x01;
                i = 0;
            }
            else
            {
                U1TXREG = 0xA3;

            }
        }
        U1STAbits.OERR = 0;
        if (U1STAbits.URXDA == 1)
        {
            k += 1;
            LATBbits.LATB8 = k;
            j = U1RXREG;
            IFS0bits.U1RXIF = 0;

            
        }
        if (j == 0xA3)
        {
            LATBbits.LATB9 = 1;
        }
        else
        {
            LATBbits.LATB9 = 0;
        }
        //LATBbits.LATB8 = 0;
        //LATBbits.LATB8 = U1STAbits.OERR;
        //LATA = i;
        //LATB = i;
    }
    return 0;
}

