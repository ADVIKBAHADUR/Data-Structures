def generate_sequence(n):
    return (-1)**n * ((n + 1)//2) * int(5000 / 2**(n//2))

# Set to store unique numbers
unique_numbers = set()

# Generate the first 10000 unique numbers
for i in range(10000):
    value = generate_sequence(i)
    unique_numbers.add(value)

# Print the first 100 unique numbers
print(len(unique_numbers))
