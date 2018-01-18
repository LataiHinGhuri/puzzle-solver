#include<bits/stdc++.h>
using namespace std;

struct node{
    int arr[10][10];
    int x,y,n;
}start,goal;

vector<node>forword_visited;
vector<node>backword_visited;
int forword_idx=0;
int backword_idx=0;
map<int,int>forword_parent;
map<int,int>backword_parent;
int forword_end,backword_end;
vector<node>solution;

int nextx[]={1,-1,0,0};
int nexty[]={0,0,1,-1};

bool isForwordGoal(node u)
{
    for(int k=0;k<backword_visited.size();k++)
    {
        node G=backword_visited[k];
        int i,j;
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                if(G.arr[i][j]!=u.arr[i][j])
                    break;
            }
            if(j<3) break;
        }
        if(i==3 and j==3)
        {
            forword_end=u.n;
            backword_end=G.n;
            return true;
        }
    }
    return false;
}

bool isBackwordGoal(node u)
{
    for(int k=0;k<forword_visited.size();k++)
    {
        node G=forword_visited[k];
        int i,j;
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                if(G.arr[i][j]!=u.arr[i][j])
                    break;
            }
            if(j<3) break;
        }
        if(i==3 and j==3)
        {
            backword_end=u.n;
            forword_end=G.n;
            return true;
        }
    }
    return false;
}


bool isForwordVisited(node v)
{
    for(int i=0;i<forword_visited .size();i++)
    {
        node vis=forword_visited [i];
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

bool isBackwordVisited(node v)
{
    for(int i=0;i<backword_visited .size();i++)
    {
        node vis=backword_visited [i];
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
    queue<node>forword_Q;
    start.n=forword_idx;
    forword_parent[forword_idx]=forword_idx;
    forword_Q.push(start);
    forword_idx++;
    forword_visited .push_back(start);

    queue<node>backword_Q;
    goal.n=backword_idx;
    backword_parent[backword_idx]=backword_idx;
    backword_Q.push(goal);
    backword_idx++;
    backword_visited.push_back(goal);

    while(forword_Q.empty()==false)
    {
        node u=forword_Q.front();
        forword_Q.pop();

        node a=backword_Q.front();
        backword_Q.pop();

        if(isForwordGoal(u)){
            return true;
        }
        if(isBackwordGoal(a)){
            return true;
        }

        for(int i=0;i<4;i++)
        {
            int newfx=u.x+nextx[i];
            int newfy=u.y+nexty[i];
            if(isValid(newfx,newfy))
            {
                node v=u;
                v.x=newfx;
                v.y=newfy;
                swap(v.arr[v.x][v.y],v.arr[u.x][u.y]);
                if(isForwordVisited(v))
                {
                    v.n=forword_idx;
                    forword_idx++;
                    forword_parent[v.n]=u.n;
                    forword_visited .push_back(v);
                    forword_Q.push(v);
                }
            }

            int newbx=a.x+nextx[i];
            int newby=a.y+nexty[i];
            if(isValid(newbx,newby))
            {
                node b=a;
                b.x=newbx;
                b.y=newby;
                swap(b.arr[b.x][b.y],b.arr[a.x][a.y]);
                if(isBackwordVisited(b))
                {
                    b.n=backword_idx;
                    backword_idx++;
                    backword_parent[b.n]=a.n;
                    backword_visited .push_back(b);
                    backword_Q.push(b);
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
            while(forword_parent[forword_end]!=forword_end)
            {
                solution.push_back(forword_visited [forword_end]);
                forword_end=forword_parent[forword_end];
            }
            solution.push_back(forword_visited [forword_end]);
            reverse(solution.begin(),solution.end());

            backword_end=backword_parent[backword_end];
            while(backword_parent[backword_end]!=backword_end)
            {
                solution.push_back(backword_visited [backword_end]);
                backword_end=backword_parent[backword_end];
            }
            solution.push_back(backword_visited[backword_end]);

            for(int k=0;k<solution.size();k++)
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
                if(k<solution.size()-1){
                    cout<<"   |"<<endl;
                    cout<<"  _|_"<<endl;
                    cout<<"  \\ /"<<endl;
                    cout<<"   `"<<endl;
                }
            }
        }
        else cout<<endl<<endl<<":( No Solution Found :("<<endl;

    /*
        for(int k=0;k<forword_visited .size();k++)
        {
            node vis=forword_visited [k];
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
        forword_visited.clear();
        backword_visited.clear();
        forword_parent.clear();
        backword_parent.clear();
        solution.clear();
    }
    return 0;
}
