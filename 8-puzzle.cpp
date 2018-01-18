#include<bits/stdc++.h>
using namespace std;

struct node{
    int arr[10][10];
    int x,y,n,depth;
}start,goal;

vector<node>visited;
int idx=0,Gn;
map<int,int>parent;
vector<node>solution;

int nextx[]={1,-1,0,0};
int nexty[]={0,0,1,-1};

bool isGoal(node u)
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(goal.arr[i][j]!=u.arr[i][j])
                return false;
        }
    }
    return true;
}

bool isVisited(node v)
{
    for(int i=0;i<visited.size();i++)
    {
        node vis=visited[i];
        int k,j;
        for(j=0;j<3;j++)
        {
            for(k=0;k<3;k++)
            {
                if(vis.arr[j][k]!=v.arr[j][k])
                    break;
            }
            if(k<3) break;
        }
        if(j==3 and k==3) return false;
    }
    return true;
}

bool isValid(int a,int b)
{
    if(a>=0 and a<3 and b>=0 and b<3)
        return true;
    else return false;
}

void print(node a)
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            cout<<a.arr[i][j]<<" ";
        }
        cout<<endl;
    }
}

bool BFS()
{
    queue<node>Q;
    start.n=idx;
    parent[idx]=idx;
    Q.push(start);
    idx++;
    start.depth=0;
    visited.push_back(start);
    while(Q.empty()==false)
    {
        node u=Q.front();
        Q.pop();
        if(isGoal(u)){
            Gn=u.n;
            return true;
        }
        for(int i=0;i<4;i++)
        {
            int newx=u.x+nextx[i];
            int newy=u.y+nexty[i];
            if(isValid(newx,newy))
            {
                node v=u;
                v.x=newx;
                v.y=newy;
                swap(v.arr[v.x][v.y],v.arr[u.x][u.y]);
                if(isVisited(v))
                {
                    v.n=idx;
                    idx++;
                    parent[v.n]=u.n;
                    v.depth=u.depth+1;
                    if(v.depth==25) return false;
                    visited.push_back(v);
                    Q.push(v);
                }
            }
        }
    }
    return false;
}

int main()
{
    long long int i,j,a,b,n,k;
    char c,ch;
    cout<<"Do You Want To Play......???????"<<endl;
    cout<<"(Y/N)"<<endl;
    cin>>c;
    c=tolower(c);
    while(c=='y')
    {
        system("CLS");
        /// start state
        cout<<"Initial State : "<<endl;
        cout<<"A B C"<<endl;
        cout<<"D E F"<<endl;
        cout<<"I J K"<<endl;
        cout<<"   |"<<endl;
        cout<<"  _|_"<<endl;
        cout<<"  \\ /"<<endl;
        cout<<"   `"<<endl;
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
            {
                cin>>start.arr[i][j];
                if(start.arr[i][j]==0)
                {
                    start.x=i;
                    start.y=j;
                }
            }

        /// goal state
        cout<<"Goal State : "<<endl;
        cout<<"A B C"<<endl;
        cout<<"D E F"<<endl;
        cout<<"I J K"<<endl;
        cout<<"   |"<<endl;
        cout<<"  _|_"<<endl;
        cout<<"  \\ /"<<endl;
        cout<<"   `"<<endl;
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
            {
                cin>>goal.arr[i][j];
                if(goal.arr[i][j]==0)
                {
                    goal.x=i;
                    goal.y=j;
                }
            }

        cout<<"wait...... result is processing............."<<endl;
        /// BFS
        bool yes=BFS();
        system("CLS");
        if(yes){
            cout<<endl<<endl<<":) Solution Found :)"<<endl;
            while(parent[Gn]!=Gn)
            {
                solution.push_back(visited[Gn]);
                Gn=parent[Gn];
            }
            solution.push_back(visited[Gn]);

            for(int k=solution.size()-1;k>=0;k--)
            {
                node sol=solution[k];
                for(i=0;i<3;i++)
                {
                    for(j=0;j<3;j++)
                    {
                        cout<<sol.arr[i][j]<<" ";
                    }
                    cout<<endl;
                }
                cout<<endl;
                if(k!=0){
                    cout<<"   |"<<endl;
                    cout<<"  _|_"<<endl;
                    cout<<"  \\ /"<<endl;
                    cout<<"   `"<<endl;
                }
            }
        }
        else cout<<endl<<endl<<":( No Solution Found :("<<endl;

    /*
        for(int k=0;k<visited.size();k++)
        {
            node vis=visited[k];
            for(i=0;i<3;i++)
                {
                    for(j=0;j<3;j++)
                    {
                        cout<<vis.arr[i][j]<<" ";
                    }
                    cout<<endl;
                }
                cout<<endl;
        }
    */
        cout<<"Do You Want To Play Again......???????"<<endl;
        cout<<"(Y/N)"<<endl;
        cin>>c;
        c=tolower(c);
        system("CLS");
        visited.clear();
        parent.clear();
        solution.clear();
    }
    return 0;
}
