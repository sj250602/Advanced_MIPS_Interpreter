#include <bits/stdc++.h>

using namespace std; 

int tot_mem[1024][1024];

int cpu_core,sim;

int curr_row = -1,dram = 0,dram1 = 0,throughput = 0;

int row_access_delay = 0, col_access_delay = 0;

int row_buffer_updates = 0;

map<string,int> mem_cnt;

map<int,pair<int,int>> mem_adr;

int queue_len,queue_len_1 = 0 ;

map<int,pair<int,int>> cyc_reg;

map<int,bool> new_map;

map<string,int> hari;

map<int,pair<int,int>>::iterator oopprr;

map<int,string> map_index;

map<int,pair<string,string>> masa;

map<int,pair<string,string>>::iterator ooo;

pair<bool,int> findd(int a,map<int,pair<int,int>> map_){
	for(oopprr = map_.begin();oopprr!=map_.end();oopprr++){
		if(oopprr->second.first==a){
			return make_pair(true,oopprr->first);
		}
	}
	return make_pair(false,-1);
}

void remove(int tv){
	vector<int> mm;
	for(oopprr = cyc_reg.begin();oopprr!=cyc_reg.end();oopprr++){
		if(oopprr->second.first==tv){
			mm.push_back(oopprr->first);
		}
	}
	for(int i=0;i<mm.size();i++){
		cyc_reg.erase(mm.at(i));
		masa.erase(mm.at(i));
		mem_adr.erase(mm.at(i));
		map_index.erase(mm.at(i));
	}
}

pair<bool,int> isdependent(string st,string st1){
	for(ooo = masa.begin();ooo!=masa.end();ooo++){
		if(ooo->second.first=="lw"){
			if(ooo->second.second==st||ooo->second.second==st1){
				return make_pair(true,cyc_reg.find(ooo->first)->second.first);
			}
		}
	}
	return make_pair(false,0);
}

bool finnn(int bn,map<int,pair<int,int>> &nj){
	for(oopprr = nj.begin();oopprr!=nj.end();oopprr++){
		if(oopprr->second.second==bn){
			return true;
		}
	}
	return false;
}

void solve_indep(int vb,map<string,int> &nm){
	oopprr = cyc_reg.begin();
	vector<int> vcc;
	while(oopprr!=cyc_reg.end()&&dram<=sim){
		int mass = oopprr->first;
		pair<int,int> aaaa = mem_adr.find(mass)->second;
		pair<int,int> arrr = cyc_reg.find(mass)->second;
		pair<string,string> piaar = masa.find(mass)->second;
		if(vb==arrr.first){
			if(aaaa.second==3){
				if(piaar.first=="sw"){
					dram+=1;
					if(dram<=sim){
						cout<<"cycle "<<": "<<dram<<"\n";
						cout<<"Executed instruction: "<<"sw "<<map_index.find(mass)->second<<"\n";
						cout<<"Memory Request Manager\n";
						cout<<"\n";
						nm.find("cycle")->second = dram;
					}
					dram+=row_access_delay ;
					if(dram<=sim){
						cout<<"cycle : "<<dram-row_access_delay+1<<"-"<<dram<<"\n";
						cout<<"DRAM: Writeback row "<<curr_row<<"\n";
						cout<<"\n";
						nm.find("cycle")->second = dram;
					}
					dram+=row_access_delay ;
					if(dram<=sim){
						cout<<"cycle : "<<dram-row_access_delay+1<<"-"<<dram<<"\n";
						cout<<"DRAM: Activate row "<<arrr.first<<"\n";
						cout<<"\n";
						nm.find("cycle")->second = dram;
					}
					dram+=col_access_delay ;
					curr_row = arrr.first;
					if(dram<=sim){
						cout<<"cycle : "<<dram-col_access_delay+1<<"-"<<dram<<"\n";
						cout<<"DRAM: Column access "<<"\n";
						cout<<"Modified Memory Location: "<<aaaa.first<<" = " <<arrr.second<<"\n";
						cout<<"\n";
						throughput++;
						nm.find("cycle")->second = dram;
						string str = to_string(aaaa.first) + "-"+to_string(aaaa.first+3);
						if(mem_cnt.find(str)!=mem_cnt.end())
						{
							mem_cnt.find(str)->second = arrr.second;
						}
						else
						{
							mem_cnt.insert(pair<string,int>(str,arrr.second));
						}
					}
				}
				if(piaar.first=="lw"){
					dram+=1;
					if(dram<=sim){
						cout<<"cycle "<<": "<<dram<<"\n";
						cout<<"Executed instruction: "<<"lw "<<map_index.find(mass)->second<<"\n";
						cout<<"Memory Request Manager\n";
						cout<<"\n";
						nm.find("cycle")->second = dram;
					}
					dram+=row_access_delay;
					if(dram<=sim){
						cout<<"cycle : "<<dram-row_access_delay+1<<"-"<<dram<<"\n";
						cout<<"DRAM: Writeback row "<<curr_row<<"\n";
						cout<<"\n";
						nm.find("cycle")->second = dram;
					}
					dram+=row_access_delay;
					if(dram<=sim){
						cout<<"cycle : "<<dram-row_access_delay+1<<"-"<<dram<<"\n";
						cout<<"DRAM: Activate row "<<arrr.first<<"\n";
						cout<<"\n";
						nm.find("cycle")->second = dram;
					}
					dram+=col_access_delay;
					curr_row = arrr.first;
					if(dram<=sim){
						cout<<"cycle : "<<dram-col_access_delay+1<<"-"<<dram<<"\n";
						cout<<"DRAM: Column request "<<"\n";
						cout<<"Modified Registers : "<<piaar.second<<" = " <<arrr.second<<"\n";
						cout<<"\n";
						throughput++;
						nm.find("cycle")->second = dram;
					}
				}
			}
			if(aaaa.second==5){
				if(piaar.first=="sw"){
					dram+=1;
					if(dram<=sim){
						cout<<"cycle "<<": "<<dram<<"\n";
						cout<<"Executed instruction: "<<"sw "<<map_index.find(mass)->second<<"\n";
						cout<<"Memory Request Manager\n";
						cout<<"\n";
						nm.find("cycle")->second = dram;
					}
					dram+=col_access_delay;
					if(dram<=sim){
						cout<<"cycle : "<<dram-col_access_delay+1<<"-"<<dram<<"\n";
						cout<<"DRAM: Column access "<<"\n";
						cout<<"Modified Memory Location: "<<aaaa.first<<" = " <<arrr.second<<"\n";
						cout<<"\n";
						throughput++;
						nm.find("cycle")->second = dram;
						string str = to_string(aaaa.first) + "-"+to_string(aaaa.first+3);
						if(mem_cnt.find(str)!=mem_cnt.end())
						{
							mem_cnt.find(str)->second = arrr.second;
						}
						else
						{
							mem_cnt.insert(pair<string,int>(str,arrr.second));
						}
					}
				}
				if(piaar.first=="lw"){
					dram+=1;
					if(dram<=sim){
						cout<<"cycle "<<": "<<dram<<"\n";
						cout<<"Executed instruction: "<<"lw "<<map_index.find(mass)->second<<"\n";
						cout<<"Memory Request Manager\n";
						cout<<"\n";
						nm.find("cycle")->second = dram;
					}
					dram+=col_access_delay;
					if(dram<=sim){
						cout<<"cycle : "<<dram-col_access_delay+1<<"-"<<dram<<"\n";
						cout<<"DRAM: Column request "<<"\n";
						cout<<"Modified Registers : "<<piaar.second<<" = " <<arrr.second<<"\n";
						cout<<"\n";
						throughput++;
						nm.find("cycle")->second = dram;
					}
				}
			}
			vcc.push_back(mass);
		}
		if(cyc_reg.size()==0){
			break;
		}
		oopprr++;
	}
	for(int i=0;i<vcc.size();i++){
		cyc_reg.erase(vcc.at(i));
		masa.erase(vcc.at(i));
		mem_adr.erase(vcc.at(i));
		map_index.erase(vcc.at(i));
	}
}

void printall(int tb,map<string,int> &bnm){
	for(oopprr = cyc_reg.begin();oopprr!=cyc_reg.end();oopprr++){
		int kris = oopprr->first;
		pair<int,int> sonu = mem_adr.find(kris)->second;
		pair<int,int> yash = cyc_reg.find(kris)->second;
		pair<string,string> shub = masa.find(kris)->second;
		if(tb==yash.first){
			if(shub.first=="sw"){
				dram+=1;
				if(dram<=sim){
					cout<<"cycle "<<": "<<dram<<"\n";
					cout<<"Executed instruction: "<<"sw "<<map_index.find(kris)->second<<"\n";
					cout<<"Memory Request Manager\n";
					cout<<"\n";
					bnm.find("cycle")->second = dram;
				}else{
					break;
				}
				dram+=col_access_delay;
				if(dram<=sim){
					cout<<"cycle : "<<dram-col_access_delay+1<<"-"<<dram<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<sonu.first<<" = " <<yash.second<<"\n";
					cout<<"\n";
					throughput++;
					bnm.find("cycle")->second = dram;
					string str = to_string(sonu.first) + "-"+to_string(sonu.first+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = yash.second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,yash.second));
					}
				}else{
					break;
				}
			}
			if(shub.first=="lw"){
				dram+=1;
				if(dram<=sim){
					cout<<"cycle "<<": "<<dram<<"\n";
					cout<<"Executed instruction: "<<"lw "<<map_index.find(kris)->second<<"\n";
					cout<<"Memory Request Manager\n";
					cout<<"\n";
					bnm.find("cycle")->second = dram;
				}else{
					break;
				}
				dram+=col_access_delay;
				if(dram<=sim){
					cout<<"cycle : "<<dram-col_access_delay+1<<"-"<<dram<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified Registers : "<<shub.second<<" = " <<yash.second<<"\n";
					cout<<"\n";
					throughput++;
					bnm.find("cycle")->second = dram;
				}else{
					break;
				}
			}
		}
	}
}

void final_done(map<string,int> &jats){
	while(mem_adr.size()!=0&&dram<=sim){
		pair<int,int> aaaa = mem_adr.begin()->second;
		pair<int,int> arrr = cyc_reg.begin()->second;
		pair<string,string> piaar = masa.find(mem_adr.begin()->first)->second;
		int mass = mem_adr.begin()->first;
		if(aaaa.second==3){
			int roww = arrr.first;
			if(piaar.first=="sw"){
				if(!new_map.at(mass)){
					dram+=1;
					if(dram<=sim){	
						cout<<"cycle "<<": "<<dram<<"\n";
						cout<<"Executed instruction: "<<"sw "<<map_index.find(mass)->second<<"\n";
						cout<<"Memory Request Manager\n";
						cout<<"\n";;
						jats.find("cycle")->second = dram;
					}else{
						break;
					}
				}
				dram+=row_access_delay ;
				if(dram<=sim){
					cout<<"cycle : "<<dram-row_access_delay+1<<"-"<<dram<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					jats.find("cycle")->second = dram;
				}else{
					break;
				}
				dram+=row_access_delay ;
				if(dram<=sim){
					cout<<"cycle : "<<dram-row_access_delay+1<<"-"<<dram<<"\n";
					cout<<"DRAM: Activate row "<<arrr.first<<"\n";
					cout<<"\n";
					jats.find("cycle")->second = dram;
				}else{
					break;
				}
				dram+=col_access_delay ;
				curr_row = arrr.first;
				if(dram<=sim){
					cout<<"cycle : "<<dram-col_access_delay+1<<"-"<<dram<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<aaaa.first<<" = " <<arrr.second<<"\n";
					cout<<"\n";
					throughput++;
					jats.find("cycle")->second = dram;
					string str = to_string(aaaa.first) + "-"+to_string(aaaa.first+3);
					if(mem_cnt.find(str)!=mem_cnt.end())
					{
						mem_cnt.find(str)->second = arrr.second;
					}
					else
					{
						mem_cnt.insert(pair<string,int>(str,arrr.second));
					}
				}else{
					break;
				}
			}
			if(piaar.first=="lw"){
				if(!new_map.at(mass)){
					dram+=1;
					if(dram<=sim){	
						cout<<"cycle "<<": "<<dram<<"\n";
						cout<<"Executed instruction: "<<"lw "<<map_index.find(mass)->second<<"\n";
						cout<<"Memory Request Manager\n";
						cout<<"\n";
						jats.find("cycle")->second = dram;
					}else{
						break;
					}
				}
				dram+=row_access_delay;
				if(dram<=sim){
					cout<<"cycle : "<<dram-row_access_delay+1<<"-"<<dram<<"\n";
					cout<<"DRAM: Writeback row "<<curr_row<<"\n";
					cout<<"\n";
					jats.find("cycle")->second = dram;
				}else{
					break;
				}
				dram+=row_access_delay;
				if(dram<=sim){
					cout<<"cycle : "<<dram-row_access_delay+1<<"-"<<dram<<"\n";
					cout<<"DRAM: Activate row "<<arrr.first<<"\n";
					cout<<"\n";
					jats.find("cycle")->second = dram;
				}else{
					break;
				}
				dram+=col_access_delay;
				curr_row = arrr.first;
				if(dram<=sim){
					cout<<"cycle : "<<dram-col_access_delay+1<<"-"<<dram<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified Registers : "<<piaar.second<<" = " <<arrr.second<<"\n";
					cout<<"\n";
					throughput++;
					jats.find("cycle")->second = dram;
				}else{
					break;
				}
			}
			cyc_reg.erase(mass);
			masa.erase(mass);
			mem_adr.erase(mass);
			map_index.erase(mass);
			printall(roww,jats);
			remove(roww);
		}
	}
}

int apply_oper(vector<string> &r,map<string,int> &f,map<string,int> &g,vector<string> &fg,map<string,int> &hj,int mn,int k)
{
	if(hari.find("sourav")!=hari.end()){
		hari.find("sourav")->second+=1;
	}else{
		hari.insert(pair<string,int>("sourav",1));
	}
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
			pair<bool,int> bhim = isdependent(t_1,t_2);
			if(bhim.first){
				solve_indep(bhim.second,hj);
			}
			if(hj.find("cycle")->second>=sim){
				return mn;
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
					throughput++;
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
						throughput++;
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
			pair<bool,int> bhim = isdependent(t_1,t_2);
			if(bhim.first){
				solve_indep(bhim.second,hj);
			}
			if(hj.find("cycle")->second>=sim){
				return mn;
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
					throughput++;
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
						throughput++;
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
			pair<bool,int> bhim = isdependent(t_1,t_2);
			if(bhim.first){
				solve_indep(bhim.second,hj);
			}
			if(hj.find("cycle")->second>=sim){
				return mn;
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
					throughput++;
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
						throughput++;
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
			pair<bool,int> bhim = isdependent(t_1,t_2);
			if(bhim.first){
				solve_indep(bhim.second,hj);
			}
			if(hj.find("cycle")->second>=sim){
				return mn;
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
				throughput++;
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
			pair<bool,int> bhim = isdependent(t_1,t_2);
			if(bhim.first){
				solve_indep(bhim.second,hj);
			}
			if(hj.find("cycle")->second>=sim){
				return mn;
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
					throughput++;
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
						throughput++;
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
			t_0 = fg[1];
			pair<bool,int> bhim = isdependent(t_0,t_0);
			if(bhim.first){
				solve_indep(bhim.second,hj);
			}
			if(hj.find("cycle")->second>=sim){
				return mn;
			}
			hj.find("cycle")->second+=1;
			hj.find(fg.at(0))->second+=1;
			if(g.find(t_0)!=g.end())
			{
				//show_register(f,r);
				cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
				cout<<"Executed instruction: "<<"j "<<t_0<<"\n";
				cout<<"\n";
				throughput++;
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
			pair<bool,int> bhim = isdependent(t_0,t_1);
			if(bhim.first){
				solve_indep(bhim.second,hj);
			}
			if(hj.find("cycle")->second>=sim){
				return mn;
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
						throughput++;
						return g.find(t_2)->second;
					}
					else
					{
						cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
						cout<<"Executed instruction: "<<"bne "<<t_0<<" "<<t_1<<" "<<t_2<<"\n";
						cout<<"\n";
						throughput++;
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
							throughput++;
							//show_register(f,r);
							return g.find(t_2)->second;
						}
						else
						{
							cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
							cout<<"Executed instruction: "<<"bne "<<t_0<<" "<<t_1<<" "<<t_2<<"\n";
							cout<<"\n";
							throughput++;
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
			pair<bool,int> bhim = isdependent(t_0,t_1);
			if(bhim.first){
				solve_indep(bhim.second,hj);
			}
			if(hj.find("cycle")->second>=sim){
				return mn;
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
						throughput++;
						//show_register(f,r);
						return g.find(t_2)->second;
					}
					else
					{
						cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
						cout<<"Executed instruction: "<<"beq "<<t_0<<" "<<t_1<<" "<<t_2<<"\n";
						cout<<"\n";
						throughput++;
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
							throughput++;
							//show_register(f,r);
							return g.find(t_2)->second;
						}
						else
						{
							cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
							cout<<"Executed instruction: "<<"beq "<<t_0<<" "<<t_1<<" "<<t_2<<"\n";
							cout<<"\n";
							throughput++;
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
			t_0 = fg[1];
			t_1 = fg[2];
			pair<bool,int> bhim = isdependent(t_0,t_0);
			if(bhim.first){
				solve_indep(bhim.second,hj);
			}
			if(hj.find("cycle")->second>=sim){
				return mn;
			}
			hj.find(fg.at(0))->second+=1;
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
				if(curr_row!=((1024/cpu_core*(k-1))+(zxc/1024))&&queue_len==queue_len_1){
					final_done(hj);
					queue_len_1 = 0;
				}
				if(curr_row<0)
				{
					dram1 = 1;
					hj.find("cycle")->second+=1;
					row_buffer_updates++;
					tot_mem[((1024/cpu_core)*(k-1))+(zxc/1024)][zxc%1024] = f.find(t_0)->second;
					cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
					cout<<"Executed instruction: "<<"sw "<<t_0<<" "<<t_1<<"\n";
					cout<<"Memory Request Manager"<<"\n";
					cout<<"\n";
					dram = hj.find("cycle")->second + row_access_delay;
					curr_row = ((1024/cpu_core)*(k-1))+(zxc/1024);
					if(dram<=sim){
						cout<<"cycle : "<<hj.find("cycle")->second+1<<"-"<<hj.find("cycle")->second+row_access_delay<<"\n";
						cout<<"DRAM: Activate row "<<curr_row<<"\n";
						cout<<"\n";
						dram+=col_access_delay;
						if(dram<=sim){
							cout<<"cycle : "<<hj.find("cycle")->second+1+row_access_delay<<"-"<<hj.find("cycle")->second+row_access_delay+col_access_delay<<"\n";
							cout<<"DRAM: Column access "<<"\n"; 
							cout<<"Modified Memory Location : "<<((1024/cpu_core)*(k-1))+(zxc)<<" = " <<f.find(t_0)->second<<"\n";
							cout<<"\n";
							throughput++;
							string str = to_string(((1024/cpu_core)*(k-1))+(zxc)) + "-"+to_string(((1024/cpu_core)*(k-1))+(zxc)+3);
							if(mem_cnt.find(str)!=mem_cnt.end())
							{
								mem_cnt.find(str)->second = f.find(t_0)->second;
							}
							else
							{
								mem_cnt.insert(pair<string,int>(str,f.find(t_0)->second));
							}
						}
					}
					return mn;
				}else if(curr_row == ((1024/cpu_core*(k-1))+(zxc/1024)))
				{
					dram1 = 1;
					tot_mem[((1024/cpu_core)*(k-1))+(zxc/1024)][zxc%1024] = f.find(t_0)->second;
					dram+=1;
					if(dram<=sim){
						cout<<"cycle "<<": "<<dram<<"\n";
						cout<<"Executed instruction: "<<"sw "<<t_0<<" "<<t_1<<"\n";
						cout<<"Memory Request Manager"<<"\n";
						cout<<"\n";
						dram = dram + col_access_delay ;
						if(dram<=sim){
							cout<<"cycle : "<<dram-col_access_delay+1<<"-"<<dram<<"\n";
							cout<<"DRAM: Column access "<<"\n"; 
							cout<<"Modified Memory Location : "<<((1024/cpu_core)*(k-1))+(zxc)<<" = " <<f.find(t_0)->second<<"\n";
							cout<<"\n";
							throughput++;
							string str = to_string(((1024/cpu_core)*(k-1))+(zxc)) + "-"+to_string(((1024/cpu_core)*(k-1))+(zxc)+3);
							if(mem_cnt.find(str)!=mem_cnt.end())
							{
								mem_cnt.find(str)->second = f.find(t_0)->second;
							}
							else
							{
								mem_cnt.insert(pair<string,int>(str,f.find(t_0)->second));
							}
						}
					}
					return mn;
				}
				else{
					pair<bool,int> pai_ = findd(((1024/cpu_core)*(k-1))+(zxc/1024),cyc_reg);
					if(pai_.first)
					{
						dram1 = 1;
						queue_len_1++;
						tot_mem[((1024/cpu_core)*(k-1))+(zxc/1024)][zxc%1024] = f.find(t_0)->second;
						string bb = t_0; bb+=" "; bb+=t_1;
						pair<int,int> ppp = make_pair(((1024/cpu_core)*(k-1))+(zxc),5);
						mem_adr.insert(pair<int,pair<int,int>>(hari.at("sourav"),ppp));
						pair<int,int> ppp1 = make_pair(((1024/cpu_core)*(k-1))+(zxc/1024),f.find(t_0)->second);
						cyc_reg.insert(pair<int,pair<int,int>>(hari.at("sourav"),ppp1));
						map_index.insert(pair<int,string>(hari.at("sourav"),bb));
						pair<string,string> ppp11 = make_pair("sw",t_0);
						masa.insert(pair<int,pair<string,string>>(hari.at("sourav"),ppp11));
						return mn;
					}else{
						int l = 0;
						if(dram1==0){
							hj.find("cycle")->second+=1;
							cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
							cout<<"Executed instruction: "<<"sw "<<t_0<<" "<<t_1<<"\n";
							cout<<"Memory Request Manager"<<"\n";
							cout<<"\n";
							dram1 = 1;
							l = 1;
							new_map.insert(pair<int,bool>(hari.at("sourav"),true));
						}
						if(l==0){
							new_map.insert(pair<int,bool>(hari.at("sourav"),false));
						}
						queue_len_1++;
						row_buffer_updates+=2;
						tot_mem[((1024/cpu_core)*(k-1))+(zxc/1024)][zxc%1024] = f.find(t_0)->second;
						string bb = t_0; bb+=" "; bb+=t_1;
						pair<int,int> ppp = make_pair(((1024/cpu_core)*(k-1))+(zxc),3);
						mem_adr.insert(pair<int,pair<int,int>>(hari.at("sourav"),ppp));
						pair<int,int> ppp1 = make_pair(((1024/cpu_core)*(k-1))+(zxc/1024),f.find(t_0)->second);
						cyc_reg.insert(pair<int,pair<int,int>>(hari.at("sourav"),ppp1));
						map_index.insert(pair<int,string>(hari.at("sourav"),bb));
						pair<string,string> ppp11 = make_pair("sw",t_0);
						masa.insert(pair<int,pair<string,string>>(hari.at("sourav"),ppp11));
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
	if(fg.at(0)=="lw")
	{
		if(fg.size()<3||fg.size()>3)
		{
			return 1000000;
		}
		else
		{
			t_0 = fg[1];
			t_1 = fg[2];
			pair<bool,int> bhim = isdependent(t_0,t_0);
			if(bhim.first){
				solve_indep(bhim.second,hj);
			}
			if(hj.find("cycle")->second>=sim){
				return mn;
			}
			hj.find(fg.at(0))->second+=1;
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
				if(curr_row!=((1024/cpu_core)*(k-1))+(zxc/1024)&&queue_len==queue_len_1){
					final_done(hj);
					queue_len_1 = 0;
				}
				if(curr_row<0)
				{
					dram1 = 1;
					hj.find("cycle")->second+=1;
					row_buffer_updates++;
					f.find(t_0)->second = tot_mem[((1024/cpu_core)*(k-1))+(zxc/1024)][zxc%1024];
					cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
					cout<<"Executed instruction: "<<"lw "<<t_0<<" "<<t_1<<"\n";
					cout<<"Memory Request Manager"<<"\n";
					cout<<"\n";
					curr_row = ((1024/cpu_core)*(k-1))+(zxc/1024);
					dram = hj.find("cycle")->second + row_access_delay;
					if(dram<=sim){
						cout<<"cycle : "<<hj.find("cycle")->second+1<<"-"<<hj.find("cycle")->second+row_access_delay<<"\n";
						cout<<"DRAM: Activate row "<<curr_row<<"\n";
						cout<<"\n";
						dram += col_access_delay;
						if(dram<=sim){
							cout<<"cycle : "<<hj.find("cycle")->second+1+row_access_delay<<"-"<<hj.find("cycle")->second+row_access_delay+col_access_delay<<"\n";
							cout<<"DRAM: Column request "<<"\n"; 
							cout<<"Modified Registers : "<<t_0<<" = " <<f.find(t_0)->second<<"\n";
							cout<<"\n";
							throughput++;
						}
					}
					return mn;
				}else if(curr_row == ((1024/cpu_core)*(k-1))+(zxc/1024))
				{
					dram1 = 1;
					f.find(t_0)->second = tot_mem[((1024/cpu_core)*(k-1))+(zxc/1024)][zxc%1024];
					dram+=1;
					if(dram<=sim){
						cout<<"cycle "<<": "<<dram<<"\n";
						cout<<"Executed instruction: "<<"lw "<<t_0<<" "<<t_1<<"\n";
						cout<<"Memory Request Manager"<<"\n";
						cout<<"\n";
						dram += col_access_delay ;
						if(dram<=sim){
							cout<<"cycle : "<<dram-col_access_delay+1<<"-"<<dram<<"\n";
							cout<<"DRAM: Column request "<<"\n"; 
							cout<<"Modified Registers : "<<t_0<<" = " <<f.find(t_0)->second<<"\n";
							cout<<"\n";
							throughput++;
						}
					}
					return mn;
				}
				else{
					pair<bool,int> pai_ = findd(((1024/cpu_core)*(k-1))+(zxc/1024),cyc_reg);
					if(pai_.first)
					{
						dram1 = 1;
						queue_len_1++;
						f.find(t_0)->second = tot_mem[((1024/cpu_core)*(k-1))+(zxc/1024)][zxc%1024];
						string bb = t_0; bb+=" "; bb+=t_1;
						pair<int,int> ppp = make_pair(((1024/cpu_core)*(k-1))+(zxc),5);
						mem_adr.insert(pair<int,pair<int,int>>(hari.at("sourav"),ppp));
						pair<int,int> ppp1 = make_pair(((1024/cpu_core)*(k-1))+(zxc/1024),f.find(t_0)->second);
						cyc_reg.insert(pair<int,pair<int,int>>(hari.at("sourav"),ppp1));
						map_index.insert(pair<int,string>(hari.at("sourav"),bb));
						pair<string,string>ppp11 = make_pair("lw",t_0);
						masa.insert(pair<int,pair<string,string>>(hari.at("sourav"),ppp11));
						return mn;
					}else{
						int l = 0;
						if(dram1==0){
							hj.find("cycle")->second+=1;
							cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
							cout<<"Executed instruction: "<<"lw "<<t_0<<" "<<t_1<<"\n";
							cout<<"Memory Request Manager"<<"\n";
							cout<<"\n";
							dram1 = 1;
							l = 1;
							new_map.insert(pair<int,bool>(hari.at("sourav"),true));
						}
						if(l==0){
							new_map.insert(pair<int,bool>(hari.at("sourav"),false));
						}
						queue_len_1++;
						row_buffer_updates+=2;
						f.find(t_0)->second = tot_mem[((1024/cpu_core)*(k-1))+(zxc/1024)][zxc%1024];
						string bb = t_0; bb+=" "; bb+=t_1;
						pair<int,int> ppp = make_pair(((1024/cpu_core)*(k-1))+(zxc),3);
						mem_adr.insert(pair<int,pair<int,int>>(hari.at("sourav"),ppp));
						pair<int,int> ppp1 = make_pair(((1024/cpu_core)*(k-1))+(zxc/1024),f.find(t_0)->second);
						cyc_reg.insert(pair<int,pair<int,int>>(hari.at("sourav"),ppp1));
						map_index.insert(pair<int,string>(hari.at("sourav"),bb));
						pair<string,string>ppp11 = make_pair("lw",t_0);
						masa.insert(pair<int,pair<string,string>>(hari.at("sourav"),ppp11));
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
	return 1000000;
}