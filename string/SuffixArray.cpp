#define mem(a,b) memset(a,b,sizeof(a))
//传入SA_s，以及数组长度L和字符集大小mx（1..mx），得到数组sa,rank,height.
//SuffixArray
int SA_s[sz*2],sa[sz*2],rank[sz*2],height[sz*2];
int radix[sz*2],tsa[sz*2],trank[sz*2];
void SuffixArray(int L,int mx)
{
    int i,j,k,kind;
	mem(sa,0); mem(rank,0); mem(height,0); mem(radix,0);
	for(i=1;i<=L;i++) radix[SA_s[i]]++;
	for(i=1;i<=mx;i++) radix[i]+=radix[i-1];
	for(i=L;i>=1;i--) sa[radix[SA_s[i]]--]=i;
	for(i=1;i<=L;i++)
		if(i==1) rank[sa[i]]=kind=1;
		else if(SA_s[sa[i]]==SA_s[sa[i-1]]) rank[sa[i]]=kind;
		else rank[sa[i]]=++kind;
	for(k=1;k<L&&kind<L;k*=2)
	{
        memset(radix,0,sizeof(radix));
		for(i=1;i<=L;i++) radix[rank[i+k]]++;
		for(i=1;i<=L;i++) radix[i]+=radix[i-1];
		for(i=L;i>=1;i--) tsa[radix[rank[i+k]]--]=i;

		memset(radix,0,sizeof(radix));
		for(i=1;i<=L;i++) radix[rank[i]]++;
		for(i=1;i<=L;i++) radix[i]+=radix[i-1];
		for(i=L;i>=1;i--) sa[ radix[rank[tsa[i]]]-- ]=tsa[i];

		for(i=1;i<=L;i++)
			if(i==1) trank[sa[i]]=kind=1;
			else if(rank[sa[i]]==rank[sa[i-1]]&&rank[sa[i]+k]==rank[sa[i-1]+k]) trank[sa[i]]=kind;
			else trank[sa[i]]=++kind;
		for(i=1;i<=L;i++) rank[i]=trank[i];
	}
	for(i=1,k=0;i<=L;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];SA_s[i+k]==SA_s[j+k];k++);
/*	printf("SA_S\n"); for(i=1;i<=L;i++){printf("[%d]_%d ",i,SA_s[i]); if(i%10==0) printf("\n");} printf("\n");
	printf("SuffixArray\n"); for(i=1;i<=L;i++){printf("[%d]_%d ",i,sa[i]); if(i%10==0) printf("\n");} printf("\n");
	printf("Rank\n"); for(i=1;i<=L;i++){printf("[%d]_%d ",i,rank[i]); if(i%10==0) printf("\n");} printf("\n");
	printf("Height\n"); for(i=1;i<=L;i++){printf("[%d]_%d ",i,height[i]); if(i%10==0) printf("\n");} printf("\n");
*/
}
//传入height数组 和 数组长度 n ，得到区间最小值数组 rmq
int rmq[sz*2*2][25];
void RMQ(int n)
{
    int i,j,k;
	memset(rmq,0,sizeof(rmq));
	for(k=0;(1<<k)<=n;k++)
		for(i=1;i<=n;i++)
			if(k==0) rmq[i][k]=height[i];
			else if(i+(1<<k-1)>n) rmq[i][k]=rmq[i][k-1];
			else rmq[i][k]=min(rmq[i][k-1],rmq[i+(1<<k-1)][k-1]);
}
int get_rmq(int i,int j)
{
    if(i>j){int t=i; i=j; j=t;}
	for(int k=0;(1<<k)<=j-i+1;k++)
		if(i+(1<<k)>j-(1<<k)) return min(rmq[i][k],rmq[j-(1<<k)+1][k]);
}
//SuffixArray
