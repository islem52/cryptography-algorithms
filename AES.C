from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
import os

KEY_FILE = "AES/aes_key.bin"  # File to store the AES key

def save_key(key):
    """Save the key to a file."""
    with open(KEY_FILE, "wb") as f:
        f.write(key)

def load_key():
    """Load the key from a file (or generate one if missing)."""
    if os.path.exists(KEY_FILE):
        with open(KEY_FILE, "rb") as f:
            return f.read()
    else:
        return regenerate_key()

def regenerate_key():
    """Generate a new key and save it."""
    key = os.urandom(32)  # Generate AES-256 key
    save_key(key)
    print("🔑 A new AES key has been generated and saved.")
    return key

def encrypt(plain_text, key):
    iv = os.urandom(16)  # Generate a random IV
    cipher = Cipher(algorithms.AES(key), modes.CFB(iv), backend=default_backend())
    encryptor = cipher.encryptor()
    cipher_text = iv + encryptor.update(plain_text.encode()) + encryptor.finalize()
    return cipher_text

def decrypt(cipher_text, key):
    iv = cipher_text[:16]  # Extract the IV
    cipher = Cipher(algorithms.AES(key), modes.CFB(iv), backend=default_backend())
    decryptor = cipher.decryptor()
    plain_text = decryptor.update(cipher_text[16:]) + decryptor.finalize()
    return plain_text.decode()

if __name__ == "__main__":
    while True:
        print("\nOptions:")
        print("  (E) Encrypt")
        print("  (D) Decrypt")
        print("  (R) Regenerate Key")
        print("  (Q) Quit")
        
        choice = input("\nEnter your choice: ").strip().lower()

        if choice == "e":
            key = load_key()
            plain_text = input("Enter text to encrypt: ")
            cipher_text = encrypt(plain_text, key)
            print("\nEncrypted (hex):", cipher_text.hex())
        
        elif choice == "d":
            key = load_key()
            cipher_text_hex = input("Enter hex-encoded ciphertext: ").strip()
            cipher_text = bytes.fromhex(cipher_text_hex)
            try:
                decrypted_text = decrypt(cipher_text, key)
                print("\nDecrypted text:", decrypted_text)
            except Exception as e:
                print("❌ Decryption failed! Make sure you used the correct key.")
        
        elif choice == "r":
            regenerate_key()
        
        elif choice == "q":
            print("👋 Exiting the program. Goodbye!")
            break
        
        else:
            print("❌ Invalid choice. Please enter 'E', 'D', 'R', or 'Q'.")