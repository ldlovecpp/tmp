#include"fight.h"
int main()
{
  Roles r1;
  Roles r2;
  r1.add_Elevs("妙蛙花");
  r2.add_Elevs("妙蛙草");
  Player_Vs_Wild pvw(&r1,&r2);
  pvw.Fight();
  return 0;
}
