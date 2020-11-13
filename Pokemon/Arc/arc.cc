#include"arc.h"
#include<unistd.h>
Elevs* Arc::choice_elevs()
{
   system("clear");
   cout << "请选择要施加的宝可梦" <<endl;
   int i;
   for(i=0;i<_roles->get_pocket().size();i++)
   {
     cout <<"[" << i+1  <<"]"; 
     cout <<_roles->get_pocket()[i].getname()<<" : "<<endl; 
     cout << "描述: " << _roles->get_pocket()[i].get_introduce() << endl;
     cout << "当前血量/最大血量: "<<_roles->get_pocket()[i].get_cur_hp() << "/"<<_roles->get_pocket()[i].get_max_hp() <<endl;
     cout << "属性: " << _roles->get_pocket()[i].getpro()<<endl;
     cout << "等级: " << _roles->get_pocket()[i].get_lv() << endl;
     cout << "稀有度: " << _roles->get_pocket()[i].get_rarity() <<endl;
     cout << "高度: " << _roles->get_pocket()[i].get_height() << endl;
     cout << "重量: " << _roles->get_pocket()[i].get_weight() << endl;
     cout << endl;
   }
   while(1)
   {
   cout << "请输入你的选择: ";
   int choice = 0;
   cin >> choice ;
   if(choice<1||choice>_roles->get_pocket().size())
   {
     cout << "输入数据不在给定范围内!! " << endl;
   }
   else 
   {
     return &_roles->get_pocket()[choice-1];
   }
  }
}
Skill* Arc::choice_skill(Elevs* elevs)
{
   for(int i=0;i<elevs->get_All_Skill().size();i++) 
   {
     cout << "["<<i+1<<"]"<<endl;
     cout <<"名称: ";
     cout <<elevs->get_All_Skill()[i].get_name() <<endl; 
     cout <<"类型: " <<elevs->get_All_Skill()[i].get_category() <<endl; 
     cout <<"属性: " <<elevs->get_All_Skill()[i].get_pro() <<endl;
     cout << "当前PP/最大PP " <<elevs->get_All_Skill()[i].get_cur_pp() <<":"<<elevs->get_All_Skill()[i].get_max_pp();
   }
   int choice=0;
   while(1)
   {
     cout <<"请输入你的选择:  ";
     cin >>choice;
     if(choice>=1&&choice<elevs->get_All_Skill().size())
     {
        return &elevs->get_All_Skill()[choice-1];
     }
     else 
     {
       cout << "你的输入有误,请重新输入"<<endl;
     }
   }
}
bool Arc::deal_arc(string name)
{
  if(catch_elevs!=nullptr)
  {
    if(deal_catch(name))
    {
      system("clear");
      cout << "恭喜得到新的宝可梦: " << catch_elevs->getname() <<endl;
      sleep(3);
      _roles->add_Elevs(catch_elevs->getname());
      return true;
    }
    else 
    {
      system("clear");
      cout << "很遗憾,捕捉失败!!" <<endl;
      sleep(3);
      return false;
    }
  }
  else 
  {
    deal_other(name);
    return false;
  }
}
void Arc::deal_other(string name)
{
   Elevs* whose = choice_elevs();
   if(name=="HP增强剂")
   {
    whose->add_base_point(10,HP);
   }
   else if(name=="攻击增强剂")
   {
    whose->add_base_point(10,ACK);
   }
   else if(name=="防御增强剂")
   {
    whose->add_base_point(10,DEF);
   }
   else if(name=="特供增强剂")
   {
    whose->add_base_point(10,S_ACK);
   }
   else if(name=="特防增强剂")
   {
    whose->add_base_point(10,S_DEF);
   }
   else if(name=="速度增强剂")
   {
    whose->add_base_point(10,SPEED);
   }
   else if(name=="PP提升剂")
   {
     Skill* sk=choice_skill(whose);
     sk->add_max_pp(sk->get_max_pp()*1.6);
   }
   else if(name=="伤药")
   {
     whose->add_hp(20);   
   }
   else if(name=="解毒药")
   {
     while(whose->stus_is_set("中毒"))
     {
        whose->remove_stus("中毒");
     }
   }
   else if(name=="灼伤药")
   {
     while(whose->stus_is_set("灼伤"))
     {
        whose->remove_stus("灼伤");
     }
   }
   else if(name=="解冻药")
   {
     while(whose->stus_is_set("冰冻"))
     {
        whose->remove_stus("冰冻");
     }
   }
   else if(name=="解麻药")
   {
     while(whose->stus_is_set("麻痹"))
     {
        whose->remove_stus("麻痹");
     }
   }
   else if(name=="全复药")
   {
    whose->add_hp(whose->get_max_hp());
    while(whose->in_buff("混乱"))
    {
        whose->remove_stus("混乱");
    }
   }
   else if(name=="全满药")
   {
    whose->add_hp(whose->get_max_hp());
   }
   else if(name== "厉害伤药")
   {
    whose->add_hp(120);
   }
   else if(name=="好伤药")
   {
     whose->add_hp(60);
   }
   else if(name=="万用药")
   {
    while(whose->in_buff("混乱"))
    {
      whose->remove_buff("混乱");
    }
    while(whose->in_buff("中毒"))
      whose->remove_buff("中毒");
    return;
     while(whose->stus_is_set("冰冻"))
     {
        whose->remove_stus("冰冻");
     }
     return;
     while(whose->stus_is_set("灼伤"))
     {
        whose->remove_stus("灼伤");
     }
     return;
    while(whose->stus_is_set("麻痹"))
     {
        whose->remove_stus("麻痹");
     }
    return;
    while(whose->stus_is_set("睡眠"))
    {
      whose->remove_buff("睡眠");
    }
    return;
   }
   else if(name== "活力碎片")
   {
     whose->add_hp(whose->get_max_hp()/2);
   }
   else if(name=="活力块")
   {
     whose->add_hp(whose->get_max_hp());
   }
   else if(name=="美味之水")
   {
     whose->add_hp(30);
   }
   else if(name=="劲爽之水")
   {
     whose->add_hp(50);
   }
   else if(name=="果汁牛奶")
   {
     whose->add_hp(70);
   }
   else if(name=="元气粉")
   {
     whose->add_hp(20);
   }
   else if(name=="PP单项全补剂")
   {
   Skill* sk=choice_skill(whose);
   sk->add_cur_pp(sk->get_max_pp());
   }
   else if(name=="釜炎仙具")
   {
     whose->remove_all_stus();
   }
   else if(name=="树果汁")
   {
    whose->add_hp(20);
   }
}
bool Arc::deal_catch(string name)
{
     int n=0;
     if(name=="精灵球")
     {
       n =rand()%255;
     }
     else if(name=="高级球")
     {
      n=rand()%200;
     }
     else if(name == "超级球")
     {
       n=rand()%150;
     }
     int s=0;
     if(catch_elevs->stus_is_set("灼伤"))
     {
      n+=12;
     }
     if(catch_elevs->stus_is_set("中毒"))
     {
      n+=12;
     }
     if(catch_elevs->stus_is_set("麻痹"))
     {
      n+=12;
     }
     if(catch_elevs->stus_is_set("睡眠"))
     {
       n+=25;
     }
     if(catch_elevs->stus_is_set("冰冻"))
     {
       n+=25;
     }
     if(n-s<=catch_elevs->get_catch_rate())
     {
       return true;
     }
     else 
     return false;  
}

