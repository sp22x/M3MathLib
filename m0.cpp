#include <string>
#include <map>
#include <utility>
#include <iostream>
#include <vector>
#include <cmath>

class m0_var
{
public:
	std::string a;
	double coff;
	double pwr;

	m0_var(std::string pa="a",double pcoff=1,double ppwr=1)
	{
		a = pa;
		coff = pcoff;
		pwr = ppwr;
	}

	double subs(double val)
	{
		return pow(val,pwr)*coff;
	}

	std::string disp(void)
	{
		std::string tmp = std::to_string(coff)+"*"+a+"^"+std::to_string(pwr);
		return tmp;
	}
	void from_string(std::string peqn)
	{
		//a*x^n
		//scoff*sa^spwr
		std::string scoff = "1", spwr = "", sa = "";
		char flag = 'c';
		for(int i=0;i<peqn.length();i++)
		{
			if(peqn[i] == '*')
			{
				flag = 'a';
			}
			else if(peqn[i] == '^')
			{
				flag = 'p';
			}
			else
			{
				if(flag == 'c')
				{
					scoff += peqn[i];
				}
				else if(flag == 'a')
				{
					sa += peqn[i];
				}
				else
				{
					spwr += peqn[i];
				}
			}
		}
		a = sa;
		coff = std::stod(scoff);
		pwr = std::stod(spwr);
	}
};

class m0_hs
{
public:
	std::vector<m0_var> v;

	void from_string(std::string peqn)
	{
		v.clear();
		std::string tmp = "";
		int sgn = 1;
		//"a*x^m +-b*y^n +-..."
		for(int i=0;i<peqn.length();i++)
		{
			if(peqn[i] != ' ')
			{
				tmp+=peqn[i];
			}
			else
			{
				m0_var tv;
				tv.from_string(tmp);
				v.push_back(tv);
				tmp = "";				
			}
		}

	}

	std::vector<m0_var> resolve()
	{
		//optimize this
		std::map<std::pair<std::string,double>,double> reso;
		for(auto it = v.begin(); it!=v.end();++it)
		{
			auto tmp = *it;
			std::pair<std::string,double> tmp_pair = {tmp.a,tmp.pwr};
			reso[tmp_pair] += tmp.coff;			
		}

		std::vector<m0_var> rsv;
		for(auto it = reso.begin(); it!=reso.end(); ++it)
		{
			m0_var tmp(it->first.first,it->second,it->first.second);
			rsv.push_back(tmp);
		}
		return rsv;
	}

	std::string disp(void)
	{
		std::string tmp = "";
		for(auto it=v.begin();it!=v.end();++it)
		{
			auto vt = *it;
			tmp+=vt.disp() + " + ";	
		}
	}
};

class m0_eqn
{
public:
	std::string eqn;
	std::vector<m0_hs> v;
private:
	//placeholder
	bool eqn_chk(std::string peqn)
	{
		if(peqn.find("=") != std::string::npos)
		{
			return true;
		}
		return false;
	}
	std::vector<m0_hs> eqn_resolve()
	{
		//limited to two sided equation a=b for now
		std::string peqn = eqn, lhs = "", rhs = "";
		bool flag = true;
		for(int i=0;i<peqn.length();i++)
		{
			if(peqn[i] == '=')
			{
				flag = false;
			}
			if(flag)
			{
				lhs += peqn[i];
			}
			else
			{
				rhs += peqn[i];
			}
		}
		m0_hs lsq,rsq;
		lsq.from_string(lhs); 
		rsq.from_string(rhs);
		v.push_back(lsq);
		v.push_back(rsq);
		return v;		
	}
public:
	void from_string(std::string peqn)
	{
		if(eqn_chk(peqn))
		{
			eqn = peqn;
			eqn_resolve();
		}
		else
		{
			throw "Invalid equation";
		}
	}
	std::string disp(void)
	{
		std::string tmp = "";
		for(auto it=v.begin();it!=v.end();++it)
		{
			auto vt = *it;
			tmp+=vt.disp() + " = ";	
		}		
	}
};

int main()
{
	return 0;
}