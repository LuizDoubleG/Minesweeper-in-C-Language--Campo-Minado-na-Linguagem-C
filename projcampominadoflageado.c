#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int negative = -1; // Flag to function that recursively finds nearby 0's (flagerRecursive)

void cleanMatriz(int size, int matriz[size][size]){
    int i, j;
    for(i=0; i<size+2; i++){
        for(j=0; j<size+2; j++){
            matriz[i][j] = 99;
        }
    }
    for(i=2; i<size; i++){
        for(j=2; j<size; j++){
            matriz[i][j] = 0;
        }
    }
}

void fillBombs(int difficulty, int size, int matriz[size][size]){ // Fill the matrix with bombs
    int i = 0 , j = 0, c;
    for(c=0 ; c <= difficulty ; c++){
        i = rand()%(size-2); // Generate random numbers based on the size of the matrix
        j = rand()%(size-2);
        i += 2;
        j += 2;
        matriz[i][j] =  9;
    }
 
}

void proximityFlager(int size, int matriz[size][size]){
    int i, j;
    for(i=2; i < size; i++){
        for(j=2; j < size; j++){
            if (matriz[i][j] != 9){
                if (matriz[i-1][j-1]==9){ 
                    matriz[i][j] += 1;
                }
                if(matriz [i-1][j]==9){
                    matriz[i][j] += 1;
                }
                if (matriz [i-1][j+1]==9) {
                    matriz[i][j] += 1;
                }
                if (matriz [i][j-1]==9) {
                    matriz[i][j] += 1;
                }
                if (matriz [i][j+1]==9) {
                    matriz[i][j] += 1;
                }
                if (matriz [i+1][j-1]==9) {
                    matriz[i][j] += 1;
                }
                if (matriz [i+1][j]==9) {
                    matriz[i][j] += 1;
                }
                if (matriz [i+1][j+1]==9) {
                    matriz[i][j] += 1;
                }
            }
        }
    }
}

void printMatrixNumbers(int size, int matriz[size][size]){ // Debbug matrix print function to know values of matrix
    int i, j;
    for(i=1; i < size; i++){
        for(j=1; j < size; j++){
            if (i == 1 || j ==1){ //Eixo cartesiano
                if (i>j){
                    printf("%2d", i-2);
                }
                else if (j>i){
                    printf("%3d", j-2);
                }
                else if (j==i){
                    printf(" ");
                }
                continue;
            }
            if (matriz[i][j] >= 0){ 
                printf("[%d]", matriz[i][j]);
            }
            else{
                printf("[%d]", matriz[i][j]);
            }
        }
    printf("\n");
    }
}

void printMatrixNumbers2(int size, int matriz[size][size]){ // End matrix -> loose or win
    int i, j;
    for(i=1; i < size; i++){
        for(j=1; j < size; j++){
            if (i == 1 || j ==1){ //Eixo cartesiano
                if (i>j){
                    printf("%2d", i-2);
                }
                else if (j>i){
                    printf("%3d", j-2);
                }
                else if (j==i){
                    printf(" ");
                }
                continue;
            }
            if (matriz[i][j] == 9){
                printf("[X]");
            }
            else
            if (matriz[i][j] >= 0){ 
                printf("[%d]", matriz[i][j]);
            }
            else
            {
            printf("[ ]", matriz[i][j]);
            }
            
        }
    printf("\n");
    }
}

void printGameMatrix(int size, int i, int j, int matriz[size][size], int matriz2[size][size]){
    int e,c;
    printf("\n");
    for(e=1; e < size; e++){
        for(c=1; c < size; c++){
            if (e == 1 || c ==1){ // Eixo cartesiano
                if (e>c){
                    printf("%2d", e-2);
                }
                else if (c>e){
                    printf("%3d", c-2);
                }
                else if (c==e){
                    printf(" ");
                }
                continue;
            }
            //
            if(matriz2[e][c] == 139){ // Flags
                printf("[f]");
                continue;
            }

            if (matriz[e][c] < 0){ // Empty spaces found by 0 proximity
                printf("[ ]");
                //flag++;
                continue;
            }
            
            if (matriz[e][c] != 0 && (matriz[e][c] == matriz2[e][c])){ // Already entered
            //if (matriz[e][c] == matriz2[e][c]){ // Already entered
                printf("[%d]", matriz[e][c]);
                continue;
            }

            if (matriz[e+1][c]<0 || matriz[e][c-1]<0 || matriz[e][c+1]<0 || matriz[e-1][c]<0){ // Filled spaces near of empty and 0 spaces found
                printf("[%d]", matriz[e][c]); 
                matriz2[e][c] = matriz[e][c];
            }
                else{
                    printf("[?]"); // Spaces not entered yet
                }
        }
        printf("\n"); // New line
    }
    printf("\n");   // End of game matrix
}

int flager (int size,int i, int j, int matriz[size][size], int negative){// doesn't need size
    int e, c, flag = 0;
    for (e = -1; e <= 1; e++){
        for (c = -1; c <= 1; c++){
            if(matriz[i-c][j-e] == 0){
                matriz[i-c][j-e] = negative;
                flag = flag + 1;
            } 
        }
    }
    //negative--;
    return flag;
}

void flagerRecursive (int size, int i, int j, int matriz[size][size]){
    int e, c, o, k;
    int flag = 0;
    int funcNegative;

    flag = flager(size, i, j, matriz, negative);
    //negative--;

    if (flag != 0){
        negative--;
        funcNegative = negative;
        for (e = -1; e <= 1; e++){
            for (c = -1; c <= 1; c++){
                if(matriz[i-c][j-e] == funcNegative+1){
                    o = i - c;
                    k = j - e;
                    //flag = flager (o, k, matriz, flag);
                    
                        //printf("%d\n", flag);
                        flagerRecursive (size, o, k, matriz);
                    
                } 
            }
        }
    }
    //free(flag);
}

int checkVitory(int size, int matriz[size][size], int matriz2[size][size]){
    int i, j, flag=0;
    for (i = 2; i < size; i++){
        for (j = 2; j < size; j++){ 
            if (matriz[i][j] > 0 && matriz[i][j] != 9){
                if (matriz[i][j] != matriz2[i][j]){
                    flag++;
		            return 0;
                }
            }
        }
    }
    return 1;
}

void iniciateMatrix(int difficulty, int size, int matriz[size][size], int matriz2[size][size]){
    cleanMatriz(size, matriz); // Initialize matrix
    cleanMatriz(size, matriz2); // Initialize auxiliar matrix
    fillBombs(difficulty, size, matriz); // Fill with bombs
    proximityFlager(size, matriz);// Flag to indicate number of bombs nearby
}

void gameInstructions(){
    printf("\nPowered by: LMdoubleG\n");

    printf("\nA qualquer momento voce pode sair do jogo digitando -1 em qualquer coordenada\n");
        
    printf("\nA qualquer momento voce pode reiniciar o jogo digitando as coordenadas -10 -10\n");

    printf("\nVoce pode colocar uma bandeira sobre uma coordenada digitando as coordenadas seguidas do caractere 'f'\n");

    printf("\nVoce pode checar se ja ganhou digitando uma coordenada vazia ou ja selecionada, que nao esteja com uma bandeira\n\n");

}

int restartGame(int size, int difficulty, int i, int j, int matriz[size][size], int matriz2[size][size]){
    int flag;
    printf("Reiniciando o jogo...\n");
    system("pause"); 
    //srand((unsigned)time(NULL));
    iniciateMatrix(difficulty, size, matriz, matriz2);
    system("cls");
    do{
        flag = gameSafeStart(size, difficulty, matriz, matriz2);
        if (flag == 1){
            return 1;
        }
    }while(flag != 0);
return 0;
}

void safeStart(int size, int difficulty, int i, int j, int matriz[size][size]){ // Doesn't need to add +2 to size
    do{
    cleanMatriz(size, matriz);
    srand((unsigned)time(NULL));
    fillBombs(difficulty, size, matriz);
    proximityFlager(size, matriz);
    }while(matriz[i][j]!=0);
}

int gameSafeStart(int size, int difficulty, int matriz[size][size], int matriz2[size][size]){
    int i = 0, j = 0;
    //printMatrixNumbers(size, matriz); -> Debug purposes
    printf("\n");
    printGameMatrix(size, i, j, matriz, matriz2);
    gameInstructions();

    printf("\nEscolha as coordenadas: ");
    scanf("%d %d", &i, &j);

    if (i == -1 || j == -1){ // Exit game
        printf("Finalizando o jogo...\n");
        return 1;
    }

    if (i == -10 && j == -10){ // Restart game
        printf("Reiniciando o jogo...\n");
        system("pause"); 
        srand((unsigned)time(NULL));
        iniciateMatrix(difficulty, size, matriz, matriz2);
        system("cls");
        return 2; // Loop this function in main again
    }

    i +=2; // To start in the real beginning of the matrix
    j +=2; // To start in the real beginning of the matrix

    if (matriz[i][j]!=0 && size > 7){ // If size < 4 x 4 do not safeStart because it takes too much time
        safeStart(size, difficulty, i, j, matriz);
    }

    if (matriz[i][j]==0){
    flagerRecursive (size, i, j, matriz);
    }
    else{ // Normal and selectable coordinate
        if (matriz[i][j] == 9){ // Bomb
            system("cls");
            printf("Coordenadas selecionadas: %d %d\n", i-2, j-2);
            printMatrixNumbers2(size, matriz);
            printf ("\nVoce se explodiu todinho!!! Mais sorte na sua outra vida...\n\n");
            printf("Reiniciando o jogo...\n");
            system("pause"); 
            srand((unsigned)time(NULL));
            iniciateMatrix(difficulty, size, matriz, matriz2);
            system("cls");
            return 2; // Loop this function in main again
        }
        else{ // Number
            matriz2[i][j] = matriz[i][j];
        }
    }

    system("cls");
    // printGameMatrix(size, i, j, matriz, matriz2);
    // gameInstructions();
    // system("pause");
    //printf("\n"); 
return 0;   
}

int normalGame(int size, int difficulty, int matriz[size][size], int matriz2[size][size]){
    int i = 0,j = 0;
    char flag, victory, exit;
    system("cls");
     /* Debug option:
    printMatrixNumbers(size, matriz);
    printf("\n");
     */
    printGameMatrix(size, i, j, matriz, matriz2);
    printf("\nEscolha as coordenadas: ");
    scanf("%d %d", &i, &j);
    printf("\nDeseja colocar ou retirar uma bandeira?\nf = colocar \nx = retirar \nc = cancelar input\nQualquer outro caractere = enviar coordenada normalmente \n\n");
    scanf(" %c", &flag);// This previous space is to avoid the program to ignore this scanf becouse of some random empty space from another scanf
    

    if (flag == 'c'){ // Cancel input
        return 0;
    }
    if (i == -1 || j == -1){ // Exit game
        printf("Finalizando o jogo...\n");
        system("pause");
        return 1;
    }

    if (i == -10 && j == -10){ // Restart game
        srand((unsigned)time(NULL));
        exit = restartGame(size, difficulty, i, j, matriz, matriz2);
        if (exit == 1){
            return 1;
        }
        else{
        return 0;
        }
    }

    i +=2; // To start in the real beginning of the matrix
    j +=2; // To start in the real beginning of the matrix

    if (flag == 'f'){ // Flag input
        matriz2[i][j] = 139;
        return 0;
    }
    if (flag == 'x'){ // Remove flag 
        matriz2[i][j] = 140;
        return 0;
    }
    if (matriz[i][j]==9 && matriz2[i][j]!=139){ // If bomb and not flagged -> game over
        system("cls");
        printf("Coordenadas selecionadas: %d %d\n", i-2, j-2);
        printMatrixNumbers2(size, matriz);
        printf ("\nVoce se explodiu todinho!!! Mais sorte na sua outra vida...\n\n");
        system("pause");
        srand((unsigned)time(NULL));
        exit = restartGame(size, difficulty, i, j, matriz, matriz2);
        if (exit == 1){
            return 1;
        }
        else{
        return 0;
        }
    }
        
    if (matriz[i][j]==0){
        flagerRecursive (size, i, j, matriz);
        return 0;
    }
            
    if (matriz[i][j]<0 || (matriz2[i][j]==matriz[i][j])){ // Already selected coordinate -> check if the user already winned 
        victory = checkVitory(size, matriz, matriz2);
        if (victory == 1){
            system("cls");
            printMatrixNumbers2(size, matriz);
            printf ("\nVoce venceu!!!Parabens!!!\nNao tem mais nenhuma coordenada pra escolher, voce escapou das bombas... (por hora)\n\n");
            system("pause");
            srand((unsigned)time(NULL));
            exit = restartGame(size, difficulty, i, j, matriz, matriz2);
            if (exit == 1){
                return 1;
            }
            else{
                return 0;
            }
        }
        printf("\nCoordenada ja selecionada\n");
        system("pause");
        return 0;
    }
    if (matriz[i][j]>0 && matriz[i][j]!=9){ // Normal and selectable coordinate
        matriz2[i][j] = matriz[i][j];
        return 0;
    }
return 0;
}

int main(void)
{
    int size, difficulty, flag;
    

    printf("Digite o tamanho da matriz: ");
    scanf("%d", &size);
    size += 2; // To add border inicialization of the matrix
    printf("Digite a dificuldade:\nEasy = 1\nMedium = 2\nHard = 3\nMaluquisse >= 4\n");
    scanf("%d", &difficulty); // Quantity of bombs
    difficulty *= 10;

    int matriz[size+2][size+2];   // Main matrix with bombs and numbers -> +2 to add border that prevents error of values comparison
    int matriz2[size+2][size+2];  // Matrix to store the coordinates that the user already selected and flags ->+2 to add border that prevents error of values comparison
    
    //srand((unsigned)time(NULL)); // Timer used to create random bombs
    iniciateMatrix(difficulty, size, matriz, matriz2); // Initialize matrix

    // Error free initializing 
     do{
        flag = gameSafeStart(size, difficulty, matriz, matriz2);
        if (flag == 1){
            return 0;
        }
    }while(flag != 0); // If flag == 2 -> restart gameSafeStart
    // End of error free initializing

    do {
    flag = normalGame(size, difficulty, matriz, matriz2);
    }while(flag == 0);

return 0;
}