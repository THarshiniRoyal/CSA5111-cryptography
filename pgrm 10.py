import math

def calculate_possible_keys():
    possible_keys = math.factorial(25)
    return possible_keys

def calculate_effectively_unique_keys():
    effectively_unique_keys = calculate_possible_keys() / (math.factorial(2) ** 2)
    return effectively_unique_keys

possible_keys = calculate_possible_keys()
effectively_unique_keys = calculate_effectively_unique_keys()

print("Number of possible keys without considering duplicates:", possible_keys)
print("Number of effectively unique keys accounting for duplicates:", effectively_unique_keys)
