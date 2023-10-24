//
//  main.c
//  third
//
//  Created by Charlie on 2023/10/18.
//

#include <stdio.h>

// Output the 32-bit binary representation of decimal number n.
void printBinary(int n) {
    int i; // loop vairable
  
    for (i=1; i<=32; i++) { // Output all 32 bits.
        printf("%d", (n>>(32-i))&1); // Output a bit of n from left to right.
        if (i%4==0) printf(" "); // Print a space every four bits.
  }
}

void fullAdder (int x, int y, int *c, int *s) {
    *s = (x ^ y) ^ *c; // s = (x xor y) xor c_in.
    *c = (x & y) | (*c & (x ^ y)); // c_out = (x and y) or (c_in and (x xor y))
}

int adder(int X, int Y, int *c, int M) {
    int S = 0; // At the end S=X+Y and its value is returned.
    int pos; // Position, from right to left. of the current bit to apply full adder.
    int x, y, s; // A single bit of X, Y, and S, respectively.
    int cin = *c, cout = M;
      
    for (pos=0; pos<32; pos++) { // 32-bit adder.
        x = X & 1; // Set x to the current bit of X, i.e., the least significant bit of X.
        y = (Y & 1) ^ M; // Set y to the current bit of Y, i.e., the least significant bit of Y.
        
        // Perform fullAdder to add x, y , and the carry in c and
        // to yield the sum bit s and the carry out c.
        // Note that c is a pointer to an integer.
        cin = cout;
        fullAdder(x, y, &cout, &s);
        
        // The shift operation is to move the next processed bit of X and Y to the least significant bit.
        X = X >> 1; // Update X to shift its bits one position to the right-hand-side.
        Y = Y >> 1; // Update Y to shift its bits one position to the right-hand-side.
        // Place the sum bit s in sum to the appropriate position of S specified by pos.
        S = S | (s << pos);
        }
        *c = cin ^ cout;
        // Return the result sum.
    return S;
}

int main(void) {
    int X, Y, S;// To compute S=X+Y.
    int M; // substrator = 1 or adder = 0
    int c; // Carry bit.
    char op; // Operator
    
    while (1){ // Continue to process the adder until both input are 0's.
        // Input two 32-bit integer
        printf("Enter \"X + Y\" or \"X - Y\" (X, Y: -2,147,483,648 to 2,147,483,647): ");
        scanf("%d %c %d", &X, &op, &Y);
        if (X==0 && Y==0) break; // If both X and Y are 0, stop the loop and terminate the program.
        // Perform binary adder to add the two positive integers X and Y with carry_in c.
        // Store the final result in variable S.
        
        
        printf("X = %-10d  Binary value: ", X); // Output decimal value of X with left alignment.
        printBinary(X); // Output binary value of X.
        printf("\n"); // Output a new line.
        printf("Y = %-10d  Binary value: ", Y); // Output decimal value of Y with left alignment.
        printBinary(Y); // Output binary value of Y.
        printf("\n"); // Output a new line.
        
        // Decide it is a substrator or adder
        if (op == '-'){
            M = 1;
        }
        else{
            M = 0;
        }
        
        c = 0; // Initial carry in to 0.
        S = adder(X, Y, &c, M); // Call function adder().
        printf("S = %-10d  Binary value: ", S); // Output decimal value of the sum S with left alignment.
        printBinary(S); // Output binary value of S.
        printf("\n"); // Output a new line.
        
        // Print the confirming message. The else case should not be executed.
        if (op == '-'){
            if (X-Y==S) printf("Correct! Adder operation test: %d - %d = %d\n", X, Y, S);
            else printf("Incorrect! Adder operation test: %d - %d != %d\n", X, Y, S);
        }
        else{
            if (X+Y==S) printf("Correct! Adder operation test: %d + %d = %d\n", X, Y, S);
            else printf("Incorrect! Adder operation test: %d + %d != %d\n", X, Y, S);
        }
        
        // Print the overflow message.
        if (c!=0) printf("**** The addition operation is overflow.\n");
        printf("-----------------------------------------------------\n");
    }
    return 0;
}
