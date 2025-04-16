#include <stdio.h>
#include <ctype.h>
#include <string.h>

int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // Inverse doesn't exist
}

void affine_encrypt(char *input, char *output, int a, int b) {
    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            output[i] = ((a * (c - base) + b) % 26) + base;
        } else {
            output[i] = c;
        }
    }
    output[strlen(input)] = '\0';
}

void affine_decrypt(char *input, char *output, int a, int b) {
    int a_inv = mod_inverse(a, 26);
    if (a_inv == -1) {
        printf("Error: 'a' must be coprime with 26!\n");
        return;
    }

    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            output[i] = (a_inv * ((c - base - b + 26)) % 26) + base;
        } else {
            output[i] = c;
        }
    }
    output[strlen(input)] = '\0';
}

int main() {
    char text[256];
    char encrypted[256];
    char decrypted[256];
    int a, b;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // remove newline

    printf("Enter key 'a' (must be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter key 'b': ");
    scanf("%d", &b);

    if (mod_inverse(a, 26) == -1) {
        printf("Invalid key 'a'. Must be coprime with 26.\n");
        return 1;
    }

    affine_encrypt(text, encrypted, a, b);
    printf("Encrypted: %s\n", encrypted);

    affine_decrypt(encrypted, decrypted, a, b);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
