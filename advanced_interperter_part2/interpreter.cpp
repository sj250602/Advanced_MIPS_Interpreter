#include <bits/stdc++.h>

using namespace std; 

int tot_mem[1024][1024];

int row_buffer[1024];

int curr_row = -1,dram = 0,curr_dd = -1,dram1 = 0;

int row_access_delay = 0, col_access_delay = 0;

int row_buffer_updates = 0;

bool activ = false;

map<string,int> mem_cnt;

map<int,pair<int,int>> mem_adr;

map<int,pair<int,int>> cyc_reg;

map<int,pair<int,int>>::iterator oopprr;

map<int,string> map_index;

map<int,pair<string,string>> masa;

map<int,pair<string,string>>::iterator ooo;

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

pair<bool,int> findd(int a,map<int,pair<int,int>> map_){
	for(oopprr = map_.begin();oopprr!=map_.end();oopprr++){
		if(oopprr->second.first==a){
			return make_pair(true,oopprr->first);
		}
	}
	return make_pair(false,-1);
}

int shiww(int b,map<int,pair<int,int>> map__){
	int maxz = -1;
	for(oopprr = map__.begin();oopprr!=map__.end();oopprr++){
		if(oopprr->second.first==b){
			maxz = max(oopprr->first,maxz);
		}
	}
	return maxz;
}

bool isdependent(string st,string st1){
	for(ooo = masa.begin();ooo!=masa.end();ooo++){
		if(ooo->second.first=="lw"){
			if(ooo->second.second==st||ooo->second.second==st1){
				return true;
			}
		}
	}
	return false;
}

bool finnn(int bn,map<int,pair<int,int>> &nj){
	for(oopprr = nj.begin();oopprr!=nj.end();oopprr++){
		if(oopprr->second.second==bn){
			return true;
		}
	}
	return false;
}

void solve_sw(int cyc,map<string,int> &maapp){
	oopprr = cyc_reg.begin();
	while(oopprr!=cyc_reg.end()){
		int mass = oopprr->first;
		pair<int,int> aaaa = mem_adr.find(mass)->second;
		pair<int,int> arrr = cyc_reg.find(mass)->second;
		pair<string,string> piaar = masa.find(mass)->second;
		if(aaaa.second==1&&mass+row_access_delay+col_access_delay==cyc)
		{
			mem_adr.erase(mass);
			cyc_reg.erase(mass);
			cout<<"cycle : "<<mass+1<<"-"<<mass+row_access_delay<<"\n";
			cout<<"DRAM: Activate row "<<aaaa.first/1024<<"\n";
			cout<<"\n";
			if(piaar.first=="sw"){
				cout<<"cycle : "<<mass+1+row_access_delay<<"-"<<mass+row_access_delay+col_access_delay<<"\n";
				cout<<"DRAM: Column access "<<"\n"; 
				cout<<"Modified Memory Location: "<<aaaa.first<<" = " <<arrr.second<<"\n";
				cout<<"\n";
			}else{
				cout<<"cycle : "<<mass+1+row_access_delay<<"-"<<mass+row_access_delay+col_access_delay<<"\n";
				cout<<"DRAM: Column request "<<"\n"; 
				cout<<"Modified Registers : "<<piaar.second<<" = " <<arrr.second<<"\n";
				cout<<"\n";
			}
			int m = 2;
			for(oopprr = cyc_reg.begin();oopprr!=cyc_reg.end();oopprr++){
				if(oopprr->second.first==curr_row){
					pair<int,int> aaa = mem_adr.find(oopprr->first)->second;
					pair<int,int> arrrr = cyc_reg.find(oopprr->first)->second;
					pair<string,string> paia = masa.find(oopprr->first)->second;
					if(mass+1+row_access_delay>oopprr->first){
						if(paia.first=="sw"){
							cout<<"cycle : "<<mass+m+1+row_access_delay<<"-"<<mass+m+row_access_delay+col_access_delay<<"\n";
							cout<<"DRAM: Column access "<<"\n";
							cout<<"Modified Memory Location: "<<aaa.first<<" = " <<arrrr.second<<"\n";
							cout<<"\n";
						}else{
							cout<<"cycle : "<<mass+m+1+row_access_delay<<"-"<<mass+m+row_access_delay+col_access_delay<<"\n";
							cout<<"DRAM: Column request "<<"\n";
							cout<<"Modified Registers : "<<paia.second<<" = " <<arrrr.second<<"\n";
							cout<<"\n";
						}
					}else{
						if(paia.first=="sw"){	
							cout<<"cycle : "<<oopprr->first+1+m<<"-"<<oopprr->first+col_access_delay+m<<"\n";
							cout<<"DRAM: Column access "<<"\n";
							cout<<"Modified Memory Location: "<<aaa.first<<" = " <<arrrr.second<<"\n";
							cout<<"\n";
						}else{
							cout<<"cycle : "<<oopprr->first+1+m<<"-"<<oopprr->first+col_access_delay+m<<"\n";
							cout<<"DRAM: Column request "<<"\n";
							cout<<"Modified Registers : "<<paia.second<<" = " <<arrrr.second<<"\n";
							cout<<"\n";
						}
					}
					if(paia.first=="sw"){
						string str = to_string(aaa.first) + "-"+to_string(aaa.first+3);
						if(mem_cnt.find(str)!=mem_cnt.end())
						{
							mem_cnt.find(str)->second = arrrr.second;
						}
						else
						{
							mem_cnt.insert(pair<string,int>(str,arrrr.second));
						}
					}
					mem_adr.erase(oopprr->first);
					cyc_reg.erase(oopprr->first);
					masa.erase(oopprr->first);
					m+=2;
				}
				if(cyc_reg.size()==0){
					break;
				}
			}
			if(piaar.first=="sw"){
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
			masa.erase(mass);
			activ = true;
			m-=2;
			maapp.find("cycle")->second = max(maapp.find("cycle")->second,(mass+row_access_delay+col_access_delay+m));
			if(cyc_reg.size()==0){
				break;
			}
			oopprr = cyc_reg.begin();
		}else if(aaaa.second==2&&mass+(col_access_delay)==cyc){
			if(!finnn(1,mem_adr)){
				mem_adr.erase(mass);
				cyc_reg.erase(mass);
				if(piaar.first=="sw"){
					cout<<"cycle : "<<cyc-1<<"-"<<cyc<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<aaaa.first<<" = " <<arrr.second<<"\n";
					cout<<"\n";
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
					cout<<"cycle : "<<cyc-1<<"-"<<cyc<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified Registers : "<<piaar.second<<" = " <<arrr.second<<"\n";
					cout<<"\n";
				}
				masa.erase(mass);
				maapp.find("cycle")->second = cyc;
				if(cyc_reg.size()==0){
					break;
				}
				oopprr = cyc_reg.begin();
			}else{
				break;
			}
		}else if(aaaa.second==3&&mass+(2*row_access_delay)+col_access_delay==cyc)
		{
			mem_adr.erase(mass);
			cyc_reg.erase(mass);
			int mmmmmm = maapp.find("cycle")->second;
			cout<<"cycle : "<<mmmmmm+1<<"-"<<mmmmmm+row_access_delay<<"\n";
			cout<<"DRAM: Writeback row "<<curr_dd<<"\n";
			cout<<"\n";
			cout<<"cycle : "<<mmmmmm+row_access_delay+1<<"-"<<mmmmmm+(2*row_access_delay)<<"\n";
			cout<<"DRAM: Activate row "<<aaaa.first/1024<<"\n";
			cout<<"\n";
			if(piaar.first=="sw"){
				cout<<"cycle : "<<mmmmmm+(2*row_access_delay)+1<<"-"<<mmmmmm+col_access_delay+(2*row_access_delay)<<"\n";
				cout<<"DRAM: Column access "<<"\n";
				cout<<"Modified Memory Location: "<<aaaa.first<<" = " <<arrr.second<<"\n";
				cout<<"\n";
			}else{
				cout<<"cycle : "<<mmmmmm+(2*row_access_delay)+1<<"-"<<mmmmmm+col_access_delay+(2*row_access_delay)<<"\n";
				cout<<"DRAM: Column access "<<"\n";
				cout<<"Modified Memory Location: "<<piaar.second<<" = " <<arrr.second<<"\n";
				cout<<"\n";
			}
			int m = 2;
			int iii = 1;
			for(oopprr = cyc_reg.begin();oopprr!=cyc_reg.end();oopprr++){
				if(oopprr->second.first==aaaa.first/1024){
					pair<int,int> aaa = mem_adr.find(oopprr->first)->second;
					pair<int,int> arrrr = cyc_reg.find(oopprr->first)->second;
					pair<string,string> paia = masa.find(oopprr->first)->second;
					if(aaa.second==5){
						if(paia.first=="sw"){
							cout<<"cycle "<<": "<<mmmmmm+iii<<"\n";
							cout<<"Executed instruction: "<<"sw "<<map_index.find(oopprr->first)->second<<"\n";
							cout<<"DRAM Request issued: "<<"Memory Location: "<<mem_adr.find(oopprr->first)->second.first<<" "<<"Row buffer: "<<curr_row<<"\n";
							cout<<"\n";
						}else{
							cout<<"cycle "<<": "<<mmmmmm+iii<<"\n";
							cout<<"Executed instruction: "<<"lw "<<map_index.find(oopprr->first)->second<<"\n";
							cout<<"DRAM Request issued: "<<"Memory Location: "<<mem_adr.find(oopprr->first)->second.first<<" "<<"Row buffer: "<<curr_row<<"\n";
							cout<<"\n";
						}
						iii++;
					}
					if(mmmmmm+(2*row_access_delay)+1>oopprr->first){
						if(paia.first=="sw"){
							cout<<"cycle : "<<mmmmmm+(2*row_access_delay)+1+m<<"-"<<mmmmmm+col_access_delay+m+(2*row_access_delay)<<"\n";
							cout<<"DRAM: Column access "<<"\n";
							cout<<"Modified Memory Location: "<<aaa.first<<" = " <<arrrr.second<<"\n";
							cout<<"\n";
						}else{
							cout<<"cycle : "<<mmmmmm+(2*row_access_delay)+1+m<<"-"<<mmmmmm+col_access_delay+m+(2*row_access_delay)<<"\n";
							cout<<"DRAM: Column request "<<"\n";
							cout<<"Modified Registers : "<<paia.second<<" = " <<arrrr.second<<"\n";
							cout<<"\n";
						}
						m+=2;	
					}
					if(mmmmmm+(2*row_access_delay)+1<=oopprr->first){
						if(paia.first=="sw"){
							cout<<"cycle : "<<oopprr->first+1+m<<"-"<<oopprr->first+col_access_delay+m<<"\n";
							cout<<"DRAM: Column access "<<"\n";
							cout<<"Modified Memory Location: "<<aaa.first<<" = " <<arrrr.second<<"\n";
							cout<<"\n";
						}else{
							cout<<"cycle : "<<oopprr->first+1+m<<"-"<<oopprr->first+col_access_delay+m<<"\n";
							cout<<"DRAM: Column request "<<"\n";
							cout<<"Modified Registers : "<<paia.second<<" = " <<arrrr.second<<"\n";
							cout<<"\n";
						}
						m+=2;	
					}
					if(paia.first=="sw"){
						string str = to_string(aaa.first) + "-"+to_string(aaa.first+3);
						if(mem_cnt.find(str)!=mem_cnt.end())
						{
							mem_cnt.find(str)->second = arrrr.second;
						}
						else
						{
							mem_cnt.insert(pair<string,int>(str,arrrr.second));
						}
					}
					mem_adr.erase(oopprr->first);
					cyc_reg.erase(oopprr->first);
					masa.erase(oopprr->first);			
				}
				if(cyc_reg.size()==0){
					break;
				}
			}
			curr_row = aaaa.first/1024;
			curr_dd = aaaa.first/1024;
			if(piaar.first=="sw"){
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
			activ = true;
			masa.erase(mass);
			m-=2;
			maapp.find("cycle")->second = max(maapp.find("cycle")->second,(mmmmmm+row_access_delay+col_access_delay+m)); 
			if(cyc_reg.size()==0){
				break;
			}
			oopprr = cyc_reg.begin();
		}
		if(activ&&mem_adr.size()!=0&&map_index.find(mem_adr.begin()->first)!=map_index.end()){
			cout<<"cycle "<<": "<<maapp.find("cycle")->second+1<<"\n";
			if(masa.find(mem_adr.begin()->first)->second.first=="sw"){
				cout<<"Executed instruction: "<<"sw "<<map_index.find(mem_adr.begin()->first)->second<<"\n";
			}else{
				cout<<"Executed instruction: "<<"lw "<<map_index.find(mem_adr.begin()->first)->second<<"\n";
			}
			cout<<"DRAM Request issued: "<<"Memory Location: "<<mem_adr.begin()->second.first<<" "<<"Row buffer: "<<curr_row<<"\n";
			cout<<"\n";
			curr_row = cyc_reg.find(mem_adr.begin()->first)->second.first;
			activ = false;
			maapp.find("cycle")->second = maapp.find("cycle")->second+1;
		}else{
			oopprr++;
		}
	}
}

void solve_sw_lw(map<string,int> &maa){
	while(mem_adr.size()!=0){
		pair<int,int> aaaa = mem_adr.begin()->second;
		pair<int,int> arrr = cyc_reg.begin()->second;
		pair<string,string> piaar = masa.find(mem_adr.begin()->first)->second;
		int cy = mem_adr.begin()->first;
		if(aaaa.second==1)
		{
			mem_adr.erase(cy);
			cyc_reg.erase(cy);
			cout<<"cycle : "<<cy+1<<"-"<<cy+row_access_delay<<"\n";
			cout<<"DRAM: Activate row "<<aaaa.first/1024<<"\n";
			cout<<"\n";
			if(piaar.first=="sw"){
				cout<<"cycle : "<<cy+1+row_access_delay<<"-"<<cy+row_access_delay+col_access_delay<<"\n";
				cout<<"DRAM: Column access "<<"\n"; 
				cout<<"Modified Memory Location: "<<aaaa.first<<" = " <<arrr.second<<"\n";
				cout<<"\n";
			}else{
				cout<<"cycle : "<<cy+1+row_access_delay<<"-"<<cy+row_access_delay+col_access_delay<<"\n";
				cout<<"DRAM: Column request "<<"\n"; 
				cout<<"Modified Registers : "<<piaar.second<<" = " <<arrr.second<<"\n";
				cout<<"\n";
			}
			int m = 2;
			for(oopprr = cyc_reg.begin();oopprr!=cyc_reg.end();oopprr++){
				if(oopprr->second.first==curr_row){
					pair<int,int> aaa = mem_adr.find(oopprr->first)->second;
					pair<int,int> arrrr = cyc_reg.find(oopprr->first)->second;
					pair<string,string> paia = masa.find(oopprr->first)->second;
					if(cy+1+row_access_delay>oopprr->first){
						if(paia.first=="sw"){
							cout<<"cycle : "<<cy+1+row_access_delay+m<<"-"<<cy+row_access_delay+col_access_delay+m<<"\n";
							cout<<"DRAM: Column access "<<"\n"; 
							cout<<"Modified Memory Location: "<<aaa.first<<" = " <<arrrr.second<<"\n";
							cout<<"\n";
						}else{
							cout<<"cycle : "<<cy+1+row_access_delay+m<<"-"<<cy+row_access_delay+col_access_delay+m<<"\n";
							cout<<"DRAM: Column request "<<"\n"; 
							cout<<"Modified Registers : "<<paia.second<<" = " <<arrrr.second<<"\n";
							cout<<"\n";
						}
					}else{
						if(paia.first=="sw"){
							cout<<"cycle : "<<oopprr->first+1+m<<"-"<<oopprr->first+col_access_delay+m<<"\n";
							cout<<"DRAM: Column access "<<"\n"; 
							cout<<"Modified Memory Location: "<<aaa.first<<" = " <<arrrr.second<<"\n";
							cout<<"\n";
						}else{
							cout<<"cycle : "<<oopprr->first+1+m<<"-"<<oopprr->first+col_access_delay+m<<"\n";
							cout<<"DRAM: Column request "<<"\n"; 
							cout<<"Modified Registers : "<<paia.second<<" = " <<arrrr.second<<"\n";
							cout<<"\n";
						}
					}
					if(paia.first=="sw"){
						string str = to_string(aaa.first) + "-"+to_string(aaa.first+3);
						if(mem_cnt.find(str)!=mem_cnt.end())
						{
							mem_cnt.find(str)->second = arrrr.second;
						}
						else
						{
							mem_cnt.insert(pair<string,int>(str,arrrr.second));
						}
					} 
					mem_adr.erase(oopprr->first);
					cyc_reg.erase(oopprr->first);
					masa.erase(oopprr->first);
					m+=2;
				}
				if(cyc_reg.size()==0){
					break;
				}
			}
			if(piaar.first=="sw"){
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
			activ = true;
			masa.erase(cy);
			m-=2;
			maa.find("cycle")->second = max(maa.find("cycle")->second,(cy+row_access_delay+col_access_delay+m)); 
			if(cyc_reg.size()==0){
				break;
			}
		}else if(aaaa.second==2){
			mem_adr.erase(cy);
			cyc_reg.erase(cy);
			if(!finnn(1,cyc_reg)){
				if(piaar.first=="sw"){
					cout<<"cycle : "<<cy-1<<"-"<<cy<<"\n";
					cout<<"DRAM: Column access "<<"\n";
					cout<<"Modified Memory Location: "<<aaaa.first<<" = " <<arrr.second<<"\n";
					cout<<"\n";
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
					cout<<"cycle : "<<cy-1<<"-"<<cy<<"\n";
					cout<<"DRAM: Column request "<<"\n";
					cout<<"Modified Request: "<<piaar.second<<" = " <<arrr.second<<"\n";
					cout<<"\n";
				}
				masa.erase(cy);
				maa.find("cycle")->second = cy; 
				if(cyc_reg.size()==0){
					break;
				}else{
					activ = true;
				}
			}else{
				break;
			}
		}else if(aaaa.second==3)
		{
			mem_adr.erase(cy);
			cyc_reg.erase(cy);
			int mmmmmm = maa.find("cycle")->second;
			cout<<"cycle : "<<maa.find("cycle")->second+1<<"-"<<maa.find("cycle")->second+row_access_delay<<"\n";
			cout<<"DRAM: Writeback row "<<curr_dd<<"\n";
			cout<<"\n";
			cout<<"cycle : "<<maa.find("cycle")->second+row_access_delay+1<<"-"<<maa.find("cycle")->second+(2*row_access_delay)<<"\n";
			cout<<"DRAM: Activate row "<<aaaa.first/1024<<"\n";
			cout<<"\n";
			if(piaar.first=="sw"){
				cout<<"cycle : "<<maa.find("cycle")->second+(2*row_access_delay)+1<<"-"<<maa.find("cycle")->second+col_access_delay+(2*row_access_delay)<<"\n";
				cout<<"DRAM: Column access "<<"\n";
				cout<<"Modified Memory Location: "<<aaaa.first<<" = " <<arrr.second<<"\n";
				cout<<"\n";
			}else{
				cout<<"cycle : "<<maa.find("cycle")->second+(2*row_access_delay)+1<<"-"<<maa.find("cycle")->second+col_access_delay+(2*row_access_delay)<<"\n";
				cout<<"DRAM: Column request "<<"\n";
				cout<<"Modified Registers : "<<piaar.second<<" = " <<arrr.second<<"\n";
				cout<<"\n";
			}
			int m =2;
			int iii = 1;
			for(oopprr = cyc_reg.begin();oopprr!=cyc_reg.end();oopprr++){
				if(oopprr->second.first==curr_row){
					pair<int,int> aaa = mem_adr.find(oopprr->first)->second;
					pair<int,int> arrrr = cyc_reg.find(oopprr->first)->second;
					pair<string,string> paia = masa.find(oopprr->first)->second;
					if(aaa.second==5){
						if(paia.first=="sw"){
							cout<<"cycle "<<": "<<mmmmmm+iii<<"\n";
							cout<<"Executed instruction: "<<"sw "<<map_index.find(oopprr->first)->second<<"\n";
							cout<<"DRAM Request issued: "<<"Memory Location: "<<mem_adr.find(oopprr->first)->second.first<<" "<<"Row buffer: "<<curr_row<<"\n";
							cout<<"\n";
						}else{
							cout<<"cycle "<<": "<<mmmmmm+iii<<"\n";
							cout<<"Executed instruction: "<<"lw "<<map_index.find(oopprr->first)->second<<"\n";
							cout<<"DRAM Request issued: "<<"Memory Location: "<<mem_adr.find(oopprr->first)->second.first<<" "<<"Row buffer: "<<curr_row<<"\n";
							cout<<"\n";
						}
						iii++;
					}
					if(maa.find("cycle")->second+(2*row_access_delay)+1>oopprr->first){
						if(paia.first=="sw"){
							cout<<"cycle : "<<maa.find("cycle")->second+(2*row_access_delay)+1+m<<"-"<<maa.find("cycle")->second+col_access_delay+(2*row_access_delay)+m<<"\n";
							cout<<"DRAM: Column access "<<"\n";
							cout<<"Modified Memory Location: "<<aaa.first<<" = " <<arrrr.second<<"\n";
							cout<<"\n";
						}else{
							cout<<"cycle : "<<maa.find("cycle")->second+(2*row_access_delay)+1+m<<"-"<<maa.find("cycle")->second+col_access_delay+(2*row_access_delay)+m<<"\n";
							cout<<"DRAM: Column request "<<"\n";
							cout<<"Modified Registers : "<<paia.second<<" = " <<arrrr.second<<"\n";
							cout<<"\n";
						}
						m+=2;
					}
					if(maa.find("cycle")->second+(2*row_access_delay)+1<=oopprr->first){
						if(paia.first=="sw"){
							cout<<"cycle : "<<oopprr->first+1+m<<"-"<<oopprr->first+col_access_delay+m<<"\n";
							cout<<"DRAM: Column access "<<"\n";
							cout<<"Modified Memory Location: "<<aaa.first<<" = " <<arrrr.second<<"\n";
							cout<<"\n";
						}else{
							cout<<"cycle : "<<oopprr->first+1+m<<"-"<<oopprr->first+col_access_delay+m<<"\n";
							cout<<"DRAM: Column request "<<"\n";
							cout<<"Modified Registers : "<<paia.second<<" = " <<arrrr.second<<"\n";
							cout<<"\n";
						}
						m+=2;
					}
					if(paia.first=="sw"){
						string str = to_string(aaa.first) + "-"+to_string(aaa.first+3);
						if(mem_cnt.find(str)!=mem_cnt.end())
						{
							mem_cnt.find(str)->second = arrrr.second;
						}
						else
						{
							mem_cnt.insert(pair<string,int>(str,arrrr.second));
						}
					}
					mem_adr.erase(oopprr->first);
					cyc_reg.erase(oopprr->first);
					masa.erase(oopprr->first);
				}
				if(cyc_reg.size()==0){
					break;
				}
			}
			curr_row = aaaa.first/1024;
			curr_dd = aaaa.first/1024;
			if(piaar.first=="sw"){
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
			m-=2;
			maa.find("cycle")->second = max(maa.find("cycle")->second,(mmmmmm+col_access_delay+(2*row_access_delay)+m));
			activ = true;
			masa.erase(cy);
			if(cyc_reg.size()==0){
				break;
			}
		}
		if(activ&&mem_adr.size()!=0&&map_index.find(mem_adr.begin()->first)!=map_index.end()){
			cout<<"cycle "<<": "<<maa.find("cycle")->second+1<<"\n";
			curr_row = cyc_reg.find(mem_adr.begin()->first)->second.first;
			if(masa.find(mem_adr.begin()->first)->second.first=="sw"){
				cout<<"Executed instruction: "<<"sw "<<map_index.find(mem_adr.begin()->first)->second<<"\n";
			}else{
				cout<<"Executed instruction: "<<"lw "<<map_index.find(mem_adr.begin()->first)->second<<"\n";
			}
			cout<<"DRAM Request issued: "<<"Memory Location: "<<mem_adr.begin()->second.first<<" "<<"Row buffer: "<<curr_row<<"\n";
			cout<<"\n";
			maa.find("cycle")->second = maa.find("cycle")->second+1;
			activ = false;
		}
	}
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
			if(isdependent(t_1,t_2)){
				solve_sw_lw(hj);
			}else{
				solve_sw(hj.find("cycle")->second,hj);
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
			if(isdependent(t_1,t_2)){
				solve_sw_lw(hj);
			}else{
				solve_sw(hj.find("cycle")->second,hj);
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
			if(isdependent(t_1,t_2)){
				solve_sw_lw(hj);
			}else{
				solve_sw(hj.find("cycle")->second,hj);
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
			if(isdependent(t_1,t_2)){
				solve_sw_lw(hj);
			}else{
				solve_sw(hj.find("cycle")->second,hj);
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
			if(isdependent(t_1,t_2)){
				solve_sw_lw(hj);
			}else{
				solve_sw(hj.find("cycle")->second,hj);
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
			t_0 = fg[1];
			if(isdependent(t_0,t_0)){
				solve_sw_lw(hj);
			}else{
				solve_sw(hj.find("cycle")->second,hj);
			}
			hj.find("cycle")->second+=1;
			hj.find(fg.at(0))->second+=1;
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
			if(isdependent(t_0,t_1)){
				solve_sw_lw(hj);
			}else{
				solve_sw(hj.find("cycle")->second,hj);
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
			if(isdependent(t_0,t_1)){
				solve_sw_lw(hj);
			}else{
				solve_sw(hj.find("cycle")->second,hj);
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
			if(isdependent(t_0,t_0)){
				solve_sw_lw(hj);
			}else{
				solve_sw(hj.find("cycle")->second,hj);
			}
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
				if(curr_row<0)
				{
					hj.find("cycle")->second+=1;
					row_buffer_updates+=2;
					tot_mem[zxc/1024][zxc%1024] = f.find(t_0)->second;
					for(int q=0; q<1024; q++){
                       row_buffer[q] = tot_mem[zxc/1024][q];
                    }
					cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
					cout<<"Executed instruction: "<<"sw "<<t_0<<" "<<t_1<<"\n";
					cout<<"DRAM Request issued: "<<"Memory Location: "<<zxc<<" "<<"Row buffer: "<<curr_row<<"\n";
					cout<<"\n";
					curr_row = zxc/1024;
					curr_dd = zxc/1024;
					pair<int,int> ppp = make_pair(zxc,1);
					mem_adr.insert(pair<int,pair<int,int>>(hj.find("cycle")->second,ppp));
					pair<int,int> ppp1 = make_pair(curr_row,f.find(t_0)->second);
					cyc_reg.insert(pair<int,pair<int,int>>(hj.find("cycle")->second,ppp1));
					dram += hj.find("cycle")->second+row_access_delay+col_access_delay+1;
					pair<string,string> ppp11 = make_pair("sw",t_0);
					masa.insert(pair<int,pair<string,string>>(hj.find("cycle")->second,ppp11));
					return mn;
				}else if(curr_row == zxc/1024)
				{
					hj.find("cycle")->second+=1;
					row_buffer_updates++;
					tot_mem[zxc/1024][zxc%1024] = f.find(t_0)->second;
					for(int q=0; q<1024; q++){
						row_buffer[q] = tot_mem[zxc/1024][q];
                    }
					cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
					cout<<"Executed instruction: "<<"sw "<<t_0<<" "<<t_1<<"\n";
					cout<<"DRAM Request issued: "<<"Memory Location: "<<zxc<<" "<<"Row buffer: "<<curr_row<<"\n";
					cout<<"\n";
					pair<int,int> ppp = make_pair(zxc,2);
					mem_adr.insert(pair<int,pair<int,int>>(hj.find("cycle")->second,ppp));
					pair<int,int> ppp1 = make_pair(curr_row,f.find(t_0)->second);
					cyc_reg.insert(pair<int,pair<int,int>>(hj.find("cycle")->second,ppp1));
					pair<string,string> ppp11 = make_pair("sw",t_0);
					masa.insert(pair<int,pair<string,string>>(hj.find("cycle")->second,ppp11));
					return mn;
				}
				else{
					pair<bool,int> pai_ = findd(zxc/1024,cyc_reg);
					if(pai_.first)
					{
						row_buffer_updates++;
						tot_mem[zxc/1024][zxc%1024] = f.find(t_0)->second;
						for(int q=0; q<1024; q++){
							row_buffer[q] = tot_mem[zxc/1024][q];
						}
						string bb = t_0;
						bb+=" ";
						bb+=t_1;
						int maxii = shiww(zxc/1024,cyc_reg);
						pair<int,int> ppp = make_pair(zxc,5);
						mem_adr.insert(pair<int,pair<int,int>>(maxii+1,ppp));
						pair<int,int> ppp1 = make_pair(zxc/1024,f.find(t_0)->second);
						cyc_reg.insert(pair<int,pair<int,int>>(maxii+1,ppp1));
						map_index.insert(pair<int,string>(maxii+1,bb));
						pair<string,string> ppp11 = make_pair("sw",t_0);
						masa.insert(pair<int,pair<string,string>>(maxii+1,ppp11));
						return mn;
					}else{
						row_buffer_updates+=3;
						tot_mem[zxc/1024][zxc%1024] = f.find(t_0)->second;
						for(int q=0; q<1024; q++){
							row_buffer[q] = tot_mem[zxc/1024][q];
						}
						int m = max(dram,hj.find("cycle")->second+1);
						if(mem_adr.size()==0){
							hj.find("cycle")->second+=1;
							cout<<"cycle "<<": "<<m<<"\n";
							cout<<"Executed instruction: "<<"sw "<<t_0<<" "<<t_1<<"\n";
							cout<<"DRAM Request issued: "<<"Memory Location: "<<zxc<<" "<<"Row buffer: "<<curr_row<<"\n";
							cout<<"\n";
							curr_row = zxc/1024;
						}
						string bb = t_0;
						bb+=" ";
						bb+=t_1;
						pair<int,int> ppp = make_pair(zxc,3);
						mem_adr.insert(pair<int,pair<int,int>>(m,ppp));
						pair<int,int> ppp1 = make_pair(zxc/1024,f.find(t_0)->second);
						cyc_reg.insert(pair<int,pair<int,int>>(m,ppp1));
						dram = m+(2*row_access_delay)+col_access_delay+1;
						map_index.insert(pair<int,string>(m,bb));
						pair<string,string> ppp11 = make_pair("sw",t_0);
						masa.insert(pair<int,pair<string,string>>(m,ppp11));
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
			if(isdependent(t_0,t_0)){
				solve_sw_lw(hj);
			}else{
				solve_sw(hj.find("cycle")->second,hj);
			}
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
				if(curr_row<0)
				{
					hj.find("cycle")->second+=1;
					row_buffer_updates++;
					f.find(t_0)->second = tot_mem[zxc/1024][zxc%1024];
					for(int q=0; q<1024; q++){
                       row_buffer[q] = tot_mem[zxc/1024][q];
                    }
					cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
					cout<<"Executed instruction: "<<"lw "<<t_0<<" "<<t_1<<"\n";
					cout<<"DRAM Request issued: "<<"Memory Location: "<<zxc<<" "<<"Row buffer: "<<curr_row<<"\n";
					cout<<"\n";
					curr_row = zxc/1024;
					curr_dd = zxc/1024;
					pair<int,int> ppp = make_pair(zxc,1);
					mem_adr.insert(pair<int,pair<int,int>>(hj.find("cycle")->second,ppp));
					pair<int,int> ppp1 = make_pair(curr_row,f.find(t_0)->second);
					cyc_reg.insert(pair<int,pair<int,int>>(hj.find("cycle")->second,ppp1));
					dram += hj.find("cycle")->second+row_access_delay+col_access_delay+1;
					pair<string,string>ppp11 = make_pair("lw",t_0);
					masa.insert(pair<int,pair<string,string>>(hj.find("cycle")->second,ppp11));
					return mn;
				}else if(curr_row == zxc/1024)
				{
					hj.find("cycle")->second+=1;
					f.find(t_0)->second = tot_mem[zxc/1024][zxc%1024];
					for(int q=0; q<1024; q++){
						row_buffer[q] = tot_mem[zxc/1024][q];
                    }
					cout<<"cycle "<<": "<<hj.find("cycle")->second<<"\n";
					cout<<"Executed instruction: "<<"lw "<<t_0<<" "<<t_1<<"\n";
					cout<<"DRAM Request issued: "<<"Memory Location: "<<zxc<<" "<<"Row buffer: "<<curr_row<<"\n";
					cout<<"\n";
					pair<int,int> ppp = make_pair(zxc,2);
					mem_adr.insert(pair<int,pair<int,int>>(hj.find("cycle")->second,ppp));
					pair<int,int> ppp1 = make_pair(curr_row,f.find(t_0)->second);
					cyc_reg.insert(pair<int,pair<int,int>>(hj.find("cycle")->second,ppp1));
					pair<string,string>ppp11 = make_pair("lw",t_0);
					masa.insert(pair<int,pair<string,string>>(hj.find("cycle")->second,ppp11));
					return mn;
				}
				else{
					pair<bool,int> pai_ = findd(zxc/1024,cyc_reg);
					if(pai_.first)
					{
						f.find(t_0)->second = tot_mem[zxc/1024][zxc%1024];
						for(int q=0; q<1024; q++){
							row_buffer[q] = tot_mem[zxc/1024][q];
						}
						string bb = t_0;
						bb+=" ";
						bb+=t_1;
						int maxii = shiww(zxc/1024,cyc_reg);
						pair<int,int> ppp = make_pair(zxc,5);
						mem_adr.insert(pair<int,pair<int,int>>(maxii+1,ppp));
						pair<int,int> ppp1 = make_pair(zxc/1024,f.find(t_0)->second);
						cyc_reg.insert(pair<int,pair<int,int>>(maxii+1,ppp1));
						map_index.insert(pair<int,string>(maxii+1,bb));
						pair<string,string>ppp11 = make_pair("lw",t_0);
						masa.insert(pair<int,pair<string,string>>(maxii+1,ppp11));
						return mn;
					}else{
						row_buffer_updates+=2;
						f.find(t_0)->second = tot_mem[zxc/1024][zxc%1024];
						for(int q=0; q<1024; q++){
							row_buffer[q] = tot_mem[zxc/1024][q];
						}
						int m = max(dram,hj.find("cycle")->second+1);
						if(mem_adr.size()==0){
							hj.find("cycle")->second+=1;
							cout<<"cycle "<<": "<<m<<"\n";
							cout<<"Executed instruction: "<<"lw "<<t_0<<" "<<t_1<<"\n";
							cout<<"DRAM Request issued: "<<"Memory Location: "<<zxc<<" "<<"Row buffer: "<<curr_row<<"\n";
							cout<<"\n";
							curr_row = zxc/1024;
						}
						string bb = t_0;
						bb+=" ";
						bb+=t_1;
						pair<int,int> ppp = make_pair(zxc,3);
						mem_adr.insert(pair<int,pair<int,int>>(m,ppp));
						pair<int,int> ppp1 = make_pair(zxc/1024,f.find(t_0)->second);
						cyc_reg.insert(pair<int,pair<int,int>>(m,ppp1));
						dram = m+(2*row_access_delay)+col_access_delay+1;
						map_index.insert(pair<int,string>(m,bb));
						pair<string,string>ppp11 = make_pair("lw",t_0);
						masa.insert(pair<int,pair<string,string>>(m,ppp11));
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
	solve_sw_lw(operate);
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