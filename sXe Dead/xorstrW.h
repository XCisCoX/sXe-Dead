#pragma once
#undef KEY
#undef BUFLEN
template <int XORSTART, int BUFLEN, int XREFKILLER>
class XorStrW
{
private:
	XorStrW();
public:
	wchar_t s[BUFLEN];

	XorStrW(const wchar_t* xs);
#ifndef DEBUG_OPTION
	~XorStrW() {
		for (int i = 0; i < BUFLEN; i++)s[i] = 0;
	} 
#endif
};
template <int XORSTART, int BUFLEN, int XREFKILLER>
XorStrW<XORSTART, BUFLEN, XREFKILLER>::XorStrW(const wchar_t* xs)
{
	int xvalue = XORSTART;
	int i = 0;
	for (; i < (BUFLEN - 1); i++) {
		s[i] = xs[i - XREFKILLER] ^ xvalue;
		xvalue += 1;
		xvalue %= 256;
	}
	s[BUFLEN - 1] = 0;
}

