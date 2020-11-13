#pragma  once
#include"../Roles/roles.h"
#include<unordered_map>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<jsoncpp/json/json.h>
using namespace std;
struct Arc_Info
{
  string name;
  string introduce;
  int price;
};
class Store 
{
public:
  Store(Roles* rols);
private:
  void read_file();
public:
  void choice_arc();
private:
  void buy_arc(string name);  
private:
  vector<Arc_Info>info;
  Roles* _roles;
};

