s = "me@tomgalvin.uk"

print(2 % 1 == 0)
start = 128
totals = 0
for c in s:
    l = c + f" {ord(c):07b}"
    n = 128 - ord(c)
    for e in range(7):
        l += f" {0 if n & (2**e) == 0 else 2**e:03d}"
    print(l)
