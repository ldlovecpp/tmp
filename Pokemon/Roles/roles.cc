#include"roles.h"
void Roles::add_Elevs(string name)
{
  Elevs* tmp = new Elevs;
  tmp->create_elevs_by_name(name);
  pocket.push_back(*tmp);
}
void Roles::del_Elevs(string name)
{
  vector<Elevs>::iterator p =pocket.begin();
  while(p!=pocket.end())
  {
    if(p->getname()==name)
    {
      pocket.erase(p);
      break;
    }
    ++p;
  }
}
vector<Elevs>& Roles::get_pocket()
{
  return pocket;
}
bool Roles::use_money(int cnt)
{
  if(money-cnt<0)
  {
    return false;
  }
  money-=cnt;
  return true;
}
int Roles::get_cur_money()
{
  return money;
}
void Roles::add_money(int cnt)
{
  money+=cnt;
}
void Roles::add_arc(string name)
{
  arc[name]++;
}
bool Roles::use_arc(string name)
{
  int cnt = arc[name];
  if(cnt==0)
    return false;
  else 
  {
    arc[name]--;
  }
  return true;
}
unordered_map<string,int>&Roles::get_arc_info()
{
  return arc;
}
bool Roles::in_arc_pocket(string name)
{
  return arc[name];
}
void Roles::add_Elevs(Elevs& elv)
{
  pocket.push_back(elv);
}
