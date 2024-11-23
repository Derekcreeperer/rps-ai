#include <iostream>
#include <cmath>
#include <time.h>
#include <vector>
#include <deque>
// rock : 1; scissors : 2; paper : 3

std::vector<int> do_game(int pcChoice){
    std::cout << "rock : 1; scissors : 2; paper : 3 break:4 choice:";
    int choice {};
    std::cin >> choice;
    int a {((choice - pcChoice) % 3 + 3) % 3};
    int winFlag {};
    if (1 <= choice and choice <= 3){
        if (a == 2){
            std::cout << "You win!  ";
            winFlag = 0;
        }
        else if (a == 1){
            std::cout << "You lose!";
            winFlag = 1;
        }
        else{
            std::cout << "Tie!";
            winFlag = 2;
        }
    }
    std::cout << "\n";
    std::vector<int> returnVector {choice, winFlag};
    return returnVector;
}

std::vector<int> get_max(std::deque<int> vec){
    int max {0};
    int maxId {0};
    for (int i {0}; i < vec.size(); i += 1){
        if (vec[i] > max){
            max = vec[i];
            maxId = i;
        }
    }
    std::vector<int> returnVector {max, maxId};
    return returnVector;
}

std::deque<std::deque<int>> gen_opt(std::deque<std::deque<std::deque<int>>> pDeque){
    std::deque<std::deque<int>> optDeque {};
    for (int a {0}; a <= 3; a += 1){
        optDeque.push_back({0, 0, 0});
    }
    
    for (int winFlag {0}; winFlag < 3; winFlag += 1){
        for (int prChoice {0}; prChoice <= 3; prChoice += 1){
            int pChoice = get_max(pDeque[winFlag][prChoice])[1] += 1;
            if (pChoice == 1){
                optDeque[winFlag][prChoice] = 3;
            }
            else if (pChoice == 2){
                optDeque[winFlag][prChoice] = 1;
            }
            else{
                optDeque[winFlag][prChoice] = 2;
            }

        }
    }
    return optDeque;
}

int main(){
    std::deque<std::deque<std::deque<int>>> pDeque {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}};
    std::cout << "warm up \n";
    int prChoice {1};
    std::vector<int> choiceVector {};
    int pcChoice {};
    int choice {};
    int winFlag {};
    /*
    for (int i = 0; i <= 50; i += 1){
        srand((int)time(0));
        pcChoice = rand() % 3 + 1;
        choiceVector = do_game(pcChoice);
        choice = choiceVector[0];
        winFlag = choiceVector[1];
        pDeque[winFlag][prChoice - 1][choice - 1] += 1;
        prChoice = choice;
        if (choice >= 4){
            break;
        }
    }
    */
    std::deque<std::deque<int>> optDeque = gen_opt(pDeque);
    std::cout << "real round start \n";
    int aiChoice {1};
    int preChoice {1};
    int prewinFlag {0};
    int conwinCnt {0};
    bool conwinFlag {false};
    choiceVector = do_game(aiChoice);
    preChoice = choiceVector[0];
    prewinFlag = choiceVector[1];
    while (true){
        aiChoice = optDeque[prewinFlag][preChoice - 1];
        choiceVector = do_game(aiChoice);
        choice = choiceVector[0];
        winFlag = choiceVector[1];
        pDeque[prewinFlag][preChoice - 1][choice - 1] += 1;
        if (winFlag == 0){
            conwinFlag = true;
        }
        else{
            conwinFlag = false;
            conwinCnt = 0;
        }
        if (conwinFlag){
            conwinCnt += 1;
        }
        if (conwinCnt >= 5){
            conwinCnt = 0;
            conwinFlag = false;
            pDeque = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}};
            std::cout << "trick" << "\n";
        }
        optDeque = gen_opt(pDeque);
        preChoice = choice;
        prewinFlag = winFlag;
    }
    return 0;
    
}