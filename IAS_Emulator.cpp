#include<bits/stdc++.h>
using namespace std;
int exec(unsigned long long *M,short PC)
{
	unsigned long long AC=0,MQ=0,MBR=0,IBR=0,IR=0,MAR=0;
	for(;PC<1000;PC++)
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
			NextInstruction:;
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
					MQ=(*(M+MAR));
				break;
				case 0x0A:
					AC=MQ;
				break;
				case 0x0B:
				{
					unsigned long long MQR=MQ%(1<<20);
					unsigned long long MQL=MQ>>20;
					
					unsigned long long MR=(*(M+MAR))%(1<<20);
					unsigned long long ML=(*(M+MAR))>>20;
					
					unsigned long long ANS11=ML*MQL;
					unsigned long long ANS10=MR*MQL;
					unsigned long long ANS01=ML*MQR;
					unsigned long long ANS00=MR*MQR;
					
					int carry=0;
					unsigned long long temp=0;
					MQ=ANS00;
					temp=MQ;
					MQ+=ANS01%(1<<20);
					if(temp>MQ)
					{
						carry++;
					}
					temp=MQ;
					MQ+=ANS10%(1<<20);
					if(temp>MQ)
					{
						carry++;
					}
					
					AC=carry;
					AC+=ANS11;
					AC+=ANS10>>20;
					AC+=ANS01>>20;
				}
				break;
				case 0x0C:
				{
					unsigned long long quo=AC/(*(M+MAR)),rem=AC%(*(M+MAR));
					MQ=quo;
					AC=rem;
				}
				break;
				case 0x0D:
					IR=MBR>>32;
					MAR=(MBR>>20)%((unsigned long long)1<<12);
					goto NextInstruction;
				break;
				case 0x0E:
					IR=(MBR>>12)%((unsigned long long)1<<8);
					MAR=MBR%((unsigned long long)1<<12);
					goto NextInstruction;
				break;
				case 0x0F:
					if(AC>=0)
					{
						IR=MBR>>32;
						MAR=(MBR>>20)%((unsigned long long)1<<12);
						goto NextInstruction;
					}
				break;
				case 0x10:
					if(AC>=0)
					{
						IR=(MBR>>12)%((unsigned long long)1<<8);
						MAR=MBR%((unsigned long long)1<<12);
						goto NextInstruction;
					}
				break;
				case 0x11:
					(*(M+MAR))=AC;
				break;
				case 0x12:
				{
					unsigned long long temp=(*(M+MAR))%(1<<20);
					unsigned long long temp1=(*(M+MAR))>>32;
					*(M+MAR)=temp1<<32 + AC<<20 + temp;
				}
				break;
				case 0x13:
				{
					unsigned long long temp=(*(M+MAR))>>12;
					*(M+MAR)=temp<<12 + AC;
				}
				break;
				case 0x14:
					AC=AC>>1;
				break;
				case 0x15:
					AC=AC<<1;
				break;
			}
		}
	}
	return 0;
}
int main()
{
	unsigned long long Memory[1000];
	while(1)
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
			cin>>Memory[memloc];
		}
		else if(s=="EXEC")
		{
			exec(Memory,memloc);
		}
		else if(s=="EXIT")
		{
			break;
		}
	}
	return 0;
}
