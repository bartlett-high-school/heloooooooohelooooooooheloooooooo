#include "main.h"
//Custom Electonics Ports
int ce_write = 17;
int ce_read = 13;

//Comm variables
pros::Serial *ce_port_w = nullptr;
pros::Serial *ce_port_r = nullptr;

void init_comm(){
  //Setup the ports
  ce_port_w = new pros::Serial(ce_write);
  ce_port_r = new pros::Serial(ce_read);
}

//flush the comm ports
void flush(){
  ce_port_w->flush();
  pros::delay(100);
  ce_port_r->flush();
}

//set the port baud rate
void setBaud(){
  ce_port_w->set_baudrate(115200);
  ce_port_r->set_baudrate(115200);
}

//read byte from port and print to cout
void recv_print(){
  //Read byte command
  int32_t r = ce_port_r->read_byte();
  //Check if error

    if(r == PROS_ERR){
      std::cout << pros::millis() << " Error read " << r << std::endl;
    } else {
      //Print recieved byte
      std::cout << pros::millis() << " Passs Read " << r << std::endl;
    }


}

void send_print(char value){
	//Send the value byte
  int32_t w = ce_port_w->write_byte(value);
	std::cout << "Sent Value " << value << std::endl;
  pros::delay(3);
}


void initialize() {
	//Set up the communication. Takes about 1/8th of a second
	init_comm();
	pros::delay(10);
	flush();
	pros::delay(10);
	setBaud();


}


void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
    int New = 0;
    int32_t r1,r2,r3,r4;
while (true){
      send_print('a');
      pros::delay(5);
      r1 = ce_port_r->read_byte();
      pros::delay(5);
      r2 = ce_port_r->read_byte();
      pros::delay(5);
      r3 = ce_port_r->read_byte();
      pros::delay(5);
      r4 = ce_port_r->read_byte();
      pros::delay(5);

      New += r1 << 24;
      New += r2 << 16;
      New += r3 << 8;
      New += r4;

      std::cout << "enc val: " << New << '\n';

      New = 0;

}
}
