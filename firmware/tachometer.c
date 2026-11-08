#include <reg51.h>

/* ---------------- LCD ---------------- */
#define LCD P2
sbit RS = P1^0;
sbit EN = P1^1;

/* ---------------- GLOBALS ---------------- */
volatile unsigned int pulse_count = 0;
volatile bit one_sec_flag = 0;

/* ---------------- SMALL DELAY ---------------- */
void delay_us(void)
{
    unsigned char i;
    for(i = 0; i < 50; i++);
}

/* ---------------- LCD FUNCTIONS ---------------- */
void lcd_cmd(unsigned char cmd)
{
    RS = 0;
    LCD = cmd;
    EN = 1;
    delay_us();
    EN = 0;
}

void lcd_data(unsigned char dat)
{
    RS = 1;
    LCD = dat;
    EN = 1;
    delay_us();
    EN = 0;
}

void lcd_string(char *s)
{
    while(*s)
        lcd_data(*s++);
}

void lcd_init(void)
{
    unsigned int i;
    for(i = 0; i < 50000; i++);

    lcd_cmd(0x38);   // 8-bit, 2-line
    lcd_cmd(0x0C);   // Display ON
    lcd_cmd(0x06);   // Auto increment
    lcd_cmd(0x01);   // Clear display
}

/* ---------------- INT0 ISR ---------------- */
void ext0_isr(void) interrupt 0
{
    pulse_count++;
}

/* ---------------- TIMER0 ISR ---------------- */
/* 50 ms tick */
void timer0_isr(void) interrupt 1
{
    static unsigned char ticks = 0;

    TH0 = 0x3C;
    TL0 = 0xB0;

    ticks++;
    if(ticks >= 100)    // 100 × 50 ms = 5 second
    {
        ticks = 0;
        one_sec_flag = 1;
    }
}

/* ---------------- MAIN ---------------- */
void main(void)
{
    unsigned int rpm;
    unsigned char d1, d2, d3, d4;

    lcd_init();

    /* ---- INT0 setup ---- */
    EA  = 0;
    IT0 = 1;      // Falling-edge triggered
    EX0 = 1;      // Enable INT0
    EA  = 1;

    /* ---- Timer0 setup ---- */
    TMOD = 0x01;  // Timer0 Mode 1
    TH0  = 0x3C;
    TL0  = 0xB0;
    ET0  = 1;
    TR0  = 1;

    while(1)
    {
        pulse_count = 0;
        one_sec_flag = 0;

        while(!one_sec_flag);   // Wait 1 second

        /* 1 pulse per revolution */
        rpm = (pulse_count * 60) / 5;

        d1 = (rpm / 1000) % 10;
        d2 = (rpm / 100)  % 10;
        d3 = (rpm / 10)   % 10;
        d4 = rpm % 10;

        lcd_cmd(0x80);
        lcd_string("RPM: ");
        lcd_data(d1 + '0');
        lcd_data(d2 + '0');
        lcd_data(d3 + '0');
        lcd_data(d4 + '0');
    }
}
