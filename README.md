# Miller-Rabin-Test

Input: An odd integer n ≥ 3.

Output: If n is prime, the algo always returns “prime”. If n is composite, the algo with probability
at least 1/2 returns “composite”.

Algo:

STEP 0: Check if n = a^b for integers a, b ≥ 2. If so, return “composite”.

STEP 1: Select a ∈ {1, 2, . . . , n − 1} uniformly at random. Compute a^(n−1)mod n. If this is not 1, then return “composite”.

STEP 2: Let n − 1 = 2^(k)*t, where t is odd. Compute a^t mod n, a^2t mod n, a^4t mod n, a^8t mod n, . . . , until a 1 is seen. 
If the number before 1 is not −1, then return “composite”; else return “prime”.
