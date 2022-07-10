#include <bits/stdc++.h>

using namespace std; 

int tot_mem[65536];

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
			hj.find(fg.at(0))->second+=1;
			t_0 = fg[1];
			t_1 = fg[2];
			t_2 = fg[3];
			if(f.find(t_0)!=dne && f.find(t_1)!=dne &&t_0!="$zero")
			{
				if(f.find(t_2)!=dne){
					f.find(t_0)->second =(f.find(t_1)->second + f.find(t_2)->second);
					show_register(f,r);
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
						show_register(f,r);
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
			hj.find(fg.at(0))->second+=1;
			t_0 = fg[1];
			t_1 = fg[2];
			t_2 = fg[3];
			if(f.find(t_0)!=dne && f.find(t_1)!=dne &&t_0!="$zero")
			{
				if(f.find(t_2)!=dne){
					f.find(t_0)->second =(f.find(t_1)->second - f.find(t_2)->second);
					show_register(f,r);
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
						show_register(f,r);
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
			hj.find(fg.at(0))->second+=1;
			t_0 = fg[1];
			t_1 = fg[2];
			t_2 = fg[3];
			if(f.find(t_0)!=dne && f.find(t_1)!=dne &&t_0!="$zero")
			{
				if(f.find(t_2)!=dne){
					f.find(t_0)->second =(f.find(t_1)->second * f.find(t_2)->second);
					show_register(f,r);
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
						show_register(f,r);
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
			hj.find(fg.at(0))->second+=1;
			t_0 = fg[1];
			t_1 = fg[2];
			t_2 = fg[3];
			if(f.find(t_0)!=dne && f.find(t_1)!=dne &&t_0!="$zero")
			{
				f.find(t_0)->second =(f.find(t_1)->second + stoi(t_2));
					//cout<<mn;
				show_register(f,r);
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
			hj.find(fg.at(0))->second+=1;
			t_0 = fg[1];
			t_1 = fg[2];
			t_2 = fg[3];
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
					show_register(f,r);
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
						show_register(f,r);
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
			hj.find(fg.at(0))->second+=1;
			t_0 = fg[1];
			if(g.find(t_0)!=g.end())
			{
				show_register(f,r);
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
			hj.find(fg.at(0))->second+=1;
			t_0 = fg[1];
			t_1 = fg[2];
			t_2 = fg[3];
			if(f.find(t_0)!=dne && g.find(t_2)!=g.end())
			{
				if(f.find(t_1)!=dne)
				{
					if(f.find(t_0)->second!=f.find(t_1)->second)
					{
						show_register(f,r);
						return g.find(t_2)->second;
					}
					else
					{
						show_register(f,r);
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
							show_register(f,r);
							return g.find(t_2)->second;
						}
						else
						{
							show_register(f,r);
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
			hj.find(fg.at(0))->second+=1;
			t_0 = fg[1];
			t_1 = fg[2];
			t_2 = fg[3];
			if(f.find(t_0)!=dne && g.find(t_2)!=g.end())
			{
				if(f.find(t_1)!=dne)
				{
					if(f.find(t_0)->second==f.find(t_1)->second)
					{
						show_register(f,r);
						return g.find(t_2)->second;
					}
					else
					{
						show_register(f,r);
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
							show_register(f,r);
							return g.find(t_2)->second;
						}
						else
						{
							show_register(f,r);
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
				if(zxc%4==0)
				{
					tot_mem[zxc/4] = f.find(t_0)->second;
					show_register(f,r);
					return mn;
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
	if(fg.at(0)=="lw")
	{
		if(fg.size()<3||fg.size()>3)
		{
			return 1000000;
		}
		else
		{
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
				if(zxc%4==0)
				{
					f.find(t_0)->second = tot_mem[zxc/4];
					show_register(f,r);
					return mn;
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
	vector<string> arr = {"add","sub","mul","beq","bne","slt","j","lw","sw","addi"}; 
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
	show_register(registers,reg);
	cout<<"--------------------------------------\n";
	cout<<"--------------------------------------\n";
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
				cout<<"--------------------------------------\n";
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
	if(dm==0)
	{
		int cycle = 0;
		for(int i=0;i<arr.size();i++)
		{
			cout<<"No of --" + arr.at(i) + "-- operation perform is: "<<operate.find(arr.at(i))->second<<"\n";
			cycle+=operate.find(arr.at(i))->second;
		}	
		cout<<"--------------------------------------\n";
		cout<<"Total no of --cycles-- perform in the execution is: "<<cycle<<"\n"; 
	}
	return 0;
}