<<<<<<< HEAD
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

class Edge{
public:
    int dest;
    double dist;
    double traf;
    double predWt;

    Edge(int dest,double dist,double traf){
        this->dest=dest;
        this->dist=dist;
        this->traf=traf;
        predWt=0.0;
    }
};

class Graph{
public:
    int numNodes;
    vector<vector<Edge>>adjList;

    void init(int n){
        numNodes=n;
        adjList.resize(n);
    }

    void addEdge(int u,int v,double distance,double traffic){
        Edge e(v,distance,traffic);
        adjList[u].push_back(e);
    }

    void displayGraph(){
        cout<<"Initail Graph\n";
        cout<<"From      To       Distance        Traffic\n";
        for(int u=0;u<numNodes;u++){
            for(int i=0;i<adjList[u].size();i++){
                Edge &e=adjList[u][i];
                cout<<u<<"          "<<e.dest<<"        "<<e.dist<<"         "<<e.traf<<"\n";
            }
        }
        cout<<endl;
    }

    void displayUpdatedGraph(){
        cout<<"Updated Graph:\n";
        cout<<"From  To  Distance  Traffic  PredictedTime\n";
        for(int u=0;u<numNodes;u++){
            for(int i=0;i<adjList[u].size();i++){
                Edge &e=adjList[u][i];
                cout<<u<<"     "<<e.dest<<"   "<<e.dist<<"       "<<e.traf<<"    "<<e.predWt<<endl;
            }
        }
    }
};

class LinReg{
public:
    double w1,w2,b;
    double alpha;
    int iter;

    void init(double a,int it){
        w1=0.1;
        w2=0.1;
        b=0.0;
        alpha=a;
        iter=it;
    }

    double computeLoss(vector<double>d,vector<double>t,vector<double>y){
        double loss=0.0;
        int n=d.size();
        for(int i=0;i<n;i++){
            double pred=w1*d[i]+w2*t[i]+b;
            double err=pred-y[i];
            loss=loss+(err*err);
        }
        return loss/n;
    }

    void train(vector<double>d,vector<double>t,vector<double>y){
        int n=d.size();
        for(int it=0;it<iter;it++){
            double dw1=0,dw2=0,db=0;
            for(int i=0;i<n;i++){
                double pred=w1*d[i]+w2*t[i]+b;
                double error=pred-y[i];
                dw1+=error*d[i];
                dw2+=error*t[i];
                db+=error;
            }
            w1=w1-(alpha*(2.0/n)*dw1);
            w2=w2-(alpha*(2.0/n)*dw2);
            b=b-(alpha*(2.0/n)*db);
        }
    }

    double predict(double dist,double traf){
        return w1*dist+w2*traf+b;
    }
};

vector<int> dijkstra(Graph &g,int source,int dest){
    int n=g.numNodes;
    vector<double> dist(n,1e9);
    vector<bool> visited(n,false);
    vector<int> parent(n,-1);
    dist[source]=0;

    for(int count=0;count<n-1;count++){
        int u=-1;
        double minDist=1e9;

        for(int i=0;i<n;i++){
            if(!visited[i]&&dist[i]<minDist){
                minDist=dist[i];
                u=i;
            }
        }

        if(u==-1)break;

        visited[u]=true;

        for(int i=0;i<g.adjList[u].size();i++){
            Edge &e=g.adjList[u][i];
            int v=e.dest;
            double weight=e.predWt;

            if(!visited[v]&&dist[u]+weight<dist[v]){
                dist[v]=dist[u]+weight;
                parent[v]=u;
            }
        }
    }

    vector<int> path;
    if(dist[dest]==1e9)return path;

    stack<int> st;
    int x=dest;
    while(x!=-1){
        st.push(x);
        x=parent[x];
    }

    while(!st.empty()){
        path.push_back(st.top());
        st.pop();
    }

    cout<<"Shortest Time: "<<dist[dest]<<endl;
    cout<<"Dijkstra Path: ";
    for(int i=0;i<path.size();i++){
        cout<<path[i];
        if(i+1<path.size())cout<<" -> ";
    }
    cout<<endl;

    return path;
}

void reconstructPath(Graph &g,vector<int>path){
    if(path.empty()){
        cout<<"No path found\n";
        return;
    }

    double totalDist=0,totalTime=0;
    cout<<"From To Dist Time\n";

    for(int i=0;i+1<path.size();i++){
        int u=path[i],v=path[i+1];

        for(int j=0;j<g.adjList[u].size();j++){
            if(g.adjList[u][j].dest==v){
                Edge &e=g.adjList[u][j];
                cout<<u<<"   "<<v<<"   "<<e.dist<<"   "<<e.predWt<<"\n";
                totalDist+=e.dist;
                totalTime+=e.predWt;
                break;
            }
        }
    }

    cout<<"\nFinal Route: ";
    for(int i=0;i<path.size();i++){
        cout<<path[i];
        if(i+1<path.size())cout<<" -> ";
    }

    cout<<"\nTotal Distance: "<<totalDist;
    cout<<"\nTotal Time: "<<totalTime;
}

int main(){
    cout<<"SMART TRAFFIC SYSTEM\n";

    Graph g;
    g.init(7);

    g.addEdge(0,1,5,0.2);
    g.addEdge(0,2,8,0.7);
    g.addEdge(1,3,4,0.3);
    g.addEdge(1,4,6,0.8);
    g.addEdge(1,2,2,0.1);
    g.addEdge(2,3,3,0.5);
    g.addEdge(2,5,7,0.4);
    g.addEdge(3,6,5,0.6);
    g.addEdge(4,6,4,0.2);
    g.addEdge(5,6,6,0.9);

    g.displayGraph();

    vector<double>d={5,8,4,6,3,7,5,4,6,2};
    vector<double>t={0.2,0.7,0.3,0.8,0.5,0.4,0.6,0.2,0.9,0.1};
    vector<double>y={7,18,7.5,20,8,14,13.5,6.5,22,4};

    LinReg lr;
    lr.init(0.001,1000);
    lr.train(d,t,y);

    for(int u=0;u<g.numNodes;u++){
        for(int i=0;i<g.adjList[u].size();i++){
            double p=lr.predict(g.adjList[u][i].dist,g.adjList[u][i].traf);
            if(p<1)p=1;
            g.adjList[u][i].predWt=p;
        }
    }

    g.displayUpdatedGraph();

    vector<int> path=dijkstra(g,0,6);
    reconstructPath(g,path);

    return 0;
=======
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

class Edge{
public:
    int dest;
    double dist;
    double traf;
    double predWt;

    Edge(int dest,double dist,double traf){
        this->dest=dest;
        this->dist=dist;
        this->traf=traf;
        predWt=0.0;
    }
};

class Graph{
public:
    int numNodes;
    vector<vector<Edge>>adjList;

    void init(int n){
        numNodes=n;
        adjList.resize(n);
    }

    void addEdge(int u,int v,double distance,double traffic){
        Edge e(v,distance,traffic);
        adjList[u].push_back(e);
    }

    void displayGraph(){
        cout<<"Initail Graph\n";
        cout<<"From      To       Distance        Traffic\n";

        for(int u=0;u<numNodes;u++){
            for(int i=0;i<adjList[u].size();i++){
                Edge &e=adjList[u][i];
                cout<<u<<"          "<<e.dest<<"        "<<e.dist<<"         "<<e.traf<<"\n";
            }
        }
        cout<<endl;
    }

    void displayUpdatedGraph(){
        cout<<"Updated Graph:\n";
        cout<<"From  To  Distance  Traffic  PredictedTime\n";

        for(int u=0;u<numNodes;u++){
            for(int i=0;i<adjList[u].size();i++){
                Edge &e=adjList[u][i];
                cout<<u<<"     "<<e.dest<<"   "<<e.dist<<"       "<<e.traf<<"    "<<e.predWt<<endl;
            }
        }
    }
};

class LinReg{
public:
    double w1,w2,b;
    double alpha;
    int iter;

    void init(double a,int it){
        w1=0.1;
        w2=0.1;
        b=0.0;
        alpha=a;
        iter=it;
    }

    double computeLoss(vector<double>d,vector<double>t,vector<double>y){
        double loss=0.0;
        int n=d.size();

        for(int i=0;i<n;i++){
            double pred=w1*d[i]+w2*t[i]+b;
            double err=pred-y[i];
            loss=loss+(err*err);
        }
        return loss/n;
    }

    void train(vector<double>d,vector<double>t,vector<double>y){
        int n=d.size();

        cout<<"\ntraining data\n";

        for(int it=0;it<iter;it++){
            double dw1=0,dw2=0,db=0;

            for(int i=0;i<n;i++){
                double pred=w1*d[i]+w2*t[i]+b;
                double error=pred-y[i];

                dw1=dw1+(error*d[i]);
                dw2=dw2+(error*t[i]);
                db=db+error;
            }

            w1=w1-(alpha*(2.0/n)*dw1);
            w2=w2-(alpha*(2.0/n)*dw2);
            b=b-(alpha*(2.0/n)*db);

            if(it%200==0||it==iter-1){
                cout<<"Iterations "<<it<<" Loss: "<<computeLoss(d,t,y)<<" w1: "<<w1<<" w2: "<<w2<<" b: "<<b<<"\n";
            }
        }
        cout<<"Training complete!\n";
    }

    double predict(double dist,double traf){
        return w1*dist+w2*traf+b;
    }
};

vector<int>BFS(Graph &g,int source,int dest){
    vector<bool>visited(g.numNodes,false);
    vector<int>parent(g.numNodes,-1);
    queue<int>q;

    cout<<"BFS Order: ";

    visited[source]=true;
    q.push(source);

    while(!q.empty()){
        int cur=q.front();
        q.pop();

        cout<<cur<<" ";

        if(cur==dest){
            break;
        }

        for(int i=0;i<g.adjList[cur].size();i++){
            int nb=g.adjList[cur][i].dest;

            if(!visited[nb]){
                visited[nb]=true;
                parent[nb]=cur;
                q.push(nb);
            }
        }
    }
    cout<<endl;

    vector<int>path;
    if(!visited[dest]){
        return path;
    }

    stack<int>st;
    int x=dest;
    while(x!=-1){
        st.push(x);
        x=parent[x];
    }

    while(!st.empty()){
        path.push_back(st.top());
        st.pop();
    }

    cout<<"BFS Path: ";
    for(int i=0;i<path.size();i++){
        cout<<path[i]<<" -> ";
    }
    return path;
}

void reconstructPath(Graph &g,vector<int>path){
    if(path.empty()){
        cout<<"No path found\n";
        return;
    }

    double totalDist=0,totalTime=0;
    cout<<"From To Dist Time\n";

    for(int i=0;i+1<path.size();i++){
        int u=path[i],v=path[i+1];

        for(int j=0;j<g.adjList[u].size();j++){
            if(g.adjList[u][j].dest==v){
                Edge &e=g.adjList[u][j];
                cout<<u<<"   "<<v<<"   "<<e.dist<<"   "<<e.predWt<<"\n";
                totalDist=totalDist+e.dist;
                totalTime=totalTime+e.predWt;
                break;
            }
        }
    }

    cout<<"\nFinal Route: ";
    for(int i=0;i<path.size();i++){
        cout<<path[i];
        if(i+1<path.size())cout<<" -> ";
    }

    cout<<"\nTotal Distance: "<<totalDist;
    cout<<"\nTotal Time: "<<totalTime;
}

int main(){
    cout<<"SMART TRAFFIC SYSTEM\n";

    Graph g;
    g.init(7);

    g.addEdge(0,1,5,0.2);
    g.addEdge(0,2,8,0.7);
    g.addEdge(1,3,4,0.3);
    g.addEdge(1,4,6,0.8);
    g.addEdge(1,2,2,0.1);
    g.addEdge(2,3,3,0.5);
    g.addEdge(2,5,7,0.4);
    g.addEdge(3,6,5,0.6);
    g.addEdge(4,6,4,0.2);
    g.addEdge(5,6,6,0.9);

    g.displayGraph();

    vector<double>d={5,8,4,6,3,7,5,4,6,2};
    vector<double>t={0.2,0.7,0.3,0.8,0.5,0.4,0.6,0.2,0.9,0.1};
    vector<double>y={7,18,7.5,20,8,14,13.5,6.5,22,4};

    LinReg lr;
    lr.init(0.001,1000);
    lr.train(d,t,y);

    for(int u=0;u<g.numNodes;u++){
        for(int i=0;i<g.adjList[u].size();i++){
            double p=lr.predict(g.adjList[u][i].dist,g.adjList[u][i].traf);
            if(p<1){
                p=1;
            }
            g.adjList[u][i].predWt=p;
        }
    }

    g.displayUpdatedGraph();

    vector<int>path=BFS(g,0,6);
    reconstructPath(g,path);

    return 0;
>>>>>>> 2b953d55a192d0224f6e29801679e2ff7ee490f6
}