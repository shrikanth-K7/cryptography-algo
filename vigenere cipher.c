#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generate_key(const char *text, const char *keyword, char *key) {
    int text_len = strlen(text);
    int keyword_len = strlen(keyword);
    for (int i = 0, j = 0; i < text_len; i++) {
        if (isalpha(text[i])) {
            key[i] = keyword[j % keyword_len];
            j++;
        } else {
            key[i] = text[i];  // non-letters remain unchanged
        }
    }
    key[text_len] = '\0';
}

void vigenere_encrypt(const char *text, const char *key, char *encrypted) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char key_base = isupper(key[i]) ? 'A' : 'a';
            encrypted[i] = ((text[i] - base + (key[i] - key_base)) % 26) + base;
        } else {
            encrypted[i] = text[i];
        }
    }
    encrypted[strlen(text)] = '\0';
}

void vigenere_decrypt(const char *encrypted, const char *key, char *decrypted) {
    for (int i = 0; encrypted[i] != '\0'; i++) {
        if (isalpha(encrypted[i])) {
            char base = isupper(encrypted[i]) ? 'A' : 'a';
            char key_base = isupper(key[i]) ? 'A' : 'a';
            decrypted[i] = ((encrypted[i] - base - (key[i] - key_base) + 26) % 26) + base;
        } else {
            decrypted[i] = encrypted[i];
        }
    }
    decrypted[strlen(encrypted)] = '\0';
}

int main() {
    char text[256];
    char keyword[256];
    char key[256];
    char encrypted[256];
    char decrypted[256];

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';  // remove newline

    printf("Enter keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';  // remove newline

    generate_key(text, keyword, key);

    vigenere_encrypt(text, key, encrypted);
    printf("Encrypted text: %s\n", encrypted);

    vigenere_decrypt(encrypted, key, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
