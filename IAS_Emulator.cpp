#include<bits/stdc++.h>
using namespace std;
#define BASE40 1099511627776
#define BASE20 1048576
#define BASE12 4096
#define BASE8 256
int exec(long long *M,short PC)
{
	long long AC=0,MQ=0,MBR=0,IBR=0,IR=0,MAR=0;
	for(;PC<1000;PC++)
	{
		MAR=PC;
		MBR=*(M+MAR);
		char first=1;
		IBR=(MBR)%BASE20;
		IR=MBR>>32;
		MAR=(MBR>>20)%BASE12;
		NextInstruction:;
		MBR=(*(M+MAR));
		switch(IR)
		{
			case 0x00:
				cout<<"HLT\n";
				return 0;
			break;
			case 0x01:
				cout<<"LOAD M("<<MAR<<")\n";
				AC=MBR;
			break;
			case 0x02:
				cout<<"LOAD -M("<<MAR<<")\n";
				AC=0-MBR;
			break;
			case 0x03:
				cout<<"LOAD |M("<<MAR<<")|\n";
				AC=MBR;
				AC=(AC>0)?AC:-AC;
			break;
			case 0x04:
				cout<<"LOAD -|M("<<MAR<<")|\n";
				AC=MBR;
				AC=(AC>0)?-AC:AC;
			break;
			case 0x05:
				cout<<"ADD M("<<MAR<<")\n";
				AC+=MBR;
				AC%=BASE40;
				
			break;
			case 0x06:
				cout<<"SUB M("<<MAR<<")\n";
				AC-=MBR;
				AC%=BASE40;
			break;
			case 0x07:
				cout<<"ADD |M("<<MAR<<")|\n";
				AC+=(MBR>0)?MBR:0-MBR;
				AC%=BASE40;
			break;
			case 0x08:
				cout<<"SUB |M("<<MAR<<")|\n";
				AC-=(MBR>0)?MBR:0-MBR;
				AC%=BASE40;
			break;
			case 0x09:
				cout<<"LOAD MQ,M("<<MAR<<")\n";
				MQ=MBR;
			break;
			case 0x0A:
				cout<<"LOAD MQ\n";
				AC=MQ;
			break;
			case 0x0B:
			{
				cout<<"MUL M("<<MAR<<")\n";
				long long MQR=MQ % BASE20;
				long long MQL=MQ>>20;
				
				long long MR=MBR % BASE20;
				long long ML=MBR>>20;
				
				long long ANS11=ML*MQL;
				long long ANS10=MR*MQL;
				long long ANS01=ML*MQR;
				long long ANS00=MR*MQR;
				
				int carry=0;
				long long temp=0;
				MQ=ANS00;
				temp=MQ;
				MQ+=(ANS01 * BASE20) % BASE40;
				if(temp>MQ)
				{
					carry++;
				}
				temp=MQ;
				MQ+=(ANS10 * BASE20) % BASE40;
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
				cout<<"DIV M("<<MAR<<")\n";
				long long quo=AC/MBR,rem=AC%MBR;
				MQ=quo;
				AC=rem;
			}
			break;
			case 0x0D:
				cout<<"JUMP M("<<MAR<<",0:19)\n";
				PC=MAR;
				IR=MBR>>32;
				MAR=(MBR>>20)%BASE12;
				IBR=MBR%BASE20;
				first=1;
				goto NextInstruction;
			break;
			case 0x0E:
				cout<<"JUMP M("<<MAR<<",20:39)\n";
				PC=MAR;
				IR=(MBR>>12)%BASE8;
				MAR=MBR%BASE12;
				first=0;
				goto NextInstruction;
			break;
			case 0x0F:
				cout<<"JUMP+ M("<<MAR<<",0:19)\n";
				if(AC>=0)
				{
					PC=MAR;
					IR=MBR>>32;
					MAR=(MBR>>20)%BASE12;
					IBR=MBR%BASE20;
					first=1;
					goto NextInstruction;
				}
			break;
			case 0x10:
				cout<<"JUMP+ M("<<MAR<<",20:39)\n";
				if(AC>=0)
				{
					PC=MAR;
					IR=(MBR>>12)%BASE8;
					MAR=MBR%BASE12;
					first=0;
					goto NextInstruction;
				}
			break;
			case 0x11:
				cout<<"STOR M("<<MAR<<")\n";
				(*(M+MAR))=AC;
			break;
			case 0x12:
			{
				cout<<"STOR M("<<MAR<<",8:19)\n";
				long long temp=MBR%BASE20;
				long long temp1=MBR>>32;
				*(M+MAR)=temp1<<32 + AC<<20 + temp;
			}
			break;
			case 0x13:
			{
				cout<<"STOR M("<<MAR<<",28:39)\n";
				long long temp=MBR>>12;
				*(M+MAR)=temp<<12 + AC;
			}
			break;
			case 0x14:
				cout<<"LSH\n";
				AC=AC<<1;
				break;
			case 0x15:
				cout<<"RSH\n";
				AC=AC>>1;
			break;
		}
		if(first)
		{
			first=0;
			IR=IBR>>12;
			MAR=IBR%BASE12;
			goto NextInstruction;
		}
	}
	return 0;
}
int main()
{
	long long Memory[1000];
	for(int i=0;i<1000;i++)
	{
		Memory[i]=0;
	}
	
	Memory[0x000]=1;
	Memory[0x001]=15;
	Memory[0x003]=0x0100106000;
	Memory[0x004]=0x0F00601000;
	Memory[0x005]=0x050010D008;
	Memory[0x006]=0x0100006001;
	Memory[0x007]=0x100080E004;
	Memory[0x008]=0x1100200000;
	Memory[0x008]=0x1100200000;
	Memory[0x009]=5;
	Memory[0x00B]=2;
	Memory[0x00C]=3;
	Memory[0x00E]=0x0900901009;
	Memory[0x00F]=0x0600C10011;
	Memory[0x010]=0x0A0001100D;
	Memory[0x011]=0x000000500B;
	Memory[0x012]=0x1100A0B00A;
	Memory[0x013]=0x0100A0D00F;
	
	char running=1;
	short memloc=0;
	while(running)
	{
		cout<<"Current memory location: "<<memloc<<endl;
		cout<<"Value at memory location: "<<Memory[memloc]<<endl;
		cout<<"INR:\t1\n";
		cout<<"DCR:\t2\n";
		cout<<"GO:\t3\n";
		cout<<"SET:\t4\n";
		cout<<"EXEC:\t5\n";
		cout<<"EXIT:\t0\n";
		cout<<"Enter your choice: ";
		int choice;
		cin>>choice;
		switch(choice)
		{
			case 0:
				running=0;
			break;
			case 1:
				memloc++;
				if(memloc>=1000)
				{
					memloc-=1000;
				}
			break;
			case 2:
				memloc--;
				if(memloc<0)
				{
					memloc+=1000;
				}
			break;
			case 3:
				cin>>memloc;
				while(memloc>=1000)
				{
					memloc-=1000;
				}
				while(memloc<0)
				{
					memloc+=1000;
				}
			break;
			case 4:
				cin>>Memory[memloc];
			break;
			case 5:
				cout<<"\n";
				exec(Memory,memloc);
			break;
		}
		cout<<"\n";
	}
	return 0;
}
