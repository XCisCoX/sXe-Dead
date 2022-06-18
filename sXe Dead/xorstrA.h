#pragma once
#undef KEY
#undef BUFLEN
template <int XORSTART, int BUFLEN, int XREFKILLER>
class XorStrA
{
private:
	XorStrA();
public:
	char s[BUFLEN];

	XorStrA(const char* xs);
#ifndef DEBUG_OPTION
	~XorStrA() {
		for (int i = 0; i < BUFLEN; i++)s[i] = 0;
	}
#endif
};
template <int XORSTART, int BUFLEN, int XREFKILLER>
XorStrA<XORSTART, BUFLEN, XREFKILLER>::XorStrA(const char* xs)
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

