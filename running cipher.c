#include <stdio.h>
#include <string.h>
#include <ctype.h>

void running_key_encrypt(const char *plaintext, const char *key, char *ciphertext) {
    int pt_len = strlen(plaintext);

    for (int i = 0, j = 0; i < pt_len; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            char key_base = isupper(key[j]) ? 'A' : 'a';

            ciphertext[i] = ((plaintext[i] - base + (key[j] - key_base)) % 26) + base;
            j++;
        } else {
            ciphertext[i] = plaintext[i]; // keep spaces, punctuation, etc.
        }
    }
    ciphertext[pt_len] = '\0';
}

void running_key_decrypt(const char *ciphertext, const char *key, char *plaintext) {
    int ct_len = strlen(ciphertext);

    for (int i = 0, j = 0; i < ct_len; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            char key_base = isupper(key[j]) ? 'A' : 'a';

            plaintext[i] = ((ciphertext[i] - base - (key[j] - key_base) + 26) % 26) + base;
            j++;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[ct_len] = '\0';
}

int main() {
    char text[512];
    char key[512];
    char encrypted[512];
    char decrypted[512];

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter running key (must be at least as long as text): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    if (strlen(key) < strlen(text)) {
        printf("Error: Running key must be at least as long as plaintext.\n");
        return 1;
    }

    running_key_encrypt(text, key, encrypted);
    printf("Encrypted: %s\n", encrypted);

    running_key_decrypt(encrypted, key, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
