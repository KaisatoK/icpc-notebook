// Sieve of Erasthotenes
int lp[N]; vector<int> primes;

for (ll i = 2; i <= N; ++i) {
	if (!lp[i]) lp[i] = i, primes.pb(i);
	for(int j = 0; j < prime.size() && pr[j] <= lp[i] && i * pr[j] < N; ++j)
		lp[i * pr[j]] = pr[j];
}
