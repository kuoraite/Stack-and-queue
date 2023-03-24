#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
#include "queue.h"

#define PROBABILITY 50
#define SANDWITCH_QUANTITY 10
#define SANDWITCH_PERIODICITY 60
#define EXPIRY_DATE 1
#define PRICE 15
#define WORKING_HOURS 14
#define TIME_INTERVALS 5
#define TIME 5

int sandwitches_Stack(){
    printf("Sandwitch cafe Stack \n");

    srand(time(NULL));

    int income = 0, loss = 0;
    int size1 = 0, size2 = 0;

    Stack holder1 = createStack();
    Stack holder2 = createStack();

    for(int days = 1; days <= TIME; days++){
        int customers = 0, sandwitches_made = 0, thrown_away = 0;
        
        for(int j = 0; j <= WORKING_HOURS * 60; j++){

            //SUMUSTINIU PAPILDYMAS
            if(j % SANDWITCH_PERIODICITY == 0){
                if(size1 <= size2){
                    push(&holder1, &j);
                    size1 += SANDWITCH_QUANTITY;
                    sandwitches_made += SANDWITCH_QUANTITY;
                }
                else{
                    push(&holder2, &j);
                    size2 += SANDWITCH_QUANTITY;
                    sandwitches_made += SANDWITCH_QUANTITY;
                }
            }

            //SUMUSTINIU PARDAVIMAS
            if(j % TIME_INTERVALS == 0){
                if((rand() % 100 + 1) < PROBABILITY){

                    if(size1 > 0 && size2 > 0){
                        customers++;
                        income += PRICE;

                        if((rand() % 2 + 1) == 1){
                            pop(&holder1);
                            size1--;
                        }
                        else{
                            pop(&holder2);
                            size2--;
                        }
                    }
                    else if((size1 > 0) && (size2 == 0)){
                        customers++;
                        income += PRICE;

                        pop(&holder1);   
                        size1--;                 
                    }
                    else if((size1 == 0) && (size2 > 0)){
                        customers++;
                        income += PRICE;

                        pop(&holder2);
                        size2--;
                    }
                } 
            }
            
        }

        //DIENOS PABAIGA
        Stack temp1 = createStack();
        for(int i = 0; i < size1; i++){

            int *value = pop(&holder1);
            push(&temp1, &value);
        }
        deleteStack(&holder1);

        Stack temp2 = createStack();
        for(int i = 0; i < size2; i++){
            int *value = pop(&holder2);
            push(&temp2, &value);
        }
        deleteStack(&holder2);

        if(days == 1){
            for(int i = 1; i < size1; i++){
                int *data = pop(&temp1);

                if((WORKING_HOURS * 60 - *data) >= EXPIRY_DATE * 60){
                    size1--;
                    loss += PRICE;
                    thrown_away++;
                }
                else{
                    data -= WORKING_HOURS;
                    push(&temp1, &data);
                }
            }

            for(int i = 1; i < size2; i++){
                int *data = pop(&temp2);

                if((WORKING_HOURS * 60 - *data) >= EXPIRY_DATE * 60){
                    size2--;
                    loss += PRICE;
                    thrown_away++;
                }
                else{
                    data -= WORKING_HOURS;
                    push(&temp2, &data);
                }
            }
        }
        else{
            int expires = (24 * (days - 1) + WORKING_HOURS);

            for(int i = 1; i < size1; i++){
                int *data = pop(&temp1);

                if((expires * 60 - *data) >= EXPIRY_DATE * 60){
                    size1--;
                    loss += PRICE;
                    thrown_away++;
                }
                else{
                    data -= expires;
                    push(&temp1, &data);
                }
            }

            for(int i = 1; i < size2; i++){
                int *data = pop(&temp2);

                if((expires * 60 - *data) >= EXPIRY_DATE * 60){
                    size2--;
                    loss += PRICE;
                    thrown_away++;
                }
                else{
                    data -= expires;
                    push(&temp2, &data);
                }
            }
        }

        Stack holder1 = createStack();
        for(int i = 0; i < size1; i++){

            int *value = pop(&temp1);
            push(&holder1, &value);
        }
        deleteStack(&temp1);

        Stack holder2 = createStack();
        for(int i = 0; i < size2; i++){
            int *value = pop(&temp2);
            push(&holder2, &value);
        }
        deleteStack(&temp2);

        /*printf("Sandwitches bought: %d\n", customers);
        printf("Sandwitches made: %d\n", sandwitches_made);
        printf("Sandwitches left (1 holder): %d \n", size1);
        printf("Sandwitches left (2 holder): %d \n", size2);
        printf("Sandwitches thrown away: %d \n", thrown_away);*/
    }
    printf("Income: %d, loss: %d \n\n", income, loss);
}

int sandwitches_Queue1(){
    printf("Sandwitch cafe Queue (1) \n");

    srand(time(NULL));

    int income = 0, loss = 0;
    int size = 0, error;

    Queue *holder;
    holder = createQueue(&error);

    for(int days = 1; days <= TIME; days++){
        int customers = 0, sandwitches_made = 0, thrown_out = 0;

        for(int j = 1; j <= (WORKING_HOURS * 60); j++){

            //SUMUSTINIU PAPILDYMAS
            if(j % SANDWITCH_PERIODICITY == 0){
                for(int i = 0; i < SANDWITCH_QUANTITY; i++){
                    enQueue(holder, &j, sizeof(int), &error);
                }
                size += SANDWITCH_QUANTITY;
                sandwitches_made += SANDWITCH_QUANTITY;
            }

            //SUMUSTINIU PARDAVIMAS
            if(j % TIME_INTERVALS == 0){
                if((rand() % 100 + 1) < PROBABILITY && size > 0){
                int data;

                customers++;
                income += PRICE;

                deQueue(holder, &data, sizeof(int), &error);
                size--;
                }
            }
        }
            
        //DIENOS PABAIGA
        if(days == 1){
            for(int i = 0; i < size; i++){
            int temp;

            deQueue(holder, &temp, sizeof(int), &error);
                if((WORKING_HOURS * 60 - temp) >= EXPIRY_DATE * 60){
                    loss += PRICE;
                    thrown_out++;
                }
                else{
                    temp -= WORKING_HOURS;
                    enQueue(holder, &temp, sizeof(int), &error);
                }
            }
        }
        else{
            int expires = (24 * (days - 1) + WORKING_HOURS);

            for(int i = 0; i < size; i++){
            int temp;

            deQueue(holder, &temp, sizeof(int), &error);
                if((expires * 60 - temp) >= EXPIRY_DATE * 60){
                    loss += PRICE;
                    thrown_out++;
                }
                else{
                    temp -= expires;
                    enQueue(holder, &temp, sizeof(int), &error);
                }
            }
        }

        /*printf("Sandwitches bought: %d\n", customers);
        printf("Sandwitches made: %d\n", sandwitches_made);
        printf("Sandwitches left: %d \n", size);
        printf("Sandwitches thrown out: %d \n", thrown_out);*/
    }
    printf("Income: %d, loss: %d \n\n", income, loss);

}

int sandwitches_Queue2(){
    printf("Sandwitch cafe Queue (2) \n");

    srand(time(NULL));

    int income = 0, loss = 0;
    int size1 = 0, size2 = 0, error;

    Queue *holder1, *holder2;
    holder1 = createQueue(&error);
    holder2 = createQueue(&error);

    for(int days = 1; days <= TIME; days++){
        int customers = 0, sandwitches_made = 0, thrown_out = 0;
        
        for(int j = 1; j <= (WORKING_HOURS * 60); j++){

            //SUMUSTINIU PAPILDYMAS
            if(j % SANDWITCH_PERIODICITY == 0){
                if(size1 > size2){
                    for(int i = 0; i < SANDWITCH_QUANTITY; i++){
                        enQueue(holder2, &j, sizeof(int), &error);
                    }
                    size2 += SANDWITCH_QUANTITY;
                    sandwitches_made += SANDWITCH_QUANTITY;
                }
                else{
                    for(int i = 0; i < SANDWITCH_QUANTITY; i++){
                        enQueue(holder1, &j, sizeof(int), &error);
                    }
                    size1 += SANDWITCH_QUANTITY;
                    sandwitches_made += SANDWITCH_QUANTITY;
                }
            }

            //SUMUSTINIU PARDAVIMAS
            if(j % TIME_INTERVALS == 0){
                if((rand() % 100 + 1) < PROBABILITY && (size1 > 0 || size2 > 0)){
                int data;

                    if(size1 != 0 && size2 != 0){
                        customers++;
                        income += PRICE;

                        if((rand() % 2 + 1) == 1){
                            deQueue(holder1, &data, sizeof(int), &error);
                            size1--;
                        }
                        else{
                            deQueue(holder2, &data, sizeof(int), &error);
                            size2--;
                        }
                    }
                    else if((size1 != 0) && (size2 == 0)){
                        customers++;
                        income += PRICE;

                        deQueue(holder1, &data, sizeof(int), &error);  
                        size1--;                 
                    }
                    else if((size1 == 0) && (size2 != 0)){
                        customers++;
                        income += PRICE;

                        deQueue(holder2, &data, sizeof(int), &error);
                        size2--;
                    }
                } 
            }
        }

        //DIENOS PABAIGA
        int temp;
        if(days == 1){
            for(int i = 0; i < size1; i++){
                deQueue(holder1, &temp, sizeof(int), &error);
                if((WORKING_HOURS * 60 - temp) >= EXPIRY_DATE * 60){
                    loss += PRICE;
                    thrown_out++;
                }
                else{
                    temp -= WORKING_HOURS;
                    enQueue(holder1, &temp, sizeof(int), &error);
                }
            }

            for(int i = 0; i < size2; i++){
                deQueue(holder2, &temp, sizeof(int), &error);
                if((WORKING_HOURS * 60 - temp) >= EXPIRY_DATE * 60){
                    loss += PRICE;
                    thrown_out++;
                }
                else{
                    temp -= WORKING_HOURS;
                    enQueue(holder2, &temp, sizeof(int), &error);
                }
            }
        }
        else{
            int expires = (24 * (days - 1) + WORKING_HOURS);

            for(int i = 0; i < size1; i++){
                deQueue(holder1, &temp, sizeof(int), &error);
                if((expires * 60 - temp) >= EXPIRY_DATE * 60){
                    loss += PRICE;
                    thrown_out++;
                }
                else{
                    temp -= expires;
                    enQueue(holder1, &temp, sizeof(int), &error);
                }
            }

            for(int i = 0; i < size2; i++){
                deQueue(holder2, &temp, sizeof(int), &error);
                if((expires * 60 - temp) >= EXPIRY_DATE * 60){
                    loss += PRICE;
                    thrown_out++;
                }
                else{
                    temp -= expires;
                    enQueue(holder2, &temp, sizeof(int), &error);
                }
            }
        }

        /*printf("Sandwitches bought: %d\n", customers);
        printf("Sandwitches made: %d\n", sandwitches_made);
        printf("Sandwitches left in 1 holder: %d \n", size1);
        printf("Sandwitches left in 2 holder: %d \n", size2);
        printf("Sandwitches thrown out: %d \n", thrown_out);*/
    }
    printf("Income: %d, loss: %d \n", income, loss);
}

int main(){

    sandwitches_Stack();
    sandwitches_Queue1();
    sandwitches_Queue2();

    return 0;
}