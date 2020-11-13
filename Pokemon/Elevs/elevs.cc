#include"elevs.h"
int Exp::get_lv()
{
  return lv;
}
bool Exp::add_exp(int x)
{
  if(lv==100)
    return false;
  cur_exp+=x;
  if(cur_exp>exp_table[level][99])
    cur_exp=exp_table[level][99];
  updata_lv();
  return true;
}
bool Exp::updata_lv()
{
   if(lv==100)
     return false;
   int i;
   for(i=1;i<=100;i++)
   {
     if(exp_table[level][i-1]>=cur_exp)
     {
        break;
     }
   }
   lv=i;
   return true;
}
bool Exp::is_full_lv()
{
  return lv==100;
}
void Exp::init_exp(int c)
{
  cur_exp=c;
  updata_lv();
}
void Exp::set_exp_lever(string s)
{
    level = s;
    read_file();
}

void Exp::read_file()
{
  Json::Value root; 
  Json::Reader reader;
  ifstream in("../Resource/exp_lever.json",ios::binary);
  if(!in.is_open())
  {
   cerr << "open file err"<<endl; 
   exit(-1);
  }
  if(reader.parse(in,root))
  {
    for(int i=0;i<100;i++)
    {
      exp_table[level].push_back(root[level][i].asInt());
    }
  }
  else 
  {
    cerr << "json reader err " <<endl;
    exit(-1);
  }
  in.close();
}

bool Hp::sub_hp(int cnt)
{
  if(cur_hp==0) 
    return false;
  if(cur_hp-cnt<=0)
    cur_hp=0;
  else 
    cur_hp-=cnt;
  return true;
}
bool Hp::is_die()
{
  return cur_hp==0;
}
int Hp::get_cur_hp()
{
  return cur_hp;
}
int Hp::get_max_hp()
{
  return max_hp;
}
void Hp::update_hp(int lv,int base_point)
{
  max_hp = (double)((double)race_hp + (double)pow((double)base_point,0.5))*(double)lv/50 + 10 + lv;
}
void Hp::init(int lv,int hp,int base_point)
{
  race_hp = hp; 
  update_hp(lv,base_point);
  cur_hp = max_hp;
}
void Hp::add_hp(int cnt)
{
  if(cur_hp + cnt  >=  max_hp)
    cur_hp  = max_hp;
  else 
  {
    cur_hp += cnt;
  }
}
int Ability::get_ack(int c,int lv,int base_point)
{
  return get_abi(lv,c,base_point);
}
int Ability::get_def(int c,int lv,int base_point)
{
  return get_abi(lv,c,base_point);
}
int Ability::get_s_ack(int c,int lv,int base_point)
{
  return get_abi(lv,c,base_point);
}

int Ability::get_s_def(int c,int lv,int base_point)
{
  return get_abi(lv,c,base_point);
}
int Ability::get_speed(int c,int lv,int base_point)
{
  return get_abi(lv,c,base_point);
}
int Ability::get_abi(int lv,int c,int base_point)
{
   return (double)((double)c+(double)pow((double)base_point,0.5)) * (double)lv / 50 + 5;
}
void Elevs::create_elevs_by_no(string no)
{
  read_elevs_Info(no);
  ep.set_exp_lever(elevs_info.exp_lever);
  ep.init_exp(elevs_info.init_exp);// 初始化经验系统
  _hp.init(ep.get_lv(),elevs_info.hp,hp_base_point);
  read_can_use_skill();
  update_can_use_skill();
  hit_per_lv=dodge_per_lv=6;
  last_use_Skill = &skill[0];   
}
void Elevs::set_stus(string str,int times)
{
   if(stus_is_set(str))
   {
     return;
   }
   else 
   {
     stus[str]+=times;
   }
}
bool Elevs::stus_is_set(string str)
{
   return stus[str];
}
bool Elevs::remove_stus(string str)
{
  if(stus_is_set(str))
  {
    stus[str]--;
    return true;
  }
  return false;
}
int Elevs::get_per(int l)
{
  int per_map[] = {29,29,33,40,50,67,100,150,200,250,300,350,400};
  return per_map[l];
}
int Elevs::get_hit_per()
{
  return get_per(hit_per_lv);
}
int Elevs::get_dodge_per()
{
  return get_per(dodge_per_lv);
}
void Elevs::sub_hit_per(int num)
{
  if(num==0)
    return;
  hit_per_lv-=num;
}
void Elevs::add_hit_per(int num)
{
  if(num==12)
    return;
  hit_per_lv+=num;
}
void Elevs::sub_dodge_per(int num)
{
  if(num==0)
    return;
  dodge_per_lv-=num;
}
void Elevs::add_dodge_per(int num)
{
  if(num==12)
    return;
  dodge_per_lv+=num;
}
void Elevs::restroe_hit_dodge_lv()
{
  hit_per_lv=dodge_per_lv=6;
}
void Elevs:: display_all_buff()
{
  unordered_map<string,int>::iterator p = buff.begin();
  while(p!=buff.end())
  {
    if(p->second)
    {
      cout << p->first << " ";
    }
    p++;
  }
}
string & Elevs::get_introduce()
{
  return  elevs_info.introduce;
}
string& Elevs::get_rarity()
{
  return elevs_info.rarity;
}
string& Elevs::get_height()
{
  return elevs_info.hight;
}
string& Elevs::get_weight()
{
  return elevs_info.weight;
}
void Elevs::read_elevs_Info(string s)
{
  Json:: Value root;
  Json:: Reader reader;
  ifstream in("../Resource/elevs.json",ios::binary);
  if(!in.is_open())
  {
    cerr << "levs::read_elevs_Info open err" <<endl;
    exit(-1);
  }
  if(reader.parse(in,root))
  {
    for(int i=0;i<root.size();i++)   
    {
      if(root[i]["name"].asString()==s||root[i]["no"].asString()==s)
      {
       elevs_info.ack = root[i]["ack"].asInt();
       elevs_info.catch_rate = root[i]["catch_rate"].asInt();
       elevs_info.def = root[i]["def"].asInt();
       elevs_info.exp_lever = root[i]["exp_lever"].asString();
       elevs_info.hight = root[i]["hight"].asString();
       elevs_info.hp = root[i]["hp"].asInt();
       elevs_info.init_exp = root[i]["init_exp"].asInt();
       elevs_info.introduce = root[i]["introduce"].asString();
       elevs_info.name = root[i]["name"].asString();
       elevs_info.no = root[i]["no"].asString();
       elevs_info.pro = root[i]["pro"].asString();
       elevs_info.rarity = root[i]["rarity"].asString();
       elevs_info.s_ack = root[i]["s_ack"].asInt();
       elevs_info.s_def = root[i]["s_def"].asInt();
       elevs_info.speed = root[i]["speed"].asInt();
       elevs_info.total = root[i]["total"].asInt();
       elevs_info.weight = root[i]["weight"].asString();
      }
    }
  }
  else 
  {
   cerr << "parse error" << endl;
   exit(-1);
  }
  in.close();
}
string Elevs::getpro()
{
  return elevs_info.pro;
}
bool Elevs::in_pro(string s)
{
  string pro = elevs_info.pro;
  for(size_t i=0;i<pro.size();++i)
  {
    if(pro[i]==',')
    {
      pro[i]=' ';
      break;
    }
  }
  stringstream ss;
  ss<<pro;
  string tmp;
  while(ss>>tmp)
  {
    if(tmp==s)
      return true;
  }
  return false;
}
string Elevs::getname()
{
  return elevs_info.name;
}
void Elevs::create_elevs_by_name(string name)
{
  //读取数据
  read_elevs_Info(name);
  //初始化经验系统
  ep.set_exp_lever(elevs_info.exp_lever);
  ep.init_exp(elevs_info.init_exp);// 初始化经验系统
  _hp.init(ep.get_lv(),elevs_info.hp,hp_base_point);
  read_can_use_skill();
  update_can_use_skill();
  hit_per_lv=dodge_per_lv=6;
  last_use_Skill = &skill[0];
}
void Elevs::set_Last_Skill(Skill* sk)
{
  last_use_Skill = sk;
}
int Elevs::get_lv()
{
  return ep.get_lv();
}
bool Elevs::add_exp(int c)
{
   bool res= ep.add_exp(c);
  if(res==false)
    return false;
  _hp.update_hp(get_lv(),hp_base_point);
  update_can_use_skill();
  return true;
}
bool Elevs::is_full_lv()
{
  return ep.is_full_lv();
}
int Elevs::get_cur_hp()
{
  return _hp.get_cur_hp();
}
int Elevs::get_max_hp()
{
  return _hp.get_max_hp();
}
void Elevs::add_hp(int c)
{
   return _hp.add_hp(c); 
}
bool Elevs::sub_hp(int c)
{
  return _hp.sub_hp(c);
}
bool Elevs::is_die()
{
  return _hp.is_die();
}
int Elevs::get_ack()
{
  int lv=get_lv()+ack_addtion;
  return abi.get_ack(elevs_info.ack,lv,ack_base_point);
}
int Elevs::get_def()
{
  int lv=get_lv()+def_addtion;
  return abi.get_ack(elevs_info.def,lv,def_base_point);
}
int Elevs::get_s_ack()
{
  int lv=get_lv()+s_ack_addtion;
  return abi.get_ack(elevs_info.s_ack,lv,s_ack_base_point);
}
int Elevs::get_s_def()
{
  int lv=get_lv()+s_def_addtion;
  return abi.get_ack(elevs_info.s_def,lv,s_def_base_point);
}
int Elevs::get_spped()
{
  int lv=get_lv()+speed_addtion;
  return abi.get_ack(elevs_info.speed,lv,speed_base_point);
}
void Elevs::add_ack_addtion(int num)
{
  ack_addtion+=num;
}
void Elevs::add_def_addtion(int num)
{
  def_addtion+=num;
}
void Elevs::add_s_ack_addtion(int num)
{
  s_ack_addtion+=num;
}
void Elevs::add_s_def_addtion(int num)
{
  s_def_addtion+=num;
}
void Elevs::add_speed_addtion(int num)
{
  speed_addtion+=num;
}
void Elevs::sub_ack_addtion(int num)
{
  ack_addtion-=num;
}
void Elevs::sub_def_addtion(int num)
{
  def_addtion-=num;
}
void Elevs::sub_s_ack_addtion(int num)
{
  s_ack_addtion-=num;
}
void Elevs::sub_s_def_addtion(int num)
{
  s_def_addtion-=num;
}
void Elevs::sub_speed_addtion(int num)
{
  speed_addtion-=num;
}
void Elevs::restore_addtion()
{
  ack_addtion=def_addtion=s_ack_addtion=s_def_addtion=speed_addtion=0;
}
void Elevs::add_base_point(int c,base_point type)
{
  if(type==HP)
  {
  hp_base_point+=c;
  _hp.update_hp(get_lv(),hp_base_point);
  }
  else if(type==ACK)
  {
   ack_base_point+=c; 
  }
  else if(type==DEF)
  {
  def_base_point+=c;
  }
  else if(type==S_ACK)
  {
   s_ack_base_point+=c;
  }
  else if(type==S_DEF)
  {
  s_def_base_point+=c;
  }
  else if(type==SPEED)
  {
  speed_base_point+=c;
  }
}
void Elevs::set_buff(string buff_name)
{
  buff[buff_name]++;
}
bool Elevs::remove_buff(string buff_name)
{
    if(buff[buff_name]==0)
    {
      return false;
    }
    else if(buff[buff_name]==1)
    {
      buff.erase(buff_name);
    }
    else 
    {
      buff[buff_name]--;
    }
    return true;
}
int Elevs::in_buff(string buff_name)
{
  return buff[buff_name];
}
void Elevs::read_can_use_skill()
{
  vector<vector<string>>res;
  ifstream in("../Resource/skill_can_use.txt",ios::in|ios::binary);
  char buf[100];
  vector<string>arr;
  while(in.getline(buf,100))
  {
     string tmp(buf);
     if(!tmp.empty())
     {
      arr.push_back(tmp);
     }
     else 
     {
       res.push_back(arr);
       arr.clear();
     }
  }  
  for(int i=0;i<res.size();i++)
  {
    if(res[i][0]==getname())
    {
     for(int j=1;j<res[i].size();j++)
     {
        prase(res[i][j]) ;
     }
    }
  }
  unordered_map<string,int>::iterator p = skill_map.begin();
  while(p!=skill_map.end())
  {
    Skill tmp;
    tmp.create_Skill_by_name(p->first);
    ++p;
    skill.push_back(tmp);
  }
  in.close();
}
void Elevs::prase(string s)
{
   stringstream ss;
   ss<<s;
   string nm;
   int l;
   ss>>nm;
   ss>>l;
   skill_map[nm]=l;
}
void Elevs::update_can_use_skill()
{
   unordered_map<string,int>::iterator p = skill_map.begin();
   while(p!=skill_map.end())
   {
    if(p->second<get_lv())
    {
      can_use[p->first]=true;
    }
    else 
    {
      can_use[p->first]=false;
    }
    ++p;
   }
   for(int i=0;i<skill.size();i++)
   {
     if(the_skill_can_use(skill[i].get_name()))
     {
        bool can_push=true;
        for(int k=0;k<can_use_skill.size();k++)
        {
          if(can_use_skill[k].get_name() == skill[i].get_name()) 
            can_push=false;
        }
        if(can_push)
        can_use_skill.push_back(skill[i]);
     }
   }
}
Skill* Elevs::getSkill_by_name(string nm)
{
   int idx;
   for(idx=0;idx<skill.size();idx++)
   {
      if(skill[idx].get_name()==nm)     
        break;
   } 
   return &skill[idx];
}
bool Elevs::the_skill_can_use(string s)
{
  return can_use[s]; 
}
Skill* Elevs::get_last_use_Skill()
{
  return last_use_Skill;
}
vector<Skill>& Elevs::get_All_Skill()
{
  return can_use_skill;
}
int Elevs::get_base_exp()
{
  return elevs_info.init_exp; 
}
vector<string>Elevs::get_all_pro()
{
  string s = elevs_info.pro;
  for(int i=0;i<s.size();i++)
  {
    if(s[i]==',')
      s[i]=' ';
  }
  stringstream ss;
  ss<<s;
  string tmp;
  vector<string>res;
  while(ss>>tmp)
  {
    res.push_back(tmp);
  }
  return res;
}
void Elevs::remove_all_buff()
{
  buff.clear();
}
void Elevs::remove_all_stus()
{
  unordered_map<string,int>::iterator p = stus.begin();
  while(p!=stus.end())
  {
    if(p->first!="中毒"&& p->first!="灼伤")
    {
      p=stus.erase(p);
    }
    else
      p++;
  }
}
int Elevs::get_catch_rate()
{
  return elevs_info.catch_rate;
}
