#include<bits/stdc++.h>
using namespace std;
int exec(unsigned long long *M,short PC)
{
	unsigned long long AC=0,AR=0,MQ=0,MBR=0,IBR=0,IR=0,MAR=0;
	for(;pc<1000;pc++)
	{
		if(IBR==0)
		{
		}
		else
		{
			MAR=PC;
			MBR=*(M+MAR);
			IBR=(MBR)%((unsigned long long)1<<20);
			IR=MBR>>32;
			MAR=(MBR>>20)%((unsigned long long)1<<12);
			switch(IR)
			{
				case 0x00:
					return 0;
				break;
				case 0x01:
					AC=(*(M+MAR));
				break;
				case 0x02:
					AC=0-(*(M+MAR));
				break;
				case 0x03:
					AC=(*(M+MAR));
					AC=(AC>0)?AC:-AC;
				break;
				case 0x04:
					AC=(*(M+MAR));
					AC=(AC>0)?-AC:AC;
				break;
				case 0x05:
					AC+=(*(M+MAR));
				break;
				case 0x06:
					AC-=(*(M+MAR));
				break;
				case 0x07:
					AC+=((*(M+MAR))>0)?(*(M+MAR)):-(*(M+MAR));
				break;
				case 0x08:
					AC-=((*(M+MAR))>0)?(*(M+MAR)):-(*(M+MAR));
				break;
				case 0x09:
					AR=(*(M+MAR));
				break;
				case 0x0A:
					AC=AR;
				break;
				case 0x0b:
					unsigned long long ARR=AR%(1<<20);
					unsigned long long ARL=AR>>20;
					
					unsigned long long MR=(*(M+MAR))%(1<<20);
					unsigned long long ML=(*(M+MAR))>>20;
					
					unsigned long long ANS11=ML*ARL;
					unsigned long long ANS10=MR*ARL;
					unsigned long long ANS01=ML*ARR;
					unsigned long long ANS00=MR*ARR;
					
					int carry=0;
					unsigned long long temp=0;
					AR=ANS00;
					temp=AR;
					AR+=ANS01%(1<<20);
					if(temp>AR)
					{
						carry++;
					}
					temp=AR;
					AR+=ANS10%(1<<20);
					if(temp>AR)
					{
						carry++;
					}
					
					AC=carry;
					AC+=ANS11;
					AC+=ANS10>>20;
					AC+=ANS01>>20;
				break;
			}
		}
	}
}
int main
{
	unsigned long long Memory[1000];
	int running=1;
	while(running)
	{
		short memloc=0;
		string s;
		cin>>s;
		cout<<"Current memory location: "<<memloc<<endl;
		cout<<"Value at memory location: "<<Memory[memloc]<<endl;
		if(s=="INR")
		{
			memloc++;
		}
		else if(s=="DCR")
		{
			memloc--;
		}
		else if(s=="GO")
		{
			cin>>memloc;
		}
		else if(s=="SET")
		{
			cin>>Memory[mamloc];
		}
		else if(s=="EXEC")
		{
			exec(Memory,memloc);
		}
	}
	return 0;
}
