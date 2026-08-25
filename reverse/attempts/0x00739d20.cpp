// ?func00739D20@@YAHH_N@Z
// partial score=0.9 date=2026-08-25

int func00739D20( int a, bool b )
{
	int result = 0;
	if ( (unsigned int)(a - 20) <= 4 )
	{
		switch ( a )
		{
		case 20:
			result = b ? 5 : 2;
			break;
		case 21:
			result = 2;
			break;
		case 22:
			result = 1;
			break;
		case 23:
			result = 3;
			break;
		case 24:
			result = 4;
			break;
		}
	}
	return result;
}
