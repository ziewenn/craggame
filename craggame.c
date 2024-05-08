/*
  => Yağız Eren KOŞAR
  => METU NCC CNG
  => https://www.linkedin.com/in/yekosar/
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



// function for rolling dice
int roll_a_dice();
// function to calculate the score
int scoring(int dice1, int dice2, int dice3);
// function for user's turn
int play_user(int round);
// function for pc'turn
int play_computer(int round);
// function for displaying the scoresheet
void scoresheet(int round, int pctotals, int usertotals);



int main() {
    int users = 0, pcs = 0;
    int pctotals = 0 , usertotals = 0;
    int pcnum = 0;// gave them the same value to start the while loop
    int usernum = 0;// we can also roll the dice here and make them enter the while loop if they get the same value
    int playround;

    printf("Welcome to Crag game.\n");
    printf("Let's get started!\n");
    printf("\nHow many rounds would you like to play? ");
    scanf("%d", &playround);

    srand(time(NULL));

    // rolls a dice for who stars the first
    // if they have the same value rolls again
    while (usernum == pcnum) {
        pcnum = roll_a_dice();
        usernum = roll_a_dice();
    }

    printf("\nI have rolled the dice and got %d!\n",pcnum);
    printf("I have rolled the dice for you and you got %d!\n",usernum);

    // starts the game after comparing the value of the dices that user and pc rolled
    // makes the game run until the last rounds end and stores the scores to the score sheet
    for (int round = 1; round <= playround ; ++round) {
        if (usernum>pcnum){
            users = play_user(round);
            usertotals += users;
            printf("\nYour score: %d Total score: %d\n",users, usertotals);
            pcs = play_computer(round);
            pctotals += pcs;
            printf("\nMy score: %d Total score: %d\n",pcs, pctotals);
        } else{
            pcs = play_computer(round);
            pctotals += pcs;
            printf("\nMy score: %d Total score: %d\n",pcs, pctotals);
            users = play_user(round);
            usertotals += users;
            printf("\nYour score: %d Total score: %d\n",users, usertotals);
        }
        scoresheet(round, pctotals, usertotals);
    }

    // decides the games result
    if (pctotals > usertotals) {
        printf("\nI WIN!!\n");
    } else if (pctotals < usertotals) {
        printf("\nYOU ARE THE WINNER!!\n");
    } else {
        printf("\nIT'S A TIE!!\n");
    }
    return 0;
}



// function to calculate the score
int scoring(int dice1, int dice2, int dice3){
    int sum = dice1 + dice2 + dice3;
    if((sum == 13) && ((dice1==dice2) || (dice1==dice3) || (dice2==dice3))){
        printf("\nCrag!!\n");
        return 50;
    } else if (sum == 13){
        return 26;
    } else if (dice1==dice2 && dice1==dice3 && dice2==dice3){
        return 25;
    } else if (dice1 == 1 && dice2 == 2 && dice3 == 3){
        return 20;
    } else if (dice1 == 4 && dice2 == 5 && dice3 == 6){
        return 20;
    } else if (dice1 == 1 && dice2 == 3 && dice3 == 5){
        return 20;
    } else if (dice1 == 2 && dice2 == 4 && dice3 == 6){
        return 20;
    } else{
        return sum;
    }
}



// function for user's turn
int play_user(int round){
    // prints the which we are in
    printf("\nRound %d --- Your Turn:\n",round);
    printf("======================================\n");

    int dice1 = roll_a_dice(), dice2 = roll_a_dice(), dice3 = roll_a_dice();
    int users;
    char choice = 'metuncc';// we defined choice something other than y or n to enter the loop

    printf("You got => [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d\n",dice1,dice2,dice3);

    // asks the user whether to roll again or not (it accepts both upper and lowercase letters)
    while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
        printf("\nShall I roll for you (Y/N)?");
        scanf(" %c", &choice);

        if (choice == 'Y' || choice == 'y') {
            printf("Which ones do you want to keep?");
            int keep1, keep2;
            scanf("%d %d", &keep1, &keep2);


            while (keep1 < 1 || keep1 > 3 || keep2 < 1 || keep2 > 3 || keep1 == keep2) {
                printf("Sorry, wrong input!\n");
                printf("\nWhich ones do you want to keep? ");
                scanf("%d %d", &keep1, &keep2);
            }


            // rolls the dice that the user wants to roll by checking what is the input of the user
            if (keep1 == 1 && keep2 == 2 || keep1 == 2 && keep2 == 1) {
                dice3 = roll_a_dice();
            } else if (keep1 == 1 && keep2 == 3 || keep1 == 3 && keep2 == 1) {
                dice2 = roll_a_dice();
            } else {
                dice1 = roll_a_dice();
            }
            printf("\nYou got => [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d\n", dice1, dice2, dice3);

        } else if (choice == 'N' || choice == 'n'){

        } else {
            printf("Sorry, I don't understand!\n");
        }
    }


    // sends the dice values to scoring function to calculate the user's score
    users = scoring(dice1,dice2,dice3);
    return users;
}



int play_computer(int round){// function for pc'turn
    // prints the which we are in
    printf("\nRound %d --- My Turn:\n",round);
    printf("======================================\n");

    int dice1 = roll_a_dice(), dice2 = roll_a_dice(), dice3 = roll_a_dice();
    int pcs;

    printf("I rolled them and I got\n");
    printf("=> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d\n",dice1, dice2, dice3);

    // checks whether is it possible to get a high straight and if possible roll the necessary dice
    if (dice1 == 4 && dice2 == 5 && dice3 != 6){
        dice3 = roll_a_dice();
        printf("Rolled dice 3!\n");
        printf("=> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d\n",dice1, dice2, dice3);
    } else if (dice2 == 5 && dice3 == 6 && dice1 != 4){
        dice1 = roll_a_dice();
        printf("Rolled dice 1!\n");
        printf("=> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d\n",dice1, dice2, dice3);
    } else if (dice1 == 4 && dice3 == 6 && dice2 != 5){
        dice2 = roll_a_dice();
        printf("Rolled dice 2!\n");
        printf("=> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d\n",dice1, dice2, dice3);
    }

    // sends the dice values to scoring function to calculate the pc's score
    pcs = scoring(dice1,dice2,dice3);
    return pcs;
}



// function for rolling dice
int roll_a_dice(){
    return (rand() % 6) + 1;
}



void scoresheet(int round, int pctotals, int usertotals){// function for displaying the scoresheet
    printf("\nOur scoresheet after round %d:",round);
    printf("\n======================================\n");
    printf("My score\tYour score\n");
    printf("%d\t\t%d\n",pctotals,usertotals);
}
