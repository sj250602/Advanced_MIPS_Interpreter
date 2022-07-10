#include "helper.h"

void show_register(map<string,int> re,vector<string> vi)
{
	for(int i=0;i<vi.size();i++)
	{
		cout<<"		"<<vi.at(i)<<" = "<<hex<<re.find(vi.at(i))->second<<"\n";
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

bool remove_sw(vector<vector<string>> &vec,vector<string> &xx){
	int i = 0;
	vector<vector<string>>::iterator ii;
	for(ii = vec.begin();ii!=vec.end();ii++){
		if(*ii==xx){
			vec.erase(vec.begin()+i);
			return true;
		}
		i++;
	}
	return false;
}

bool remove_lw(vector<vector<string>> &vec1,vector<string> &xx1){
	int i = 0,d = 0,asd = -1;
	string hh;
	vector<vector<string>>::iterator ii;
	for(ii = vec1.begin();ii!=vec1.end();ii++){
		vector<string> sfg = *ii;
		if(d==1){
			if(sfg.size()==2&&hh==sfg.at(1)){
				return false;
			}else if(sfg.size()==3&&(hh==sfg.at(1)||hh==sfg.at(2))){
				return false;
			}else if(sfg.size()==4&&(hh==sfg.at(1)||hh==sfg.at(2)||hh==sfg.at(3))){
				return false;
			}
		}if(*ii==xx1){
			hh = xx1[1];
			d = 1; 
			asd = i;
		}
		i++;
	}
	if(d==1){
		vec1.erase(vec1.begin()+asd);
		return true;
	}
	return false;
}

int count_sw_lw(vector<vector<string>> &asdf){
	int mom = 0,dad = 0;
	while(mom<asdf.size()){
		if(asdf.at(mom).at(0)=="sw"||asdf.at(mom).at(0)=="lw"){
			dad++;
		}
		mom++;
	}
	return -1*dad;
}
	
int main()
{
	cout<<"Number of CPU cores: ";
	cin>>cpu_core;
	cout<<"Simulation Time: ";
	cin>>sim;
	vector<string> reg = {"$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra"};
	vector<string> arr = {"add","sub","mul","beq","bne","slt","j","lw","sw","addi","cycle"}; 
	map<string,int>operate;
	map<string,int>::iterator opr;
	for(int i=0;i<arr.size();i++){
		operate.insert(pair<string,int>(arr.at(i),0));
	}
	map<int,vector<vector<string>>> core;
	map<int,map<string,int>> cor_funct;
	for(int i=1;i<=cpu_core;i++){		
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
				//cout<<va<<"\n";
				//cout<<line<<"\n";
				if(faltu.size()==1)
				{
					vector<string> fa= split(faltu.at(0),':');
					funct.insert(pair<string,int>(fa.at(0),va));
				}
				if(faltu.size()!=0){
					if(faltu[0]=="sw"){
						bool b = remove_sw(file_line,faltu);
					}
					if(faltu[0]=="lw"){
						bool b = remove_lw(file_line,faltu);
					}
					file_line.push_back(faltu);
					va++;
				}			
			}
			file.close();
			cor_funct.insert(pair<int,map<string,int>>(i,funct));
			core.insert(pair<int,vector<vector<string>>>(i,file_line));
		}
		else
		{
			cout<<"No such file exist please check your give address\n";
			return 0;
		}
	}
	vector<pair<int,pair<int,int>>> jatin;
	for(int s=1;s<=cpu_core;s++){
		vector<vector<string>> file_line = core.at(s);
		int m = 0,k=0,dd = 0;
		pair<int,int> pap;
		while(m<file_line.size()){
			if(file_line.at(m).size()>1){
				k++;
			}
			if(file_line.at(m).at(0)=="sw"||file_line.at(m).at(0)=="lw"){
				pap = make_pair(k,s);
				dd =1;
				break;
			}
			m++;
		}
		int total_sw_lw = 0;
		if(dd==0){
			pap = make_pair(0,s);
		}else{
			total_sw_lw = count_sw_lw(file_line);
		}
		jatin.push_back(make_pair(total_sw_lw,pap));
	}
	sort(jatin.begin(),jatin.end());
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
	cout<<"Enter the queue length: ";
	cin>>queue_len;
	cout<<"\n";
	cout<<"Every cycle description\n";
	cout<<"\n";
	int dm =0;
	int l = 1;
	for(auto it = jatin.begin();it!=jatin.end();it++){
		int j = it->second.second;
		cout<<"***CORE"<<l<<":"<<"\n";
		cout<<"\n";
		vector<vector<string>> file_line = core.at(j);
		int i =0;
		operate.find("cycle")->second = 0;
		dram1 = 0;
		map<string,int> registers;
		for(int i=0;i<reg.size();i++)
		{
			registers.insert(pair<string,int>(reg.at(i),0));
		}
		while(i<file_line.size())
		{
			if(file_line.at(i).size()>1)
			{
				if(search(arr,file_line.at(i).at(0)))
				{
					//cout<<"----------"<<i<<"\n";
					i = apply_oper(reg,registers,cor_funct.at(j),file_line.at(i),operate,i,j);
					//cout<<"----------"<<i<<"\n";
					if(i==1000000)
					{
						dm =1;
						cout<<"Wrong Input"<<"\n";
						break;
					}
					if(operate.find("cycle")->second>=sim){
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
		final_done(operate);
		l++;
		cout<<"\n";
		cout<<"********Final content of registers********"<<"\n";
		show_register(registers,reg);
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
		cout<<"No of row buffer updates : "<<row_buffer_updates<<"\n";
		cout<<"\n";
		int y;
		stringstream stream;
		stream<<sim;
		stream>>hex>>y;
		cout<<"Total number of instructions completed by the whole system in "<<y<<" cycles  : "<<throughput<<"\n";
		cout<<"\n";
		cout<<"*****Your code is executed*****"<<"\n";
	}
	return 0;
}