#include"skill.h"
void PP::init_pp(int pp)
{
  max_pp = cur_pp =pp;
}
void PP::add_max_pp(int pp)
{
  max_pp += pp;
}
bool PP::add_cur_pp(int pp)
{
  if(cur_pp + pp == max_pp)
    return false;
  if(cur_pp+pp>=max_pp)
  {
    cur_pp = max_pp;
  }
  else
  {
   cur_pp+=pp;
  }
  return true;
}
bool PP::sub_cur_pp(int pp)
{
  if(cur_pp-pp < 0)
  {
    return false;
  }
  else 
    cur_pp-=pp;
  return true;
}
bool PP::pp_run_out()
{
  return cur_pp == 0;
}
int PP::get_cur_pp()
{
  return cur_pp;
}
int PP::get_max_pp()
{
  return max_pp;
}

template<typename T>
void Skill::read_file(T s)
{
   Json::Value root;
   Json::Reader reader;
   ifstream in;
   in.open("../Resource/skill.json");
   if(!in.is_open())
   {
     cerr << "skill.json open err" <<endl;
     exit(1);
   }
   if(reader.parse(in,root))
   {
    for(int i=0;i<root.size();i++)
    {
      const type_info& type= typeid(s);
      const type_info& type_string= typeid(string);
      if(type==type_string)
      {
       if(root[i]["name"]==s)
       {
         skill_info.ack=root[i]["ack"].asInt();
         skill_info.category = root[i]["category"].asString();
         skill_info.hit_persent = root[i]["hit_persent"].asInt();
         skill_info.introduce = root[i]["introduce"].asString();
         skill_info.name = root[i]["name"].asString();
         skill_info.no = root[i]["no"].asInt();
         skill_info.pp = root[i]["pp"].asInt();
         skill_info.pro = root[i]["pro"].asString();
         skill_info.target_num = root[i]["target_num"].asInt();
         skill_info.ways = root[i]["ways"].asString();
         break;
       }
      }
      else 
      {
        if(root[i]["no"]==s)
        {
         skill_info.ack=root[i]["ack"].asInt();
         skill_info.category = root[i]["category"].asString();
         skill_info.hit_persent = root[i]["hit_persent"].asInt();
         skill_info.introduce = root[i]["introduce"].asString();
         skill_info.name = root[i]["name"].asString();
         skill_info.no = root[i]["no"].asInt();
         skill_info.pp = root[i]["pp"].asInt();
         skill_info.pro = root[i]["pro"].asString();
         skill_info.target_num = root[i]["target_num"].asInt();
         skill_info.ways = root[i]["target_num"].asString();
         break;
       }
     }
   }
   }
   else 
   {
     cerr << "Skill::reader :: reader.parse err" << endl; 
     exit(-1);
   }
   in.close();
}
void Skill::create_Skill_by_name(string name)
{
  read_file(name);
  p.init_pp(skill_info.pp);
}
void Skill::create_Skill_by_no(int no)
{
  read_file(no);
  p.init_pp(skill_info.pp);
}
string Skill::get_name()
{
  return skill_info.name;
}
string Skill::get_category()
{
  return skill_info.category;
}
string Skill::get_pro()
{
  return skill_info.pro;
}
string Skill::get_skill_ways()
{
  return skill_info.ways;
}
int Skill::get_skill_base_ack()
{
  return skill_info.ack;
}
int Skill::get_cur_pp()
{
  return p.get_cur_pp();
}
int Skill::get_max_pp()
{
  return p.get_max_pp();
}
bool Skill::add_cur_pp(int c)
{
  return p.add_cur_pp(c);
}
void Skill::add_max_pp(int c)
{
  p.add_max_pp(c);
}
bool Skill::sub_cur_pp(int c)
{
 return p.sub_cur_pp(c) ;
}
bool Skill::is_Hit()
{
  int r = rand()%100+1;
  return r<=skill_info.hit_persent;
}
int Skill::get_target_num()
{
  return skill_info.target_num;
}
string Skill::get_introduce()
{
  return skill_info.introduce;
}
int Skill::hit_per()
{
  return skill_info.hit_persent;
}
void Skill::set_buff(string name)
{
   buff[name]++;
}
void Skill::remove_buff(string name)
{
   buff[name]--;
}
bool Skill::in_buff(string name)
{
   return buff[name];
}
