#pragma once
#include<unordered_map>
#include<unistd.h>
#include"keyboard/keyboard.h"
#include<sstream>
#include"../Store/store.h"
#include"../Fight/fight.h"
#include<vector>
#include<iostream>
#include<fstream>
using namespace std;
class Map;
class Blank;
class Entry;
//地图上的一块
class Block
{
public:
 void parse(Roles* roles);
 void create_Block(string name);
 string get_name();
private:
 string type;//代表这一块是什么
};
//出口
class Entry
{
public:
  void create_Entry(int row,int col,Map* np); 
  bool is_Entry(int row,int col);
  Map* get_next_Entry_ptr();
private:
  int row;
  int col;
  Map* next_map;
};
//块的集合，表示当前可见的地域
class Map
{
public:
  Map(Roles* roles)
    :ros(roles)
  {}
 void read_file(string road);
 void parse(string s);
public:
 void draw_main_map();
 void dis_play();
 void init(int row,int col);
 void set_Entry(int rows,int cols,Map* next_map);
 Map* deal_Entry();
 void move();
private:
 int cur_rows=2;
 int cur_cols=2;
 int true_rows;
 int true_cols;
 //当前显示到屏幕的地图
 Block mp[5][5];
 //当前所处的大地图
 vector<vector<Block>>big_map;
 //一个地方可能会含有很多个出口
 vector<Entry>entry;
 //当前大地图的名字
 string name;
 Roles* ros;
};
class Game
{
public:
  Game(Roles* roles)
   :ros(roles)
  {}
  void create_map();
  void run();
private:
  Map* home_map;
  Map* main_map;
  Map* store_map;
  Map* cur_map;
  Roles* ros;
};
