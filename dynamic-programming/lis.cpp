// Longest Increasing Subsequence - O(nlogn)
int dp[N], a[N], n, ans=0, mx;
memset(dp, 63, sizeof dp); mx = dp[0];
for (int i = 0; i < n; ++i) *lower_bound(dp, dp + n, a[i]) = a[i]; 
while (n && dp[ans] != mx) ++ans;