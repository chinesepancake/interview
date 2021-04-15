#include <stdio.h>
#include <string.h>

#define MAX_POKER_NUM     5
#define NUM_HAND          2
#define NUM_INPUT_PARAM  (NUM_HAND + 1)

#define IT_IS_TIE         0
#define FIRST_HAND_WIN    1
#define SECOND_HAND_WIN   2

typedef struct {
	int type;
	int num;
}stPoker, *pstPoker;

int totalcardnum[15] = {0};

int poker_format(char *hand, pstPoker pokerset)
{
	int res = 0;
	int i = 0;
	int j = 0;
	int length = 0;
	char tmp = 0;
	int tmpnum = 0;
	pstPoker tmppoker = NULL;
	
	length = strlen(hand);
	if(length != MAX_POKER_NUM)
	{
		printf("Error! input poker's number is %d!\n", length);
		return -1;
	}
	
	for(i=0; i<MAX_POKER_NUM; i++)
	{
		tmp = hand[i];
	
		switch(tmp)
		{
			case '2': 
				tmpnum = 2;
				totalcardnum[2]++;
				break;
			case '3': 
				tmpnum = 3;
				totalcardnum[3]++;
				break;
			case '4': 
				tmpnum = 4;
				totalcardnum[4]++;
				break;
			case '5': 
				tmpnum = 5;
				totalcardnum[5]++;
				break;
			case '6': 
				tmpnum = 6;
				totalcardnum[6]++;
				break;
			case '7': 
				tmpnum = 7;
				totalcardnum[7]++;
				break;
			case '8': 
				tmpnum = 8;
				totalcardnum[8]++;
				break;
			case '9': 
				tmpnum = 9;
				totalcardnum[9]++;
				break;
			case 'T':
			case 't':			
				tmpnum = 10;
				totalcardnum[10]++;
				break;
			case 'J': 
			case 'j': 
				tmpnum = 11;
				totalcardnum[11]++;
				break;
			case 'Q': 
			case 'q': 
				tmpnum = 12;
				totalcardnum[12]++;
				break;
			case 'K': 
			case 'k': 
				tmpnum = 13;
				totalcardnum[13]++;
				break;
			case 'A': 
			case 'a': 
				tmpnum = 14;
				totalcardnum[14]++;
				break;
			default:
				printf("Error! card %d is not correct\n", i+1);
				return -1;
		}
		
		tmppoker = pokerset;
		
		for(j=0; j<=i; j++)
		{
			if(0 == tmppoker->num)
			{
				tmppoker->type = tmpnum;
				tmppoker->num = 1;
				break;
			}
			else if(tmpnum == tmppoker->type)
			{
				tmppoker->num++;
				break;
			} 
			else
			{
				tmppoker++;
			}
		}
	}
	
	for(j=0; j<15; j++)
	{
		if(totalcardnum[j] > 4)
		{
			printf("more than 4 pieces for total\n");
			return -1;
		}
	}

	return 0;
}


int poker_order(pstPoker pokerset)
{
	stPoker tmp = {0,0};
	pstPoker currentpoker = NULL;
	pstPoker nextpoker = NULL;
	int i = 0;
	int j = 0;
	
	for(i=0; i<MAX_POKER_NUM-1; i++)
	{
		currentpoker = pokerset;
		nextpoker = currentpoker + 1;

		for(j=0; j<(MAX_POKER_NUM-1-i); j++)
		{
			if(0 == currentpoker->type)
			{
				break;
			}
			
			if(currentpoker->num < nextpoker->num)
			{
				tmp.num = currentpoker->num;
				tmp.type = currentpoker->type;
				currentpoker->num = nextpoker->num;
				currentpoker->type = nextpoker->type;
				nextpoker->num = tmp.num;
				nextpoker->type = tmp.type;
			}
			else if(currentpoker->num == nextpoker->num)
			{
				if(currentpoker->type < nextpoker->type)
				{
					tmp.type = currentpoker->type;
					currentpoker->type = nextpoker->type;
					nextpoker->type = tmp.type;
				}
			}
			
			currentpoker++;
			nextpoker = currentpoker + 1;
		}
	}

	return 0;
}

int poker_judge(pstPoker lpokerset, pstPoker rpokerset, int *whowin)
{
	int result = 0;
	int i = 0;
	int llength = 0;
	int rlength = 0;
	pstPoker firsthand = NULL;
	pstPoker secondhand = NULL;
	
	firsthand = lpokerset;
	secondhand = rpokerset;
	
	for(i=0; i<MAX_POKER_NUM; i++)
	{
		if(0 != firsthand->num)
		{
			llength++;
			firsthand++;
		}
		
		if(0 != secondhand->num)
		{
			rlength++;
			secondhand++;
		}
	}
	
	if(llength > rlength)
	{
		printf("second hand length is short\n");
		result = SECOND_HAND_WIN;
		*whowin = result;
		return 0;
	}
	
	if(llength < rlength)
	{
		printf("first hand length is short\n");
		result = FIRST_HAND_WIN;
		*whowin = result;
		return 0;
	}
	
	//length is equal
	firsthand = lpokerset;
	secondhand = rpokerset;
	for(i=0; i<MAX_POKER_NUM; i++)
	{
		if(firsthand->num == secondhand->num)
		{
			if(firsthand->type == secondhand->type)
			{
				firsthand++;
				secondhand++;
				continue;
			}
			else if(firsthand->type > secondhand->type)
			{
				result = FIRST_HAND_WIN;
				*whowin = result;
				return 0;
			}
			else //firsthand->type < secondhand->type
			{
				result = SECOND_HAND_WIN;
				*whowin = result;
				return 0;
			}
		}
		else if(firsthand->num > secondhand->num)
		{
			result = FIRST_HAND_WIN;
			*whowin = result;
			return 0;
		}
		else //firsthand->num < secondhand->num
		{
			result = SECOND_HAND_WIN;
			*whowin = result;
			return 0;
		}
	}

	result = IT_IS_TIE;
	*whowin = result;
	return 0;
}


int main(int argc, char *argv[])
{
	int res = 0;
	int result = 0;
	stPoker firstpokerset[MAX_POKER_NUM];
	stPoker secondpokerset[MAX_POKER_NUM];

	if(NUM_INPUT_PARAM != argc)
	{
		printf("the number of input param error\n");
		return -1;
	}
	
	//printf("%s, %s, %d\n", argv[1], argv[2], argc);
	memset(firstpokerset, 0, sizeof(firstpokerset));
	memset(secondpokerset, 0, sizeof(secondpokerset));
	
	res = poker_format(argv[1], firstpokerset);
	if(res != 0)
	{
		printf("error, poker format for first hand abort\n");
		return res;
	}
	
	res = poker_format(argv[2], secondpokerset);
	if(res != 0)
	{
		printf("error, poker format for second hand abort\n");
		return res;
	}

	res = poker_order(firstpokerset);
	if(res != 0)
	{
		printf("error, poker order for first hand abort\n");
		return res;
	}
	
	res = poker_order(secondpokerset);
	if(res != 0)
	{
		printf("error, poker order for second hand abort\n");
		return res;
	}
	
	res = poker_judge(firstpokerset, secondpokerset, &result);
	if(res != 0)
	{
		printf("error, poker judge abort\n");
		return res;
	}
	
	if(FIRST_HAND_WIN == result)
	{
		printf("First hand wins!\n");
	}
	else if(SECOND_HAND_WIN == result)
	{
		printf("Second hand wins!\n");
	}
	else
	{
		printf("It's a tie!\n");
	}
	
	return 0;
}