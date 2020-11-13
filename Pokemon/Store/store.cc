#include"store.h"
Store::Store(Roles* rols)
  :_roles(rols)
{
  read_file();
}
void Store::read_file()
{
  Json::Value root;
  Json::Reader reader;
  ifstream in("../../resource/arc.json",ios::binary);
  if(!in.is_open())
  {
    cerr << "Stroe open file err " << endl;
    return;
  }
  reader.parse(in,root);
  for(int i=0;i<root.size();i++)
  {
    Arc_Info tmp;
    tmp.name = root[i]["name"].asString();
    tmp.introduce = root[i]["introduce"].asString();
    tmp.price = root[i]["price"].asInt();
    info.push_back(tmp);
  }
  in.close();
}
void Store::choice_arc()
{
   system("clear");
   int i=0;
   for(i=0;i<info.size();i++)
   {
     cout << "[" << i+1 << "]" <<endl;
     cout << "名称: " <<info[i].name <<endl;
     cout << "作用: " <<info[i].introduce<<endl; 
     cout  << "价格: " <<info[i].price<<endl;
   }
   cout << endl;
   cout << i+1<<":退出"<<endl;
   int choice =0 ;
   while(1)
   {
      cin >>choice; 
      if(choice==43)
      {
        return;
      }
      else if(i>0&&i<=info.size())
      {
       buy_arc(info[i-1].name);
      }
      else 
      {
       cout << "你的输入有误"<<endl;
      }
   }
}
void Store::buy_arc(string name) 
{
  for(int i=0;i<info.size();i++) 
  {
    if(info[i].name==name)
    {
    if(_roles->get_cur_money()>=info[i].price)
    {
        _roles->use_money(info[i].price);
        _roles->add_arc(info[i].name);
      cout << "购买成功!!!" <<endl;
    }
    else 
    {
        cout << "你的余额不足!!"<<endl;
    }
    }
  }
}
