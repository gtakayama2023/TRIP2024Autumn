#include "signal.h"
// function to exit loop at keyboard interrupt. 
bool stoploop = false;
void sig_interrupt(int signo){
  if(signo == SIGINT){
    cout << "=================================" << endl;
    cout << "Keyboard interrupt is detected." << endl;
    cout << "=================================" << endl;
    stoploop = true;
  }
}
