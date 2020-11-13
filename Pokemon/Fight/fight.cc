#include"fight.h"
Elevs* Player_Vs_Wild::change_player_elevs()
{
   system("clear");
   cout << "选择您的宝可梦" << endl;
   int i;
   for(i=0;i<_role->get_pocket().size();i++)
   {
     if(_role->get_pocket()[i].in_buff("吹飞"))
       continue;
     if(_role->get_pocket()[i].is_die())
     {
       continue;
     }
     cout <<"[" << i+1  <<"]"; 
     cout <<_role->get_pocket()[i].getname()<<" : "<<endl; 
     cout << "描述: " << _role->get_pocket()[i].get_introduce() << endl;
     cout << "当前血量/最大血量: "<<_role->get_pocket()[i].get_cur_hp() << "/"<<_role->get_pocket()[i].get_max_hp() <<endl;
     cout << "属性: " << _role->get_pocket()[i].getpro()<<endl;
     cout << "等级: " << _role->get_pocket()[i].get_lv() << endl;
     cout << "稀有度: " << _role->get_pocket()[i].get_rarity() <<endl;
     cout << "高度: " << _role->get_pocket()[i].get_height() << endl;
     cout << "重量: " << _role->get_pocket()[i].get_weight() << endl;
     cout << endl;
   }
   while(1)
   {
   cout << "请输入你的选择: ";
   int choice = 0;
   cin >> choice;
   if(choice<1||choice>_role->get_pocket().size())
   {
     cout << "输入数据不在给定范围内!! " << endl;
   }
   else if(_role->get_pocket()[choice-1].is_die())
   {
     cout << "当前精灵已经死亡,不可选择" << endl;
   }
   else 
   {
     return &_role->get_pocket()[choice-1];
   }
  }
}
bool Player_Vs_Wild::wild_have_other_elevs()
{
    for(int i=0;i<_wild->get_pocket().size();i++)
    {
      if(_wild->get_pocket()[i].is_die() || _wild->get_pocket()[i].in_buff("吹飞"))
        continue;
      else
        return true;
    }
    return false;
}

void Player_Vs_Wild::dis_play(Elevs* elvs,Elevs* elvs2)
{
     system("clear");
     cout << "对战信息: " <<endl <<endl;
     cout <<elvs->getname()<<" : "<<endl; 
     cout << "描述: " << elvs->get_introduce() << endl;
     cout << "当前血量/最大血量: "<<elvs->get_cur_hp() << "/"<<elvs->get_max_hp() <<endl;
     cout << "属性: " << elvs->getpro()<<endl;
     cout << "等级: " << elvs->get_lv() << endl;
     cout << "稀有度: " << elvs->get_rarity() <<endl;
     cout << "高度: " << elvs->get_height() << endl;
     cout << "重量: " << elvs->get_weight() << endl;
     cout << "异常状态:  " ;
     elvs->display_all_buff();
     cout << endl;
     cout << endl <<endl;
     cout << "vs" <<endl<<endl;
     cout <<elvs2->getname()<<" : "<<endl; 
     cout << "描述: " << elvs2->get_introduce() << endl;
     cout << "当前血量/最大血量: "<<elvs2->get_cur_hp() << "/"<<elvs2->get_max_hp() <<endl;
     cout << "属性: " << elvs2->getpro()<<endl;
     cout << "等级: " << elvs2->get_lv() << endl;
     cout << "稀有度: " << elvs2->get_rarity() <<endl;
     cout << "高度: " << elvs2->get_height() << endl;
     cout << "重量: " << elvs2->get_weight() << endl;
     cout << "异常状态:  " ;
     elvs2->display_all_buff();
     cout << endl;
     sleep(5);
}

void Player_Vs_Wild::deal_player_buff()
{
  for(int i=0;i<_role->get_pocket().size();i++)
  {
    //寄生种子
    if(_role->get_pocket()[i].in_buff("寄生种子"))
    {
      _role->get_pocket()[i].sub_hp(_role->get_pocket()[i].get_max_hp()/8);
      for(int i=0;i<_wild->get_pocket().size();i++) 
      {
        if(_wild->get_pocket()[i].in_buff("吸取寄生种子"))
        {
          _wild->get_pocket()[i].add_hp(_role->get_pocket()[i].get_max_hp());
        }
      }
    }
  }
}

void Player_Vs_Wild::deal_buff_in_end_type(Roles* role)
{
  for(int i=0;i<role->get_pocket().size();i++)
  {
    if(_role->get_pocket()[i].stus_is_set("灼伤"))
    {
      _role->get_pocket()[i].sub_hp(_role->get_pocket()[i].get_max_hp()/16);
    }
    if(role->get_pocket()[i].stus_is_set("中毒"))
    {
      role->get_pocket()[i].sub_hp(_role->get_pocket()[i].get_max_hp()/8);
    }
  }
}
Elevs* Player_Vs_Wild::change_wild_elevs()
{
  while(1)
  {
    int r = rand()%_wild->get_pocket().size();
    if(_wild->get_pocket()[r].is_die()||_wild->get_pocket()[r].in_buff("吹飞"))
      continue;
    else
      return &_wild->get_pocket()[r];
  }
}
bool Player_Vs_Wild::player_have_other_elevs()
{
   for(int i=0;i<_role->get_pocket().size();i++)
   {
      if(_role->get_pocket()[i].in_buff("吹飞")|| _role->get_pocket()[i].is_die()) 
      {
          continue;
      }
      else
        return true;
   }
   return false;
}
void Player_Vs_Wild::deal_wild_buff()
{
  for(int i=0;i<_wild->get_pocket().size();i++)
  {
    //寄生种子
    if(_wild->get_pocket()[i].in_buff("寄生种子"))
    {
      _wild->get_pocket()[i].sub_hp(_wild->get_pocket()[i].get_max_hp()/8);
      for(int i=0;i<_wild->get_pocket().size();i++) 
      {
        if(_role->get_pocket()[i].in_buff("吸取寄生种子"))
        {
          _role->get_pocket()[i].add_hp(_wild->get_pocket()[i].get_max_hp());
        }
      }
    }
  }
}
bool Player_Vs_Wild::attaker_can_use_skill(Elevs* att)
{
  if(att->in_buff("畏缩"))
  {
    att->remove_buff("畏缩");
    return false;
  }
  return true;
}
void Player_Vs_Wild::player_ack_wild(Elevs* player,Elevs* wild)
{
      fight_Sys fs;
      fs.create_fighting(player,wild,true,_role,_wild);
      system("clear");
      cout << "你对对方宝可梦发动了攻击.."<< endl;
      sleep(3); 
}

void Player_Vs_Wild::wild_ack_player(Elevs* player,Elevs* wild)
{
      fight_Sys fs;
      fs.create_fighting(wild,player,false,_role,_wild);
       system("clear");
      cout << "对方宝可梦对你发动了攻击.."<< endl;
      sleep(3);
}

bool Player_Vs_Wild::player_fist_hit(Elevs* player,Elevs* wild)
{
    int player_speed = player->get_spped();
    int wild_speed = wild->get_spped();
    if(player->stus_is_set("麻痹"))
    {
       player_speed/=2;
    }
    if(wild->stus_is_set("麻痹"))
    {
      wild_speed/=2;
    }
    if(player_speed>=wild_speed)
    {
      return true;
    }
    else 
    {
      return false;
    }
}

bool Player_Vs_Wild::player_can_hit(Elevs* player)
{
   if(player->in_buff("破坏光线"))
   {
   player->remove_buff("破坏光线");
   return false;
   }
   return true;
}
bool Player_Vs_Wild:: wild_can_hit(Elevs* wild)
{
   if(wild->in_buff("破坏光线"))
   {
    wild->remove_buff("破坏光线");
     return false;
   }
   return true;
}
bool Player_Vs_Wild::deal_arc()
{
  cout << "当前所持有的物品: " <<endl;
  unordered_map<string ,int>::iterator p = _role->get_arc_info().begin();
  int idx=0;
  while(p!=_role->get_arc_info().end())
  {
    cout << "[" << idx+1 <<"]" <<endl;
    idx++;
    cout <<"名称: " <<p->first <<endl;
    cout <<"数量: "<<p->second <<endl;
    cout <<endl;
    p++;
  }
  cout << endl;
  if(idx!=0)
  {
  cout << "[" << idx+1 <<"]" << ": " <<"退出" <<endl;
  int choice=0;
  p=_role->get_arc_info().begin();
  while(1)
  {
    cout << "请输入你的选择: ";
    cin >>choice;
    if(choice==idx+1)
    {
      return false;
    }
    else if(choice>=1&&choice<=idx)
    {
       for(int i=0;i<choice-1;i++) 
       {
         p++;
       }
       if(p->first=="精灵球"||p->first=="超级球"||p->first=="高级球")
       {
         if(is_triner)
         {
           system("cls");
           cout << "无法对训练师使用" <<endl;
           sleep(3);
           return false;
         }
         else 
         {
          _role->use_arc(p->first);
           Arc arc(_role,&_wild->get_pocket()[0]);
           bool cat_sus=arc.deal_arc(p->first); 
           return cat_sus;
         }
       }
       else 
       {
       _role->use_arc(p->first);
        Arc arc(_role);
        arc.deal_arc(p->first);
        system("cls");
        sleep(3);
        cout << "使用成功" <<endl;
        return false;;
       }
    }
    else 
    {
      cout << "你的输入有误" <<endl;
    }
  }
  }
  else 
  {
    cout << "当前物品为空" <<endl;
    sleep(3);
    return false;
  }
}
bool Player_Vs_Wild::talk_with_player(Elevs*& player)
{

   int choice  =0;
   while(1)
   {
     system("clear");
     cout <<"1.更换妖怪"  <<endl;
     cout <<"2.使用药剂"  <<endl;
     cout <<"3.退出" <<endl;
     cout << "请输入您的选择: ";
     cin >>choice;
     if(choice==1)
     {
      if(player->in_buff("束缚"))
      {
         cout <<"当前精灵被束缚无法被换下....." <<endl;
         sleep(1);
      }
      else 
      {
        player = change_player_elevs();
      }
     }
     else if(choice == 2)
     {
       bool ca=deal_arc();
       if(ca)
         return ca;
     }
     else if(choice==3)
       return false;
     else 
     {
       cout << "您的输入有误,请重新输入" << endl;
     }
   }
}
void Player_Vs_Wild::Fight()
{
  Elevs* player =&_role->get_pocket()[0];
  Elevs* wild=&_wild->get_pocket()[0];
  for(;;)
  {
    deal_wild_buff();
    deal_player_buff();
    deal_buff_in_end_type(_role);
    deal_buff_in_end_type(_wild);
    if(player->in_buff("瞬间移动"))
    {
      deal_fail_info();
      return;
    }
    //显示当前对阵的宝可梦
    //判断当前双方谁先出手
    //if(玩家先)
    //{
    //   if(玩家可以发动攻击) ）
    //   玩家交互(是否更换英雄/使用物品)
    //   玩家对对方发动攻击 
    //   判断当前对方妖怪是否被击倒 ,如果对方已经被击倒则需要更换妖怪如果对方没有可以用的妖怪   游戏结束 
    //   
    //   
    //   if(对方可以发动攻击)
    //   对方对玩家发动攻击
    //   判断玩家当前妖怪是否死亡,如果死亡询问玩家是否要使用药剂或者是更换妖怪  如果玩家没有对应的药剂并且没有英雄游戏结束
    //}
    if(role_is_die())
       deal_fail_info();
    if(wild_is_die())
       deal_success_info();
    //判断玩家是否被吹飞
    if(player->in_buff("吹飞"))
    {
    if(player_have_other_elevs())
    {
       player=change_player_elevs();
    }
    else 
    {
       deal_fail_info();
       return;
    }
    }
    if(wild->in_buff("吹飞"))
    {
      if(wild_have_other_elevs())
      {
        wild=change_wild_elevs();
      }
      else 
      {
        deal_success_info();
        return;
      }
    }
    if(player->in_buff("吼叫"))
    {
    wild->remove_buff("吼叫");
    if(player_have_other_elevs())
    {
       player=change_player_elevs();
    }
    else 
    {
       deal_fail_info();
       return;
    }
    }
    if(wild->in_buff("吼叫"))
    {
      wild->remove_buff("吼叫");
      if(wild_have_other_elevs())
      {
        wild=change_wild_elevs();
      }
      else 
      {
        deal_success_info();
        return;
      }
    }
    dis_play(player,wild);
    if(player_fist_hit(player,wild))
    {
      if(talk_with_player(player))
      {
        deal_success_info();
        return;
      }
      if(player_can_hit(player))
      {
        player_ack_wild(player,wild);
        if(wild->is_die())
        {
           if(wild_have_other_elevs())
           wild=change_wild_elevs();
           else
           {
             deal_success_info();
             return;
           }
        }
      }
      if(wild_can_hit(wild))
      {
          wild_ack_player(player,wild);
          if(player->is_die())
          {
            if(player_have_other_elevs())
            {
               player=change_player_elevs();
            }
            else 
            {
               deal_fail_info();
               return;
            }
          }
      }
    }
    else
    {
      if(wild_can_hit(wild))
      {
          wild_ack_player(player,wild);
          if(player->is_die())
          {
            if(player_have_other_elevs())
            {
               player=change_player_elevs();
            }
            else 
            {
               deal_fail_info();
               return;
            }
          }
      }
      if(talk_with_player(player))
      {
        deal_success_info();
        return;
      }
      if(player_can_hit(player))
      {
        player_ack_wild(player,wild);
        if(wild->is_die())
        {
           if(wild_have_other_elevs())
           wild=change_wild_elevs();
           else
           {
             deal_success_info();
             return;
           }
        }
      }
    }
  }
}

bool Player_Vs_Wild::wild_is_die()
{
  int cnt=0;
  for(int i=0;i<_wild->get_pocket().size();++i)
  {
    if(_wild->get_pocket()[i].is_die())
    {
      ++cnt;
    }
  }
  if(cnt==_wild->get_pocket().size())
    return true;
  return false;
}
bool Player_Vs_Wild::role_is_die()
{
  int cnt=0;
  for(int i=0;i<_role->get_pocket().size();++i)
  {
    if(_role->get_pocket()[i].is_die())
    {
      ++cnt;
    }
  }
  if(cnt==_role->get_pocket().size())
    return true;
  return false;
}

void Player_Vs_Wild::deal_fail_info()
{
  remove_all_buff();
  system("clear"); 
  cout << "你被对方击败了 " <<endl;
  sleep(3);
}

void Player_Vs_Wild::deal_success_info()
{
  //回复状态
  remove_all_buff();
  //计算收益
  int a=1;
  int t=1;
  int b=0;
  for(int i=0;i<_wild->get_pocket().size();i++)
  {
   b+=_wild->get_pocket()[i].get_base_exp();
  }
  int L = 0;
  for(int i=0;i<_wild->get_pocket().size();i++)
  {
   L+=_wild->get_pocket()[i].get_lv();
  } 
  int s=0;
  for(int i=0;i<_role->get_pocket().size();++i)
  {
    if(_role->get_pocket()[i].is_die()==false)
      ++s;
  }
  int k=1;
  int get_exp= (a*t*b*L)/(7*s*k);
  for(int i=0;i<_role->get_pocket().size();i++)
  {
    if(_role->get_pocket()[i].is_die()==false)
      _role->get_pocket()[i].add_exp(get_exp);
  }
  int moneyCnt=0;
  for(int i=0;i<_role->get_pocket().size();i++)
  {
    int cnt = _role->get_pocket()[i].in_buff("聚宝功"); 
    moneyCnt+=cnt*_role->get_pocket()[i].get_lv()*5;
    while(_role->get_pocket()[i].in_buff("聚宝功"))
    {
      _role->get_pocket()[i].remove_buff("聚宝功");
    }
  }
  _role->add_money(moneyCnt);
  //打印胜利logal
  system("clear"); 
  cout << "你击败了对方 " <<endl;
  sleep(3);
}
void Player_Vs_Wild::remove_all_buff()
{
  //移除精灵身上的buff和status
  //回复闪避率和攻防等级
  for(int i=0;i<_role->get_pocket().size();i++) 
  {
     _role->get_pocket()[i].remove_all_buff();
     _role->get_pocket()[i].remove_all_stus();
     _role->get_pocket()[i].restore_addtion();
     _role->get_pocket()[i].restroe_hit_dodge_lv();
  }
}
bool fight_Sys::is_Hit(Skill* sk)
{
    int hit_persent = _attcker->get_hit_per();
    int dodge_persent = _defender->get_dodge_per();
    int skill_persent = sk->hit_per();
    int r =rand()%255+1;
    int a = 0;
    if(skill_persent==100)
    {
      a=255;
    }
    else if(skill_persent==95)
    {
      a=242;
    }
    else if(skill_persent==90)
    {
      a=229;
    }
    else if(skill_persent==85)
    {
      a=216;
    }
    else if(skill_persent==80)
    {
      a=204;
    }
    else if(skill_persent==75)
    {
      a=191;
    }
    else if(skill_persent==70)
    {
      a=178;
    }
    else if(skill_persent==60)
    {
      a=153;
    }
    else if(skill_persent== 55)
    {
      a=140;
    }
    else if(skill_persent==50)
    {
      a=127;
    }
    else 
    {
      a=100;
    }
    int A= a*hit_persent*dodge_persent;
    if(A>=r)
    {
      return true;
    }
    else 
      return false;
}
int fight_Sys::get_rand()
{
  return rand()%100+1;
}
bool fight_Sys::hit_main()
{
   int r= _attcker->get_spped()/512; 
   r*=100;
   int rd= get_rand();
   return r>=rd; 
}
void fight_Sys::create_fighting(Elevs* att,Elevs* def,bool judge,Roles*roles ,Roles* wild)
{
  _attcker = att;
  _defender = def;
  _roles = roles;
  is_player = judge;
  _wild = wild;
  stru.create_Skill_by_name("挣扎"); 
  deal_skill();
}
Skill* fight_Sys::player_choice_skill()
{
  system("clear");
  cout <<"请选择你的技能: " <<endl<<endl;
  cout<< "宝可梦: " <<_attcker->getname(); 
  cout << endl;
  int cnt = 0;
  for(int i=0;i<_attcker->get_All_Skill().size();i++)
  {
   if(_attcker->get_All_Skill()[i].get_cur_pp()==0)
   {
     ++cnt;
   }
   if(_attcker->get_All_Skill()[i].in_buff("定身法"))
   {
     _attcker->get_All_Skill()[i].remove_buff("定身法");
     ++cnt;
   }
  }
  cout <<"1"<<endl;
  if(cnt == _attcker->get_All_Skill().size())
  {
     return &stru;
  }
  for(int i=0 ;i <_attcker->get_All_Skill().size();i++)
  {
   if(_attcker->get_All_Skill()[i].in_buff("定身法"))
   {
     continue;
   }  
    cout << "[" <<i+1 << "] ";
    cout << _attcker->get_All_Skill()[i].get_name() <<endl;
    cout << "技能描述: " << _attcker->get_All_Skill()[i].get_introduce() << endl;
    cout << "属性: "; 
    cout << _attcker->get_All_Skill()[i].get_pro() <<endl;
    cout << "当前pp/最大pp: " << _attcker->get_All_Skill()[i].get_cur_pp() <<"/" << _attcker->get_All_Skill()[i].get_max_pp() << endl;
    cout << "施法方式: " << _attcker->get_All_Skill()[i].get_skill_ways() <<endl;
    cout << "技能类型: " << _attcker->get_All_Skill()[i].get_category() <<endl;
  }
  while(1)
  {
    cout << "请输入您的选择: ";
    int choice=0;
    cin >> choice;
  
    if(choice <1 || choice >_attcker->get_All_Skill().size())
    {
      cout << "输入信息不在可选范围内..." <<endl;
    }
    else if(_attcker->get_All_Skill()[choice-1].get_cur_pp()==0)
    {
      cout << "技能pp已经耗尽,无法释放!!"<<endl;
    }
    else 
    {
    _attcker->set_Last_Skill(&_attcker->get_All_Skill()[choice-1]);
     return &_attcker->get_All_Skill()[choice-1];
    }
  }
}
Skill* fight_Sys::computer_choice_skill()
{
  system("clear");
  cout << "对方选择技能中........" <<endl;
  sleep(3);
  int cnt=0;
  for(int i=0;i<_attcker->get_All_Skill().size();i++)
  {
   if(_attcker->get_All_Skill()[i].get_cur_pp()==0)
   {
     ++cnt;
   }
  }
  if(cnt == _attcker->get_All_Skill().size())
  {
     return &stru;
  }
  while(1)
  {
  int r= rand()%_attcker->get_All_Skill().size();
  if(_attcker->get_All_Skill()[r].get_cur_pp()!=0)
  return &_attcker->get_All_Skill()[r];
  else 
    continue;
  }
}
int fight_Sys::get_ack(double ack,double def,double lv,double base_ack)
{
  double  res = (2*lv+10)/250*(ack/def)*base_ack + 2;
  return res;
}
bool fight_Sys::sp_hit_main()
{
  int r = _attcker->get_spped()*4/256 ;
  r*=100;
  int rd = get_rand();
  return r>=rd;
}
int fight_Sys::get_skill_ack(Skill* sk)
{
    //特殊技能踢倒的技能威力和对方宝可梦的体重有关因此要单独处理
    int base=0;
    if(sk->get_name()=="踢到")
    {
      stringstream ss;
      ss<<_defender->get_weight();
      double a=0.0;
      ss>>a;
      if(a<=9.9) 
      {
        base=20;
      }
      else if(a>=10.0&&a<=24.9)
      {
        base=40;
      }
      else if(a>=25&&a<=49.9)
      {
        base=60;
      }
      else if(a>=50&&a<=99.9)
      {
        base=80;
      }
      else if(a>=100&&a<=199.9)
      {
        base=100;
      }
      else if(a>=200)
      {
        base=120;
      }
    }
    else 
    {
      base=sk->get_skill_base_ack();
    }
    //属性一致
    if(_attcker->in_pro(sk->get_pro()))
      base*=1.5;
    return base;
}
void fight_Sys::deal_skill()
{
   Skill* sk;
   if(is_player)   
   {
    sk=player_choice_skill(); 
   }
   else 
   {
     sk=computer_choice_skill();
   }
   //睡眠
   if(_attcker->stus_is_set("睡眠"))
   {
     _attcker->remove_stus("睡眠");
     if(sk->get_name()!="梦话"&&sk->get_name()!="打鼾")
     {
       return;
     }
   }
   //冰冻
   if(_attcker->stus_is_set("冰冻"))
   {
   if(sk->get_name()!="火焰轮"&&sk->get_name()!="神圣之火"&&sk->get_name()!="闪焰重返"&&sk->get_name()!="热水"&&sk->get_name()!="交错火焰"&&sk->get_name()!="蒸汽爆炸"&&sk->get_name()!="燃尽"&&sk->get_name()!="熊熊火爆")
     return;
   else 
     _attcker->remove_stus("冰冻");
   } 
   if(sk->get_name() == "模仿")
   {
     sk->sub_cur_pp();  
     if(sk->get_name() == "指挥")
       return;
     if(sk->get_name() == "模仿")
       return;
     if(sk->get_name() == "挣扎")
       return;
     sk = _defender->get_last_use_Skill();
   }
   if(sk->get_name() == "鹦鹉学舌")
   {
     sk->sub_cur_pp();  
     if(sk->get_name() == "指挥")
       return;
     if(sk->get_name() == "模仿")
      return;
     if(sk->get_name() == "挣扎")
       return;
     if(sk->get_name() == "变身")
       return;
     if(sk->get_name() == "挣扎")
       return;
     if(sk->get_name() == "鹦鹉学舌")
       return;
     if(sk->get_name() == "双倍奉还")
       return;
     if(sk->get_name() == "忍耐")
       return;
     if(sk->get_name() == "替身")
       return;
     sk = _defender->get_last_use_Skill();
   }

   int base_ack=0;
   if(sk->get_skill_base_ack()!=0)
   {
    int att_ack = _attcker->get_ack();
    int defder_def=_defender->get_def();
    base_ack = get_ack(att_ack,defder_def,_attcker->get_lv(),get_skill_ack(sk));
   }
  //混乱
   if(_attcker->in_buff("混乱"))
   {
     int r = rand()%3;
     if(r==0)
     {
       _attcker->sub_hp(get_ack(_attcker->get_ack(),_attcker->get_def(),_attcker->get_lv(),40));
       _attcker->remove_buff("混乱");
       return;
     }
   }
   //灼伤
   if(sk->get_category()!="物理"&&_attcker->stus_is_set("灼伤"))
   {
      base_ack/=2;
   }
   if(sk->get_category() == "特殊"&&_defender->in_buff("光墙"))
   {
     base_ack/=2;
   }
   if(base_ack<1)
     base_ack=1;
   if(sk->get_name() == "拍击")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="空手劈")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="连环巴掌")
   {
     sk->sub_cur_pp();
     int r= get_rand();
     if(r>=60)
     {
       int c = rand()%1+2;
       base_ack*=c;
     }
     else if(r>=85)
     {
       int c=rand()%1+5;
       base_ack*=c;
     }
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="连续拳")
   {
     sk->sub_cur_pp();
     int r= get_rand();
     if(r>=60)
     {
       int c = rand()%1+2;
       base_ack*=c;
     }
     else if(r>=85)
     {
       int c=rand()%1+5;
       base_ack*=c;
     }
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="百万吨重拳")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="聚宝功")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
     _attcker->set_buff("聚宝功");
   }
   else if(sk->get_name()=="撞击")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
   }
   else if(sk->get_name()=="火焰拳")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
     int r = get_rand();
     if(r>=90)
     {
       _defender->set_stus("灼伤");
     }
   }
   else if(sk->get_name()=="冰冻拳")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=90)
     {
       _defender->set_stus("冰冻",2);
     }
   }
   else if(sk->get_name()=="雷电拳")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=90)
     {
       _defender->set_stus("麻痹");
     }
   }
   else if(sk->get_name()=="抓")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="夹住")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="断头钳")
   {
     if(_attcker->get_lv()<_defender->get_lv())
     {
      return;
     }
     sk->sub_cur_pp();
     int per = 100-_attcker->get_lv()+30-_defender->get_lv();
     int r =get_rand();
     if(r>=per)
     {
       _defender->sub_hp(_defender->get_cur_hp());
     }
   }
   else if(sk->get_name()=="旋风刀")
   {
     sk->sub_cur_pp();
     if(_attcker->in_buff("旋风刀"))
     {
       _attcker->remove_buff("旋风刀");
      _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     else 
     {
       _attcker->set_buff("旋风刀");
     }
   }
   else if(sk->get_name()=="剑舞")
   {
     sk->sub_cur_pp();
     _attcker->add_ack_addtion(2);
   }
   else if(sk->get_name()=="居合斩")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="起风")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        if(_defender->in_buff("飞翔"))
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro())*2);
        else 
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
  }
  else if(sk->get_name()=="翅膀攻击")
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
  }
  else if(sk->get_name()=="吹飞")
  {
    if(_defender->get_lv() > _attcker->get_lv())
    {
      return;
    }
    else 
    {
     sk->sub_cur_pp();
      _defender->set_buff("吹飞");
    }
  }
  else if(sk->get_name()=="飞翔")
  {
    if(_attcker->in_buff("飞翔"))
    {
       _attcker->remove_buff("飞翔");
       if(is_Hit(sk))
       {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
       }
    }
    else 
    {
        sk->sub_cur_pp();
        _attcker->set_buff("飞翔");
    }
  }
  else if(sk->get_name()=="绑紧")
  {
     sk->sub_cur_pp();

     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
  }
  else if(sk->get_name()=="摔打")
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
  }
  else if(sk->get_name()=="藤鞭")
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
  }
  else if(sk->get_name()=="踩踏")
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
  }
  else if(sk->get_name()=="二连踢")
  {
      sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
  }
  else if(sk->get_name()=="百万吨重踢")
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
  }
  else if(sk->get_name()=="飞踢")
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
        _attcker->sub_hp(_attcker->get_cur_hp()/2);
     }
  }
  else if(sk->get_name()=="回旋踢")
  {
      sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=75)
     {
       _defender->set_buff("畏惧");
     }
  }
  else  if(sk->get_name() == "泼沙")
  {
    sk->sub_cur_pp();
    if(_defender->in_buff("白雾"))
    {
      _defender->remove_buff("白雾");
    }
    else
    _defender->sub_hit_per(1);
  }
  else if(sk->get_name() == "头锤")
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=70)
     {
       _defender->set_buff("畏缩");
     }
  }
  else if(sk->get_name() == "角撞")
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
  }
  else if(sk->get_name() == "乱击")
  {
     sk->sub_cur_pp();
     int r= get_rand();
     if(r>=60)
     {
       int c = rand()%1+2;
       base_ack*=c;
     }
     else if(r>=85)
     {
       int c=rand()%1+5;
       base_ack*=c;
     }
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
  }
  else if(sk->get_name() == "角钻")
  {
     if(_attcker->get_lv()<_defender->get_lv())
     {
      return;
     }
     sk->sub_cur_pp();
     int per = 100-_attcker->get_lv()+30-_defender->get_lv();
     int r =get_rand();
     if(r>=per)
     {
       _defender->sub_hp(_defender->get_cur_hp());
     }
  }
  else if(sk->get_name() == "撞击")
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
  }
  else if(sk->get_name() == "泰山压顶")
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=70)
     {
       _defender->set_stus("麻痹");
     }
  }
  else if(sk->get_name() == "紧束" )
  {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
     if(!_defender->in_buff("束缚"))
     {
       _defender->set_buff("束缚");
       _defender->set_buff("束缚");
       _defender->set_buff("束缚");
       _defender->set_buff("束缚");
     }
  }
  else if(sk->get_name() == "猛撞")
  {
      sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
        _attcker->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro())/4);
     }
  }
  else if(sk->get_name()== "大闹一番")
  {
    if(!is_player)
    {
    int r = _roles->get_pocket().size();
    _roles->get_pocket()[r].sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro())); 
    }
    else 
    {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
    }
    sk->sub_cur_pp();
    _attcker->set_buff("混乱");
  }
   else if(sk->get_name()=="舍身冲撞")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
        _attcker->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro())/4);
     }
   }
   else if(sk->get_name()=="摇尾巴")
   {
      sk->sub_cur_pp();
     if(is_Hit(sk))
     {
      if(_defender->in_buff("白雾"))
      {
       _defender->remove_buff("白雾");
      }
      else
      _defender->sub_def_addtion(1);
     }
   }
   else if(sk->get_name()=="毒针")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = rand()%100;
     if(r>=70)
       _defender->set_buff("毒针");
   }
   else if(sk->get_name()=="双击")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(2*base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = rand()%100;
     if(r>=80)
      _defender->set_stus("中毒");
   }
   else if(sk->get_name()=="飞弹针")
   {
     sk->sub_cur_pp();
     int r= get_rand();
     if(r>=60)
     {
       int c = rand()%1+2;
       base_ack*=c;
     }
     else if(r>=85)
     {
       int c=rand()%1+5;
       base_ack*=c;
     }
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="瞪眼")
   {
      sk->sub_cur_pp();
    if(is_Hit(sk))
     {
      _defender->sub_def_addtion(1);
     }
   }
   else if(sk->get_name() == "咬住")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = rand()%20;    
     if(r>=70)
       _defender->set_buff("畏惧");
   }
   else if(sk->get_name()== "叫声")
   {
      sk->sub_cur_pp();
      if(is_Hit(sk))
      {
      if(_defender->in_buff("白雾"))
      {
      _defender->remove_buff("白雾");
      }
      else
      _defender->sub_ack_addtion(1);
      }
   }
   else if(sk->get_name()=="吼叫")
   {
     if(_attcker->get_lv() > _defender -> get_lv())
       return;
     else 
     {
       sk->sub_cur_pp();
       _defender->set_buff("吼叫");
     }
   }
   else if(sk->get_name() == "唱歌")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
    {
      _defender->set_stus("睡眠");
    }
   }
   else if(sk->get_name()=="超音波")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->in_buff("混乱");
     }
   }
   else if(sk->get_name()=="音爆")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->sub_hp(20);
     }
   }
   else if(sk->get_name()=="定身法")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->get_last_use_Skill()->set_buff("定身法");
       _defender->get_last_use_Skill()->set_buff("定身法");
       _defender->get_last_use_Skill()->set_buff("定身法");
       _defender->get_last_use_Skill()->set_buff("定身法");
     }
   }
   else if(sk->get_name()=="溶解液")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r=get_rand();
     if(r>=90)
     {
       _defender->set_buff("溶解液");
     }
   }
   else if(sk->get_name()=="火花")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=90)
     {
       _defender->set_stus("灼伤");
     }
   }
   else if(sk->get_name()=="喷射火焰")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=90)
     {
       _defender->set_stus("灼伤");
     }
   }
   else if(sk->get_name() == "白雾")
   {
     sk->sub_cur_pp();
     _attcker->set_buff("白雾");
     _attcker->set_buff("白雾");
     _attcker->set_buff("白雾");
     _attcker->set_buff("白雾");
     _attcker->set_buff("白雾");
   }
   else if(sk->get_name()=="水枪")
   {
      sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="水炮")
   {
       sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="冲浪")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk)&&_defender->in_buff("潜水"))
     {
        _defender->sub_hp(2*base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="冰冻光束")
   {
     sk->sub_cur_pp();
    if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
    int r= get_rand();
    if(r>=90)
    {
      _defender->set_stus("冰冻",2);
    }
   }
   else if(sk->get_name()=="暴风雪")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
    int r= get_rand();
    if(r>=90)
    {
      _defender->set_stus("冰冻",2);
    }
   }
   else if(sk->get_name()=="幻象光线")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
    int r= get_rand();
    if(r>=90)
    {
      _defender->set_buff("混乱");
    }
   }
   else if(sk->get_name()=="泡沫光线")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
    int r= get_rand();
    if(r>=90)
    {
      _defender->set_buff("泡沫光线");
    }
   }
   else if(sk->get_name()=="极光束")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
    int r= get_rand();
    if(r>=90)
    {
      if(_defender->in_buff("白雾"))
      {
        _defender->remove_buff("白雾");
      }
      else
      _defender->sub_ack_addtion(1);
    }
   }
   else if(sk->get_name()=="破坏光线")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
      _defender->set_buff("破坏光线");
   }
   else if(sk->get_name()=="啄")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="啄钻")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="地狱翻滚")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
        _attcker->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro())/4);
     }
   }
   else if(sk->get_name()=="踢倒")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
        _attcker->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro())/4);
     }
   }
   else if(sk->get_name()=="双倍奉还")
   {
     
   }
   else if(sk->get_name()=="地球上投")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(_defender->get_lv());
     }
   }
   else if(sk->get_name()=="怪力")
   {
      sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name()=="吸取")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
        _attcker->add_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro())/2);
     }
   }
   else if(sk->get_name() == "超级汲取")
   {
      sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
        _attcker->add_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro())/2);
     }
   }
   else if(sk->get_name() == "寄生种子")
   {
     vector<string>pro = _defender-> get_all_pro();
     bool is_can_hit = true;
     for(int i=0;i<pro.size();i++)
     {
       if(pro[i]=="草")
       {
        is_can_hit=false;
       }
     }
     if(is_can_hit)
     {
       _defender->set_buff("寄生种子");
       _attcker->set_buff("吸取寄生种子");
     }
   }
   else if(sk->get_name()=="生长")
   {
      sk->sub_cur_pp();
      _attcker->add_ack_addtion(1);
      _attcker->add_s_ack_addtion(1);
   }
   else if(sk->get_name()=="飞叶快刀")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name() == "日光束")
   {
     sk->sub_cur_pp();
     if(_attcker->in_buff("日光束")) 
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
        _attcker->remove_buff("日光束");
     }
     else 
     {
        _attcker->set_buff("日光束");
     }
   }
   else if(sk->get_name() == "毒粉")
   {
     sk->sub_cur_pp(); 
     if(_defender->in_pro("草"))
     {
       return;
     }
     else 
     {
       if(is_Hit(sk))
       _defender->set_stus("中毒");
     }
   }
   else if(sk->get_name()== "麻痹粉")
   {
    sk->sub_cur_pp(); 
     if(_defender->in_pro("草"))
     {
       return;
     }
     else 
     {
       if(is_Hit(sk))
       _defender->set_stus("麻痹");
     }
   }
   else if(sk->get_name() == "催眠粉")
   {
     sk->sub_cur_pp(); 
     if(_defender->in_pro("草"))
     {
       return;
     }
     else 
     {
       if(is_Hit(sk))
       _defender->set_stus("睡眠");
     }
   }
   else if(sk->get_name()=="花瓣舞")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
    {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
    } 
   }
   else if(sk->get_name() =="吐丝" )
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->set_buff("吐丝");
     }
   }
   else if(sk->get_name()== "龙之怒")
   {
      sk->sub_cur_pp();
      if(is_Hit(sk))
      {
        _defender->sub_hp(40);
      }
   }
   else if(sk->get_name()=="火之漩涡")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     _defender->set_buff("束缚");
   }
   else if(sk->get_name()=="电击")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r=get_rand();
     if(r>=90)
     _defender->set_stus("麻痹");
   }
   else if(sk->get_name() == "十万福特")
   {
      sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r=get_rand();
     if(r>=90)
     _defender->set_stus("麻痹");
   }
   else if(sk->get_name() == "电磁波")
   {
      sk->sub_cur_pp();
      vector<string>pro= _defender->get_all_pro();
      for(int i=0;i<pro.size() ; i++ )
      {
        if(pro[i]=="地面")
        {
          _defender->set_stus("麻痹");
        }
      }
   }
   else if(sk->get_name() == "打雷")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r=get_rand();
     if(r>=70)
     _defender->set_stus("麻痹");
   }
   else if(sk->get_name()=="打雷")
   {
     sk->sub_cur_pp();
    if(is_Hit(sk))
    {
    if(is_player)
    {
      for(int i=0;i<_roles->get_pocket().size();i++)
      {
         _roles->get_pocket()[i].sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));     
      }
    }
    else 
    {
      for(int i=0;i<_wild->get_pocket().size();i++)
      {
         _wild->get_pocket()[i].sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));     
      }
    }
    }
   }
   else if(sk->get_name() == "地裂")
   {
     sk->sub_cur_pp();
      _defender->sub_hp(_defender->get_cur_hp() * pro_restant(sk->get_pro()));
   }
   else if(sk->get_name() == "挖洞")
   {
     if(_attcker->in_buff("挖洞"))
     {
     if(is_Hit(sk))
     {
       _attcker->remove_buff("挖洞");
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     }
     else 
     {
       sk->sub_cur_pp();
       _attcker->set_buff("挖洞");
     }
   }
   else if(sk->get_name()=="剧毒")
   {
     sk->sub_cur_pp();
     vector<string>pro = _attcker->get_all_pro();
     for(int i=0;i<pro.size();i++)
     {
       if(pro[i]=="毒")
       {
         _defender->set_stus("中毒");
         return;
       }
     }
     if(is_Hit(sk))
     {
      _defender->set_stus("中毒");
     }
   }
   else if(sk->get_name() == "念力")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r=get_rand();
     if(r>=90)
     {
       _defender->set_stus("麻痹");
     }
   }
   else if(sk->get_name() == "精神强念")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=90)
     {
       if(_defender->in_buff("白雾"))
       {
          _defender->remove_buff("白雾");
       }
       else 
       {
         _defender->sub_s_def_addtion(1);
       }
     }
   }
   else if(sk->get_name() == "催眠术")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->set_stus("睡眠");
     }
   }
   else if(sk->get_name() == "瑜伽姿势")
   {
     sk->sub_cur_pp();
     _attcker->add_ack_addtion(1);
   }
   else if(sk->get_name() == "高速移动")
   {
    sk->sub_cur_pp();
    _attcker->set_buff("高速移动");
   }
   else if(sk->get_name() == "电光一闪")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name() == "愤怒")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
    {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
    }
   }
   else if(sk->get_name() == "瞬间移动")
   {
     if(is_player)
       _attcker->set_buff("瞬间移动");
   }
   else if(sk->get_name()== "黑夜魔影")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
     _defender->sub_hp(_defender->get_lv());
     }
   }
   else if(sk->get_name() == "刺耳声")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->sub_def_addtion(2);
     }
   }
   else if(sk->get_name() == "影子分身")
   {
     sk->sub_cur_pp();
     _attcker->add_dodge_per(1);
   }
   else if(sk->get_name() == "自我再生")
   {
     sk->sub_cur_pp();
     _attcker->add_hp(_attcker->get_max_hp()/2);
   }
   else if(sk->get_name() == "变硬")
   {
     sk->sub_cur_pp();
     _attcker->add_def_addtion(1);
   }
   else if(sk->get_name() == "变小")
   {
    sk->sub_cur_pp();
    _attcker->add_dodge_per(1);
   }
   else if(sk->get_name() == "烟幕")
   {
    sk->sub_cur_pp();
    if(_defender->in_buff("白雾"))
    {
      _defender->remove_buff("白雾");
    }
    else
    _defender->sub_hit_per(1);
   }
   else if(sk->get_name() == "奇异之光")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->set_buff("混乱");
     }
   }
   else if(sk->get_name()=="缩入壳中")
   {
     sk->sub_cur_pp();
     _attcker->add_def_addtion(1);
   } 
   else if(sk->get_name() == "变圆")
   {
     sk->sub_cur_pp();
     _attcker->add_def_addtion(1);
   }
   else if(sk->get_name() == "屏障")
   {
     sk->sub_cur_pp();
     _attcker->add_def_addtion(2);
   }
   else if(sk->get_name() == "光墙")
   {
    _defender->set_buff("光墙"); 
    _defender->set_buff("光墙"); 
    _defender->set_buff("光墙"); 
    _defender->set_buff("光墙"); 
    _defender->set_buff("光墙"); 
   }
   else if(sk->get_name() == "黑雾")
   {
     sk->sub_cur_pp();
     for(int i=0;i<_roles->get_pocket().size();i++)
     {
       _roles->get_pocket()[i].restore_addtion();
       _roles->get_pocket()[i].restroe_hit_dodge_lv();
     }
     for(int i=0;i<_wild->get_pocket().size();i++)
     {
       _wild->get_pocket()[i].restore_addtion();
       _wild->get_pocket()[i].restroe_hit_dodge_lv();
     }
   }
   else if(sk->get_name() == "反射壁")
   {
   }
   else if(sk->get_name() == "聚气")
   {
     sk->sub_cur_pp();
     _defender->set_buff("易中要害");
   }
   else if(sk->get_name()=="忍耐")
   {
     _attcker->set_buff("忍耐");
   }
   else if(sk->get_name() == "指挥")
   {
   }
   else if(sk->get_name() == "自爆")
   {
     _attcker->sub_hp(_attcker->get_cur_hp());
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name() == "炸蛋")
   {
    sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name() == "舌舔")
   {
    sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=70)
     {
       _defender->set_stus("麻痹");
     }
   }
   else if(sk->get_name() == "浊雾")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=60)
     {
       _defender->set_stus("中毒");
     }
   }
   else if(sk->get_name() == "污泥攻击")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=70)
     {
       _defender->set_stus("中毒");
     }
   }
   else if(sk->get_name() == "鼓棒")
   {
      sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=90)
     {
       _defender->set_buff("畏缩");
     }
   }
   else if(sk->get_name() == "大字爆炎")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=90)
     {
       _defender->set_stus("灼伤");
     }
   }
   else if(sk->get_name() == "攀爆")
   {
    sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=80)
     {
       _defender->set_buff("畏缩");
     }
   }
   else if(sk->get_name() == "贝壳夹击")
   {
     _defender->set_buff("束缚");
     _defender->set_buff("束缚");
     _defender->set_buff("束缚");
   }
   else if(sk->get_name() == "高速星星")
   {
     sk->sub_cur_pp();
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
   }
   else if(sk->get_name() == "火箭头锤")
   {
    if(!_attcker->in_buff("火箭头锤"))
    {
    sk->sub_cur_pp();
    _attcker->add_def_addtion(1);
    }
    else 
    {
      sk->sub_cur_pp();
      _attcker->remove_buff("火箭头锤");
      _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
    }
   }
   else if(sk->get_name() == "尖刺加农炮")
   {
     sk->sub_cur_pp();
     int r= get_rand();
     if(r>=60)
     {
       int c = rand()%1+2;
       base_ack*=c;
     }
     else if(r>=85)
     {
       int c=rand()%1+4;
       base_ack*=c;
     }
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name() == "缠绕")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     int r = get_rand();
     if(r>=90)
     {
       _defender->set_buff("缠绕");
     }
   }
   else if(sk->get_name() == "瞬间失忆")
   {
     sk->sub_cur_pp();
      _defender->set_buff("瞬间失忆");
   }
   else if(sk->get_name() == "折弯钥匙")
   {
     sk->sub_cur_pp();
     if(_defender->in_buff("白雾"))
     {
       _defender->remove_buff("白雾");
     }
     else 
     {
     _defender->sub_hit_per(1);
     }
   }
   else if(sk->get_name() == "生蛋")
   {
     sk->sub_cur_pp();
     _attcker->add_hp(_attcker->get_max_hp()/2);
   }
   else if(sk->get_name() == "飞膝踢")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     else 
     {
       _attcker->sub_hp(_attcker->get_max_hp()/2);
     }
   }
   else if(sk->get_name() == "大蛇瞪眼")
   {
     sk->sub_cur_pp();
     _defender->set_stus("麻痹");
   }
   else if(sk->get_name() == "食梦")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
    _attcker->add_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro())/2);
     }
   }
   else if(sk->get_name() == "毒瓦斯")
   {
     sk->sub_cur_pp();
     _defender->set_stus("中毒");
   }
   else if(sk->get_name() == "投球")
   {
     sk->sub_cur_pp();
     int r= get_rand();
     if(r>=77)
     {
       int c = rand()%1+2;
       base_ack*=c;
     }
     else if(r>=85)
     {
       int c=rand()%1+4;
       base_ack*=c;
     }
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name() == "吸血")
   {
    sk->sub_cur_pp();
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
    _attcker->add_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro())/2);
     }
   }
   else if(sk->get_name() == "恶魔之吻")
   {
     sk->sub_cur_pp();
     _defender->set_stus("睡眠");
   }
   else if(sk->get_name() == "神鸟猛击")
   {
     if(_attcker->in_buff("神鸟猛击"))
     {
     _attcker->remove_buff("神鸟猛击");
     if(is_Hit(sk))
     {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }  
     }
     else 
     {
     if(is_Hit(sk))
     {
       sk->sub_cur_pp();
       _defender->set_buff("神鸟猛击");
     } 
     }
   }
   else if(sk->get_name() == "变身")
   {
     sk->sub_cur_pp();
     _attcker->in_buff("变身");
   }
   else if(sk->get_name() == "泡沫")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
     _defender->set_buff("泡沫");
   }
   else if(sk->get_name() == "迷昏拳")
   {
     sk->sub_cur_pp();
   if(is_Hit(sk))
     {
       _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     } 
     int r = get_rand();
     if(r>=80)
     {
       _defender->set_buff("混乱");
     } 
   }
   else if(sk->get_name() == "蘑菇孢子")
   {
     vector<string> pro = _defender->get_all_pro();
     for(int i =0 ;i<pro.size() ;++i)
     {
       if(pro[i]=="草")
       {
          return;
       }
     }
     _defender->set_buff("草");
   }
   else if(sk->get_name() == "闪光")
   {
     sk->sub_cur_pp();
     if(_defender->in_buff("白雾"))
     {
       _defender->remove_buff("白雾");
     }
     else
     _defender->sub_hit_per(1);
   }
   else if(sk->get_name() == "精神波")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
       int r = get_rand()/100;
       _defender->sub_hp((double)(r+0.5)*_attcker->get_lv());
     }
   }
   else if(sk->get_name() == "跃起")
   {
     return;
   }
   else if(sk->get_name() == "溶化")
   {
     sk->sub_cur_pp();
      _attcker->add_def_addtion(2);
   }
   else if(sk->get_name() == "蟹钳锤")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
    _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
   }
   else if(sk->get_name() == "大爆炸")
   {
     _attcker->sub_hp(_attcker->get_cur_hp());
     if(is_Hit(sk))
     {
    _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name() == "乱抓")
   {
     sk->sub_cur_pp();
     int r= get_rand();
     if(r>=77)
     {
       int c = rand()%1+2;
       base_ack*=c;
     }
     else if(r>=85)
     {
       int c=rand()%1+4;
       base_ack*=c;
     }
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   } 
   else if(sk->get_name() == "骨头回力镖")
   {
     sk->sub_cur_pp();
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
     if(is_Hit(sk))
     {
        _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
     }
   }
   else if(sk->get_name() == "睡觉")
   {
     sk->sub_cur_pp();
     _attcker->add_hp(_attcker->get_max_hp());
     _attcker->set_stus("睡眠");
     _attcker->set_stus("睡眠");
   }
   else if(sk->get_name() == "岩崩")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
    {
      _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
    }
    int r =get_rand();
    if(r>=70)
    {
      _defender->set_buff("畏缩");
    }
   }
   else if(sk->get_name() == "必杀门牙")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
    {
      _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
    }
    int r =get_rand();
    if(r>=70)
    {
      _defender->set_buff("畏缩");
    }
   }
   else if(sk->get_name() == "棱角化")
   {
   sk->sub_cur_pp();
   _attcker->add_ack_addtion(1);
   }
   else if(sk->get_name() == "三重攻击")
   {
   sk->sub_cur_pp();
    if(is_Hit(sk))
    {
      _defender->sub_hp(base_ack*(hit_main()?1.5:1)*pro_restant(sk->get_pro()));
    }
    int r = rand()%3;
    if(r==0)
    {
    _defender->set_stus("灼伤");
    }
    else if(r==1)
    {
    _defender->set_stus("冰冻",2);
    }
    if(r==2)
    {
    _defender->set_stus("麻痹");
    }
   }
   else if(sk->get_name() == "愤怒门牙")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
    {
      int s = _defender->get_cur_hp()/2;
      if(s<1)
      s=1;
      _defender->sub_hp(s);
    }
   }
   else if(sk->get_name() == "劈开")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
    {
      _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
    }
   }
   else if(sk->get_name() == "挣扎")
   {
    sk->sub_cur_pp();
    if(is_Hit(sk))
    {
      _defender->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro()));
      _attcker->sub_hp(base_ack*(sp_hit_main()?1.5:1)*pro_restant(sk->get_pro())/4);
    }
   }
   return;
}
double fight_Sys::pro_restant(string s)
{
  vector<string>pro = _defender->get_all_pro();
  if(pro.size()==1)
  {
    return restrant(s,pro[0]);
  }
  else 
  {
    return restrant(s,pro[0])*restrant(s,pro[1]);
  }
}
double fight_Sys::restrant(string str1, string str2)
{
		if (str1 == "一般")
		{
			if (str2 == "岩石")
			{
				return 0.5;
			}
			else if (str2 == "幽灵")
			{
				return 0;
			}
		}
		else if (str1 == "火")
		{
			if (str2 == "火")
			{
				return 0.5;
			}
			else if (str2 == "水")
			{
				return 0.5;
			}
			else if (str2 == "草")
			{
				return 2;
			}
			else if (str2 == "冰")
			{
				return 2;
			}
			else if (str2 == "虫")
			{
				return 2;
			}
			else if (str2 == "岩石")
			{
				return  0.5;
			}
			else if (str2 == "龙")
			{
				return 0.5;
			}
		}
		else if (str1 == "水")
		{
			if (str2 == "火")
			{
				return 2;
			}
			else  if (str2 == "水")
			{
				return 0.5;
			}
			else if (str2 == "草")
			{
				return 0.5;
			}
			else if (str2 == "地面")
			{
				return 2;
			}
			else if (str2 == "岩石")
			{
				return 2;
			}
			else if (str2 == "龙")
			{
				return 0.5;
			}
		}
		else if (str1 == "草")
		{
			if (str2 == "火")
			{
				return 0.5;
			}
			else if (str2 == "水")
			{
				return 2;
			}
			else if (str2 == "草")
			{
				return 0.5;
			}
			else if (str2 == "毒")
			{
				return 0.5;
			}
			else if (str2 == "地面")
			{
				return 2;
			}
			else if (str2 == "飞行")
			{
				return 0.5;
			}
			else if (str2 == "虫")
			{
				return 0.5;
			}
			else if (str2 == "岩石")
			{
				return 2;
			}
			else if (str2 == "龙")
			{
				return 0.5;
			}
		}
		else if (str1 == "电")
		{
			if (str2 == "水")
			{
				return 2;
			}
			else if (str2 == "草")
			{
				return 0.5;
			}
			else if (str2 == "电")
			{
				return 0.5;
			}
			else if (str2 == "地面")
			{
				return 0;
			}
			else if (str2 == "飞行")
			{
				return 2;
			}
			else if (str2 == "龙")
			{
				return 0.5;
			}
		}
		else if (str1 == "冰")
		{
			if (str2 == "水")
			{
				return 0.5;
			}
			else if (str2 == "草")
			{
				return 2;
			}
			else if (str2 == "冰")
			{
				return 0.5;
			}
			else if (str2 == "地面")
			{
				return 2;
			}
			else if (str2 == "飞行")
			{
				return 2;
			}
			else if (str2 == "龙")
			{
				return 2;
			}
		}
		else if (str1 == "格斗")
		{
			if (str2 == "一般")
			{
				return 2;
			}
			else if (str2 == "冰")
			{
				return 2;
			}
			else if (str2 == "毒")
			{
				return 0.5;
			}
			else if (str2 == "飞行")
			{
				return 0.5;
			}
			else if (str2 == "超能力")
			{
				return 0.5;
			}
			else if (str2 == "虫")
			{
				return 0.5;
			}
			else if (str2 == "岩石")
			{
				return 2;
			}
			else if (str2 == "幽灵")
			{
				return 0;
			}
		}
		else if (str1 == "毒")
		{
			if (str2 == "草")
			{
				return 2;
			}
			else if (str2 == "毒")
			{
				return 0.5;
			}
			else if (str2 == "地面")
			{
				return 0.5;
			}
			else if (str2 == "虫")
			{
				return 2;
			}
			else if (str2 == "岩石")
			{
				return 0.5;
			}
			else if (str2 == "幽灵")
			{
				return 0.5;
			}
		}
		else if (str1 == "地面")
		{
			if (str2 == "火")
			{
				return 2;
			}
			else if (str2 == "草")
			{
				return 0.5;
			}
			else if (str2 == "电")
			{
				return 2;
			}
			else if (str2 == "毒")
			{
				return 2;
			}
			else if (str2 == "飞行")
			{
				return 0;
			}
			else if (str2 == "虫")
			{
				return 0.5;
			}
			else if (str2 == "岩石")
			{
				return 2;
			}
		}
		else if (str1 == "飞行")
		{
			if (str2 == "草")
			{
				return 2;
			}
			else if (str2 == "电")
			{
				return 0.5;
			}
			else if (str2 == "格斗")
			{
				return 2;
			}
			else if (str2 == "虫")
			{
				return 2;
			}
			else if (str2 == "岩石")
			{
				return 0.5;
			}
		}
		else if (str1 == "超能力")
		{
			if (str2 == "格斗")
			{
				return 2;
			}
			else if (str2 == "毒")
			{
				return 2;
			}
			else if (str2 == "超能力")
			{
				return 0.5;
			}
		}
		else if (str1 == "虫")
		{
			if (str2 == "火")
			{
				return 0.5;
			}
			else if (str2 == "草")
			{
				return 2;
			}
			else if (str2 == "格斗")
			{
				return 0.5;
			}
			else if (str2 == "毒")
			{
				return 2;
			}
			else if (str2 == "飞行")
			{
				return 0.5;
			}
			else if (str2 == "超能力")
			{
				return 2;
			}
		}
		else if (str1 == "岩石")
		{
			if (str2 == "火")
			{
				return 2;
			}
			else if (str2 == "冰")
			{
				return 2;
			}
			else if (str2 == "格斗")
			{
				return 0.5;
			}
			else if (str2 == "地面")
			{
				return 0.5;
			}
			else if (str2 == "飞行")
			{
				return 2;
			}
			else if (str2 == "虫")
			{
				return 2;
			}
		}
		else if (str1 == "幽灵")
		{
			if (str2 == "一般") {
				return 0;
			}
			else if (str2 == "超能力")
			{
				return 0;
			}
			else if (str2 == "幽灵")
			{
				return 2;
			}
		}
		else if (str1 == "龙")
		{
			if (str2 == "龙")
			{
				return 2;
			}
		}
		return 1;
}
