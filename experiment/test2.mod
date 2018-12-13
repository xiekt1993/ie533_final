set N; # nodes

set T; # time

set T_pos; # time excluding 0
 
set A within (N cross N); # arcs (ij)




param NS {i in N} binary; # negative stubborn
param PS1 {i in N} binary; # positive stubborn

param beta {N} >= 0; # beta(n)

param w {A} >= 0; # weight(a)

param m = 5;

param p_plus = 0.8;

param p_minus = -0.8; 




var Y_plus {i in N, t in T} binary;

var Y_minus {i in N, t in T} binary;

var C {i in N, t in T};

var PS {i in N} binary;

var Evidence {i in N, j in N, t in T};



maximize Total_Act:

	sum{i in N, t in T} (Y_plus[i,t]-Y_minus[i,t]);




subject to Threshold1 {i in N, t in T}:

Y_plus[i,t] <= (C[i,t] - p_plus)/2 + 1;

subject to Threshold2 {i in N, t in T}:

Y_minus[i,t] >= (p_minus - C[i,t]);

subject to PS_NS_Cons {i in N}:

PS[i] + NS[i] <= 1;

 

subject to Pos_Cons:

sum {i in N} PS[i] <= m;

 

subject to N_stubborn {i in N, t in T}:
  C[i,t] <= - NS[i]*2 + 1;
  
subject to P_stubborn {i in N, t in T}:
  C[i,t] >= 2*PS[i] - 1;

subject to initial_value {i in N}:
  C[i,0] <= PS[i] + NS[i];

subject to Evidence_val_p {(j,i) in A, t in T_pos}:
  Evidence[i,j,t] <= Y_plus[j,t - 1];

subject to Evidence_val_n {(j,i) in A, t in T_pos}:
  Evidence[i,j,t] >= - Y_minus[j,t - 1];
  
subject to Evidence_regular {(j,i) in A, t in T_pos}:
   Evidence[i,j,t] <= w[j,i] * C[j,t - 1];

subject to regular {i in N, t in T_pos}:
  C[i,t] <= PS[i] * 2 + beta[i]*C[i,t-1] + sum {(j,i) in A} Evidence[i,j,t];

subject to fix_pos {i in N}:
  PS[i] = PS1[i]