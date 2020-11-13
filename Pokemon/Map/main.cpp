#include"map.h"
void meau()
{
  system("clear");
  cout << "你好,欢迎来到激烈的宝可梦世界!!"<<endl; 
  sleep(3);
  system("clear");
  cout<<"下面是本游戏的提示,你可以按照提示尽情的享受游戏" <<endl; 
  sleep(3);
  system("clear");
  cout <<"开局一定要先找到美女(地图标识为为'美')完成交互,得到皮卡丘,然后就可以尽情的战斗了 " <<endl;
  cout << "训代表训练师" <<endl;
  cout << "草代表野生宝可梦的地点!!"<<endl;
  cout <<"商代表商店,你可以在商店里边找到售台来买物品" <<endl;
  sleep(10);
}
int main()
{
  meau();
  Roles ros;
  Game game(&ros);
  game.create_map();
  game.run();
  return 0;
}
