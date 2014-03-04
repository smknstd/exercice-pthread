#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#include <unistd.h>
#define psleep(sec) sleep ((sec))

#define STOCK_INITIAL   1000 //stock infini dans l'énoncé
#define NB_CUISINIERES  6


/* Structure stockant les informations communes des threads des cuisinieres et de l'épicier. */
typedef struct
{
   int nb_ingredient1;
   int nb_ingredient2;
   int nb_ingredient3;
   int nb_ingredient4;

   pthread_t thread_epicier;
   pthread_t thread_cuisinieres [NB_CUISINIERES];

   pthread_mutex_t mutex_epicier;
   pthread_cond_t condition_epicier;
   pthread_cond_t condition_cuisinieres;
}
struct_commun;

static struct_commun epicier =
{
   .nb_ingredient1 = 1, //valeurs initiales à la creation du thread
   .nb_ingredient2 = 1, //valeurs initiales à la creation du thread
   .nb_ingredient3 = 0,
   .nb_ingredient4 = 0,
   .mutex_epicier = PTHREAD_MUTEX_INITIALIZER,
   .condition_epicier = PTHREAD_COND_INITIALIZER,
   .condition_cuisinieres = PTHREAD_COND_INITIALIZER,
};


/* Fonction pour tirer un nombre au sort entre 0 et max. */
static int get_random (int max){
   double val;

   val = (double) max * rand ();
   val = val / (RAND_MAX + 1.0);

   return ((int) val);
}


static void * fn_epicier (void * p_data){

   while (1){

      /* Debut de la zone protegee. */
      pthread_mutex_lock (& epicier.mutex_epicier);
      pthread_cond_wait (& epicier.condition_epicier, & epicier.mutex_epicier);

      //tirage au sort du premier ingredient
      int hasard_ing1 = get_random (4) + 1;
      switch(hasard_ing1){
         case 1:
            epicier.nb_ingredient1++;
            break;
         case 2:
            epicier.nb_ingredient2++;
            break;
         case 3:
            epicier.nb_ingredient3++;
            break;
         case 4:
            epicier.nb_ingredient4++;
            break;
      }

      //tirage au sort du deuxieme ingredient
      int hasard_ing2 = get_random (4) + 1;
      while(hasard_ing1==hasard_ing2)
         hasard_ing2 = get_random (4) + 1;

      switch(hasard_ing2){
         case 1:
            epicier.nb_ingredient1++;
            break;
         case 2:
            epicier.nb_ingredient2++;
            break;
         case 3:
            epicier.nb_ingredient3++;
            break;
         case 4:
            epicier.nb_ingredient4++;
            break;
      }

      printf ("Remplissage du panier de l'épicier avec les ingredients %d et %d.\n", hasard_ing1, hasard_ing2);
      
      pthread_cond_signal (& epicier.condition_cuisinieres);
      pthread_mutex_unlock (& epicier.mutex_epicier);
      /* Fin de la zone protegee. */
   }

   return NULL;
}


static void * fn_cuisiniere (void * p_data){

   int numero = (int) p_data;

   int nb_ingredient1 = 0;
   int nb_ingredient2 = 0;
   int nb_ingredient3 = 0;
   int nb_ingredient4 = 0;

   switch(numero){

      case 0:
         nb_ingredient1 = STOCK_INITIAL;
         nb_ingredient2 = STOCK_INITIAL;
         break;
      case 1:
         nb_ingredient1 = STOCK_INITIAL;
         nb_ingredient3 = STOCK_INITIAL;
         break;
      case 2:
         nb_ingredient1 = STOCK_INITIAL;
         nb_ingredient4 = STOCK_INITIAL;
         break;
      case 3:
         nb_ingredient2 = STOCK_INITIAL;
         nb_ingredient3 = STOCK_INITIAL;
         break;
      case 4:
         nb_ingredient2 = STOCK_INITIAL;
         nb_ingredient4 = STOCK_INITIAL;
         break;
      case 5:
         nb_ingredient3 = STOCK_INITIAL;
         nb_ingredient4 = STOCK_INITIAL;
         break;
   }

   while (1){

      psleep (get_random (4) + 1);
      
      /* Debut de la zone protegee. */
      pthread_mutex_lock (& epicier.mutex_epicier);

      printf ("Cuisinière %d vérifie ses ingredients.\n", numero+1);
      if (epicier.nb_ingredient1+nb_ingredient1 > 0 && epicier.nb_ingredient2+nb_ingredient2 > 0 && epicier.nb_ingredient3+nb_ingredient3 > 0 && epicier.nb_ingredient4+nb_ingredient4 > 0){

         epicier.nb_ingredient1 = 0;
         epicier.nb_ingredient2 = 0;
         epicier.nb_ingredient3 = 0;
         epicier.nb_ingredient4 = 0;
         printf ("Cuisinière %d utilise les ingredients de l'épicier pour faire un gateau !\n", numero+1);
         printf ("Le gateau est prêt !\n");

         pthread_cond_signal (& epicier.condition_epicier);
         pthread_cond_wait (& epicier.condition_cuisinieres, & epicier.mutex_epicier);

      }
      pthread_mutex_unlock (& epicier.mutex_epicier);
      /* Fin de la zone protegee. */
   }

   return NULL;
}


int main (void)
{
   int i = 0;
   int ret = 0;

   /* Creation des threads. */
   printf ("Creation du thread de lépicier !\n");
   ret = pthread_create (& epicier.thread_epicier, NULL, fn_epicier, NULL);
   if (ret){
      fprintf (stderr, "%s", strerror (ret));
   }

   printf ("Creation des 6 threads des cuisinières!\n");
   for (i = 0; i < NB_CUISINIERES; i++){
      ret = pthread_create (& epicier.thread_cuisinieres [i], NULL, fn_cuisiniere, (void *) i);

      if (ret){
         fprintf (stderr, "%s", strerror (ret));
      }
   }

   //attente de la fin du thread de l'épicier: ca n'arrive jamais ! C'est pour que el programme ne s'arrête pas.
   pthread_join (epicier.thread_epicier, NULL);

   return 0;
}

