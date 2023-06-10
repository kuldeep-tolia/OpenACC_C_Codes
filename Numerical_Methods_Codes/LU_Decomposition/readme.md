Problem Description:  

-> This is an OpenACC program to compute the LU decomposition without pivoting, and subsequently solve the system of linear equations using forward/backward substitutions.  
-> Given a matrix $A[N][N]$ is decomposed into a lower and upper triangular matrix such that $A = L * U$. This is can be given as  
$$U(i, j) = A(i, j) - \sum_{k=0}^{i-1} L(i, k) U(k, j)$$  
$$L(i, j) = \frac{A(i, j) - \sum_{k=0}^{j-1} L(i, k) U(k, j)}{U(j, j)}$$  

-> In the present program, both the coefficients for $L$ and $U$ matrices are stored inside the original input matrix $A$.
