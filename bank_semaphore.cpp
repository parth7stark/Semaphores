#include <bits/stdc++.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>
using namespace std;

#define N 5        //5 account in banks

int globalbal = 600;   
int min_cust_bal = 100;   //min bal for each customer is 100
int min_bank_bal =500;      //as 5 customers

int rc=0;
struct Acc
{
    int Ano;
    int bal;
};

struct DT{
	int a;
	int b;
    int c;  //token
};

//all are binary semaphore

sem_t withd; 	//ensures one person at a time withdraw
sem_t depo;		//ensure one person at a time deposit
sem_t mutex;    
// sem_t token; //ensure token generator
sem_t token[3];     //as three token

struct Acc A[N];

void* customer(void* par)
{
    // cout<<"\n Enter Accno: ";
    // cin>>no;

    // cout<<"\n 1. Withdraw \n 2. Deposit "<<endl;
    // cout<<"\n Enter operation: "
    // cin>>op;

    // cout<<"\n Enter amount to withdraw or deposit"; //later give using random
    // cin>>


    //extract data
    struct DT *data = (struct DT*)par;
    int no = data->a;
    int op = data->b;

    int counter = data->c;

    sem_wait(&token[counter]);


   if(op==1)
   {
       //entry section
        sem_wait(&withd);

        int  debt = (rand() % 100);  /* generate a random amt of withdraw */
        if (A[no].bal - debt < min_cust_bal || globalbal-debt < min_bank_bal)       //min bal
        {
            cout<<"\n counterno: "<<counter;
            printf("\n sorry can't withdraw");
            cout<<"\n withdraw "<<debt<<" from accno: "<<no<<" curr bal = "<<A[no].bal<<endl;
        }    

        else
        {
            A[no].bal -= debt;
            globalbal -= debt;
        //   printf("%d withdraw %10.2f : by  :%d: balance %10.2f\n",i, debt, *id, balance);
        // cout<<"\n i withdraw debt from accno.. bal =";

        cout<<"\n counterno:"<<counter;
        cout<<"\n withdraw "<<debt<<" from accno: "<<no<<" curr bal = "<<A[no].bal<<endl;
        }
        // sleep(1);
                //exit section
        sem_post(&withd);
   }
   else if(op==2)
   {
       //entry section
       sem_wait(&depo);
       rc++;
       if(rc==1)
         sem_wait(&withd);       //when person is depositing. dont allow withdraw


       int debt = (rand() % 60);  /* generate a random amt of deposit */
       A[no].bal += debt;
       globalbal+=debt;
        cout<<"\n counterno:"<<counter;

       cout<<"\n deposit "<<debt<<" to accno: "<<no<<" curr bal = "<<A[no].bal<<endl;
    //    sleep(1);

       rc--;

       if(rc==0)
            sem_post(&withd);


       //exit section
       sem_post(&depo);

   }
    
   sem_post(&token[counter]);


}

int main()
{   
     pthread_t tid[N*N];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
    // sem_init(&mutex, 0, 1);
	sem_init(&withd, 0, 1);
	sem_init(&depo, 0, 1);
	// sem_init(&token, 0, 1);
    for(int i=0;i<3;i++)
        sem_init(&token[i],0,1);


    srand(time(0));
    //enter bank details
    int i;
    for(i=0;i<N;i++)
    {
        cout<<"\n Enter cust " <<i<<" details:"<<endl;
        // cout<<"\nEnter account no: ";
        // cin>>A[i].Ano;

        A[i].Ano = i;
    
        cout<<"\n Enter bal: ";
        cin>>A[i].bal;
    }

    //create customer thread with different operation

    //simulating using for loop
    // customer(0,1);
    // customer(0,1);
    // customer(0,1);
    // customer(0,1);

    // int k=0;
    // for(i=0;i<4;i++)
    // {
    //    struct DT *data = (struct DT *) malloc(sizeof(struct DT));

	// 			data->a = 0;
	// 			data->b = 1;

    //     pthread_create(&tid[k],&attr,customer,data);
    //     k++;
    // }

    // for(int i=0; i<k; i++)
	// 	pthread_join(tid[i],NULL);
    

    // // customer(1,2);
    // k=0;
    // struct DT *data = (struct DT *) malloc(sizeof(struct DT));

	// 			data->a = 1;
	// 			data->b = 2;

    //     pthread_create(&tid[k],&attr,customer,data);
    //     k++;

    // for(int i=0; i<k; i++)
	// 	pthread_join(tid[i],NULL);

    int k=0;
    for(i=0;i<10;i++)
    {
        struct DT *data = (struct DT *) malloc(sizeof(struct DT));

		data->a = rand()%N; //N is no of accounts in bank
		data->b = rand()%2 + 1;
        data->c = rand()%3;

        // cout<<"\n data->c: "<<data->c;       //print to show difference

        /*
            order of printing here is not same as accessing the customer
        */

        pthread_create(&tid[k],&attr,customer,data);
        k++;
    }

     for(int i=0; i<k; i++)
		pthread_join(tid[i],NULL);




    cout<<endl;
    return 0;
}