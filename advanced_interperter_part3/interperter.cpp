#include <bits/stdc++.h>

using namespace std; 

int tot_mem[1024][1024];

int row_buffer[1024];

int curr_row = -1;

int row_access_delay = 0, col_access_delay = 0;

int row_buffer_updates = 0;

bool dram = false,dram1 = false;

int inii = 0,inii1 = 0;

int dram_cy = 0,dram_cy1 = 0;

int mem_adr = 0,mem_adr1 = 0;

string dra,dra_,dra1,dra_1;

map<string,int> mem_cnt;

void show_register(map<string,int> re,vector<string> vi)
{
	for(int i=0;i<vi.size();i++)
	{
		cout<<vi.at(i)<<" = "<<hex<<re.find(vi.at(i))->second<<"\n";
	}
}

bool search(vector<string> vect,string as)
{
	for(int i=0;i<vect.size();i++)
	{
		if(vect.at(i)==as)
		{
			return true;
		}
	}
	return false;
}

vector<string> split(string str,char c)
{
	replace(str.begin(), str.end(), c , ' ');
	stringstream ss(str);
	string val;
	vector<string> vec;
	while(ss>>val)
	{
		vec.push_back(val);
	}
	return vec;
}	

int apply_oper(vector<string> &r,map<string,int> &f,map<string,int> &g,vector<string> &fg,map<string,int> &hj,int mn)
{
	auto dne = f.end();
	string t_0,t_1,t_2;
	if(fg.at(0)=="add")
	{
		if(fg.size()<4||fg.size()>4)
		{
			return 1000000;
		}
		else
		{
			t_0 = fg[1];
			t_1 = fg[2];
			t_2 = fg[3];
			if(dram && ((t_0==dra||t_1==dra||t_2==dra||t_0==dra_||t_1==dra_||t_2==dra_)||((dram_cy+row_access_delay+col_access_delay == hj.find("cycle")->second)||(dram_cy+col_access_delay == hj.find("cycle")->second)||(dram_cy+row_access_delay+col_access_delay+row_access_delay == hj.find("cycle")->second))))
			{
				dram = false;
				if(inii==1)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n"; 
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr/1024;
					hj.find("cycle")->second = (dram_cy + row_access_delay+col_access_delay);
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}else if(inii==2)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					hj.find("cycle")->second = dram_cy+col_access_delay;
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}
				else if(inii==3)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr/1024;
					hj.find("cycle")->second =(dram_cy + row_access_delay+row_access_delay+col_access_delay);
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}
				else
				{
					return 1000000;
				}
			}
			if(dram1 && ((t_0==dra1||t_1==dra1||t_2==dra1||t_0==dra_1||t_1==dra_1||t_2==dra_1)||((dram_cy1+col_access_delay == hj.find("cycle")->second)||(dram_cy1+row_access_delay+col_access_delay+row_access_delay == hj.find("cycle")->second))))
			{
				dram1 = false;
				if(inii1==1)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr1/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr1/1024;
					hj.find("cycle")->second = (dram_cy1 + row_access_delay+col_access_delay);	
					dram_cy1 = -1;
				} else if(inii1==2)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					hj.find("cycle")->second = (dram_cy1 + col_access_delay);
					dram_cy1 = -1;
				}else if(inii1==3)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay<<"\n";
					cout<<"DRAM: Active row "<<mem_adr1/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr1/1024;
					hj.find("cycle")->second =(dram_cy1+row_access_delay+row_access_delay+col_access_delay);
					dram_cy1 = -1;
				}else
				{
					return 1000000;
				}
			}
			hj.find("cycle")->second+=1;
			hj.find(fg.at(0))->second+=1;
			if(f.find(t_0)!=dne && f.find(t_1)!=dne &&t_0!="$zero")
			{
				if(f.find(t_2)!=dne){
					f.find(t_0)->second =(f.find(t_1)->second + f.find(t_2)->second);
					cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
					cout<<"Executed instruction: "<<"add "<<t_0<<" "<<t_1<<" "<<t_2<<"\n";
					cout<<"Modified regitsers: "<<t_0<<" = "<<f.find(t_0)->second<<"\n";
					cout<<"\n";
					//show_register(f,r);
					return mn;
				}
				else
				{
					if(t_2[0]=='$')
					{
						return 1000000;
					}
					else
					{
						f.find(t_0)->second =(f.find(t_1)->second + stoi(t_2));
						cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
						cout<<"Executed instruction: "<<"add "<<t_0<<" "<<t_1<<" "<<t_2<<"\n";
						cout<<"Modified regitsers: "<<t_0<<" = "<<f.find(t_0)->second<<"\n";
						cout<<"\n";
						//show_register(f,r);
						return mn;
					}	
				}
			}
			else
			{
				return 1000000;
			}
		}
	}
	if(fg.at(0)=="sub")
	{
		if(fg.size()<4||fg.size()>4)
		{
			return 1000000;
		}
		else
		{
			t_0 = fg[1];
			t_1 = fg[2];
			t_2 = fg[3];
			if(dram && ((t_0==dra||t_1==dra||t_2==dra||t_0==dra_||t_1==dra_||t_2==dra_)||((dram_cy+row_access_delay+col_access_delay == hj.find("cycle")->second)||(dram_cy+col_access_delay == hj.find("cycle")->second)||(dram_cy+row_access_delay+col_access_delay+row_access_delay == hj.find("cycle")->second))))
			{
				dram = false;
				if(inii==1)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n"; 
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr/1024;
					hj.find("cycle")->second = (dram_cy + row_access_delay+col_access_delay);
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}else if(inii==2)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					hj.find("cycle")->second = dram_cy+col_access_delay;
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}
				else if(inii==3)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr/1024;
					hj.find("cycle")->second =(dram_cy + row_access_delay+row_access_delay+col_access_delay);
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}
				else
				{
					return 1000000;
				}
			}
			if(dram1 && ((t_0==dra1||t_1==dra1||t_2==dra1||t_0==dra_1||t_1==dra_1||t_2==dra_1)||((dram_cy1+col_access_delay == hj.find("cycle")->second)||(dram_cy1+row_access_delay+col_access_delay+row_access_delay == hj.find("cycle")->second))))
			{
				dram1 = false;
				if(inii1==1)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr1/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr1/1024;
					hj.find("cycle")->second = (dram_cy1 + row_access_delay+col_access_delay);	
					dram_cy1 = -1;
				} else if(inii1==2)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					hj.find("cycle")->second = (dram_cy1 + col_access_delay);
					dram_cy1 = -1;
				}else if(inii1==3)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay<<"\n";
					cout<<"DRAM: Active row "<<mem_adr1/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr1/1024;
					hj.find("cycle")->second =(dram_cy1+row_access_delay+row_access_delay+col_access_delay);
					dram_cy1 = -1;
				}else
				{
					return 1000000;
				}
			}
			hj.find("cycle")->second+=1;
			hj.find(fg.at(0))->second+=1;
			if(f.find(t_0)!=dne && f.find(t_1)!=dne &&t_0!="$zero")
			{
				if(f.find(t_2)!=dne){
					f.find(t_0)->second =(f.find(t_1)->second - f.find(t_2)->second);
					cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
					cout<<"Executed instruction: "<<"sub "<<t_0<<" "<<t_1<<" "<<t_2<<"\n";
					cout<<"Modified regitsers: "<<t_0<<" = "<<f.find(t_0)->second<<"\n";
					cout<<"\n";
					//show_register(f,r);
					return mn;
				}
				else
				{
					if(t_2[0]=='$')
					{
						return 1000000;
					}
					else
					{
						f.find(t_0)->second =(f.find(t_1)->second - stoi(t_2));
						cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
						cout<<"Executed instruction: "<<"sub "<<t_0<<" "<<t_1<<" "<<t_2<<"\n";
						cout<<"Modified regitsers: "<<t_0<<" = "<<f.find(t_0)->second<<"\n";
						cout<<"\n";
						//show_register(f,r);
						return mn;
					}	
				}
			}
			else
			{
				return 1000000;
			}
		}
	}
	if(fg.at(0)=="mul")
	{
		if(fg.size()<4||fg.size()>4)
		{
			return 1000000;
		}
		else
		{
			t_0 = fg[1];
			t_1 = fg[2];
			t_2 = fg[3];
			if(dram && ((t_0==dra||t_1==dra||t_2==dra||t_0==dra_||t_1==dra_||t_2==dra_)||((dram_cy+row_access_delay+col_access_delay == hj.find("cycle")->second)||(dram_cy+col_access_delay == hj.find("cycle")->second)||(dram_cy+row_access_delay+col_access_delay+row_access_delay == hj.find("cycle")->second))))
			{
				dram = false;
				if(inii==1)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n"; 
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr/1024;
					hj.find("cycle")->second = (dram_cy + row_access_delay+col_access_delay);
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}else if(inii==2)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					hj.find("cycle")->second = dram_cy+col_access_delay;
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}
				else if(inii==3)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr/1024;
					hj.find("cycle")->second =(dram_cy + row_access_delay+row_access_delay+col_access_delay);
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}
				else
				{
					return 1000000;
				}
			}
			if(dram1 && ((t_0==dra1||t_1==dra1||t_2==dra1||t_0==dra_1||t_1==dra_1||t_2==dra_1)||((dram_cy1+col_access_delay == hj.find("cycle")->second)||(dram_cy1+row_access_delay+col_access_delay+row_access_delay == hj.find("cycle")->second))))
			{
				dram1 = false;
				if(inii1==1)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr1/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr1/1024;
					hj.find("cycle")->second = (dram_cy1 + row_access_delay+col_access_delay);	
					dram_cy1 = -1;
				} else if(inii1==2)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					hj.find("cycle")->second = (dram_cy1 + col_access_delay);
					dram_cy1 = -1;
				}else if(inii1==3)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay<<"\n";
					cout<<"DRAM: Active row "<<mem_adr1/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr1/1024;
					hj.find("cycle")->second =(dram_cy1+row_access_delay+row_access_delay+col_access_delay);
					dram_cy1 = -1;
				}else
				{
					return 1000000;
				}
			}
			hj.find("cycle")->second+=1;
			hj.find(fg.at(0))->second+=1;
			if(f.find(t_0)!=dne && f.find(t_1)!=dne &&t_0!="$zero")
			{
				if(f.find(t_2)!=dne){
					f.find(t_0)->second =(f.find(t_1)->second * f.find(t_2)->second);
					cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
					cout<<"Executed instruction: "<<"mul "<<t_0<<" "<<t_1<<" "<<t_2<<"\n";
					cout<<"Modified regitsers: "<<t_0<<" = "<<f.find(t_0)->second<<"\n";
					cout<<"\n";
					//show_register(f,r);
					return mn;
				}
				else
				{
					if(t_2[0]=='$')
					{
						return 1000000;
					}
					else
					{
						f.find(t_0)->second =(f.find(t_1)->second * stoi(t_2));
						cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
						cout<<"Executed instruction: "<<"mul "<<t_0<<" "<<t_1<<" "<<t_2<<"\n";
						cout<<"Modified regitsers: "<<t_0<<" = "<<f.find(t_0)->second<<"\n";
						cout<<"\n";
						//show_register(f,r);
						return mn;
					}	
				}
			}
			else
			{
				return 1000000;
			}
		}
	}
	if(fg.at(0)=="addi")
	{
		if(fg.size()<4||fg.size()>4)
		{
			return 1000000;
		}
		else
		{
			t_0 = fg[1];
			t_1 = fg[2];
			t_2 = fg[3];
			if(dram && ((t_0==dra||t_1==dra||t_2==dra||t_0==dra_||t_1==dra_||t_2==dra_)||((dram_cy+row_access_delay+col_access_delay == hj.find("cycle")->second)||(dram_cy+col_access_delay == hj.find("cycle")->second)||(dram_cy+row_access_delay+col_access_delay+row_access_delay == hj.find("cycle")->second))))
			{
				dram = false;
				if(inii==1)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n"; 
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr/1024;
					hj.find("cycle")->second = (dram_cy + row_access_delay+col_access_delay);
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}else if(inii==2)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					hj.find("cycle")->second = dram_cy+col_access_delay;
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}
				else if(inii==3)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr/1024;
					hj.find("cycle")->second =(dram_cy + row_access_delay+row_access_delay+col_access_delay);
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}
				else
				{
					return 1000000;
				}
			}
			if(dram1 && ((t_0==dra1||t_1==dra1||t_2==dra1||t_0==dra_1||t_1==dra_1||t_2==dra_1)||((dram_cy1+col_access_delay == hj.find("cycle")->second)||(dram_cy1+row_access_delay+col_access_delay+row_access_delay == hj.find("cycle")->second))))
			{
				dram1 = false;
				if(inii1==1)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr1/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr1/1024;
					hj.find("cycle")->second = (dram_cy1 + row_access_delay+col_access_delay);	
					dram_cy1 = -1;
				} else if(inii1==2)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					hj.find("cycle")->second = (dram_cy1 + col_access_delay);
					dram_cy1 = -1;
				}else if(inii1==3)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay<<"\n";
					cout<<"DRAM: Active row "<<mem_adr1/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr1/1024;
					hj.find("cycle")->second =(dram_cy1+row_access_delay+row_access_delay+col_access_delay);
					dram_cy1 = -1;
				}else
				{
					return 1000000;
				}
			}
			hj.find("cycle")->second+=1;
			hj.find(fg.at(0))->second+=1;
			if(f.find(t_0)!=dne && f.find(t_1)!=dne &&t_0!="$zero")
			{
				f.find(t_0)->second =(f.find(t_1)->second + stoi(t_2));
					//cout<<mn;
				cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
				cout<<"Executed instruction: "<<"addi "<<t_0<<" "<<t_1<<" "<<t_2<<"\n";
				cout<<"Modified regitsers: "<<t_0<<" = "<<f.find(t_0)->second<<"\n";
				cout<<"\n";
				//show_register(f,r);
				return mn;
			}
			else
			{
				return 1000000;
			}
		}
	}
	if(fg.at(0)=="slt")
	{
		if(fg.size()<4||fg.size()>4)
		{
			return 1000000;
		}
		else
		{
			t_0 = fg[1];
			t_1 = fg[2];
			t_2 = fg[3];
			if(dram && ((t_0==dra||t_1==dra||t_2==dra||t_0==dra_||t_1==dra_||t_2==dra_)||((dram_cy+row_access_delay+col_access_delay == hj.find("cycle")->second)||(dram_cy+col_access_delay == hj.find("cycle")->second)||(dram_cy+row_access_delay+col_access_delay+row_access_delay == hj.find("cycle")->second))))
			{
				dram = false;
				if(inii==1)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n"; 
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr/1024;
					hj.find("cycle")->second = (dram_cy + row_access_delay+col_access_delay);
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}else if(inii==2)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					hj.find("cycle")->second = dram_cy+col_access_delay;
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}
				else if(inii==3)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr/1024;
					hj.find("cycle")->second =(dram_cy + row_access_delay+row_access_delay+col_access_delay);
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}
				else
				{
					return 1000000;
				}
			}
			if(dram1 && ((t_0==dra1||t_1==dra1||t_2==dra1||t_0==dra_1||t_1==dra_1||t_2==dra_1)||((dram_cy1+col_access_delay == hj.find("cycle")->second)||(dram_cy1+row_access_delay+col_access_delay+row_access_delay == hj.find("cycle")->second))))
			{
				dram1 = false;
				if(inii1==1)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr1/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr1/1024;
					hj.find("cycle")->second = (dram_cy1 + row_access_delay+col_access_delay);
					dram_cy1 = -1;					
				} else if(inii1==2)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					hj.find("cycle")->second = (dram_cy1 + col_access_delay);
					dram_cy1 = -1;
				}else if(inii1==3)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay<<"\n";
					cout<<"DRAM: Active row "<<mem_adr1/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr1/1024;
					hj.find("cycle")->second =(dram_cy1+row_access_delay+row_access_delay+col_access_delay);
					dram_cy1 = -1;
				}else
				{
					return 1000000;
				}
			}
			hj.find("cycle")->second+=1;
			hj.find(fg.at(0))->second+=1;
			if(f.find(t_0)!=dne && f.find(t_1)!=dne &&t_0!="$zero")
			{
				if(f.find(t_2)!=dne){
					if(f.find(t_1)->second < f.find(t_2)->second)
					{
						f.find(t_0)->second = 1;
					}
					else
					{
						f.find(t_0)->second = 0;
					}
					cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
					cout<<"Executed instruction: "<<"slt "<<t_0<<" "<<t_1<<" "<<t_2<<"\n";
					cout<<"Modified regitsers: "<<t_0<<" = " <<f.find(t_0)->second<<"\n";
					cout<<"\n";
					//show_register(f,r);
					return mn;
				}
				else
				{
					if(t_2[0]=='$')
					{
						return 1000000;
					}	
					else
					{
						if(f.find(t_1)->second < stoi(t_2))
						{
							f.find(t_0)->second = 1;
						}
						else
						{
							f.find(t_0)->second = 0;
						}
						cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
						cout<<"Executed instruction: "<<"slt "<<t_0<<" "<<t_1<<" "<<t_2<<"\n";
						cout<<"Modified regitsers: "<<t_0<<" = "<<f.find(t_0)->second<<"\n";
						cout<<"\n";
						//show_register(f,r);
						return mn;
					}	
				}
			}
			else
			{
				return 1000000;
			}
		}
	}
	if(fg.at(0)=="j")
	{
		if(fg.size()<2||fg.size()>2)
		{
			return 1000000;
		}
		else
		{
			if(dram && (((dram_cy+row_access_delay+col_access_delay == hj.find("cycle")->second)||(dram_cy+col_access_delay == hj.find("cycle")->second)||(dram_cy+row_access_delay+col_access_delay+row_access_delay == hj.find("cycle")->second))))
			{
				dram = false;
				if(inii==1)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n"; 
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr/1024;
					hj.find("cycle")->second = (dram_cy + row_access_delay+col_access_delay);
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}else if(inii==2)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					hj.find("cycle")->second = dram_cy+col_access_delay;
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}
				else if(inii==3)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr/1024;
					hj.find("cycle")->second =(dram_cy + row_access_delay+row_access_delay+col_access_delay);
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}
				else
				{
					return 1000000;
				}
			}
			if(dram1 && (((dram_cy1+col_access_delay == hj.find("cycle")->second)||(dram_cy1+row_access_delay+col_access_delay+row_access_delay == hj.find("cycle")->second))))
			{
				dram1 = false;
				if(inii1==1)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr1/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr1/1024;
					hj.find("cycle")->second = (dram_cy1 + row_access_delay+col_access_delay);
					dram_cy1 = -1;					
				} else if(inii1==2)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					hj.find("cycle")->second = (dram_cy1 + col_access_delay);
					dram_cy1 = -1;
				}else if(inii1==2)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay<<"\n";
					cout<<"DRAM: Active row "<<mem_adr1/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr1/1024;
					hj.find("cycle")->second =(dram_cy1+row_access_delay+row_access_delay+col_access_delay);
					dram_cy1 = -1;
				}else
				{
					return 1000000;
				}
			}
			hj.find("cycle")->second+=1;
			hj.find(fg.at(0))->second+=1;
			t_0 = fg[1];
			if(g.find(t_0)!=g.end())
			{
				//show_register(f,r);
				cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
				cout<<"Executed instruction: "<<"j "<<t_0<<"\n";
				cout<<"\n";
				return g.find(t_0)->second;
			}
			else
			{
				return 1000000;
			}
		}
	}
	if(fg.at(0)=="bne")
	{
		if(fg.size()<4||fg.size()>4)
		{
			return 1000000;
		}
		else
		{
			t_0 = fg[1];
			t_1 = fg[2];
			t_2 = fg[3];
			if(dram && ((t_0==dra||t_1==dra||t_2==dra||t_0==dra_||t_1==dra_||t_2==dra_)||((dram_cy+row_access_delay+col_access_delay == hj.find("cycle")->second)||(dram_cy+col_access_delay == hj.find("cycle")->second)||(dram_cy+row_access_delay+col_access_delay+row_access_delay == hj.find("cycle")->second))))
			{
				dram = false;
				if(inii==1)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n"; 
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr/1024;
					hj.find("cycle")->second = (dram_cy + row_access_delay+col_access_delay);
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}else if(inii==2)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					hj.find("cycle")->second = dram_cy+col_access_delay;
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}
				else if(inii==3)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr/1024;
					hj.find("cycle")->second =(dram_cy + row_access_delay+row_access_delay+col_access_delay);
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}
				else
				{
					return 1000000;
				}
			}
			if(dram1 && ((t_0==dra1||t_1==dra1||t_2==dra1||t_0==dra_1||t_1==dra_1||t_2==dra_1)||((dram_cy1+col_access_delay == hj.find("cycle")->second)||(dram_cy1+row_access_delay+col_access_delay+row_access_delay == hj.find("cycle")->second))))
			{
				dram1 = false;
				if(inii1==1)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr1/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr1/1024;
					hj.find("cycle")->second = (dram_cy1 + row_access_delay+col_access_delay);	
					dram_cy1 = -1;
				} else if(inii1==2)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					hj.find("cycle")->second = (dram_cy1 + col_access_delay);
					dram_cy1 = -1;
				}else if(inii1==3)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay<<"\n";
					cout<<"DRAM: Active row "<<mem_adr1/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr1/1024;
					hj.find("cycle")->second =(dram_cy1+row_access_delay+row_access_delay+col_access_delay);
					dram_cy1 = -1;
				}else
				{
					return 1000000;
				}
			}
			hj.find("cycle")->second+=1;
			hj.find(fg.at(0))->second+=1;
			if(f.find(t_0)!=dne && g.find(t_2)!=g.end())
			{
				if(f.find(t_1)!=dne)
				{
					if(f.find(t_0)->second!=f.find(t_1)->second)
					{
						//show_register(f,r);
						cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
						cout<<"Executed instruction: "<<"bne "<<t_0<<" "<<t_1<<" "<<t_2<<"\n";
						cout<<"\n";
						return g.find(t_2)->second;
					}
					else
					{
						cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
						cout<<"Executed instruction: "<<"bne "<<t_0<<" "<<t_1<<" "<<t_2<<"\n";
						cout<<"\n";
						//show_register(f,r);
						return mn;
					}
				}
				else
				{
					if(t_1[0] == '$')
					{
						return 1000000;
					}
					else
					{
						if(f.find(t_0)->second!=stoi(t_1))
						{
							cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
							cout<<"Executed instruction: "<<"bne "<<t_0<<" "<<t_1<<" "<<t_2<<"\n";
							cout<<"\n";
							//show_register(f,r);
							return g.find(t_2)->second;
						}
						else
						{
							cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
							cout<<"Executed instruction: "<<"bne "<<t_0<<" "<<t_1<<" "<<t_2<<"\n";
							cout<<"\n";
							//show_register(f,r);
							return mn;
						}
					}
				}
			}else{
				return 1000000;
			}
		}
	}
	if(fg.at(0)=="beq")
	{
		if(fg.size()<4||fg.size()>4)
		{
			return 1000000;
		}
		else
		{
			t_0 = fg[1];
			t_1 = fg[2];
			t_2 = fg[3];
			if(dram && ((t_0==dra||t_1==dra||t_2==dra||t_0==dra_||t_1==dra_||t_2==dra_)||((dram_cy+row_access_delay+col_access_delay == hj.find("cycle")->second)||(dram_cy+col_access_delay == hj.find("cycle")->second)||(dram_cy+row_access_delay+col_access_delay+row_access_delay == hj.find("cycle")->second))))
			{
				dram = false;
				if(inii==1)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n"; 
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr/1024;
					hj.find("cycle")->second = (dram_cy + row_access_delay+col_access_delay);
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}else if(inii==2)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					hj.find("cycle")->second = dram_cy+col_access_delay;
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}
				else if(inii==3)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr/1024;
					hj.find("cycle")->second =(dram_cy + row_access_delay+row_access_delay+col_access_delay);
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}
				else
				{
					return 1000000;
				}
			}
			if(dram1 && ((t_0==dra1||t_1==dra1||t_2==dra1||t_0==dra_1||t_1==dra_1||t_2==dra_1)||((dram_cy1+col_access_delay == hj.find("cycle")->second)||(dram_cy1+row_access_delay+col_access_delay+row_access_delay == hj.find("cycle")->second))))
			{
				dram1 = false;
				if(inii1==1)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr1/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr1/1024;
					hj.find("cycle")->second = (dram_cy1 + row_access_delay+col_access_delay);	
					dram_cy1 = -1;
				} else if(inii1==2)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					hj.find("cycle")->second = (dram_cy1 + col_access_delay);
					dram_cy1 = -1;
				}else if(inii1==3)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay<<"\n";
					cout<<"DRAM: Active row "<<mem_adr1/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr1/1024;
					hj.find("cycle")->second =(dram_cy1+row_access_delay+row_access_delay+col_access_delay);
					dram_cy1 = -1;
				}else
				{
					return 1000000;
				}
			}
			hj.find("cycle")->second+=1;
			hj.find(fg.at(0))->second+=1;
			if(f.find(t_0)!=dne && g.find(t_2)!=g.end())
			{
				if(f.find(t_1)!=dne)
				{
					if(f.find(t_0)->second==f.find(t_1)->second)
					{
						cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
						cout<<"Executed instruction: "<<"beq "<<t_0<<" "<<t_1<<" "<<t_2<<"\n";
						cout<<"\n";
						//show_register(f,r);
						return g.find(t_2)->second;
					}
					else
					{
						cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
						cout<<"Executed instruction: "<<"beq "<<t_0<<" "<<t_1<<" "<<t_2<<"\n";
						cout<<"\n";
						//show_register(f,r);
						return mn;
					}
				}
				else
				{
					if(t_1[0] == '$')
					{
						return 1000000;
					}
					else
					{
						if(f.find(t_0)->second==stoi(t_1))
						{
							cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
							cout<<"Executed instruction: "<<"beq "<<t_0<<" "<<t_1<<" "<<t_2<<"\n";
							cout<<"\n";
							//show_register(f,r);
							return g.find(t_2)->second;
						}
						else
						{
							cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
							cout<<"Executed instruction: "<<"beq "<<t_0<<" "<<t_1<<" "<<t_2<<"\n";
							cout<<"\n";
							//show_register(f,r);
							return mn;
						}
					}
				}
			}else{
				return 1000000;
			}
		}
	}
	if(fg.at(0)=="sw")
	{
		if(fg.size()<3||fg.size()>3)
		{
			return 1000000;
		}
		else
		{
			if(dram)
			{
				dram = false;
				if(inii==1)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n"; 
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr/1024;
					hj.find("cycle")->second = (dram_cy + row_access_delay+col_access_delay);
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}else if(inii==2)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					hj.find("cycle")->second = dram_cy+col_access_delay;
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}
				else if(inii==3)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr/1024;
					hj.find("cycle")->second =(dram_cy + row_access_delay+row_access_delay+col_access_delay);
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}
				else
				{
					return 1000000;
				}
			}
			if(dram1)
			{
				dram1 = false;
				if(inii1==1)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr1/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr1/1024;
					hj.find("cycle")->second = (dram_cy1 + row_access_delay+col_access_delay);	
					dram_cy1 = -1;
				} else if(inii1==2)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					hj.find("cycle")->second = (dram_cy1 + col_access_delay);
					dram_cy1 = -1;
				}else if(inii1==3)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay<<"\n";
					cout<<"DRAM: Active row "<<mem_adr1/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr1/1024;
					hj.find("cycle")->second =(dram_cy1+row_access_delay+row_access_delay+col_access_delay);
					dram_cy1 = -1;
				}else
				{
					return 1000000;
				}
			}
			hj.find("cycle")->second+=1;
			hj.find(fg.at(0))->second+=1;
			t_0 = fg[1];
			t_1 = fg[2];
			int m=-1;
			string jk = "",kl = "";
			for(int k = 0;k<t_1.length();k++)
			{		
				if(t_1[k]!='(')
				{
					jk+=t_1[k];
				}
				else
				{
					m = k;
					break;
				}
			}
			for(int k = m+1;k<t_1.length()-1;k++)
			{
				kl+=t_1[k];
			}				
			int mj = stoi(jk);
			if(f.find(kl)!=dne && f.find(t_0)!=dne && t_0!="$zero")
			{
				int mjk = f.find(kl)->second;
				int zxc = mj+mjk;
				dram = true;
				dra = t_0;
				dra_ = kl;
				mem_adr = zxc;
				if(curr_row<0)
				{
					inii = 1;
					row_buffer_updates+=2;
					tot_mem[zxc/1024][zxc%1024] = f.find(t_0)->second;
					for(int q=0; q<1024; q++){
                       row_buffer[q] = tot_mem[zxc/1024][q];
                    }
					cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
					cout<<"Executed instruction: "<<"sw "<<t_0<<" "<<t_1<<"\n";
					cout<<"DRAM Request issued: "<<"Memory Location: "<<zxc<<" "<<"Row buffer: "<<curr_row<<"\n";
					cout<<"\n";
					dram_cy = hj.find("cycle")->second;
					return mn;
				}else if(curr_row == zxc/1024)
				{
					inii = 2;
					row_buffer_updates++;
					tot_mem[zxc/1024][zxc%1024] = f.find(t_0)->second;
					for(int q=0; q<1024; q++){
						row_buffer[q] = tot_mem[zxc/1024][q];
                    }
					cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
					cout<<"Executed instruction: "<<"sw "<<t_0<<" "<<t_1<<"\n";
					cout<<"DRAM Request issued: "<<"Memory Location: "<<zxc<<" "<<"Row buffer: "<<curr_row<<"\n";
					cout<<"\n";
					dram_cy = hj.find("cycle")->second;
					return mn;
				}
				else 
				{
					inii = 3;
					row_buffer_updates+=3;
					tot_mem[zxc/1024][zxc%1024] = f.find(t_0)->second;
					for(int q=0; q<1024; q++){
                        row_buffer[q] = tot_mem[zxc/1024][q];
                    }
					cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
					cout<<"Executed instruction: "<<"sw "<<t_0<<" "<<t_1<<"\n";
					cout<<"DRAM Request issued: "<<"Memory Location: "<<zxc<<" "<<"Row buffer: "<<curr_row<<"\n";
					cout<<"\n";
					dram_cy = hj.find("cycle")->second;
					return mn;
				}
				//show_register(f,r);
			}
			else
			{
				return 1000000;
			}
		}
	}
	if(fg.at(0)=="lw")
	{
		if(fg.size()<3||fg.size()>3)
		{
			return 1000000;
		}
		else
		{
			if(dram)
			{
				dram = false;
				if(inii==1)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n"; 
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr/1024;
					hj.find("cycle")->second = (dram_cy + row_access_delay+col_access_delay);
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}else if(inii==2)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					hj.find("cycle")->second = dram_cy+col_access_delay;
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}
				else if(inii==3)
				{
					cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy+1+row_access_delay+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<mem_adr<<" = " <<f.find(dra)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr/1024;
					hj.find("cycle")->second =(dram_cy + row_access_delay+row_access_delay+col_access_delay);
					string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = f.find(dra)->second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,f.find(dra)->second));
					}
					dram_cy = -1;
				}
				else
				{
					return 1000000;
				}
			}
			if(dram1)
			{
				dram1 = false;
				if(inii1==1)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
					cout<<"DRAM: Activate row "<<mem_adr1/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr1/1024;
					hj.find("cycle")->second = (dram_cy1 + row_access_delay+col_access_delay);	
					dram_cy1 = -1;
				} else if(inii1==2)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					hj.find("cycle")->second = (dram_cy1 + col_access_delay);
					dram_cy1 = -1;
				}else if(inii1==3)
				{
					cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay<<"\n";
					cout<<"DRAM: Active row "<<mem_adr1/1024<<"\n";
					cout<<"\n";
					cout<<"cycle : "<<dram_cy1+1+row_access_delay+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay+col_access_delay<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified registers: "<<dra1<<" = " <<f.find(dra1)->second<<"\n";
					cout<<"\n";
					curr_row = mem_adr1/1024;
					hj.find("cycle")->second =(dram_cy1+row_access_delay+row_access_delay+col_access_delay);
					dram_cy1 = -1;
				}else
				{
					return 1000000;
				}
			}
			hj.find("cycle")->second+=1;
			hj.find(fg.at(0))->second+=1;
			t_0 = fg[1];
			t_1 = fg[2];
			int m=-1;
			string jk = "",kl = "";
			for(int k = 0;k<t_1.length();k++)
			{	
				if(t_1[k]!='(')
				{
					jk+=t_1[k];
				}
				else
				{
					m = k;
					break;
				}
			}
			for(int k = m+1;k<t_1.length()-1;k++)
			{
				kl+=t_1[k];
			}
			int mj = stoi(jk);
			if(f.find(kl)!=dne && f.find(t_0)!=dne && t_0!="$zero")
			{
				int mjk = f.find(kl)->second;
				int zxc = mj+mjk;
				string ssttrr = to_string(zxc) + "-"+to_string(zxc+3);
				if( mem_cnt.find(ssttrr)!=mem_cnt.end())
				{
					dram1 = true;
					dra1 = t_0;
					dra_1 = kl;
					mem_adr1 = zxc;
					if(curr_row<0)
					{
						inii = 1;
						row_buffer_updates++;
						f.find(t_0)->second = tot_mem[zxc/1024][zxc%1024];
						for(int q=0; q<1024; q++){
							row_buffer[q] = tot_mem[zxc/1024][q];
						}
						cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
						cout<<"Executed instruction: "<<"lw "<<t_0<<" "<<t_1<<"\n";
						cout<<"DRAM Request issued: "<<"Memory Location: "<<zxc<<" "<<"Row buffer: "<<curr_row<<"\n";
						cout<<"\n";
						dram_cy = hj.find("cycle")->second;
						return mn;
					} else if(curr_row == zxc/1024)
					{
						inii1 = 2;
						f.find(t_0)->second = tot_mem[zxc/1024][zxc%1024];
						for(int q=0; q<1024; q++){
							row_buffer[q] = tot_mem[zxc/1024][q];
						}
						cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
						cout<<"Executed instruction: "<<"lw "<<t_0<<" "<<t_1<<"\n";
						cout<<"DRAM Request issued: "<<"Memory Location: "<<zxc<<" "<<"Row buffer: "<<curr_row<<"\n";
						cout<<"\n";
						dram_cy1 = hj.find("cycle")->second;
						return mn;
					}
					else 
					{
						inii1 = 3;
						row_buffer_updates+=2;
						f.find(t_0)->second = tot_mem[zxc/1024][zxc%1024];
						for(int q=0; q<1024; q++){
							row_buffer[q] = tot_mem[zxc/1024][q];
						}
						cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
						cout<<"Executed instruction: "<<"lw "<<t_0<<" "<<t_1<<"\n";
						cout<<"DRAM Request issued: "<<"Memory Location: "<<zxc<<"-"<<zxc+3<<" "<<"Row buffer: "<<curr_row<<"\n";
						cout<<"\n";
						dram_cy1 = hj.find("cycle")->second;
						return mn;
					}
				}
				else
				{
					return 1000000;
				}
			}
			else
			{
				return 1000000;
			}
		}
	}
	return 1000000;
}
	
int main()
{
	vector<string> reg = {"$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra"};
	vector<string> arr = {"add","sub","mul","beq","bne","slt","j","lw","sw","addi","cycle"}; 
	map<string,int> registers;
	for(int i=0;i<reg.size();i++)
	{
		registers.insert(pair<string,int>(reg.at(i),0));
	}
	
	map<string,int>operate;
	map<string,int>::iterator opr;
	for(int i=0;i<arr.size();i++){
		operate.insert(pair<string,int>(arr.at(i),0));
	}
	
	string file_path;
	cout<<"Enter the path of MIPS file: ";
	cin>>file_path;
	vector<vector<string>> file_line;
	map<string,int> funct;
	fstream file;
	file.open(file_path);
	string line;
	if(file.is_open())
	{
		int va = 0;
		while(getline(file,line))
		{
			vector<string> faltu = split(line,',');
			file_line.push_back(faltu);
			if(faltu.size()==1)
			{
				vector<string> fa= split(faltu.at(0),':');
				funct.insert(pair<string,int>(fa.at(0),va));
			}
			va++;			
		}
		file.close();
	}
	else
	{
		cout<<"No such file exist please check your give address\n";
		return 0;
	}
	//show_register(registers,reg);
	//cout<<"--------------------------------------\n";
	//cout<<"--------------------------------------\n";
	int a,b;
	cout<<"Enter the row_access_delay: ";
	cin>>a;
	row_access_delay = a;
	cout<<"Enter the col_access_delay: ";
	cin>>b;
	col_access_delay = b;
	cout<<"\n";
	cout<<"Every cycle description\n";
	cout<<"\n";
	int i =0,dm =0;
	while(i<file_line.size())
	{
		if(file_line.at(i).size()>1)
		{
			if(search(arr,file_line.at(i).at(0)))
			{
				//cout<<"----------"<<i<<"\n";
				i = apply_oper(reg,registers,funct,file_line.at(i),operate,i);
				//cout<<"----------"<<i<<"\n";
				if(i==1000000)
				{
					dm =1;
					cout<<"Wrong Input"<<"\n";
					break;
				}
				//cout<<"--------------------------------------\n";
			}
			else
			{
				dm = 1;
				cout<<"Symbol in line "+to_string(i+1)+" is not defined in this scope"<<"\n";
				break;
			}
		}
		i++;
	}
	if(dram)
	{
		dram = false;
		if(inii==1)
		{
			cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
			cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
			cout<<"\n";
			cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+col_access_delay<<"\n";
			cout<<"DRAM: Column access "<<"\n"; 
			cout<<"Modified Memory Location: "<<mem_adr<<" = " <<registers.find(dra)->second<<"\n";
			cout<<"\n";
			curr_row = mem_adr/1024;
			operate.find("cycle")->second = (dram_cy + row_access_delay+col_access_delay);
			string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
			if(mem_cnt.find(str)!=mem_cnt.end())
			{
				mem_cnt.find(str)->second = registers.find(dra)->second;
			}
			else
			{
				mem_cnt.insert(pair<string,int>(str,registers.find(dra)->second));
			}
			dram_cy = -1;
		}else if(inii==2)
		{
			cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+col_access_delay<<"\n";
			cout<<"DRAM: Column access "<<"\n";
			cout<<"Modified Memory Location: "<<mem_adr<<" = " <<registers.find(dra)->second<<"\n";
			cout<<"\n";
			operate.find("cycle")->second = dram_cy+col_access_delay;
			string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
			if(mem_cnt.find(str)!=mem_cnt.end())
			{
				mem_cnt.find(str)->second = registers.find(dra)->second;
			}
			else
			{
				mem_cnt.insert(pair<string,int>(str,registers.find(dra)->second));
			}
			dram_cy = -1;
		}
		else if(inii==3)
		{
			cout<<"cycle : "<<dram_cy+1<<"-"<<dram_cy+row_access_delay<<"\n";
			cout<<"DRAM: Writeback row "<<curr_row<<"\n";
			cout<<"\n";
			cout<<"cycle : "<<dram_cy+1+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay<<"\n";
			cout<<"DRAM: Activate row "<<mem_adr/1024<<"\n";
			cout<<"\n";
			cout<<"cycle : "<<dram_cy+1+row_access_delay+row_access_delay<<"-"<<dram_cy+row_access_delay+row_access_delay+col_access_delay<<"\n";
			cout<<"DRAM: Column access "<<"\n";
			cout<<"Modified Memory Location: "<<mem_adr<<" = " <<registers.find(dra)->second<<"\n";
			cout<<"\n";
			curr_row = mem_adr/1024;
			operate.find("cycle")->second =(dram_cy + row_access_delay+row_access_delay+col_access_delay);
			string str = to_string(mem_adr) + "-"+to_string(mem_adr+3);
			if(mem_cnt.find(str)!=mem_cnt.end())
			{
				mem_cnt.find(str)->second = registers.find(dra)->second;
			}
			else
			{
				mem_cnt.insert(pair<string,int>(str,registers.find(dra)->second));
			}
			dram_cy = -1;
		}else{
			cout<<"Wrong input\n";
			return 0;
		}
	}
	if(dram1)
	{
		dram1 = false;
		if(inii1==1)
		{
			cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
			cout<<"DRAM: Activate row "<<mem_adr1/1024<<"\n";
			cout<<"\n";
			cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+col_access_delay<<"\n";
			cout<<"DRAM: Column request "<<"\n"; 
			cout<<"Modified registers: "<<dra1<<" = " <<registers.find(dra1)->second<<"\n";
			cout<<"\n";
			curr_row = mem_adr1/1024;
			operate.find("cycle")->second = (dram_cy1 + row_access_delay+col_access_delay);	
			dram_cy1 = -1;
		} else if(inii1==2)
		{
			cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+col_access_delay<<"\n";
			cout<<"DRAM: Column request "<<"\n";
			cout<<"Modified registers: "<<dra1<<" = " <<registers.find(dra1)->second<<"\n";
			cout<<"\n";
			operate.find("cycle")->second = (dram_cy1 + col_access_delay);
			dram_cy1 = -1;
		}else if(inii1==3)
		{
			cout<<"cycle : "<<dram_cy1+1<<"-"<<dram_cy1+row_access_delay<<"\n";
			cout<<"DRAM: Writeback row "<<curr_row<<"\n";
			cout<<"\n";
			cout<<"cycle : "<<dram_cy1+1+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay<<"\n";
			cout<<"DRAM: Active row "<<mem_adr1/1024<<"\n";
			cout<<"\n";
			cout<<"cycle : "<<dram_cy1+1+row_access_delay+row_access_delay<<"-"<<dram_cy1+row_access_delay+row_access_delay+col_access_delay<<"\n";
			cout<<"DRAM: Column request "<<"\n";
			cout<<"Modified registers: "<<dra1<<" = " <<registers.find(dra1)->second<<"\n";
			cout<<"\n";
			curr_row = mem_adr1/1024;
			operate.find("cycle")->second =(dram_cy1+row_access_delay+row_access_delay+col_access_delay);
			dram_cy1 = -1;
		}
		else{
			cout<<"Wrong input\n";
		}
	}
	if(dm==0)
	{
		cout<<"\n";
		cout<<"Memory content at the end of the execution:\n";
		cout<<"\n";
		for(opr = mem_cnt.begin();opr!=mem_cnt.end();opr++)
		{
			cout<<opr->first<<":"<<opr->second<<"\n";
		}
		cout<<"\n";
		cout<<"Total execution time in clock cycle : "<<operate.find("cycle")->second<<"\n";
		cout<<"\n";		
		cout<<"No of row buffer updates : "<<row_buffer_updates<<"\n";
	}
	return 0;
}