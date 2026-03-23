#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SBOX_SIZE 256

typedef struct {
    unsigned char S[SBOX_SIZE];
    int i, j;
} rc4_state;

void rc4_init(rc4_state *state, const unsigned char *key, int key_length) {
    // Key Scheduling Algorithm (KSA)
    for (int i = 0; i < SBOX_SIZE; i++) {
        state->S[i] = i;
    }
    
    int j = 0;
    for (int i = 0; i < SBOX_SIZE; i++) {
        j = (j + state->S[i] + key[i % key_length]) % SBOX_SIZE;
        // Swap S[i] and S[j]
        unsigned char temp = state->S[i];
        state->S[i] = state->S[j];
        state->S[j] = temp;
    }
    
    state->i = state->j = 0;
}

unsigned char rc4_next_byte(rc4_state *state) {
    // Pseudo-Random Generation Algorithm (PRGA)
    state->i = (state->i + 1) % SBOX_SIZE;
    state->j = (state->j + state->S[state->i]) % SBOX_SIZE;
    
    // Swap S[i] and S[j]
    unsigned char temp = state->S[state->i];
    state->S[state->i] = state->S[state->j];
    state->S[state->j] = temp;
    
    return state->S[(state->S[state->i] + state->S[state->j]) % SBOX_SIZE];
}

void rc4_crypt(rc4_state *state, const unsigned char *input, unsigned char *output, int length) {
    for (int k = 0; k < length; k++) {
        output[k] = input[k] ^ rc4_next_byte(state);
    }
}

int main() {
    rc4_state state;
    char key[256];
    char plaintext[1024];
    unsigned char ciphertext[1024];
    unsigned char decrypted[1024];
    
    printf("RC4 Encryption/Decryption\n");
    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0; // Remove newline
    
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0; // Remove newline
    
    // Initialize RC4 with key
    rc4_init(&state, (unsigned char*)key, strlen(key));
    
    // Encrypt
    rc4_crypt(&state, (unsigned char*)plaintext, ciphertext, strlen(plaintext));
    printf("\nCiphertext (hex): ");
    for (size_t i = 0; i < strlen(plaintext); i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");
    
    // Reset state for decryption
    rc4_init(&state, (unsigned char*)key, strlen(key));
    
    // Decrypt
    rc4_crypt(&state, ciphertext, decrypted, strlen(plaintext));
    decrypted[strlen(plaintext)] = '\0';
    printf("Decrypted text: %s\n", decrypted);
    
    return 0;
}
