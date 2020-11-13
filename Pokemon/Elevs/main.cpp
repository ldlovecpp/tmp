#include"elevs.h"
int main()
{
  Elevs els;
  els.create_elevs_by_name("妙蛙种子");
  cout <<"基础经验值: "<< els.get_base_exp() <<endl <<"属性: "<< els.getpro() <<endl;
  return 0;
}
