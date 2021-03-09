#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* トークン番号は+, *，(, )はそれぞれのASCIIコードを使用 */
/* 数値はIDというトークンとして処理し，その番号は256を使用 */
#define	ID	256
#define MAXTOKEN	256
/* E1, T1はそれぞれE', T'の代わり */
#define	TBL_E 		0
#define	TBL_E1		1
#define	TBL_T		2
#define	TBL_T1		3
#define	TBL_F		4
#define N_BASE		10000
#define	E 		(N_BASE+TBL_E)
#define	E1		(N_BASE+TBL_E1)
#define	T		(N_BASE+TBL_T)
#define	T1		(N_BASE+TBL_T1)
#define	F		(N_BASE+TBL_F)
#define	NT_SIZE		5
#define	ACT_BASE	20000
#define	ACT_ID		(ACT_BASE+ID)
#define	ACT_ADD		(ACT_BASE+'+')
#define	ACT_MUL		(ACT_BASE+'*')
#define	STACK_SIZE	256

int token;
int tval;
int stack[STACK_SIZE];
int sp;

int isterm(int);
int isnonterm(int);
int isaction(int);
void puttoken(int);
void gettoken(void);
void error(void);

int* table[NT_SIZE][MAXTOKEN + 2]; // EOF(-1)からID(256)まで258

// 生成規則（スタックに1つずつ積むため，逆順）
// 「-1」は生成規則の終端（#defineしないのは記号と区別しやすくするため）
int RHS_0[] = { E1,T,-1 };		// E  ::= T E1
int RHS_1[] = { E1,ACT_ADD,T,'+',-1 };	// E1 ::= + T [+] E1
int RHS_2[] = { -1 };			// E1 ::= ε
int RHS_3[] = { T1,F,-1 };		// T  ::= F T1
int RHS_4[] = { T1,ACT_MUL,F,'*',-1 };	// T1 ::= * F [*] T1
int RHS_5[] = { -1 };			// T1 ::= ε
int RHS_6[] = { ')',E,'(',-1 };		// F  ::= ( E )
int RHS_7[] = { ACT_ID,ID,-1 };		// F  ::= i [i]

void inittable(void) {	// スライドp.23の構文解析表を配列で表現
	table[TBL_E][ID + 1] = RHS_0;	// +1はEOF(-1)を0にするため
	table[TBL_E]['(' + 1] = RHS_0;
	table[TBL_E1]['+' + 1] = RHS_1;
	table[TBL_E1][')' + 1] = RHS_2;
	table[TBL_E1][EOF + 1] = RHS_2;
	table[TBL_T][ID + 1] = RHS_3;
	table[TBL_T]['(' + 1] = RHS_3;
	table[TBL_T1]['+' + 1] = RHS_5;
	table[TBL_T1]['*' + 1] = RHS_4;
	table[TBL_T1][')' + 1] = RHS_5;
	table[TBL_T1][EOF + 1] = RHS_5;
	table[TBL_F][ID + 1] = RHS_7;
	table[TBL_F]['(' + 1] = RHS_6;

	stack[0] = EOF;
	stack[1] = E;			// 開始記号
	sp = 1;
}

void main(void) {
	int* p;

	inittable();
	gettoken();
	while (sp > 0) {
		if (isterm(stack[sp])) {
			if (stack[sp] == token) {
				stack[sp--] = 0;	// pop
				gettoken();
			}
			else {
				error();
			}
		}
		else if (isnonterm(stack[sp])) {
			if (p = table[stack[sp] - N_BASE][token + 1]) {
				stack[sp--] = 0;	// pop
				while (*p != -1) { // 「-1」は生成規則の終端
					stack[++sp] = *p++;	// push
					if (sp > STACK_SIZE) {
						fflush(stdout);
						fprintf(stderr, "Stack overflow!\n");
						exit(2);
					}
				}
			}
			else {
				error();
			}
		}
		else if (isaction(stack[sp])) {
			switch (stack[sp]) {
			case ACT_ID:
				puttoken(ID);
				break;
			case ACT_ADD:
				puttoken('+');
				break;
			case ACT_MUL:
				puttoken('*');
				break;
			default:
				error();
			}
			stack[sp--] = 0;	// pop
		}
		else {
			error();
		}
	}
	if (token != EOF) {
		error();
	}
}

void puttoken(int token) {
	switch (token) {
	case ID:
		printf("%d ", tval);
		break;
	case EOF:
		printf("\n");
		break;
	default:
		printf("%c ", token);
	}
}

void error() {
	fflush(stdout);
	if (token == ID) {
		fprintf(stderr, "\nError occurs when reading token %d.\n", tval);
	}
	else {
		fprintf(stderr, "\nError occurs when reading token '%c'.\n", token);
	}
	exit(1);
}

void gettoken(void) {
	int ch;
	while ((ch = getchar()) == ' ' || ch == '\t') { // skip white spaces
		continue;
	}
	if (isdigit(ch)) {
		tval = 0;
		do {
			tval *= 10;
			tval += ch - '0';
		} while (isdigit(ch = getchar()));
		ungetc(ch, stdin);
		token = ID;
		return;
	}
	else {
		switch (ch) {
		case '+':
		case '*':
		case '(':
		case ')':
			token = ch;
			return;
		case '\n':
		case '\r':
		case EOF:
			token = EOF;
			return;
		default:
			fprintf(stderr, "incorrect char: %c\n", ch);
			exit(1);
		}
	}
}

int isterm(int x) {
	return x < N_BASE;
}

int isnonterm(int x) {
	return x >= N_BASE && x < ACT_BASE;
}

int isaction(int x) {
	return x >= ACT_BASE;
}