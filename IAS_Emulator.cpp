#include<bits/stdc++.h>
using namespace std;
int exec(long long *M,short PC)
{
	long long AC=0,MQ=0,MBR=0,IBR=0,IR=0,MAR=0;
	for(;PC<1000;PC++)
	{
		MAR=PC;
		MBR=*(M+MAR);
		char first=1;
		IBR=(MBR)%((long long)1<<20);
		IR=MBR>>32;
		MAR=(MBR>>20)%((long long)1<<12);
		NextInstruction:;
		switch(IR)
		{
			case 0x00:
				cout<<"HLT\n";
				return 0;
			break;
			case 0x01:
				cout<<"LOAD M("<<MAR<<")\n";
				AC=(*(M+MAR));
			break;
			case 0x02:
				cout<<"LOAD -M("<<MAR<<")\n";
				AC=0-(*(M+MAR));
			break;
			case 0x03:
				cout<<"LOAD |M("<<MAR<<")|\n";
				AC=(*(M+MAR));
				AC=(AC>0)?AC:-AC;
			break;
			case 0x04:
				cout<<"LOAD -|M("<<MAR<<")|\n";
				AC=(*(M+MAR));
				AC=(AC>0)?-AC:AC;
			break;
			case 0x05:
				cout<<"ADD M("<<MAR<<")\n";
				AC+=(*(M+MAR));
			break;
			case 0x06:
				cout<<"SUB M("<<MAR<<")\n";
				AC-=(*(M+MAR));
			break;
			case 0x07:
				cout<<"ADD |M("<<MAR<<")|\n";
				AC+=((*(M+MAR))>0)?(*(M+MAR)):-(*(M+MAR));
			break;
			case 0x08:
				cout<<"SUB |M("<<MAR<<")|\n";
				AC-=((*(M+MAR))>0)?(*(M+MAR)):-(*(M+MAR));
			break;
			case 0x09:
				cout<<"LOAD MQ,M("<<MAR<<")\n";
				MQ=(*(M+MAR));
			break;
			case 0x0A:
				cout<<"LOAD MQ\n";
				AC=MQ;
			break;
			case 0x0B:
			{
				cout<<"MUL M("<<MAR<<")\n";
				long long MQR=MQ%(1<<20);
				long long MQL=MQ>>20;
				
				long long MR=(*(M+MAR))%(1<<20);
				long long ML=(*(M+MAR))>>20;
				
				long long ANS11=ML*MQL;
				long long ANS10=MR*MQL;
				long long ANS01=ML*MQR;
				long long ANS00=MR*MQR;
				
				int carry=0;
				long long temp=0;
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
				cout<<"DIV M("<<MAR<<")\n";
				long long quo=AC/(*(M+MAR)),rem=AC%(*(M+MAR));
				MQ=quo;
				AC=rem;
			}
			break;
			case 0x0D:
				cout<<"JUMP M("<<MAR<<",0:19)\n";
				MBR=*(M+MAR);
				PC=MAR;
				IR=MBR>>32;
				MAR=(MBR>>20)%((long long)1<<12);
				IBR=MBR%((long long)1<<20);
				first=1;
				goto NextInstruction;
			break;
			case 0x0E:
				cout<<"JUMP M("<<MAR<<",20:39)\n";
				MBR=*(M+MAR);
				PC=MAR;
				IR=(MBR>>12)%((long long)1<<8);
				MAR=MBR%((long long)1<<12);
				first=0;
				goto NextInstruction;
			break;
			case 0x0F:
				cout<<"JUMP+ M("<<MAR<<",0:19)\n";
				if(AC>=0)
				{
					MBR=*(M+MAR);
					PC=MAR;
					IR=MBR>>32;
					MAR=(MBR>>20)%((long long)1<<12);
					IBR=MBR%((long long)1<<20);
					first=1;
					goto NextInstruction;
				}
			break;
			case 0x10:
				cout<<"JUMP+ M("<<MAR<<",20:39)\n";
				if(AC>=0)
				{
					MBR=*(M+MAR);
					PC=MAR;
					IR=(MBR>>12)%((long long)1<<8);
					MAR=MBR%((long long)1<<12);
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
				long long temp=(*(M+MAR))%(1<<20);
				long long temp1=(*(M+MAR))>>32;
				*(M+MAR)=temp1<<32 + AC<<20 + temp;
			}
			break;
			case 0x13:
			{
				cout<<"STOR M("<<MAR<<",28:39)\n";
				long long temp=(*(M+MAR))>>12;
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
			MAR=IBR%(1<<12);
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
	
	Memory[0]=1;
	Memory[1]=15;
	Memory[3]=0x0100006001;
	Memory[4]=0x1000601000;
	Memory[5]=0x0500111002;
	Memory[6]=0x0000001001;
	Memory[7]=0x0600010008;
	Memory[8]=0x1000411002;
	Memory[9]=0x0000000000;
	
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
