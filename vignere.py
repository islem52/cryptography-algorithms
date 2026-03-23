def generer_cle(message, key):
    longclediv = len(message) // len(key)
    longclereste = len(message) % len(key)
    cle = key * longclediv + key[:longclereste]
    return cle

def chiffrer_vigenere(message, key):
    cle = generer_cle(message, key)
    chaine_chiffree = ""

    for i in range(len(message)):
        if "A" <= message[i] <= "Z":
            lettre_chiffree = chr(((ord(message[i]) - ord("A")) + (ord(cle[i]) - ord("A"))) % 26 + ord("A"))
        elif "a" <= message[i] <= "z":
            lettre_chiffree = chr(((ord(message[i]) - ord("a")) + (ord(cle[i]) - ord("a"))) % 26 + ord("a"))
        else:
            lettre_chiffree = message[i]
        chaine_chiffree += lettre_chiffree

    return chaine_chiffree

def dechiffrer_vigenere(message_chiffre, key):
    cle = generer_cle(message_chiffre, key)
    message_dechiffre = ""

    for i in range(len(message_chiffre)):
        if "A" <= message_chiffre[i] <= "Z":
            lettre_dechiffree = chr(((ord(message_chiffre[i]) - ord("A")) - (ord(cle[i]) - ord("A")) + 26) % 26 + ord("A"))
        elif "a" <= message_chiffre[i] <= "z":
            lettre_dechiffree = chr(((ord(message_chiffre[i]) - ord("a")) - (ord(cle[i]) - ord("a")) + 26) % 26 + ord("a"))
        else:
            lettre_dechiffree = message_chiffre[i]
        message_dechiffre += lettre_dechiffree

    return message_dechiffre

# --- Programme principal ---
message = input("Entrez le message à chiffrer : ")
key = input("Veuillez entrer la clé : ")

message_chiffre = chiffrer_vigenere(message, key)
print("Message chiffré :", message_chiffre)

chiffre = input("Entrez le message deja chiffre : ")


message_dechiffre = dechiffrer_vigenere(chiffre, key)
print("Message déchiffré :", message_dechiffre)
print("c'est bien le message d'origine ")