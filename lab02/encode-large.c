#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SYMBOLS 256
#define MAX_LEN 256

struct tnode {
    struct tnode* left;   /*used when in tree*/
    struct tnode* right;  /*used when in tree*/
    struct tnode* parent; /*used when in tree*/
    struct tnode* next;   /*used when in list*/
    float freq;
    int isleaf;
    char symbol;
};

/*global variables*/
char code[MAX_SYMBOLS][MAX_LEN];
struct tnode* root = NULL;  /*tree of symbols*/
struct tnode* qhead = NULL; /*list of current symbols*/
struct cnode* chead = NULL; /*list of code*/

/*
    @function   talloc
    @desc       allocates new node 
*/
struct tnode* talloc(int symbol, float freq)
{
    struct tnode* p = (struct tnode*)malloc(sizeof(struct tnode));
    if (p != NULL) {
        p->left = p->right = p->parent = p->next = NULL;
        p->symbol = symbol;
        p->freq = freq;
        p->isleaf = 1;
    }
    return p;
}

/*
    @function display_tnode_list
    @desc     displays the list of tnodes during code construction
*/
void pq_display(struct tnode* head)
{
    struct tnode* p = NULL;
    printf("list:");
    for (p = head; p != NULL; p = p->next) {
        printf("(%c,%f) ", p->symbol, p->freq);
    }
    printf("\n");
}

/*
    @function pq_insert
    @desc     inserts an element into the priority queue
    NOTE:     makes use of global variable qhead
*/
void pq_insert(struct tnode* p)
{
    struct tnode* curr = NULL;
    struct tnode* prev = NULL;
    printf("inserting:%c,%f\n", p->symbol, p->freq);
    if (qhead == NULL) /*qhead is null*/
    {
        /*write code to insert when queue is empty*/
        qhead = p;
        return;
    }
    /* write code to find correct position to insert*/
    curr = qhead;
    while (curr != NULL) {
        if (curr->freq < p->freq) {
            prev = curr;
            curr = curr->next;
        } else {
            break;
        }
    }

    if (curr == qhead) {
        /*write code to insert before the current start*/
        p->next = qhead;
        qhead = p;
    } else /*insert between prev and next*/
    {
        /*write code to insert in between*/
        prev->next = p;
        p->next = curr;
    }
}

/*
    @function pq_pop
    @desc     removes the first element
    NOTE:     makes use of global variable qhead
*/

struct tnode* pq_pop()
{
    struct tnode* p = NULL;
    /*write code to remove front of the queue*/
    if (qhead) {
        p = qhead;
        qhead = qhead->next;
        p->next = NULL;
        printf("popped:%c,%f\n", p->symbol, p->freq);
    }
    return p;
}

/*
	@function build_code
	@desc     generates the string codes given the tree
	NOTE: makes use of the global variable root
*/
void generate_code(struct tnode* root, int depth)
{
    int symbol;
    int len; /*length of code*/
    if (root->isleaf) {
        symbol = root->symbol;
        len = depth;
        /*start backwards*/
        code[(unsigned char)symbol][len] = 0;
        /*
			follow parent pointer to the top
			to generate the code string
		*/
        for (; len > 0; --len) {
            if (root == root->parent->left) {
                code[(unsigned char)symbol][len - 1] = '0';
            } else if (root == root->parent->right) {
                code[(unsigned char)symbol][len - 1] = '1';
            }
            root = root->parent;
        }
        printf("built code:%c,%s\n", symbol, code[(unsigned char)symbol]);
    } else {
        generate_code(root->left, depth + 1);
        generate_code(root->right, depth + 1);
    }
}

/*
	@func	dump_code
	@desc	output code file
*/
void dump_code(FILE* fp)
{
    int i = 0;
    for (i = 0; i < MAX_SYMBOLS; i++) {
        if (code[i][0]) /*non empty*/
            fprintf(fp, "%c %s\n", i, code[i]);
    }
}

/* 
 *  @func   encodechar
 *  @desc   outputs compressed character
 */
void encodechar(char ch, FILE* fout)
{
    fprintf(fout, "%s", code[(unsigned char)ch]);
}

/*
	@func	encode
	@desc	outputs compressed stream
*/
void encode(char* str, FILE* fout)
{
    while (*str) {
        fprintf(fout, "%s", code[(unsigned char)*str]);
        str++;
    }
}
/*
	@function freetree
	@desc	  cleans up resources for tree
*/

void freetree(struct tnode* root)
{
    if (root == NULL)
        return;
    freetree(root->right);
    freetree(root->left);
    free(root);
}
/*
    @function main
*/
int main()
{
    /*test pq*/
    struct tnode* p = NULL;
    struct tnode *lc, *rc;
    int NCHAR = 256; /*number of characters*/
    int print_char_count = 0;
    float freq[NCHAR];
    int i = 0;
    const char* CODE_FILE = "code.txt";
    const char* OUT_FILE = "encoded.txt";
    const char* IN_FILE = "book.txt";
    FILE* fin = NULL;
    FILE* fout = NULL;
    char ch;
    /*zero out code*/
    memset(code, 0, sizeof(code));

    /* calculate freq */
    for (i = 0; i < NCHAR; ++i) {
        freq[i] = 0;
    }
    fin = fopen(IN_FILE, "r");
    while ((ch = fgetc(fin)) != EOF) {
        if (isprint(ch)) {
            freq[(unsigned char)ch]++;
        }
    }

    qhead = NULL;
    /*initialize with freq*/
    for (i = 0; i < NCHAR; i++) {
        if (freq[i]) {
            pq_insert(talloc(i, freq[i]));
            print_char_count++;
        }
    }
    /*build tree*/
    for (i = 0; i < print_char_count - 1; i++) {
        lc = pq_pop();
        rc = pq_pop();
        /*create parent*/
        p = talloc(0, lc->freq + rc->freq);
        /*set parent link*/
        lc->parent = rc->parent = p;
        /*set child link*/
        p->right = rc;
        p->left = lc;
        /*make it non-leaf*/
        p->isleaf = 0;
        /*add the new node to the queue*/
        pq_insert(p);
    }
    /*get root*/
    root = pq_pop();
    /*build code*/
    generate_code(root, 0);
    /*output code*/
    puts("code:");
    fout = fopen(CODE_FILE, "w");
    dump_code(stdout);
    dump_code(fout);
    fclose(fout);

    /*encode book.txt*/
    if (fseek(fin, 0L, SEEK_SET) != 0) {
        printf("fseek error\n");
    }
    fout = fopen(OUT_FILE, "w");
    printf("src:\n");
    while ((ch = fgetc(fin)) != EOF) {
        printf("%c %d\n", ch, ch);
        encodechar(ch, fout);
    }
    printf("\n");
    fclose(fout);
    getchar();
    /*clear resources*/
    freetree(root);

    return 0;
}
