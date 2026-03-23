# Table de substitution pour le chiffrement
substitution_table = {
    "A": "Q", "a": "q", "B": "W", "b": "w",
    "C": "E", "c": "e", "D": "R", "d": "r",
    "E": "T", "e": "t", "F": "Y", "f": "y",
    "G": "U", "g": "u", "H": "I", "h": "i",
    "I": "O", "i": "o", "J": "P", "j": "p",
    "K": "A", "k": "a", "L": "S", "l": "s",
    "M": "D", "m": "d", "N": "F", "n": "f",
    "O": "G", "o": "g", "P": "H", "p": "h",
    "Q": "J", "q": "j", "R": "K", "r": "k",
    "S": "Z", "s": "z", "T": "X", "t": "x",
    "U": "C", "u": "c", "V": "V", "v": "v",
    "W": "B", "w": "b", "X": "N", "x": "n",
    "Y": "L", "y": "l", "Z": "M", "z": "m"
}

# Création de la table inverse pour le déchiffrement
reverse_table = {v: k for k, v in substitution_table.items()}

# Fonction de chiffrement
def chiffrer(message):
    return "".join(substitution_table.get(c, c) for c in message)

# Fonction de déchiffrement
def dechiffrer(message_chiffre):
    return "".join(reverse_table.get(c, c) for c in message_chiffre)

# Menu utilisateur
choix = input("Voulez-vous chiffrer (c) ou déchiffrer (d) ? ").lower()
if choix == "c":
    message = input("Entrez le message à chiffrer : ")
    print("Message chiffré :", chiffrer(message))
elif choix == "d":
    message_chiffre = input("Entrez le message à déchiffrer : ")
    print("Message déchiffré :", dechiffrer(message_chiffre))
else:
    print("Choix invalide.")
