#pragma once
#include<math.h>
#include<list>
#include<unordered_map>
#include<string>
#include<sstream>
#include<stdlib.h>
#include<sstream>
#include<iostream>
#include<jsoncpp/json/json.h>
#include<fstream>
#include<vector>
#include"skill.h"
using namespace std;
enum base_point{
   HP,
   ACK,
   DEF,
   S_ACK,
   S_DEF,
   SPEED
};
struct Elevs_Info
{
  //编号
  string no;
  //精灵名称
  string name;
  //精灵属性
  string pro;
  //精灵高度
  string hight;
  //精灵质量
  string weight;
  //精灵的稀有度
  string rarity;
  //精灵基本描述
  string introduce;
  //捕获率
  int catch_rate;
  //血量
  int hp;
  //伤害
  int ack;
  //防御
  int def;
  //特攻
  int s_ack;
  //特防
  int s_def;
  //速度
  int speed;
  //总种族值
  int total;
  //经验级别(到达100级的速度)
  string exp_lever;
  //初始经验值
  int init_exp;
};
class Exp
{
public:
  int get_lv();
  bool add_exp(int x);
  bool is_full_lv();
  void init_exp(int c);
  void set_exp_lever(string l);
private:
  bool updata_lv();
  void read_file();
private:
  int lv;
  int cur_exp;
  int full_exp;
  string level;
  unordered_map<string,vector<int>>exp_table; 
};
class Hp
{
public:
  bool sub_hp(int cnt);
  bool is_die();
  int get_cur_hp();
  int get_max_hp();
  void update_hp(int lv,int base_point);
  void init(int lv,int hp,int base_point);
  void add_hp(int cnt);
private:
  int cur_hp;
  int max_hp;
  int race_hp;
};
class Ability{
public:
  int get_ack(int ack,int lv,int base_point);
  int get_def(int ack,int lv,int base_point);
  int get_s_ack(int ack,int lv,int base_point);
  int get_s_def(int ack,int lv,int base_point);
  int get_speed(int ack,int lv,int base_point);
private:
  int get_abi(int lv,int c,int base_point);
};
class Elevs 
{
  //介绍
public:
  string& get_introduce();
  //稀有度
  string& get_rarity();
  //身高
  string& get_height();
  //体重
  string& get_weight();
private:
  //读取精灵信息
  void read_elevs_Info(string s);
//属性接口
public:
  string getpro();
  bool in_pro(string s);
  vector<string>get_all_pro();

//名称接口
public:
  string getname();
  void create_elevs_by_name(string name);
  void create_elevs_by_no(string no);

//经验接口
public:
int get_lv();
bool add_exp(int c); //注意出错
bool is_full_lv();
int get_base_exp();

//血量接口
int get_cur_hp();
int get_max_hp();
void add_hp(int c);
bool sub_hp(int c);
bool is_die();
//其他能力值接口
public:
 int get_ack();
 int get_def();
 int get_s_ack();
 int get_s_def();
 int get_spped();
 void add_ack_addtion(int num);
 void add_def_addtion(int num);
 void add_s_ack_addtion(int num);
 void add_s_def_addtion(int num);
 void add_speed_addtion(int num);
 void sub_ack_addtion(int num);
 void sub_def_addtion(int num);
 void sub_s_ack_addtion(int num);
 void sub_s_def_addtion(int num);
 void sub_speed_addtion(int num); 
 void restore_addtion();
//基础点数(野怪没有)
  
public:
void set_base_point();
void add_base_point(int c,base_point  type);//注意出错
//命中率与回避率
private:
int get_per(int l);
public:
void sub_hit_per(int num);
void add_hit_per(int num);
void sub_dodge_per(int num);
void add_dodge_per(int num);
int get_hit_per();
int get_dodge_per();
void restroe_hit_dodge_lv();
//buff
void set_buff(string buff_name);
int in_buff(string buff_name);
bool remove_buff(string buff_name);
void display_all_buff();
void remove_all_buff();
//可以使用的技能
private:
  void read_can_use_skill(); 
  void prase(string s);
  void update_can_use_skill();
  bool the_skill_can_use(string name);
public:
  Skill* getSkill_by_name(string nm);
  vector<Skill>& get_All_Skill();
  Skill* get_last_use_Skill();
  void set_Last_Skill(Skill* sk);
//异常状态
public:
  void set_stus(string stu,int times=1);
  bool remove_stus(string str);
  bool stus_is_set(string str);
  void remove_all_stus();
//捕获率
public:
  int get_catch_rate();
private:
  vector<Skill>skill;
  unordered_map<string,bool>can_use;
  unordered_map<string,int>skill_map;
  unordered_map<string,int>buff;
  unordered_map<string,int>stus;
  Skill* last_use_Skill;
  int hp_base_point = 0;
  int ack_base_point=0;
  int def_base_point=0;
  int s_ack_base_point=0;
  int s_def_base_point=0;
  int speed_base_point=0;
  vector<Skill>can_use_skill;
  Elevs_Info elevs_info;
  Hp _hp;
  Ability abi;
  Exp ep;
  int hit_per_lv=6;
  int dodge_per_lv=6;
  int ack_addtion=0;
  int def_addtion=0;
  int s_ack_addtion=0;
  int s_def_addtion=0;
  int speed_addtion=0;
};
