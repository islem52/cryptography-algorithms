import math

def sont_premiers_entre_eux(a, b):
    return math.gcd(a, b) == 1

def est_premier(n):
    if n <= 1:
        return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            return False
    return True

def inverse_modulaire(a, n):
    t, new_t = 0, 1
    r, new_r = n, a
    while new_r != 0:
        quotient = r // new_r
        t, new_t = new_t, t - quotient * new_t
        r, new_r = new_r, r - quotient * new_r
    if r > 1:
        raise ValueError(f"{a} n'a pas d'inverse modulo {n}")
    if t < 0:
        t += n
    return t

def chiffrement(message, e, n):
    resultat = []
    for char in message:
        code_ascii = ord(char)
        code_chiffre = pow(code_ascii, e, n)
        resultat.append(str(code_chiffre))
    return ' '.join(resultat)

def dechiffrement(message_chiffre, d, n):
    chiffres = message_chiffre.split()
    resultat = ''
    for code in chiffres:
        code_int = int(code)
        m = pow(code_int, d, n)
        try:
            resultat += chr(m)
        except ValueError:
            resultat += '?'  # caractère invalide, met un ?
    return resultat

# Entrée sécurisée de p et q
while True:
    try:
        p = int(input("Entrez un nombre premier p : "))
        q = int(input("Entrez un nombre premier q : "))
        if est_premier(p) and est_premier(q) and p * q > 127:
            break
        else:
            print("Erreur : p et q doivent être premiers et p*q > 127.")
    except ValueError:
        print("Entrée invalide.")

n = p * q
phi = (p - 1) * (q - 1)

# Entrée sécurisée de e
while True:
    try:
        e = int(input(f"Entrez un entier e premier avec φ(n)={phi} : "))
        if sont_premiers_entre_eux(e, phi):
            break
        else:
            print("Erreur : e doit être premier avec φ(n).")
    except ValueError:
        print("Entrée invalide.")

# Chiffrement
message = input("Message à chiffrer : ")
message_chiffre = chiffrement(message, e, n)
print("Message chiffré :", message_chiffre)

# Déchiffrement
d = inverse_modulaire(e, phi)
message_dechiffre = dechiffrement(message_chiffre, d, n)
print("Message déchiffré :", message_dechiffre)