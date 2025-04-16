#include <stdio.h>
#include <string.h>
#include <ctype.h>

void repeat_key(const char *text, const char *key, char *full_key) {
    int key_len = strlen(key);
    int j = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            full_key[i] = key[j % key_len];
            j++;
        } else {
            full_key[i] = text[i];  
        }
    }
    full_key[strlen(text)] = '\0';
}

void beaufort_cipher(const char *text, const char *key, char *output) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char k_base = isupper(key[i]) ? 'A' : 'a';

            int pi = text[i] - base;
            int ki = key[i] - k_base;

            int ci = (ki - pi + 26) % 26;
            output[i] = base + ci;
        } else {
            output[i] = text[i]; 
        }
    }
    output[strlen(text)] = '\0';
}

int main() {
    char text[256];
    char keyword[256];
    char full_key[256];
    char encrypted[256];
    char decrypted[256];

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    repeat_key(text, keyword, full_key);

    beaufort_cipher(text, full_key, encrypted);
    printf("Encrypted: %s\n", encrypted);

    beaufort_cipher(encrypted, full_key, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
