vector<ll> inv(vector<ll> a){
	int m = a.size();
	vector<ll> res(1, modpow(a[0], mod - 2));
	for(int n = 2; n / 2 < m; n <<= 1){
		if(a.size() < n) a.resize(n);
		vector<ll> v1(a.begin(), a.begin() + n), v2 = res;
		v1.resize(n * 2), v2.resize(n * 2);
		ntt(v1, n * 2), ntt(v2, n * 2);
		for(int i = 0; i < n * 2; ++i) v1[i] = mul(mul(v1[i], v2[i]), v2[i]);
		ntt(v1, n * 2, 1);
		vector<ll> nres(n);
		for(int i = 0; i < n / 2; ++i) nres[i] = add(res[i], res[i]);
		for(int i = 0; i < n; ++i) nres[i] = sub(nres[i], v1[i]);
		res = nres;
	}
	res.resize(m);
	return res;
}