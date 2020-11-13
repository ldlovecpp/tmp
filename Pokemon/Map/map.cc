#include"map.h"
#include<sstream>
string Block::get_name()
{
  return type;
}
void Block::create_Block(string name)
{
  type=name;
}
void Block::parse(Roles* roles)
{
  recover_keyboard();
  if(type=="草")
  {
   int r = rand()%153;
   Roles wild;
   Elevs elvs;
   stringstream ss;
   ss<<r;
   string tmp;
   ss>>tmp;
   elvs.create_elevs_by_no(tmp);
   wild.add_Elevs(elvs);
   Player_Vs_Wild pvw(roles,&wild);
   pvw.Fight();
  }
  else if(type=="训")
  {
    Roles trainer;
    int n = roles->get_pocket().size();
    for(int i=0;i<n;i++)
    {
   int r = rand()%153;
   Elevs elvs;
   stringstream ss;
   ss<<r;
   string tmp;
   ss>>tmp;
   elvs.create_elevs_by_no(tmp);
   trainer.add_Elevs(elvs);
    }
   Player_Vs_Wild pvw(roles,&trainer);
   pvw.Fight();
  }
  else if(type == "售台")
  {
   Store store(roles);
   store.choice_arc();
  }
  else if(type == "美")
  {
   system("cls");
   cout << "你: 美女好!!"<<endl;
   cout <<"按Enter键继续.." <<endl;
   getchar();
   cout << "美女: 你好,去干嘛啊" <<endl;
   cout <<"按Enter键继续.." <<endl;
   getchar();
   cout << "你: 去打野怪啊" <<endl;
   cout <<"按Enter键继续.." <<endl;
   getchar();
   cout << "美女: 小心啊" <<endl;
   cout <<"按Enter键继续.." <<endl;
   getchar();
   cout << "你: 好的"<<endl;
   cout <<"按Enter键继续.." <<endl;
   getchar();
   bool key=true;
   for(int i=0;i<roles->get_pocket().size();i++)
   {
     if(roles->get_pocket()[i].getname()=="皮卡丘") 
     {
       key=false;
       break;
     }
   }
   if(key==true)
   {
   cout << "美女 很好,你很棒,送你你置皮卡丘,去吧,皮卡丘 " <<endl;
   getchar();
   system("cls");
   cout << "你获得了精灵皮卡丘!!"<<endl;
   cout << "恭喜你完成了获得皮卡丘的任务,奖励金钱5000"<<endl;
   roles->add_money(1000);
   roles->add_Elevs("皮卡丘");
   }
   else 
   {
   cout << "你已经拥有了皮卡丘,去把皮卡丘"<<endl;
   }
  }
  init_keyboard();
}
Map* Entry::get_next_Entry_ptr()
{
  return next_map;
}
void Entry::create_Entry(int x,int y,Map* mp)
{
  row=x;
  col=y;
  next_map=mp;
}
bool Entry::is_Entry(int r,int c)
{
  return row==r&&col==c;
}
void Map::set_Entry(int rows,int cols,Map* np)
{
  Entry ent;
  ent.create_Entry(rows,cols,np);
  entry.push_back(ent);
}
Map* Map::deal_Entry()
{
  for(int i=0;i<entry.size();i++)
  {
    if(entry[i].is_Entry(true_rows,true_cols))
    {
      return entry[i].get_next_Entry_ptr();
    }
  }
  return this;
}
void Map::init(int row,int col)
{
   true_rows=row;
   true_cols = col;
}
void Map::dis_play()
{
   for(int i=0;i<5;i++)
   {
     for(int j=0;j<5;j++)
     {
       if(i==cur_rows&&j==cur_cols)
       {
       cout << "웃" <<" " <<std::flush;
       }
       else 
       {
         string s= mp[i][j].get_name();
         if(s=="树")
         { 
           cout << "▲ "<<" " <<std::flush;
         }
         else if(s=="草")
         {
           cout << "▓" << " " <<std::flush;
         }
         else if(s=="路"||s=="地板")
         {
           cout << "▨"<<" " <<std::flush;
         }
         else if(s=="美")
         {
           cout << "유"<< " " <<std::flush;
         }
         else if(s=="商")
         {
           cout << " ☂"<< " " <<std::flush;
         }
         else if(s=="家")
         {
           cout << "田" << " " <<std::flush;
         }
         else 
         {
           cout << s << " " <<endl;
         }
       }
     }
     cout << endl;
     cout << endl;
   }
}
void Map::draw_main_map()
{
  int begin_rows=true_rows-cur_rows;
  int begin_cols = true_cols-cur_cols;
  for(int i=0;i<5;i++)
  {
    for(int j=0;j<5;j++)
    {
      mp[i][j]=big_map[begin_rows+i][begin_cols+j];
    }
  }
}
void Map::move()
{
  init_keyboard();
  char ch=get_ch();
  if(ch=='w')
  {
   if(big_map[true_rows-1][true_cols].get_name()=="路"||big_map[true_rows-1][true_cols].get_name()=="地板"||big_map[true_rows-1][true_cols].get_name()=="家"||big_map[true_rows-1][true_cols].get_name()=="出口"||big_map[true_rows-1][true_cols].get_name()=="商")//网上走
   {
      true_rows--;
      //走到边缘的下一行,更新当前小地图
      if(cur_rows==1)
      {
        //矩阵下移
        for(int i=3;i>=0;i--)
        {
          for(int j=0;j<5;j++)
          {
            mp[i+1][j]=mp[i][j];
          }
        }
        //导入上行
        int begin = true_cols-cur_cols;
        for(int j=0;j<5;j++)
        {
          mp[0][j]=big_map[true_rows][begin+j];
        }
      }
      else 
        cur_rows--;
   }
   else 
     big_map[true_rows-1][true_cols].parse(ros);
  }
  else if(ch=='s')
  {
   if(big_map[true_rows+1][true_cols].get_name()=="路"||big_map[true_rows+1][true_cols].get_name()=="地板"||big_map[true_rows+1][true_cols].get_name()=="家"||big_map[true_rows+1][true_cols].get_name()=="出口"||big_map[true_rows+1][true_cols].get_name()=="商")//网下走
   {
      true_rows++;
      if(cur_rows==3)
      {
      //矩阵上移
      for(int i=1;i<5;i++)
      {
        for(int j=0;j<5;j++)
        {
          mp[i-1][j]=mp[i][j];
        }
      }
      //导入下行
      int begin =true_cols-cur_cols;
      for(int j=0;j<5;j++)
      {
       mp[4][j]=big_map[true_rows][begin+j];
      }
      }
      else 
        cur_rows++;
  }
   else 
   {
     big_map[true_rows+1][true_cols].parse(ros);
   }
  }
  else if(ch=='a')
  {
   if(big_map[true_rows][true_cols-1].get_name()=="路"||big_map[true_rows][true_cols-1].get_name()=="地板"||big_map[true_rows][true_cols-1].get_name()=="家"||big_map[true_rows][true_cols-1].get_name()=="出口"||big_map[true_rows][true_cols-1].get_name()=="商")//网下走
   {
    true_cols--;
    if(cur_cols==1)
    {
    //矩阵右移
    for(int j=3;j>=0;j--)
    {
     for(int i=0;i<5;i++)
     {
      mp[i][j+1]=mp[i][j];
     }
    }
    //导入左行
    int begin=true_rows-cur_rows;
    for(int i=0;i<5;i++)
    {
     mp[i][0]=big_map[begin+i][true_cols];
    }
    }
    else 
      cur_cols--;
   }
   else 
     big_map[true_rows][true_cols-1].parse(ros);
  }
  else if(ch=='d')
  {
   if(big_map[true_rows][true_cols+1].get_name()=="路"||big_map[true_rows][true_cols+1].get_name()=="地板"||big_map[true_rows][true_cols+1].get_name()=="家"||big_map[true_rows][true_cols+1].get_name()=="出口"||big_map[true_rows][true_cols+1].get_name()=="商")//网下走
   {
   true_cols++;
   //矩阵左移
   if(cur_cols==3)
   {
    for(int j=1;j<5;j++)
    {
      for(int i=0;i<5;i++)
      {
        mp[i][j-1]=mp[i][j];
      }
    }
   //导入右行
   int begin=true_rows-cur_rows;
   for(int i=0;i<5;i++)
   {
     mp[i][4]=big_map[begin+i][true_cols];
   }
  }
  else 
  {
    cur_cols++;
  }
  }
  else
    big_map[true_rows][true_cols+1].parse(ros);
  }
  recover_keyboard();
}
void Map::parse(string buf)
{
 stringstream ss;
 ss<<buf;
 vector<Block>arr;
 string tmp;
 while(ss>>tmp)
 {
   Block t;
   t.create_Block(tmp);
   arr.push_back(t);
 }
 big_map.push_back(arr);
}
void Map::read_file(string name)
{
   string s="../Resource/";
   s+=name;
   s+=".txt";
   ifstream in(s.c_str());
   if(!in.is_open())
   {
     cerr << "Map::read_file open err"<<s <<endl;
     exit(1);
   }
   string buf;
   while(getline(in,buf))
   {
     parse(buf);
     buf.clear();
   }
   in.close();
}
void Game::create_map()
{    
  home_map=new Map(ros);    
  main_map=new Map(ros);    
  store_map = new Map(ros);    
  home_map->read_file("home_map");    
  main_map->read_file("main_map");    
  store_map->read_file("store_map");    
  home_map->set_Entry(4,6,main_map);    
  store_map->set_Entry(5,8,main_map);
  main_map->set_Entry(9,25,home_map);
  main_map->set_Entry(8,23,store_map);
  store_map->init(5,7);
  home_map->init(4,5);
  main_map->init(9,24);
  cur_map=main_map;
}    
void Game::run()
{
  while(1)
  {
    system("clear");
    cur_map->draw_main_map();
    cur_map->dis_play();
    cur_map->move();
    cur_map=cur_map->deal_Entry();
  }
}
