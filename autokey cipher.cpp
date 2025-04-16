#include <stdio.h>
#include <string.h>
#include <ctype.h>

void auto_key_encrypt(const char *text, const char *keyword, char *encrypted) {
    int text_len = strlen(text);
    int key_len = strlen(keyword);
    char key[512];

    strcpy(key, keyword);

    int j = key_len;
    for (int i = 0; i < text_len && j < sizeof(key) - 1; i++) {
        if (isalpha(text[i])) {
            key[j++] = text[i];
        }
    }
    key[j] = '\0';

    for (int i = 0, k = 0; i < text_len; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char key_base = isupper(key[k]) ? 'A' : 'a';
            encrypted[i] = ((text[i] - base + (key[k] - key_base)) % 26) + base;
            k++;
        } else {
            encrypted[i] = text[i];
        }
    }
    encrypted[text_len] = '\0';
}

void auto_key_decrypt(const char *encrypted, const char *keyword, char *decrypted) {
    int text_len = strlen(encrypted);
    int key_len = strlen(keyword);
    char current_key[512];

    strcpy(current_key, keyword);

    for (int i = 0, k = 0; i < text_len; i++) {
        if (isalpha(encrypted[i])) {
            char base = isupper(encrypted[i]) ? 'A' : 'a';
            char key_char = current_key[k];
            char key_base = isupper(key_char) ? 'A' : 'a';

            int pi = ((encrypted[i] - base - (key_char - key_base) + 26) % 26);
            decrypted[i] = base + pi;

            current_key[key_len + k] = decrypted[i];
            current_key[key_len + k + 1] = '\0';
            k++;
        } else {
            decrypted[i] = encrypted[i];
        }
    }
    decrypted[text_len] = '\0';
}

int main() {
    char text[256];
    char keyword[256];
    char encrypted[256];
    char decrypted[256];

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    auto_key_encrypt(text, keyword, encrypted);
    printf("Encrypted: %s\n", encrypted);

    auto_key_decrypt(encrypted, keyword, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
