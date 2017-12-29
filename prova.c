#include <stdio.h>
#include <string.h>

int IntToStr(int valin, int base, char *strout, int dimstr)
{
	int i;
	int len;
	char c;
	short idx;
	char *digit = "0123456789ABCDEF";

	/* verifica dei parametri, stringa lunga almeno 2 caratteri e base compresa fra 2 e 16 */
	if (dimstr < 2)
		return 0;

	if ((base < 2) || (base > 16))
	{
		strcpy(strout, "");
		return 0;
	}
	
	/* esegue la conversione delle cifre */
	i = 0;
	do
	{
		idx = valin % base;
		strout[i] = digit[idx];
		valin = valin / base;
		i++;

		if (i == (dimstr - 1))	/* verifichiamo di non sforare */
			break;
	} while (valin > 0);

	if (valin > 0)	/* se siamo usciti senza poter esprimere tutti i bit */
	{
		strcpy(strout, "");
		return 0;
	}

	len = i;
	strout[len] = '\0'; 

	/* inversione della stringa */
	for (i = 0; i < len / 2; i++)
	{
		c = strout[i];
		strout[i] = strout[len-i-1];
		strout[len-i-1] = c;
	}
	
	return 1;
}

int IntToStrRec2(int valin, int base, char *strout, int dimstr, int *currlen);

int IntToStrRec(int valin, int base, char *strout, int dimstr)
{
	int currlen = 0;
	int ret;

	if (dimstr < 2)
		return 0;

	if ((base < 2) || (base > 16))
	{
		strcpy(strout, "");
		return 0;
	}

	ret = IntToStrRec2(valin, base, strout, dimstr, &currlen);
	if (ret == 0)
		strout[0] = '\0';
	return ret;
}

int IntToStrRec2(int valin, int base, char *strout, int dimstr,int *currlen)
{
	int ret;
	char *digit = "0123456789ABCDEF";

	if (valin < base)
	{
		strout[0] = digit[valin];
		strout[1] = '\0';

		*currlen = 1;
	}
	else
	{
		ret = IntToStrRec2(valin / base, base, strout, dimstr, currlen);
		if (ret == 0)
			return ret;

		if (*currlen >= (dimstr - 1))
			return 0;

		strout[*currlen] = digit[valin%base];
		strout[(*currlen)+1] = '\0';

		(*currlen)++;
	}
	return 1;
}

void main()
{
	int i;
	char binstr[10];
	char octstr[10];
	char hexstr[10];

//	IntToStrRec(12, 2, binstr, 10);
//	printf("%d %s\n", 12, binstr);

	for (i = 0; i <= 256; i++)
	{
		IntToStr(i, 2, binstr, 10);
		IntToStr(i, 8, octstr, 10);
		IntToStr(i, 16, hexstr, 10);
		//		IntToStrRec(i, 2, binstr, 8);
		printf("%d %o %X %s\n", i, i, i, binstr);
//		printf("%d %s %s %s\n", i, octstr, hexstr, binstr);
	}
}

