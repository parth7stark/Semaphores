# Semaphores
 
CPP program to synchronize Banking operations.

As in any real banking applications, a user account may be accessed at the same time by two different owners, withdrawing from or depositing to the account. Suppose we have a checking account with a balance of $1000 and two owners of the account may withdraw from it at the same time. The two withdrawals by the two owners would be translated to two processes or threads both of which execute the withdraw method at the same time. Let’s say owner 1 tries to withdraw $500 and owner 2 $600. Since the balance of the account is only $1000, not enough for both withdrawals, one process should have the –1 returned from withdraw. If owner 1 withdraws successfully, the correct remaining balance should be $500, and if owner2 successfully, it should be $400. But since there is no synchronization on the access to this account, it is possible that in mid of the execution of withdraw for owner1, the process for owner 2 preempts and executes. When that happens, the balance may become negative.
From the above example, we can see that the withdraw method must be executed mutually exclusively when it called by multiple processes/threads. There are two other scenarios of concurrency in this banking example. Owner 1 could withdraw while owner 2 deposit, and owner 1 deposits and so does owner2. 

Used semaphores to ensure:
1.	When one person is withdrawing, others shouldn’t be allowed to withdraw.
2.	When one person is depositing, others shouldn’t be allowed to deposit.
3.	When one person is depositing, others shouldn’t be allowed to withdraw.
