/**
 * Consegna 6
 * @author Andrea Storci
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>

/// KEYWORDS
const std::string conditionals[] = { "if", "else", "switch", "case", "default" }; const size_t size_conds = sizeof(conditionals) / sizeof(conditionals[0]);
const std::string loops[] = { "do", "for", "while" }; const size_t size_loops = sizeof(loops) / sizeof(loops[0]);

/// VARS
const std::string numbers[] = { "int", "float", "double", "long", "long int", "long long", "long double", "long float" }; const size_t size_numbers = sizeof(numbers) / sizeof(numbers[0]);
const std::string chars[] = { "std::string", "string", "char" }; const size_t size_chars = sizeof(chars) / sizeof(chars[0]);
const std::string bools[] = { "bool" }; const size_t size_bools = sizeof(bools) / sizeof(bools[0]);
const std::string voids[] = { "void" }; const size_t size_voids = sizeof(voids) / sizeof(voids[0]);

enum SCORING_RULES {
    EMATCH_SCOPE    = +10,  // Match esatto dei blocchi
    EMATCH_VAR      = +4,   // Match esatto di due variabili
    RENAMING        = +1,   // Rinomina di una variabile

    GAP_PENALTY     = -2,   // Penalita' per elimina/inserimento di una nuova riga (token)
    MISMATCH_LIGHT  = -1,   // Mismatch lieve
    MISMATCH_SEVERE = -5,   // Mismatch pesante

    NO_SCORE        = 0,
};
typedef SCORING_RULES ScoringRules_t;

enum TOKEN_TYPE {
    /// Valori testuali/generici
    DIRECTIVES, // #include <libreria>, #define <qualcosa>
    IDENTIFIER, // nome della variabile o funzione
    NUMBER,     // valore numerico
    STRING,     // valore testuale
    POINTER,    // puntatore
    OPERATOR,   // +, -, *, /, ==, =, ...
    SEMICOLON,  // ;

    /// Parole chiave del linguaggio
    TYPE,       // tipo della variabile: int, float, double, ...
    KEYWORD,    // if, else, for, while, return, class, ...
    OBRACE,     // {
    CBRACE,     // }
    OPAREN,     // (
    CPAREN,     // )

    UNKNOWN,    // da cpaire come gestire
    EMPTY = -1,
};
typedef TOKEN_TYPE TokenType_t;

/// solo per visualizzare meglio il tipo di token
std::string tokenToString(TokenType_t t);

/// Nodo della lista
struct node;
typedef node node_t;

/// Lista contente i tokens
struct queue;
typedef queue queue_t;

/// Struttura del token per identificare i vari elementi
/// del file che leggo.
/// I nomi degli identificatori possono essere:
/// * `IDENTIFIER`: consiste nel nome della variabile
/// * `TYPE`: consiste nel tipo della variabile
/// * `NUMBER`: consiste nel valore numerico
/// * `STRING`: consiste nel valore testuale
/// * `OTHER`: ancora da definire
struct token;
typedef token token_t;

/// Funzioen che controlla se una delle stringhe contenute in `keys`
/// e' contenuta in `val`
/// @param size Dimensione dell'array `keys`
/// @param keys Array di stringhe
/// @param val  Stringa da controllare
bool oneOf(int size, const std::string keys[], const std::string& val);

/// Funzione di parsing
///
/// @param file_name
/// @return
queue_t* parser(const std::string& file_name);
/// Serve per assgeneare il tipo del token in base alla stringa letta
TokenType_t parserAux(queue_t* tokens, std::string& str);

/// Calcola la similarita' tra due token e ritorna
/// il valore della similarita' che puo' essere una tra quelle
/// presenti nella enumeration TOKEN_TYPE
/// @param t1 Primo token
/// @param t2 Secondo token
/// @return TOKEN_TYPE
ScoringRules_t similarity(token_t* t1, token_t* t2);

/// Algoritmo di Needleman-Wunsch
void needlemanWunsch(std::string fname_source, std::string fname_new);

struct token {
    TokenType_t key;
    char val[64] = "\0";
    int line; // non so se usarlo

    void print() {
        std::cout << "[" << tokenToString(key) << ": " << val << "]" << std::endl;
    }
};

struct node {
    token_t * data = nullptr;
    node* next = nullptr;
};

struct queue {
    size_t size = 0;
    node* head = nullptr;
    node* tail = nullptr;

    void push(token_t* data) {
        auto new_node = new node{data};

        if (this->head == nullptr) {
            this->head = this->tail = new_node;
        } else {
            this->tail->next = new_node;
            this->tail = new_node;
        }

        ++size;
    }

    token_t* pop() {
        if (this->head == nullptr)
            return nullptr;

        auto temp = this->head;
        auto ret = temp->data;

        this->head = this->head->next;

        if (this->head == nullptr) {
            this->tail = nullptr;
        }

        delete temp;
        --size;
        return ret;
    }

    token_t** c_array() {
        auto ogSize = size;
        auto ret = new token_t*[ogSize + 1];
        for (int i = 0; i < ogSize; ++i)
            ret[i + 1] = this->pop();

        ret[0] = nullptr; // lo faccio per gestire meglio

        return ret;
    }

    void print() {
        auto current = head;
        while (current != nullptr) {
            current->data->print();
            current = current->next;
        }
    }
};

std::string tokenToString(TokenType_t t) {
    switch (t) {
        case DIRECTIVES: return "DIRECTIVES";
        case IDENTIFIER: return "IDENTIFIER";
        case NUMBER: return "NUMBER";
        case STRING: return "STRING";
        case POINTER: return "POINTER";
        case OPERATOR: return "OPERATOR";
        case SEMICOLON: return "SEMICOLON";
        case TYPE: return "TYPE";
        case KEYWORD: return "KEYWORD";
        case OBRACE: return "OBRACE";
        case CBRACE: return "CBRACE";
        case CPAREN: return "CPAREN";
        case OPAREN: return "OPAREN";
        case EMPTY: return "EMPTY";
        default: return "UNKNOWN";
    }
}

void printArray(int* A, int n) {
    for (int i = 0; i < n - 1; ++i)
        std::cout << A[i] << ", ";
    std::cout << A[n - 1] << std::endl;
}

void printMatrix(int* A, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << A[i * m + j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {

    { /// TEST 1
        const std::string f1 = "tests/source.cpp";
        const std::string f2 = "tests/test001.cpp";

        needlemanWunsch(f1, f2);
    }
}

// variabile che utilizzo per controllare che l'elemento precedente
// era un token di tipo "TYPE" (ovvero, "tipo della variabiale")
bool is_type_var = false;

queue_t* parser(const std::string& file_name) {
    std::ifstream stream;
    stream.open(file_name);

    if (!stream.is_open())
        return nullptr;

    auto tokens_source = new queue_t;

    char c;
    std::string temp;
//    TokenType_t parsedRet;

    /// Parsing del fiel source
    while (stream.get(c)) {
        /// controllo per le direttive
        if (c == '#') {
            if (!temp.empty())
                parserAux(tokens_source, temp);

            temp += c;
            while (stream.get(c) && c != '\n')
                temp += c;

            parserAux(tokens_source, temp);
            continue;
        }

        /// controollo per le stringhe
        if (c == '"') {
            if (!temp.empty())
                parserAux(tokens_source, temp);

            temp += c;
            while (stream.get(c) && c != '"')
                temp += c;
            temp += '"';

            parserAux(tokens_source, temp);
            continue;
        }

        /// quando finisce una parola
        if (c == ' ' || c == '\t' || c == '\n') {
            if (!temp.empty()) {
                parserAux(tokens_source, temp);
                temp.clear();
            }
            continue;
        }

        /// controllo per caratteri specioali
        if (c == '{' || c == '}' || c == '(' || c == ')' || c == ';' ||
            c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=') {

            if (!temp.empty())
                parserAux(tokens_source, temp);

            if (is_type_var && c == '*') {
                temp = c;
                parserAux(tokens_source, temp);
            } else {
                char single_char[2] = {c, '\0'};
                TokenType_t t_type;

                if (c == '{') t_type = OBRACE;
                else if (c == '}') t_type = CBRACE;
                else if (c == '(') t_type = OPAREN;
                else if (c == ')') t_type = CPAREN;
                else if (c == ';') t_type = SEMICOLON;
                else t_type = OPERATOR;

                auto new_token = new token_t();
                new_token->key = t_type;
                std::strncpy(new_token->val, single_char, 64);

                tokens_source->push(new_token);
            }
        } else {
            temp += c;
        }
    }

    if (!temp.empty())
        parserAux(tokens_source, temp);

    tokens_source->print();

    stream.close();
    return tokens_source;
}

TokenType_t parserAux(queue_t* tokens, std::string& str) {
    if (str.empty())
        return EMPTY;

    TokenType_t type;

    // Valori con un solo carattere
    if (is_type_var && str[0] == '*') {
        type = POINTER;
    } else if (oneOf(size_loops, loops, str) || oneOf(size_conds, conditionals, str)) {
        is_type_var = false;
        type = KEYWORD;
    } else if (oneOf(size_numbers, numbers, str) || oneOf(size_chars, chars, str) || oneOf(size_bools, bools, str) || oneOf(size_voids, voids, str)) {
        is_type_var = true;
        type = TYPE;
    } else if (str[0] >= '0' && str[0] <= '9') {
        is_type_var = false;
        type = NUMBER;
    } else if (str[0] == '"') {
        is_type_var = false;
        type = STRING;
    } else if (str[0] == '#') {
        type = DIRECTIVES;
    } else {
        is_type_var = false;
        type = IDENTIFIER;
    }

    auto new_token = new token_t{type};
    std::strncpy(new_token->val, str.c_str(), 64);
    tokens->push(new_token);

    // cancello la stringa
    str.clear();

    return type;
}

bool oneOf(int size, const std::string keys[], const std::string& val) {
    for (int i = 0; i <= size; ++i)
        if (val == keys[i])
            return true;

    return false;
}

ScoringRules_t similarity(token_t* t1, token_t* t2) {

    if (t1 == nullptr || t2 == nullptr)
        return NO_SCORE;

//    std::cout << "Token1: " << t1->key  << ", \"" << t1->val << "\"";
//    std::cout << "; Token2: " << t2->key  << ", \"" << t2->val << "\"" << std::endl;

    /// Gestisco il caso inj cui il tipo dei token sia uguale
    if (t1->key == t2->key) {
        /// gestisco lo score per il token con tipo "VARIABILE"
        if (t1->key == TYPE) {
            if (strcmp(t1->val, t2->val) == 0)
                return EMATCH_VAR; /// nel caso ci sia un match esatto di due variabili

            bool checkT1_numbers = oneOf(4, numbers, t1->val);
            bool checkT2_numbers = oneOf(4, numbers, t2->val);

            bool checkT1_chars = oneOf(2, chars, t1->val);
            bool checkT2_chars = oneOf(2, chars, t2->val);

            bool checkT1_bool = oneOf(1, bools, t1->val);
            bool checkT2_bool = oneOf(1, bools, t2->val);

            /// controllo che ci sia stato un cambio di tipo sempre numerico oppure letterale
            if ((checkT1_numbers && checkT2_numbers) || (checkT1_chars && checkT2_chars))
                return MISMATCH_LIGHT;
            if ((checkT1_numbers && checkT2_chars) || (checkT1_chars && checkT2_numbers))
                return MISMATCH_SEVERE;
            if ((checkT1_numbers && checkT2_bool) || (checkT1_bool && checkT2_numbers))
                return MISMATCH_SEVERE;
            if ((checkT1_chars && checkT2_bool) || (checkT1_bool && checkT2_chars))
                return MISMATCH_SEVERE;
        }
        /// Gestisco il token con il tipo "KEYWORD" (blocchi if, for, ...)
        else if (t1->key == KEYWORD) {
            if (strcmp(t1->val, t2->val) == 0)
                return EMATCH_SCOPE; /// nel caso ci sia un match esatto di due blocchi

            bool checkT1_cond = oneOf(4, conditionals, t1->val);
            bool checkT2_cond = oneOf(4, conditionals, t2->val);

            bool checkT1_loops = oneOf(3, loops, t1->val);
            bool checkT2_loops = oneOf(2, loops, t2->val);

            /// controllo che ci sia stato un cambio di tipo sempre numerico oppure letterale
            if ((checkT1_cond && checkT2_cond) || (checkT1_loops && checkT2_loops))
                return MISMATCH_LIGHT;
            if ((checkT1_cond && checkT2_loops) || (checkT1_loops && checkT2_cond))
                return MISMATCH_SEVERE;
        }
        /// gestisoc qualsiasi altro caso in mainera equa
        else {
            if (strcmp(t1->val, t2->val) == 0)
                return EMATCH_SCOPE;

            return MISMATCH_LIGHT;
        }
    }
    /// Gestisoc il caso in cui il tipo dei token sia cambiato
    else {
        return MISMATCH_SEVERE;
    }
}

void needlemanWunsch(std::string fname_source, std::string fname_new) {
    // tokens del file originale
    auto t_source = parser(fname_source);
    // tokens del file nuovo
    auto t_new = parser(fname_new);

    if (t_source == nullptr || t_new == nullptr) {
        perror("file vuoti");
        delete t_source;
        delete t_new;
        return;
    }

    const size_t size1 = t_source->size + 1;
    const size_t size2 = t_new->size + 1;

    // gli trasformo in array per facilitarne l'accesso
    auto S1 = t_source->c_array();
    // gli trasformo in array per facilitarne l'accesso
    auto S2 = t_new->c_array();

    auto matrix = new int*[size1];
    for (int i = 0; i < size1; ++i)
        matrix[i] = new int[size2];

    for (int i = 0; i < size1; ++i)
        matrix[i][0] = GAP_PENALTY * i;

    for (int i = 0; i < size2; ++i)
        matrix[0][i] = GAP_PENALTY * i;

    for (int i = 1; i < size1; ++i) {
        for (int j = 1; j < size2; ++j) {
            auto match = matrix[i - 1][j - 1] + similarity(S1[i], S2[j]);
            auto del = matrix[i - 1][j] + GAP_PENALTY;
            auto ins = matrix[i][j - 1] + GAP_PENALTY;
            auto max = (match > del) ? ((match > ins) ? match : ins) : (del > ins ? del : ins);
            matrix[i][j] = max;
        }
    }

    std::string alignSource, alignNew, sepNew;

    assert(matrix[0][0] == 0);
    assert(size1 > 0 && size2 > 0);

    int i = static_cast<int>(size1 - 1);
    int j = static_cast<int>(size2 - 1);

    bool del_already_ins = false; // per gestire se hoo gia' inserito il carattere '-' (di elimina)

    while (i > 0 || j > 0) {
        sepNew = " ";
        if (j > 0 && (S2[j]->key == DIRECTIVES || strcmp(S2[j]->val, ";") == 0 ||
                      strcmp(S2[j]->val, "{") == 0 || strcmp(S2[j]->val, "}") == 0)) {
            sepNew = "\n";
        }

        if (i > 0 && j > 0 && matrix[i][j] == matrix[i - 1][j - 1] + similarity(S1[i], S2[j])) {
            alignSource = std::string(S1[i]->val) + " " + alignSource;
            alignNew = std::string("-: ") + std::string(S2[j]->val) + sepNew + alignNew;
            --i;
            --j;
            del_already_ins = false;
        } else if (i > 0 && matrix[i][j] == matrix[i - 1][j] + GAP_PENALTY) {
            alignSource = std::string(S1[i]->val) + " " + alignSource;
            if (!del_already_ins) {
                alignNew = "d: \n" + alignNew;
                del_already_ins = true;
            }
            --i;
        } else {
            // alignSource = "-\n" + alignSource;
            alignNew = std::string("-: ") + std::string(S2[j]->val) + sepNew + alignNew;
            --j;
            del_already_ins = false;
        }
    }

    std::cout << "------------------------------ SOURCE ------------------------------" << std::endl;
    std::cout << alignSource << std::endl;
    std::cout << "---------------------------- END SOURCE ----------------------------" << std::endl;

    std::cout << "-------------------------------- NEW -------------------------------" << std::endl;
    std::cout << alignNew << std::endl;
    std::cout << "------------------------------ END NEW -----------------------------" << std::endl;

    delete t_source;
    delete t_new;

    for (int u = 0; u < size2; ++u)
        delete[] S2[u];
    delete[] S2;

    for (int u = 0; u < size1; ++u)
        delete[] S1[u];
    delete[] S1;

    for (int u = 0; u < size1; ++u)
        delete[] matrix[u];
    delete[] matrix;

}