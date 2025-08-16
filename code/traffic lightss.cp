#line 1 "C:/Users/workstation/Documents/.idea/calc/calcproj1_G/build/empty/my final project in emb _y/code/traffic lightss.c"
#line 13 "C:/Users/workstation/Documents/.idea/calc/calcproj1_G/build/empty/my final project in emb _y/code/traffic lightss.c"
char led[ 4 ] = {0b00100001, 0b00110001, 0b00001100, 0b00001110};
char current_led = 0;
char counter = 0;
char delay_count =0;
char temp_portd = 0;
char rr =0;
char ll = 0;
char ii = 0;


void manual_mode() {
 while (portb.b0 == 0) {
 portc = 0;
 portd = led[current_led];

 if (portb.b1 == 0) {
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

 if (current_led ==  4  | portb.b0 == 1) {
 current_led = 0;
 }
 }
}


void interrupt() {
 if (intf_bit == 1) {
 intf_bit = 0;
 portc=0;
 temp_portd = portd;
  portd.b0 =1;
  portd.b5 =1;

 manual_mode();
 portd = temp_portd;
 }
}


void automatic_mode() {
 if(portb.b0 == 1) {
 rr=20;
  portd.b0  = 1;
  portd.b5  = 1;
 for (ii=0; ii < 23; ii++) {
 ll = 23 - ii;

 if (ll == 3) {
 rr = 3;
  portd.b4  = 1;
  portd.b5  = 0;
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
 if(portb.b0 == 0){ portc=0;
portd=0;
break;}}
  portd.b4  = 0;
  portd.b0  = 0;


 rr = 12;
  portd.b3  = 1;
  portd.b2  = 1;
 for (ii = 0; ii < 15; ii++) {
 ll = 15 - ii;

 if (ll == 3) {
 rr = 3;
  portd.b1  = 1;
  portd.b2  = 0;
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
 if(portb.b0 == 0){ portc=0;
portd=0;
break;}}
 rr--;
 if(portb.b0 == 0){ portc=0;
portd=0;
break;}}
  portd.b3  = 0;
  portd.b1  = 0;
 rr=0;
} }


void main() {

 trisb = 0;
 trisb.b0 = 1;
 trisb.b1 = 1;
 trisc = 0;
 trisd = 0;


 portb.b2 = 1;
 portb.b4 = 1;
 portc = 0;
 portd = 0;


 gie_bit = 1;
 inte_bit = 1;
 intedg_bit = 0;
 option_reg.b7 = 0;

 while (1) {
 automatic_mode();
 }
}
