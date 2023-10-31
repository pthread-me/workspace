# matrix_mul
exploring different avenues in optimizing matrix multiplications, all recordings are from the multiplications of two 3000x3000 matrices

## Steps
1.  find different methods
2.  implement the cool methods
3.  apply multithreading
4. find the point of diminishing return 

## Benchmarks 
### unoptimized: 
- using the iterative algorithm
- time complexity of theta (nmp) for  (n by m) * (m by p)
- times: 191s, 201s, 234s

### Iterative with Cache size Optimization
- used the algorithm here: https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm
- my laptop seems to have 5 processors each with a 64kb cache, so M=320, b=64. and our optimal step size T=565
- time complexity Theta (nmp)
- times when T=8: 94s, 85s, 92s
- times when T=565: 92s, 86s, 81s

### Error checking (to be implemented)
- we will be using this algorithm to check if the multiplications are correct :
https://en.wikipedia.org/wiki/Freivalds%27_algorithm
- 