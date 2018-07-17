#include<iostream>
#include<vector>
using std::vector;
using namespace std;

int queue[20000];
int head=0;
int tail=0;
int element=0;
int stack[20000];
int visited[20000];
int sp=0;
int a;
int b;
vector<int> vec;
vector<int> path;
int time1=0;
int time2=0;

void in_queue(int k)
{
	if(tail<(20000-1))
	{
		queue[tail++]=k;
	}
	else
	{
		cout<<"Queue is full!"<<endl;
		exit(-1);
	}
}

int out_queue(void)  
{  
    if(head == tail)  
    {  
        cout<<"queue underflow"<<endl;;  
        exit(0);  
    }  
    return queue[head=head+1];  
}  


void in_stack(int f)  
{  
    if(sp < 20000)  
       stack[sp++] = f;  
    else  
       cout<<"stack full!"<<endl; 

}  

int out_stack(void)  
{  
    if(sp > 0)  
      return stack[sp--];  
    else {  
      cout<<"stack is empty!";  
      return 0;  
    }  
}  

void in_visited(int b)
{
	visited[element++]=b;
}


bool isexit(int line[],int control, int obj)
{
    bool flag=0;
    for(int y=0;y<=control;y++)
	{
	   if (line[y]==obj)
	   {
	    	flag=1||flag;
	   }
	   else
	   {
	    	flag=0||flag;
	   }
	}
    return flag;
}

void find_father(int queue[], int gra[][20], int control_value, int beg,int end)
{  
	if(beg!=end)
	{
	  for(int val=0; val<=19; val++)
	  {
		 if(gra[end][val]!=0)
		 {
		    	for(int val2=0; val2<=control_value-1; val2++)
				{
				    if(val==queue[val2])
					{
					   path.push_back(val);
					   end=val;
					   find_father(queue, gra, control_value,beg,end);
					}
				}
		 }
	  }
	}
	else
	{
		for(int yy=path.size()-1;yy>=0;yy--)
		{
			cout<<path[yy]<<" ";
		}
		cout<<b;
		cout<<endl;
		cout<<endl;
		exit(0);
	

	}
}

void Breadth_Search (int present, int destination, int gra[][20])
{

	    bool z;
		if (present!=destination)
	{
		for(int i=0;i<=19;i++)
		{
			if((gra[present][i]!=0))
			{
				z=isexit(queue,head,i);
				if (z==0)
				{
				in_queue(i);
				time1++;
				time2++;
				}
			}
		}
		out_queue();
		time1--;
		present=queue[head];
		Breadth_Search(present, destination, gra);
	}
	else
	{

		cout<<"Time: "<<time1<<"     "<<"Space: "<<time2<<endl;
		cout<<"Here is the Breath_Search Path:"; find_father(queue,gra,head,a,b);
		exit(0);
	}
}



void Depth_Search(int present, int destination, int gra[][20])
{
	path.push_back(present);
	int c=0;
	if(present!=destination)
	{
    for(c;c<=19;c++)
	   {
     	  if (gra[present][c]!=0)
	      {
			  bool r=isexit(visited,element-1,c);
			  if (r==0)
			  {
				  in_visited(c);
				  in_stack(c);
				  time1++;
				  time2++;
				  present=c;  
				  Depth_Search(present,destination,gra);
			  }
			  else
			  {
			  }
		  }
	    }
	   out_stack();
	   present=stack[sp];
	   time1--;
	   Depth_Search(present,destination,gra);
	}
	else
	{
		cout<<"Time: "<<time1<<"     "<<"Space: "<<time2<<endl;
		cout<<"Here is the Depth_Search Path:";
		for(int vince=0;vince<=(path.size()-1);vince++)
		{
			for(int vince1=0;vince1<=vince;vince1++)
			{
				if (path[vince1]==path[vince])
				{
		        	cout<<path[vince]<<"  ";
				}
				else
				{
				cout<<"";
				}
			}

		}
		cout<<endl;
		exit(0);

	}
}



void Uni_Search (int present, int destination, int gra[][20])
{
		if (present!=destination)
		{
		    for(int i=0;i<=19;i++)
			{
			    if((gra[present][i]!=0))
				{
			    	vec.push_back(i);
				}
			}
		    for(int loop1=0;loop1<=vec.size()-1;loop1++)
			{
		     	for(int loop2=loop1+1;loop2<=vec.size()-1;loop2++)
				{
				    if(gra[present][vec[loop1]]<gra[present][vec[loop2]])
					{
					     int vecmid=vec[loop1];
					     vec[loop1]=vec[loop2];
					     vec[loop2]=vecmid;
					}
				}
			}
			for (int vers=vec.size()-1;vers>=0;vers--)
			{
				in_queue(vec[vers]);
				time1++;
			    time2++;
				vec.pop_back();
			}
		out_queue();
		time1--;
		present=queue[head];
		Uni_Search(present, destination, gra);
	}
		else
    cout<<"Time: "<<time1<<"     "<<"Space: "<<time2<<endl;
    cout<<"Here is the Uni_CostPath:"; find_father(queue,gra,head,a,b);


    cout<<endl;

}



int main()
{
	int graph[20][20]={0};
    graph[ 0][ 1]=71;
	graph[ 0][ 7]=151;
	graph[ 1][ 2]=75;
	graph[ 2][ 3]=118;
	graph[ 2][ 7]=140;
	graph[ 3][ 4]=111;
	graph[ 4][ 5]=70;
	graph[ 5][ 6]=75;
	graph[ 6][ 9]=120;
	graph[ 7][ 8]=80;
	graph[ 7][10]=99;
	graph[ 8][ 9]=146;
	graph[ 8][11]=97;
	graph[ 9][11]=138;
	graph[10][12]=211;
	graph[11][12]=101;
	graph[12][13]=90;
	graph[12][14]=85;
	graph[14][17]=142;
	graph[14][18]=98;
	graph[15][16]=87;
	graph[16][17]=92;
	graph[18][19]=86;
	for(int aa=0;aa<=19;aa++)
	{
		for(int bb=aa;bb<=19;bb++)
		{
			graph[bb][aa]=graph[aa][bb];
		}
	}

    int gra[20][20];
	for(int rr=0;rr<=19;rr++)
	{
		for( int cc=0;cc<=19;cc++)
		{
			gra[rr][cc]=graph[rr][cc];

		}
	}


	cout<<"Welcome to our Journey"<<endl;
    cout<<endl;

	cout<<"Here is the representation of the Cities by numbers: "<<endl;
	cout<<"0 :Oradea   1 :zerind   2 : Arad    3 :Timisoara  4 :Lugoj"<<endl;
	cout<<"5 :Mehadia  6 :Drobeta  7 :Sibiu    8 :Rimnicu    9 :Craiova"<<endl;
	cout<<"10:Fagaras  11:Pitesti  12:Bucha    13:Giurgiu    14:Urziceni"<<endl;
	cout<<"15:Neamt    16:Iasi     17:Vaslui   18:Hirsova    19:Eferie"<<endl;




	cout<<endl;
	cout<<"please give me the destination:"<<endl;
	cout<<"Start: ";cin>>a;
	cout<<"End  : ";cin>>b;
	cout<<endl;
	in_queue(a);
	in_stack(a);
    in_visited(a);

	cout<<"Algorithm selection:"<<endl;
	cout<<"1.Breadth Search;   2.Depth Search;   3.Uniformed Cost Search"<<endl;
	int sele;
	int con_value;
	while(cin>>con_value)
	{
		cout<<endl;
		switch(con_value)
		{
		case 1:
			Breadth_Search(a,b,gra);
			break;
		case 2:
			Depth_Search(a,b,gra);;
			break;
		case 3: 
			Uni_Search(a,b,gra);;
			break;
		}
	}

	return 0;
}

