def encrypt(text, shift):
    result = ""

    # Traverse each character in the text
    for char in text:
        # Encrypt uppercase characters
        if char.isupper():
            result += chr((ord(char) + shift - 65) % 26 + 65)
        # Encrypt lowercase characters
        elif char.islower():
            result += chr((ord(char) + shift - 97) % 26 + 97)
        else:
            result += char  # Non-alphabetic characters are unchanged

    return result

def decrypt(text, shift):
    return encrypt(text, -shift)


if __name__ == "__main__":
    print("choose an operation :")
    choice = int(input("1-Encryption.\n2-Decryption.\n"))
    text= str(input("enter the text:"))
    shift = int(input("enter the shift:"))
    if choice ==1 :

        encrypted = encrypt(text, shift)
        print("Encrypted:"+ encrypted)
    else:
        decrypted = decrypt(text, shift)
        print("Decrypted:"+ decrypted)
