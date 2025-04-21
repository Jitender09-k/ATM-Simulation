#include <stdio.h>
#include <string.h>

float balance = 10000.0;    // asumed already 10000 rup in account
char miniStatement[3][50];
int statementIndex = 0;
int withdrawCount = 0;

int langMode = 1;  // choose language 1 = English, 2 = Hindi
int storedPIN = -1;

// --- Function ---
void showMenu();
void processChoice(int choice);
void selectLanguage();
void showWelcomeMessage();
int registerPIN();
int authenticateUser(int pin);

void addTransaction(const char *msg) {
    if (statementIndex < 3) {
        strcpy(miniStatement[statementIndex], msg);
        statementIndex++;
    } else {
        for (int i = 0; i < 2; i++) {
            strcpy(miniStatement[i], miniStatement[i + 1]);
        }
        strcpy(miniStatement[2], msg);
    }
}

void checkBalance() {
    if (langMode == 1)
        printf("Your current balance is: ₹%.2f\n", balance);
    else
        printf("Aapka balance hai: ₹%.2f\n", balance);
}

void withdrawMoney() {
    if (withdrawCount >= 3) {
        if (langMode == 1)
            printf("Withdrawal limit reached for this session \n");
        else
            printf("Iss session ke liye withdrawal limit poori ho gayi \n");
        return;
    }

    float amount;
    if (langMode == 1)
        printf("Enter amount to withdraw: ₹");
    else
        printf("Kitni rakam nikalni hai: ₹");
    scanf("%f", &amount);

    if (amount <= 0 || amount > balance) {
        if (langMode == 1)
            printf("Invalid amount or insufficient balance \n");
        else
            printf("Galat rakam ya balance kam hai \n");
    } else {
        balance -= amount;
        withdrawCount++;

        if (langMode == 1)
            printf("Withdrawal successful. Remaining balance: ₹%.2f \n", balance);
        else
            printf("Rakam nikal li gayi. Bacha hua balance: ₹%.2f \n", balance);

        char msg[50];
        sprintf(msg, "Withdraw: -₹%.2f", amount);
        addTransaction(msg);
    }
}

void depositMoney() {
    float amount;
    if (langMode == 1)
        printf("Enter amount to deposit: ₹");
    else
        printf("Kitni rakam jama karni hai: ₹");
    scanf("%f", &amount);

    if (amount <= 0) {
        if (langMode == 1)
            printf("Invalid amount \n");
        else
            printf("Galat rakam \n");
    } else {
        balance += amount;

        if (langMode == 1)
            printf("Deposit successful. New balance: ₹%.2f \n", balance);
        else
            printf("Jama safaltapoorvak. Naya balance: ₹%.2f \n", balance);

        char msg[50];
        sprintf(msg, "Deposit: +₹%.2f", amount);
        addTransaction(msg);
    }
}

void showMiniStatement() {
    if (langMode == 1)
        printf("Last 3 Transactions:\n");
    else
        printf("Aakhri 3 len-den:\n");

    for (int i = 0; i < statementIndex; i++) {
        printf("%s\n", miniStatement[i]);
    }

    if (statementIndex == 0) {
        if (langMode == 1)
            printf("No transactions yet.\n");
        else
            printf("Abhi tak koi len-den nahi hua.\n");
    }
}

void showMenu() {
    int choice;
    do {
        if (langMode == 1) {
            printf("\n----- MAIN MENU -----\n");
            printf("1. Check Balance\n");
            printf("2. Withdraw Money\n");
            printf("3. Deposit Money\n");
            printf("4. Mini Statement\n");
            printf("5. Exit\n");
        } else {
            printf("\n----- MUKHYA MENU -----\n");
            printf("1. Balance Dekhein\n");
            printf("2. Paise Nikalein\n");
            printf("3. Jama Karein\n");
            printf("4. Mini Statement\n");
            printf("5. Bahar Niklein\n");
        }

        printf("Enter your choice: ");
        scanf("%d", &choice);

        processChoice(choice);
    } while (choice != 5);
}

void processChoice(int choice) {
    switch (choice) {
        case 1:
            checkBalance();
            break;
        case 2:
            withdrawMoney();
            break;
        case 3:
            depositMoney();
            break;
        case 4:
            showMiniStatement();
            break;
        case 5:
            if (langMode == 1)
                printf("Thank you for using ATM. Goodbye! \n");
            else
                printf("ATM ka istemal karne ke liye dhanyavaad. Alvida! \n");
            break;
        default:
            if (langMode == 1)
                printf("Invalid choice. Try again \n");
            else
                printf("Galat vikalp. Dobara koshish karein \n");
    }
}

void selectLanguage() {
    printf("Select Language / Bhasha Chunein:\n1. English\n2. Hindi\nEnter choice: ");
    scanf("%d", &langMode);
}

void showWelcomeMessage() {
    if (langMode == 1)
        printf("\nWelcome to Smart ATM System....! \n");
    else
        printf("\nSmart ATM System mein aapka swagat hai....! \n");
}

int registerPIN() {
    int pin1, pin2;
    printf("Create a 4-digit PIN: ");
    scanf("%d", &pin1);
    printf("Confirm your PIN: ");
    scanf("%d", &pin2);

    if (pin1 == pin2) {
        if (langMode == 1)
            printf("PIN successfully registered \n\n");
        else
            printf("PIN safaltapoorvak ban gaya \n\n");
        return pin1;
    } else {
        if (langMode == 1)
            printf("PINs do not match. Try again \n\n");
        else
            printf("PIN match nahi kar rahe. Dobara prayas karein \n\n");
        return -1;
    }
}

int authenticateUser(int pin) {
    int inputPIN;
    printf("Enter your 4-digit PIN: ");
    scanf("%d", &inputPIN);

    if (inputPIN == pin) {
        if (langMode == 1)
            printf("Login successful \n");
        else
            printf("Login safal \n");
        return 1;
    } else {
        if (langMode == 1)
            printf("Incorrect PIN \n");
        else
            printf("Galat PIN \n");
        return 0;
    }
}

int main() {
    selectLanguage();
    showWelcomeMessage();

    int option;
    printf("\n1. Register (New User)\n2. Already Registered (Login)\nChoose option: ");
    scanf("%d", &option);

    if (option == 1) {
        storedPIN = registerPIN();
        if (storedPIN == -1) return 0;
    }

    if (storedPIN == -1) {
        if (langMode == 1)
            printf("Please register first to use the ATM.\n");
        else
            printf("ATM use karne ke liye pehle register karein.\n");
        return 0;
    }

    if (authenticateUser(storedPIN)) {
        showMenu();
    }

    return 0;
}
