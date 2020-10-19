"""
Discrete logarithm

a: given number
b: base
m: modulus

log_{b,m}(a)

"""

# from tqdm import tqdm  # progress bar
from exponentiation import exp
import random


def dlog(b, a, m):
    cur = 1
    for i in range(1,m):
        cur = exp(b,i,m)
        if cur == a:
            return i


if __name__ == "__main__":
    base = 3
    modulus = 65537  # 2 ** 16 + 1

    expos = [
        1,
        2,
        65535
    ]

    try:
        # for expo in tqdm(expos):
        for expo in expos:
            powed = exp(base, expo, modulus)
            loged = dlog(base, powed, modulus)
            print("({},{},{},{},{}),".format(expo, base, powed, loged, modulus))
            assert expo == loged
        print(">> All the tests passed <<")
    except:
        print("expo({}) and loged({}) is not equal".format(expo, loged))
