/*
 * sem2.cpp
 *
 * Display values 0-20, with one thread handling even numbers
 * and the other handling odd numbers.  Thus, the threads are
 * interleaved.
 *
 * Correct version of producer-consumer relationship using mutex
 */


#include<iostream>
#include<pthread.h>

using namespace std;

pthread_mutex_t S_odd, S_even;  // semaphore

void * printvals (void *);

int main ()
{
   pthread_t thread1, thread2;    // two threads
   int odd, even;

   pthread_mutex_init (&S_odd, NULL);
   pthread_mutex_init (&S_even, NULL);
   pthread_mutex_lock (&S_odd);      // C R U C I A L - deadlock if not done
		// get 0 3 2 5 4 7 6 9 8 and dead if not done
		// besides order not right, when odd gets 9, that thread
		// finishes, and never lets evens go again
		// this locks up odds so that even (0) can go first

   //pthread_mutex_lock (&S_even);      //  DEADLOCK if you do this
		// get same as above if you do this

   odd = 0;
   pthread_create (&thread1, NULL, printvals, (void *) odd);
   even = 1;
   pthread_create (&thread2, NULL, printvals, (void *) even);
   pthread_join (thread1, NULL);  // wait for thread1 to finish
   pthread_join (thread2, NULL);  // wait for thread2 to finish

   pthread_mutex_destroy (&S_even);
   pthread_mutex_destroy (&S_odd);

   cout << endl << "Done" << endl;
   return 0;
}

void * printvals (void* ptr)
{
   int i;
   int min, max;
   int even = (int) ptr;

   cout << "Debug: In thread, even = " << even << endl;

   if (even) {
      max = 10;
      min = 0;
   } else {
      max = 9;
      min = 1;
   }

   for (i = min; i <= max; i+=2) {
      if (even) {
         pthread_mutex_lock (&S_even);   // don't let me do this until odd goes
         cout << i; // << endl;
         pthread_mutex_unlock (&S_odd);  // unlock the odd numbers!
      } else {
         pthread_mutex_lock (&S_odd);    // wait until unlocked
	 cout << i; // << endl;
         pthread_mutex_unlock (&S_even); // let evens go
      }
   }
}
