from math import gcd
from collections import Counter
import re

def find_repeated_sequences(text, seq_len=3):
    """Find all repeated sequences of given length and their distances"""
    repeats = {}
    for i in range(len(text) - seq_len):
        seq = text[i:i+seq_len]
        for j in range(i + 1, len(text) - seq_len):
            if text[j:j+seq_len] == seq:
                if seq not in repeats:
                    repeats[seq] = []
                repeats[seq].append(j - i)
    return repeats

def kasiski_test(ciphertext):
    """Performs the Kasiski examination on the ciphertext"""
    ciphertext = re.sub(r'[^A-Za-z]', '', ciphertext)  # clean non-letters
    distances = []

    for seq_len in range(3, 6):  # Try trigram, 4-gram, and 5-gram
        repeated_seqs = find_repeated_sequences(ciphertext, seq_len)
        for dist_list in repeated_seqs.values():
            distances.extend(dist_list)

    # Compute GCDs between all distances
    gcds = []
    for i in range(len(distances)):
        for j in range(i + 1, len(distances)):
            g = gcd(distances[i], distances[j])
            if g > 1:
                gcds.append(g)

    if not gcds:
        print("❌ Aucune clé probable trouvée avec le test de Kasiski.")
        return []

    freq = Counter(gcds)
    most_common = freq.most_common(5)

    print("\n🔍 Longueurs de clé probables (ordre décroissant de fréquence) :")
    for length, count in most_common:
        print(f"- Longueur: {length}, Fréquence: {count}")

    return [length for length, _ in most_common]

# ----------- Main block -----------
if __name__ == "__main__":
    print("=== Test de Kasiski pour le chiffrement de Vigenère ===")
    ciphertext = input("Entrez le texte chiffré (sans accents) : ")
    kasiski_test(ciphertext)
