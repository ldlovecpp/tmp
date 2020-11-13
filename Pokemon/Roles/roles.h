#pragma once
#include"../Elevs/elevs.h"
class Roles
{
public:
  //物品
  void add_arc(string n);
  bool use_arc(string n);
  bool in_arc_pocket(string name);
  unordered_map<string ,int >& get_arc_info();

  //金钱
  bool use_money(int cnt);
  int get_cur_money();
  void add_money(int cnt);

  //包裹
  void add_Elevs(string name);  
  vector<Elevs>& get_pocket();
  void del_Elevs(string name);
  void add_Elevs(Elevs& eles);
private:
  int money=100000;
  unordered_map<string,int>arc;
  vector<Elevs>pocket;
   
};
