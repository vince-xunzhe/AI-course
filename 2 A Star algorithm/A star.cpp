#include <iostream>
#include <queue>
using namespace std;
  
struct smile                                      // the properities of smile, using a structure. 
{
    int x,y,steps;
    int g,h,f;
    bool operator < (const smile & sim) const
	{      
      return f > sim.f;
    }
}  sim;

int maze[9][9];                                    // the game plate.

bool visited[9][9];                                // the node that has been visited. 
    
int x1,y1,x2,y2,ans;             // we start at (x1,y1), and end with (x2,y2), while ans presents the steps.

int dirs[4][2]={{-1,0},{1,0},{0,-1},{0,1}};        // there would be four directions to go: upper, down, left, and right. 

priority_queue<smile> que;                         // it is a priority queue(less-first) to select the best Heuristic value.

bool in(const smile & a)                           // state sensor.
{
	bool obs1=(((a.x==1)&&(a.y==1))||((a.x==2)&&(a.y==1))||((a.x==3)&&(a.y==1)));
	bool obs2=(((a.x==3)&&(a.y==2))||((a.x==4)&&(a.y==2))||((a.x==5)&&(a.y==2)));
	bool obs3=(((a.x==0)&&(a.y==3))||((a.x==5)&&(a.y==3))||((a.x==6)&&(a.y==5)));
	bool obs4=(((a.x==1)&&(a.y==4))||((a.x==2)&&(a.y==4))||((a.x==3)&&(a.y==4))||((a.x==5)&&(a.y==4)));
	bool emp1=(((a.x==2)&&(a.y==7))||((a.x==3)&&(a.y==7))||((a.x==4)&&(a.y==7))||((a.x==5)&&(a.y==7))||((a.x==6)&&(a.y==7)));
	bool emp2=(((a.x==2)&&(a.y==8))||((a.x==3)&&(a.y==8))||((a.x==4)&&(a.y==8))||((a.x==5)&&(a.y==8))||((a.x==6)&&(a.y==8)));
    bool edge=(a.x<0)||(a.y<0)||(a.x>8)||(a.y>8);

    if(obs1||obs2||obs3||obs4||emp1||emp2||edge)   // make sure that the smile is always in the maze.
	{
		return false;
	}
    return true;
}

int heu_obs( const smile & a, int maze[][9])       // detect how many the obstacles in the way to the house
{
	int loc_ver=x2;
	int loc_hor=y2;
	int s_hor=a.x;
	int s_ver=a.y;
	int obstacle=0;

	if(s_hor<=loc_hor)                              // horizontal search for obstacles
	{
		for(int i=s_hor;i<=loc_hor;i++)
		{
			if(maze[i][s_ver]==1)
				obstacle++;
		}
	}
	else
	{
		for(int i=s_hor;i>=loc_hor;i--)
		{
			if (maze[i][s_ver]==2)
				obstacle++;
		}
	}
	s_hor=loc_hor;
	if(s_ver<=loc_ver)                              // vertical search for obstacles
	{
		for(int m=s_ver+1;m<=loc_ver;m++)
		{
			if(maze[s_hor][m]==2)
				obstacle++;
		}
	}
	else
	{
		for(int n=s_ver-1;n>=loc_ver;n--)
		{
			if (maze[s_hor][n]==2)
				obstacle++;
		}
	}
	return obstacle;                                 // return the total numbers of obstacles in the path.
}



 int heuristic(const smile &a)                       // it is a h'(x)=obs_in_vertical+obs_in_horizontal+distance.
 {                                                  
     return (heu_obs(a, maze)+abs(a.x-x2)+abs(a.y-y2));;
 }
 
 void Astar(){                                       // A* algorithm.
     smile t,s;
     while(!que.empty())
	 {
         t=que.top();                                // pick up the best value of node in priority queue.
		 que.pop();
		 visited[t.x][t.y]=true;                     // and push that node to the visited area. 
         if(t.x==x2 && t.y==y2)
		 {
             ans=t.steps;                            // reach the destination successfully.
			 cout<<"Got position.";
			 cout<<endl;
			 cout<<endl;
			 cout<<"After A* sreach, there would be "<<ans<<" steps to the house."<<endl;
             break;
         }
         for(int i=0;i<4;i++)                        // make a movment.
		 {
             s.x=t.x+dirs[i][0];
			 s.y=t.y+dirs[i][1];
             if(in(s) && !visited[s.x][s.y])
			 {
                 s.g=t.g+1;                          // the depth of the node increase by 1 after every single movment.
                 s.h=heuristic(s);
                 s.f=s.g+s.h;
                 s.steps=t.steps+1;
                 que.push(s);                        // save the new node in the que. 
				 cout<<"("<<s.x<<","<<s.y<<")"<<"-";
             }
         }
     }
 }

 void main()
 {
	 maze[9][9];
	 maze[1][4]=maze[2][2]=maze[2][5]=1;              // presentation of the maze;
	 maze[3][2]=maze[3][5]=maze[4][2]=1;                
	 maze[4][3]=maze[4][5]=maze[5][3]=1;                  
	 maze[6][3]=maze[6][4]=maze[6][5]=maze[7][6]=1;
	 for(int ij=2;ij<=6;ij++)
	 {
	  	 for(int ji=7;ji<=8;ji++)
		 {
			 maze[ij][ji]=1;
		 }
	 }

	
	cout<<"1:(0,0)   2:(0,8)   3:(8,0)   4:(8,8)"<<endl;
	cout<<"Please choose the start position: ";
	int option;
	cin>>option;


	switch(option)
	{
		case 1:
			x1=0, y1=0;
			break;
		case 2:
			x1=0, y1=8;
			break;
		case 3:
			x1=8, y1=0;
			break;
		case 4:
			x1=8, y1=8;
			break;
		default:
			cout<<"error";
	}
	
	y2=3,x2=3;
	cout<<endl;
	cout<<"Here is the nodes travel pathing:"<<endl;
    sim.x=x1;
	sim.y=y1;
	sim.g=sim.steps=0;
	sim.h=heuristic(sim);
	sim.f=sim.g+sim.h;
    while( !que.empty() )
	{
		que.pop();
	}
	que.push(sim);
    Astar();
	cout<<endl;
	cout<<endl;
 }
