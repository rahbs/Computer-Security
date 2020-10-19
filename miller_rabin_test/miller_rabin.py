"""
miller-rabin prime test

Test if n is prime with error probability less than 2^(−𝑠).

"""

import random
from exponentiation import exp

Prime = 0
Composite = 1

def miller_rabin(n, s):
    if n == 2:
        return Prime
    elif n % 2 == 0:
        return Composite

    for _ in range(s):
        a = random.randint(1, n-1)
        if test(a, n) == True:
            return Composite

    return Prime

def test(a, n):
    # n-1 = (2^t) * u
    t = 0
    u = n-1
    while u % 2 == 0:
        t += 1
        u //= 2
    
    # x0 = (a^u) mod n
    x = exp(a,u,n)
    updated_x = x

    # NSR test
    for _ in range (t):
        updated_x = exp(x,2,n)
        if updated_x == 1 and x != 1 and x != n-1:
            return True
        x = updated_x

    # Fermat test
    if updated_x != 1:
        return True

    return False


if __name__ == "__main__":

    primes = [7879, 7883, 7901, 7907, 7919, 7927, 7933, 7937, 7949, 7951,
              7963, 7993, 8009, 8011, 8017, 8039, 8053, 8059, 8069, 8081,
              8087, 8089, 8093, 8101, 8111, 8117, 8123, 8147, 8161, 8167]

    for p in primes:
        result = miller_rabin(p, 20)
        if result == Prime:
            print("Prime")
        elif result == Composite:
            print("Composite")
        else:
            print("Undefined")
