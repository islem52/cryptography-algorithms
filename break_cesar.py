def decrypt(text, shift):
    result = ""

    for char in text:
        if char.isupper():
            result += chr((ord(char) + shift - 65) % 26 + 65)
        elif char.islower():
            result += chr((ord(char) + shift - 97) % 26 + 97)
        else:
            result += char  # Non-alphabetic characters are unchanged

    return result

def break_cesar(ciphertext):
    for shift in range(1, 26):  # Try all possible shifts from 1 to 25
        decrypted_text = decrypt(ciphertext, shift)
        print(f"Shift {shift}: {decrypted_text}")

# Example usage
if __name__ == "__main__":
    encrypted_message = "Khoor, Zruog!"  # Example encrypted message
    break_cesar(encrypted_message)
