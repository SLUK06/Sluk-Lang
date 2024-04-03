#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEXEME_SIZE 100

// Enumeração para os tipos de token
typedef enum {
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_IDENTIFIER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_OPARENT,
    TOKEN_CPARENT,
    TOKEN_EOF,
    TOKEN_INVALID
} TokenType;

// Estrutura para representar um token
typedef struct {
    TokenType type;
    char lexeme[MAX_LEXEME_SIZE];
} Token;

// Função para verificar se um caractere é um delimitador
int is_delimiter(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
}

// Função para verificar se um caractere é um operador
int is_operator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')';
}

// Função para verificar se um caractere é um dígito
int is_digit(char ch) {
    return ch >= '0' && ch <= '9';
}

// Função para verificar se um caractere é uma letra
int is_alpha(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

// Função para retornar o tipo de token para um lexema
TokenType get_token_type(char *lexeme) {
    if (strcmp(lexeme, "+") == 0) return TOKEN_PLUS;
    if (strcmp(lexeme, "-") == 0) return TOKEN_MINUS;
    if (strcmp(lexeme, "*") == 0) return TOKEN_MULTIPLY;
    if (strcmp(lexeme, "/") == 0) return TOKEN_DIVIDE;
    if (strcmp(lexeme, "(") == 0) return TOKEN_OPARENT;
    if (strcmp(lexeme, ")") == 0) return TOKEN_CPARENT;
    if (is_digit(lexeme[0])) return TOKEN_INT;
    if (is_alpha(lexeme[0])) return TOKEN_IDENTIFIER;
    return TOKEN_INVALID;
}

// Função para tokenizar a entrada
Token* tokenize(char *input) {
    Token *tokens = malloc(sizeof(Token) * MAX_LEXEME_SIZE);
    char lexeme[MAX_LEXEME_SIZE];
    int i = 0, j = 0, k = 0;

    while (input[i] != '\0') {
        if (is_delimiter(input[i])) {
            i++;
            continue;
        }

        if (is_operator(input[i])) {
            lexeme[0] = input[i];
            lexeme[1] = '\0';
            tokens[k].type = get_token_type(lexeme);
            strcpy(tokens[k].lexeme, lexeme);
            i++;
            k++;
            continue;
        }

        while (input[i] != '\0' && !is_delimiter(input[i]) && !is_operator(input[i])) {
            lexeme[j++] = input[i++];
        }
        lexeme[j] = '\0';
        tokens[k].type = get_token_type(lexeme);
        strcpy(tokens[k].lexeme, lexeme);
        j = 0;
        k++;
    }

    tokens[k].type = TOKEN_EOF;
    strcpy(tokens[k].lexeme, "");
    
    return tokens;
}

// Função auxiliar para imprimir os tokens
void print_tokens(Token *tokens) {
    int i = 0;
    while (tokens[i].type != TOKEN_EOF) {
        printf("Type: %d, Lexeme: %s\n", tokens[i].type, tokens[i].lexeme);
        i++;
    }
}

int main(int argc, char *argv[]) {
    //verifica se o numero de argumentos esta correto
    if (argc != 2) {
        printf("Uso: %s <nome_do_arquivo>\n", argv[0]);
        return 1; // Terminar o programa com código de erro
    }

    // Abrir o arquivo para leitura
    FILE *arquivo = fopen(argv[1], "r");

    // Verificar se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1; // Terminar o programa com código de erro
    }

    // Ler o conteúdo do arquivo
    char linha[MAX_LEXEME_SIZE];
    char input[MAX_LEXEME_SIZE * 10]; // Tamanho arbitrário para a entrada
    strcpy(input, "");
    while (fgets(linha, MAX_LEXEME_SIZE, arquivo) != NULL) {
        strcat(input, linha);
    }

    // Fechar o arquivo após terminar de usá-lo
    fclose(arquivo);

    // Tokenizar o conteúdo do arquivo
    Token *tokens = tokenize(input);

    print_tokens(tokens);

    // Liberar memória alocada para os tokens
    free(tokens);

    return 0;
}
