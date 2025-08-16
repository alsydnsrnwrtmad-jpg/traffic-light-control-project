#define COUNTLED 4

// Led Port Definitions
#define ledR1 portd.b0
#define ledY1 portd.b1
#define ledG1 portd.b2
#define ledR2 portd.b3
#define ledY2 portd.b4
#define ledG2 portd.b5


// Global Variables
char led[COUNTLED] = {0b00100001, 0b00110001, 0b00001100, 0b00001110};
char current_led = 0;
char counter = 0;
char delay_count =0;
char temp_portd = 0;
char rr =0;
char ll = 0;
char ii = 0;

// Manual Mode Function
void manual_mode() {
    while (portb.b0 == 0) {  // Wait until manual mode is deactivated
        portc = 0;
        portd = led[current_led];

        if (portb.b1 == 0) {  // Cycle through LED patterns on button press
            portd = led[++current_led];
            for (counter = 0; counter <3; counter++) {
                for (delay_count = 0; delay_count <= 50; delay_count++) {
                    portb.b2 = 0;
            portb.b3 = 1;
            portb.b4 = 0;
            portb.b5 = 1;

                    portc = 0;
                    delay_ms(5);

                 portb.b2 = 1;
            portb.b3 = 0;
            portb.b4 = 1;
            portb.b5 = 0;
                    portc = (((3 - counter) % 10) << 4) | (((3 - counter) % 10) & 0x0F);
                    delay_ms(10);
                }
            }
            current_led ++;
        }

        if (current_led == COUNTLED | portb.b0 == 1) {
            current_led = 0;  // Reset LED index
        }
    }
}

// Interrupt Handler Function
void interrupt() {
    if (intf_bit == 1) {
        intf_bit = 0;
        portc=0;
        temp_portd = portd;
        ledR1=1;
        ledG2=1;

        manual_mode();
        portd = temp_portd;
    }
}

// Automatic Mode Function
void automatic_mode() {
 if(portb.b0 == 1) {
 rr=20;
    ledR1 = 1;
    ledG2 = 1;
    for (ii=0; ii < 23; ii++) {
        ll = 23 - ii;

        if (ll == 3) {
            rr = 3;
            ledY2 = 1;
            ledG2 = 0;
        }

        for (delay_count = 0; delay_count <= 50; delay_count++) {
           portb.b2 = 0;
            portb.b3 = 1;
            portb.b4 = 0;
            portb.b5 = 1;

            portc = ((rr / 10) << 4) | ((ll / 10) & 0x0F);
            delay_ms(5);


            portb.b2 = 1;
            portb.b3 = 0;
            portb.b4 = 1;
            portb.b5 = 0;

            portc = ((rr % 10) << 4) | ((ll % 10) & 0x0F);
            delay_ms(10);
        if(portb.b0 == 0){
         portc=0;
portd=0;
break;}}
        rr--;
    if(portb.b0 == 0){  portc=0;
portd=0;
break;}}
    ledY2 = 0;
    ledR1 = 0;

    // Second loop
    rr = 12;
    ledR2 = 1;
    ledG1 = 1;
    for (ii = 0; ii < 15; ii++) {
        ll = 15 - ii;

        if (ll == 3) {
            rr = 3;
            ledY1 = 1;
            ledG1 = 0;
        }

        for (delay_count = 0; delay_count <= 50; delay_count++) {
            portb.b2 = 0;
            portb.b3 = 1;
            portb.b4 = 0;
            portb.b5 = 1;

            portc = ((ll / 10) << 4) | ((rr / 10) & 0x0F);
            delay_ms(5);

            portb.b2 = 1;
            portb.b3 = 0;
            portb.b4 = 1;
            portb.b5 = 0;

            portc = ((ll % 10) << 4) | ((rr % 10) & 0x0F);
            delay_ms(10);
        if(portb.b0 == 0){  portc=0;
portd=0;
break;}}
        rr--;
    if(portb.b0 == 0){  portc=0;
portd=0;
break;}}
    ledR2 = 0;
    ledY1 = 0;
    rr=0;
} }

// Main Function
void main() {
    // Port Initialization
    trisb = 0;
    trisb.b0 = 1;  // Set RB0 as input for manual mode trigger
    trisb.b1 = 1;  // Set RB1 as input for LED cycling
    trisc = 0;
    trisd = 0;

    // Initial Port States
    portb.b2 = 1;
    portb.b4 = 1;
    portc = 0;
    portd = 0;

    // Enable Interrupts
    gie_bit = 1;
    inte_bit = 1;
    intedg_bit = 0;
    option_reg.b7 = 0;

    while (1) {
        automatic_mode();  // Default to automatic mode
    }
}