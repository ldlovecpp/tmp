#include<unordered_map>
#include<string>
#include"../Roles/roles.h"
using namespace std;
class Arc
{
public:
  Arc(Roles* ros,Elevs* to_catch=nullptr)
    :_roles(ros),
    catch_elevs(to_catch)
  {}
public:
  bool deal_arc(string name);
  bool deal_catch(string name);
  void deal_other(string name);
  Elevs* choice_elevs();
  Skill* choice_skill(Elevs* elvs);
private:
 Roles* _roles; 
 Elevs* catch_elevs;
};
