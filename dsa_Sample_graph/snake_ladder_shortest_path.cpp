public:
    int minThrow(int N, int arr[]){
        int moves[35];
        bool vis[35];
        memset(moves, -1, sizeof(moves));
        memset(vis, false, sizeof(vis));
        for(int i = 0;i < 2*N;i += 2)
            moves[arr[i]] = arr[i+1];
        
        queue<pair<int, int>> q;
        pair<int, int> p;
        q.push({1, 0});
        vis[1] = true;
        while(!q.empty()){
    		p = q.front();
    		int ii = p.first;
    		int ss = p.second;
    		if(ii == 30)
    		break;
    		q.pop();
    		for(int i = ii+1;i <= ii+6 && i <= 30;i++){
    			pair<int,int> pp;
    			if(!vis[i]){
    				pp.second = ss+1;
    				vis[i] = true;
    				if(moves[i] != -1)
    					pp.first = moves[i];
    				else
    				    pp.first = i;
    				q.push(pp);
    			}
    		}
    	}
    	return p.second;
    }
};