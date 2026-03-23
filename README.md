# Cryptography Algorithms

A collection of classical and modern cryptographic implementations in C and Python. This repo explores how encryption works—from simple substitution ciphers to industry-standard AES and RSA.

## What's Inside

### Classical Ciphers
- **cesar.py** — Caesar cipher. Shift every letter by a fixed number. Easy to break, useful for understanding the basics.
- **break_cesar.py** — Automated Caesar cipher breaker. Tries all 25 shifts and finds the one that produces readable text.
- **substitution.py** — Substitution cipher. Map each letter to another letter. More shifts possible than Caesar, but still vulnerable to frequency analysis.
- **vignere.py** — Vigenère cipher. Use a keyword to vary the shift for each letter. Much harder to crack than Caesar if the key is long and unknown.
- **kasiski.py** — Vigenère breaker using Kasiski examination. Finds the key length by looking for repeated ciphertext patterns, then breaks it.

### Modern Symmetric Encryption
- **AES.C** — Advanced Encryption Standard. Industry standard for symmetric encryption. Uses 128-bit blocks and keys up to 256 bits. Fast and secure when implemented correctly.
- **RC4.c** — Symmetric stream cipher. Generates a keystream that XORs with plaintext. Historically popular, now considered weak and deprecated for new systems.
- **matrixCypher.c** — Matrix-based cipher. Uses matrix operations for encryption. Educational more than practical.

### Asymmetric Encryption
- **RSA.py** — RSA public-key cryptography. Two keys: one public (encrypt), one private (decrypt). Slow compared to symmetric encryption but solves the key-exchange problem.

## Why This Matters

Breaking classical ciphers teaches you how attackers think. Understanding AES shows you how modern encryption actually works. RSA introduces the math behind public-key systems. Together, they cover the evolution and principles behind real-world cryptography.

## Running It

Python files run directly:
```bash
python3 cesar.py
python3 break_cesar.py
```

C files need compilation:
```bash
gcc -o aes AES.C
./aes
```

## Notes

These are educational implementations. For production systems, use well-tested libraries (OpenSSL, libsodium, cryptography module). The classical ciphers here are broken by design—don't use them to hide real secrets.

## About

Built to understand how encryption works from first principles.
