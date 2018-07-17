#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
using std::vector;

int house=4;
int box[][2]={0};
int g=0;
int hor;
int ver;
vector<int> row;
vector<int> col;
vector<int> heu;


int heu_ver_first(int s_hor, int s_ver, int maze[][11])
{
	int loc_ver=house;
	int loc_hor=house;
	int dis=0;
	int obstacle=0;

	dis=abs(s_hor-house)+abs(s_ver-house);

	if(s_hor<=loc_hor)
	{
		for(int i=s_hor;i<=loc_hor;i++)
		{
			if(maze[i][s_ver]==2)
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

	if(s_ver<=loc_ver)
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
    cout<<"ver Obstacles="<<obstacle<<endl;
	cout<<"distance= "<<dis<<endl;
	return obstacle+dis;
}

int heu_hor_first(int s_hor, int s_ver, int maze[][11])
{
	int loc_ver=house;
	int loc_hor=house;
	int dis=0;
	int obstacle=0;

	dis=abs(s_hor-house)+abs(s_ver-house);

	if(s_ver<=loc_ver)
	{
		for(int j=s_ver;j<=loc_ver;j++)
		{
			if(maze[s_hor][j]==2)
				obstacle++;
		}
	}
	else
	{
		for(int i=s_ver;i>=loc_ver;i--)
		{
			if (maze[s_hor][i]==2)
				obstacle++;
		}
	}
	
	s_ver=loc_ver;

	if(s_hor<=loc_hor)
	{
		for(int i=s_hor+1;i<=loc_hor;i++)
		{
			if(maze[i][s_ver]==2)
				obstacle++;
		}
	}
	else
	{
		for(int i=s_hor-1;i>=loc_hor;i--)
		{
			if (maze[i][s_ver]==2)
				obstacle++;
		}
	}
	cout<<"Hor Obstacles="<<obstacle<<endl;
	cout<<"distance= "<<dis<<endl;
	return obstacle+dis;
}



void sort_vec( vector<int> & heut )    // from greatest to smallest
{
	for(int it1=0;it1<=heut.size();it1++)
	{
		for(int it2=it1+1;it2<=heut.size();it2++)
		{
			if(heut[it2]>=heut[it1])
			{
				int temp=heut[it1];
				heut[it1]=heut[it2];
				heut[it2]=temp;
			}
		}
	}
	cout<<"The heu is sorted:";
	for(int i=0;i<=heut.size()-1;i++)
	{
		cout<<" "<<heut[i];
	}
	cout<<endl;
}



void sensor(int s_hor, int s_ver, int maze[][11])
{
	if ((maze[s_hor][s_ver-1]!=2)||(maze[s_hor][s_ver+1]!=2))    // Left or Right
	{
		box[g][0]=heu_hor_first(s_hor,s_ver,maze)+g;
	}
	else
	{
		box[g][0]=200;
	}
	heu.push_back(box[g][0]);

	if ((maze[s_hor-1][s_ver]!=2)||(maze[s_hor+1][s_ver]!=2))    // Up or Down
	{
		box[g][1]=heu_ver_first(s_hor,s_ver,maze)+g;
	}
	else
	{
		box[g][1]=200;
	}
	heu.push_back(box[g][1]);

	cout<<"The original heu is: ";
	for(int i=0;i<=heu.size()-1;i++)
	{
		cout<<heu[i]<<" ";
	}
	cout<<endl;
	sort_vec(heu);
	cout<<endl;
	row.push_back(hor);
	col.push_back(ver);
}

//int find_min(int con[4])
//{
//	int min=con[0];
//	for(int i=1;i<=3;i++)
//	{
//		if(con[i]<=min)
//		{
//			min=con[i];
//		}
//	}
//	return min;
//}

int move_command(int & g,int i,int sm_hor, int sm_ver, int maze[][11])
{
	sensor(sm_hor,sm_ver,maze);
	int gg=g;
	int last=heu.size()-1;

	if(heu[last]==box[gg][0])
	{
		heu.pop_back();
		return 0;
	}
	else if(heu[last]==box[gg][1])
	{
		heu.pop_back();
		return 1;
	}
	else
	{
		g--;
		int back=row.size()-i;
		int back_hor=row[back];
		int back_ver=col[back];
		i++;
		move_command(g,i,back_hor,back_ver,maze);
	}
}


void make_move(int order,int & hor, int & ver,int maze[][11])
{
	if((order==0)&&((maze[hor][ver+1]!=0)||(maze[hor][ver-1]!=0)))
	{
		order=1;
	}
	if((order==1)&&((maze[hor+1][ver]!=0)||(maze[hor-1][ver]!=0)))
	{
		order=0;
	}
	switch(order)
	{
	case 0:
		if((maze[hor][ver+1]==2))
		{
			ver=ver-1;
		}
		else
		{
			ver=ver+1;
		}
		break;
	case 1:
		if((maze[hor+1][ver]==2))
		{
			hor=hor-1;
		}
		else
		{
			hor=hor+1;
		}
		break;
	}
	maze[hor][ver]=1;
	g++;
	cout<<"Now, g= "<<g<<endl;
}

void on_vacation(int hor, int ver, int maze[][11])
{
	if((hor==house)&&(ver==house))
	{
		cout<<"Successful!"<<endl;
		exit(0);
	}
	else
	{
//		sensor(hor,ver,maze);
	 //   sort_vec(heu);	
	    int command=move_command(g,1,hor,ver,maze);
	    make_move(command,hor,ver,maze);
//		cout<<"hor="<<hor<<"  "<<"ver="<<ver;
	}
	on_vacation(hor,ver,maze);
}
//{
//	int s_hor=hor;
//	int s_ver=ver;
//	sensor(s_hor,s_ver,maze);
//	command=move_command(s_hor,s_ver,maze);
//	make_move(command,s_hor,s_ver,maze);
//	if((hor==house)&&(ver==house))
//	{
//		cout<<"Here is the Path"<<endl;
//		for(int CNM=0;CNM<=10;CNM++)
//		{
//			for(int MGB=0;MGB<=10;MGB++)
//			{
//				cout<<maze[CNM][MGB]<<"  ";
//			}
//		}
//
//	}
//	else
//	{
//		on_vacation(hor, ver, maze);
//	}
//}





//{
//	int ver_distance=abs(a-house);
//	int hor_distance=abs(b-house);
//	int heu=ver_distance+hor_distance;
//	heu_hor_first(a,b,maze)+heu_ver_first(a,b,maze);
//	cout<<"h_obs="<<heuristic_hor(a,b,maze)<<" "<<"v_obs"<<heuristic_ver(a,b,maze)<<endl;
//	return heu;
//}

int main()
{
	int maze[11][11]={0};
	maze[1][4]=maze[2][2]=maze[2][5]=2;                  // presentation of the maze;
	maze[3][2]=maze[3][5]=maze[4][2]=2;                  // 2 presents the obstacles;
	maze[4][3]=maze[4][5]=maze[5][3]=2;                  // 1 presents the house;
	maze[6][3]=maze[6][4]=maze[6][5]=maze[7][6]=2;
	maze[house][house]=8;
	for(int iiiii=0;iiiii<=10;iiiii++)
	{
		maze[iiiii][10]=2;
	}
	for(int iiii=0;iiii<=10;iiii++)
	{
		maze[iiii][0]=2;
	}
	for(int iii=0;iii<=11;iii++)
	{
		maze[10][iii]=2;
	}
	for( int ii=0;ii<=11;ii++)
	{
		maze[0][ii]=2;
	}
	for(int ij=3;ij<=7;ij++)
	{
		for(int ji=8;ji<=9;ji++)
		{
			maze[ij][ji]=2;
		}
	}
	cout<<"please select your location: "<<endl;
	cin>>hor;
	cin>>ver;
	if(maze[hor][ver]==2)
	{
	    cout<<"No way, you cannot be there"<<endl;
		exit(0);
	}
	else
		maze[hor][ver]=1;
	
	for(int i=0;i<=10;i++)
	{
		for(int j=0;j<=10;j++)
		{
			cout<<maze[i][j]<<"  ";
		}
		cout<<endl;
	}
	cout<<endl;

//	int g=0;
//	sensor(hor,ver,maze);
//	cout<<box[0]<<" "<<box[1]<<" "<<box[2]<<" "<<box[3]<<endl;
//	sort_vec(heu);


//	sensor(s_hor,s_ver,maze);
//	sort_vec(heu);	
//	command=move_command(s_hor,s_ver,maze);
//	make_move(command,hor,ver,maze);

	on_vacation(hor,ver,maze);
	cout<<"Here is the Path"<<endl;
	for(int CNM=0;CNM<=10;CNM++)
	{
		for(int MGB=0;MGB<=10;MGB++)
		{
			cout<<maze[CNM][MGB]<<"  ";
		}
		cout<<endl;
	}

	cout<<box[g][0]<<"~~~~~~~~"<<box[g][1]<<endl;
//	int x=heu_ver_first(ver,hor,maze);
//	int y=heu_hor_first(ver,hor,maze);
//	cout<<"ver_first="<<x<<endl;
//	cout<<"hor_first="<<y<<endl;
	cout<<endl;
	system("pause");
	return 0;
}