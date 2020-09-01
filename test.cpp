#include "DragonAudio.h"
#include <iostream>

using namespace std;


int main()
{
  DragonAudio da;

  da.playWaveFile("test.wav");

  cout<<"ready \n";
}
