from [decimal, fractions, math, random] import *
# input
arr = list(map(int, input().split())) 
# decimal
setcontext(Context(prec=10, Emax=MAX_EMAX, rounding=ROUND_FLOOR))
Decimal('1.1') / Decimal('0.2')
# fractions
Fraction(3, 7)
Fraction(Decimal('1.14'))
Fraction('1.2').limit_denominator(4).numerator
Fraction(cos(pi / 3)).limit_denominator()
# set
S = set() S.add((a, b)) S.remove((a, b))
if not (a, b) in S:
# dict
D = dict() D[(a, b)] = 1 del D[(a, b)]
for (a, b) in D.items():
# random
arr = [randint(1, C) for i in range(N)]
choice([8, 6, 4, 1]) # random pick one
shuffle(arr) #shuffle a list
# print array
print(*arr, sep=' ')