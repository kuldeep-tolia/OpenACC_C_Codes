Problem Description:  

-> This is an OpenACC program to compute the LU decomposition without pivoting, and subsequently solve the system of linear equations using forward/backward substitutions.  
-> Given a matrix $A[N][N]$ is decomposed into a lower and upper triangular matrix such that $A = L * U$. This is can be given as  
$$U(i, j) = A(i, j) - \sum_{k=0}^{i-1} L(i, k) U(k, j)$$  
$$L(i, j) = \left( A(i, j) - \sum_{k=0}^{j-1} L(i, k) U(k, j) \right) / U(j, j)$$  

-> In the present program, both the coefficients for $L$ and $U$ matrices are stored inside the original input matrix $A$.  
-> For a given matrix $A[N][N]$ and RHS vector $b[N]$, such that $A * x = b$, it is solved as $L * y = b$ followed by $U * x = y$. This can be given as  
$$y(i) = \left( b(i) - \sum_{j=0}^{i-1} L(i, j) y(j) \right) / L(i, i)$$  
$$x(i) = \left( y(i) - \sum_{j=0}^{i-1} U(i, j) x(j) \right) / U(i, i)$$
